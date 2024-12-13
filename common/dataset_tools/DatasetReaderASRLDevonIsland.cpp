///////////////////////////////////////////////////////////////////////////////
/// \file DatasetReaderASRLDevonIsland.cpp
///////////////////////////////////////////////////////////////////////////////

/*
This file is part of the Robotics Toolbox.

Copyright (C) 2024

Authors: Bernd Kitt (b.kitt@berndkitt.de)

The Robotics Toolbox is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 3 of the License,
or any later version.

The Robotics Toolbox is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
Public License for more details.

You should have received a copy of the GNU General Public License along with
the Robotics Toolbox. If not, see https://www.gnu.org/licenses/.
*/

#include <regex>

#include "../CSVReader.h"
#include "../FileInterface.h"
#include "DatasetReaderASRLDevonIsland.h"

DatasetReaderASRLDevonIsland::DatasetReaderASRLDevonIsland(const std::string&  BaseDirectory,
                                                           const std::string&  SequenceName,
                                                           const ASRLImageType ImageType) :
    DatasetReaderBase(BaseDirectory, SequenceName),
    m_ImageType{ImageType}
{
    // set information which is specific for the dataset
    const std::filesystem::path RelativePathTimestamps("logs");
    const std::filesystem::path FilenameTimestampsImagesStereo("image-times.txt");
    const std::filesystem::path AbsolutePathTimestampsImagesStereoLeft(m_BaseDirectory / RelativePathTimestamps / FilenameTimestampsImagesStereo);
    const std::filesystem::path AbsolutePathTimestampsImagesStereoRight(m_BaseDirectory / RelativePathTimestamps / FilenameTimestampsImagesStereo);

    std::filesystem::path DirectoryIdentifier;
    std::filesystem::path SequenceDirectory;
    std::filesystem::path FileBasenameImagesStereoLeft;
    std::filesystem::path FileBasenameImagesStereoRight;
    std::filesystem::path FileExtensionImagesStereo;

    if(m_ImageType == ASRLImageType::ASRLColor)
    {
        DirectoryIdentifier           = "color-rectified-1280x960";
        SequenceDirectory             = "color-rectified-1280x960-" + SequenceName;
        FileBasenameImagesStereoLeft  = "color-rectified-left-";
        FileBasenameImagesStereoRight = "color-rectified-right-";
        FileExtensionImagesStereo     = ".ppm";
    }
    else
    {
        DirectoryIdentifier           = "grey-rectified-512x384";
        SequenceDirectory             = "color-rectified-512x384-" + SequenceName;
        FileBasenameImagesStereoLeft  = "grey-rectified-left-";
        FileBasenameImagesStereoRight = "grey-rectified-right-";
        FileExtensionImagesStereo     = ".ppm";
    }

    // create absolute paths to stereo camera information
    const std::filesystem::path AbsolutePathImagesStereoLeft{m_BaseDirectory / DirectoryIdentifier / SequenceDirectory};
    const std::filesystem::path AbsolutePathImagesStereoRight{m_BaseDirectory / DirectoryIdentifier / SequenceDirectory};

    // extract filenames of the stereo camera images
    FileInterface FileInterfaceImagesStereoLeft(AbsolutePathImagesStereoLeft, FileBasenameImagesStereoLeft, FileExtensionImagesStereo);
    FileInterface FileInterfaceImagesStereoRight(AbsolutePathImagesStereoRight, FileBasenameImagesStereoRight, FileExtensionImagesStereo);

    m_NumberOfImagesStereoLeft  = FileInterfaceImagesStereoLeft.GetNumberOfFiles();
    m_NumberOfImagesStereoRight = FileInterfaceImagesStereoRight.GetNumberOfFiles();

    m_FilenamesWithPathImagesStereoLeft  = FileInterfaceImagesStereoLeft.GetListOfFilenamesWithPath();
    m_FilenamesWithPathImagesStereoRight = FileInterfaceImagesStereoRight.GetListOfFilenamesWithPath();

    // extract timestamps of the stereo camera images
    m_NumberOfTimestampsStereoLeft  = ExtractTimestamps(AbsolutePathTimestampsImagesStereoLeft, m_TimestampsImagesStereoLeftNanoseconds);
    m_NumberOfTimestampsStereoRight = ExtractTimestamps(AbsolutePathTimestampsImagesStereoRight, m_TimestampsImagesStereoRightNanoseconds);

    // extract image dimensions
    DatasetReaderBase::ExtractImagesDimensions(m_FilenamesWithPathImagesStereoLeft[0], m_HeightImagesStereo, m_WidthImagesStereo);

    // set projection matrices of the stereo cameras
    SetProjectionMatrices(m_ProjectionMatrixStereoLeft, m_ProjectionMatrixStereoRight);
}

DatasetReaderASRLDevonIsland::~DatasetReaderASRLDevonIsland()
{
}

uint64 DatasetReaderASRLDevonIsland::ConvertTimestampIntoNanoSeconds(const std::vector<std::string>& TimestampParts)
{
    // ignore the date as all images of the dataset have been captured at the same day
    const sint32 Hours{std::stoi(TimestampParts[3])};
    const sint32 Minutes{std::stoi(TimestampParts[4])};
    const sint32 Seconds{std::stoi(TimestampParts[5])};
    const sint32 Milliseconds{std::stoi(TimestampParts[6])};

    const std::chrono::hours        HoursChrono{std::chrono::hours(Hours)};
    const std::chrono::minutes      MinutesChrono{std::chrono::minutes(Minutes)};
    const std::chrono::seconds      SecondsChrono{std::chrono::seconds(Seconds)};
    const std::chrono::milliseconds MillisecondsChrono{std::chrono::milliseconds(Milliseconds)};

    const std::chrono::nanoseconds HoursInNanoseconds{std::chrono::duration_cast<std::chrono::nanoseconds>(HoursChrono)};
    const std::chrono::nanoseconds MinutesInNanoseconds{std::chrono::duration_cast<std::chrono::nanoseconds>(MinutesChrono)};
    const std::chrono::nanoseconds SecondsInNanoseconds{std::chrono::duration_cast<std::chrono::nanoseconds>(SecondsChrono)};
    const std::chrono::nanoseconds MillisecondsInNanoseconds{std::chrono::duration_cast<std::chrono::nanoseconds>(MillisecondsChrono)};

    const std::chrono::nanoseconds TimestampNanosecondsChrono{HoursInNanoseconds + MinutesInNanoseconds + SecondsInNanoseconds + MillisecondsInNanoseconds};

    const sint64 TimestampNanoseconds{TimestampNanosecondsChrono.count()};

    return TimestampNanoseconds;
}

uint64 DatasetReaderASRLDevonIsland::ExtractTimestamps(const std::filesystem::path& FileTimestampsWithPath,
                                                       ListUInt64&                  ListTimestamps)
{
    // initialize number of timestamps found
    uint64 NumberOfTimestampsFound{0U};

    // read file
    CSVReader Reader(FileTimestampsWithPath, " ");

    // extract all timestamps
    ListUInt64 ListTimestampsAll;

    std::regex regular_expression_timestamp("[-:T.]{1}");

    for(uint64 i_FrameCounter{0}; i_FrameCounter < Reader.GetNumberOfRows(); i_FrameCounter++)
    {
        std::string Timestamp{Reader.GetValue(i_FrameCounter, 1U)};

        std::sregex_token_iterator iter(Timestamp.begin(), Timestamp.end(), regular_expression_timestamp, -1);
        std::sregex_token_iterator end;

        std::vector<std::string> TimestampParts;

        for(; iter != end; ++iter)
        {
            TimestampParts.push_back(*iter);
        }

        const uint64 TimestampNanoseconds{ConvertTimestampIntoNanoSeconds(TimestampParts)};

        ListTimestampsAll.push_back(TimestampNanoseconds);
    }

    // filter timestamps to get the relevant timestamps only
    NumberOfTimestampsFound = FilterTimestamps(ListTimestampsAll, ListTimestamps);

    return NumberOfTimestampsFound;
}

uint64 DatasetReaderASRLDevonIsland::FilterTimestamps(const ListUInt64& ListTimestampsAll,
                                                      ListUInt64&       ListTimestamps) const
{
    uint64 NumberOfTimestampsFound{0U};

    const std::string FilenameFirst{m_FilenamesWithPathImagesStereoLeft[0]};
    const std::string FilenameLast{m_FilenamesWithPathImagesStereoLeft[m_NumberOfImagesStereoLeft - 1]};

    const uint64 FilenameFirstIndexStartFramenumber{FilenameFirst.find_last_of('-')};
    const uint64 FilenameFirstIndexEndFramenumber{FilenameFirst.find_last_of('.')};
    const uint64 FilenameLastIndexStartFramenumber{FilenameLast.find_last_of('-')};
    const uint64 FilenameLastIndexEndFramenumber{FilenameLast.find_last_of('.')};

    const uint64 FilenameFirstFramenumberLength{FilenameFirstIndexEndFramenumber - FilenameFirstIndexStartFramenumber - 1U};
    const uint64 FilenameLastFramenumberLength{FilenameLastIndexEndFramenumber - FilenameLastIndexStartFramenumber - 1U};

    const std::string FramenumberFirstTemp{FilenameFirst.substr(FilenameFirstIndexStartFramenumber + 1, FilenameFirstFramenumberLength)};
    const std::string FramenumberLastTemp{FilenameLast.substr(FilenameLastIndexStartFramenumber + 1, FilenameLastFramenumberLength)};

    uint64 FramenumberFirst{static_cast<uint64>(std::stoi(FramenumberFirstTemp))};
    uint64 FramenumberLast{static_cast<uint64>(std::stoi(FramenumberLastTemp))};

    for(uint64 i_Frame{FramenumberFirst}; i_Frame <= FramenumberLast; i_Frame++)
    {
        ListTimestamps.push_back(ListTimestampsAll[i_Frame - 1]); // -1 as Framenumbers start with 1
        NumberOfTimestampsFound++;
    }

    return NumberOfTimestampsFound;
}

void DatasetReaderASRLDevonIsland::SetProjectionMatrices(MatrixFloat64_3x4& ProjectionMatrixStereoLeft,
                                                         MatrixFloat64_3x4& ProjectionMatrixStereoRight)
{
    // define data
    float64 FocalLength{0.0};
    float64 PrincipalPointHorizontal{0.0};
    float64 PrincipalPointVertical{0.0};

    const float64 Baseline{0.239977002};

    if(m_ImageType == ASRLImageType::ASRLColor)
    {
        FocalLength              = 968.999694824; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
        PrincipalPointHorizontal = 635.139038086; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
        PrincipalPointVertical   = 463.537109375; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    }
    else
    {
        FocalLength              = 387.599884033; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
        PrincipalPointHorizontal = 253.755615234; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
        PrincipalPointVertical   = 185.114852905; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    }

    // create projection matrices
    ProjectionMatrixStereoLeft.setZero();
    ProjectionMatrixStereoRight.setZero();

    ProjectionMatrixStereoLeft(0U, 0U) = FocalLength;
    ProjectionMatrixStereoLeft(0U, 2U) = PrincipalPointHorizontal;
    ProjectionMatrixStereoLeft(1U, 1U) = FocalLength;
    ProjectionMatrixStereoLeft(1U, 2U) = PrincipalPointVertical;
    ProjectionMatrixStereoLeft(2U, 2U) = 1.0;

    ProjectionMatrixStereoRight(0U, 0U) = FocalLength;
    ProjectionMatrixStereoRight(0U, 2U) = PrincipalPointHorizontal;
    ProjectionMatrixStereoRight(0U, 3U) = -FocalLength * Baseline;
    ProjectionMatrixStereoRight(1U, 1U) = FocalLength;
    ProjectionMatrixStereoRight(1U, 2U) = PrincipalPointVertical;
    ProjectionMatrixStereoRight(2U, 2U) = 1.0;
}
