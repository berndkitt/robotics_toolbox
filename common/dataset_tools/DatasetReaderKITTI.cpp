///////////////////////////////////////////////////////////////////////////////
/// \file DatasetReaderKITTI.cpp
///////////////////////////////////////////////////////////////////////////////

/*
This file is part of the Robotics Toolbox.

Copyright (C) 2023

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

#include <fstream>

#include "DatasetReaderKITTI.h"
#include "../CSVReader.h"
#include "../FileInterface.h"

DatasetReaderKITTI::DatasetReaderKITTI(const std::string& BaseDirectory,
                                       const std::string& SequenceName) : DatasetReaderBase(BaseDirectory, SequenceName)
{
    // set information which is specific for the dataset
    const std::filesystem::path RelativePathImagesStereoLeft("image_0");
    const std::filesystem::path RelativePathImagesStereoRight("image_1");
    const std::filesystem::path FileBasenameImagesStereo("");
    const std::filesystem::path FileExtensionImagesStereo(".png");
    const std::filesystem::path FilenameTimestampsImagesStereo("times.txt");
    const std::filesystem::path FilenameCalibrationStereo("calib.txt");

    // create absolute paths to stereo camera information
    const std::filesystem::path AbsolutePathImagesStereoLeft            {m_BaseDirectory / m_SequenceName / RelativePathImagesStereoLeft};
    const std::filesystem::path AbsolutePathImagesStereoRight           {m_BaseDirectory / m_SequenceName / RelativePathImagesStereoRight};
    const std::filesystem::path AbsolutePathTimestampsImagesStereoLeft  {m_BaseDirectory / m_SequenceName / FilenameTimestampsImagesStereo};
    const std::filesystem::path AbsolutePathTimestampsImagesStereoRight {m_BaseDirectory / m_SequenceName / FilenameTimestampsImagesStereo};
    const std::filesystem::path AbsolutePathCalibrationStereo           {m_BaseDirectory / m_SequenceName / FilenameCalibrationStereo};

    // extract filenames of the stereo camera images
    FileInterface FileInterfaceImagesStereoLeft(AbsolutePathImagesStereoLeft, FileBasenameImagesStereo, FileExtensionImagesStereo);
    FileInterface FileInterfaceImagesStereoRight(AbsolutePathImagesStereoRight, FileBasenameImagesStereo, FileExtensionImagesStereo);

    m_NumberOfImagesStereoLeft  = FileInterfaceImagesStereoLeft.GetNumberOfFiles();
    m_NumberOfImagesStereoRight = FileInterfaceImagesStereoRight.GetNumberOfFiles();

    m_FilenamesWithPathImagesStereoLeft  = FileInterfaceImagesStereoLeft.GetListOfFilenamesWithPath();
    m_FilenamesWithPathImagesStereoRight = FileInterfaceImagesStereoRight.GetListOfFilenamesWithPath();

    // extract timestamps of the stereo camera images
    m_NumberOfTimestampsStereoLeft  = ExtractTimestamps(AbsolutePathTimestampsImagesStereoLeft,  m_TimestampsImagesStereoLeftNanoseconds);
    m_NumberOfTimestampsStereoRight = ExtractTimestamps(AbsolutePathTimestampsImagesStereoRight, m_TimestampsImagesStereoRightNanoseconds);

    // extract image dimensions
    DatasetReaderBase::ExtractImagesDimensions(m_FilenamesWithPathImagesStereoLeft[0], m_HeightImagesStereo, m_WidthImagesStereo);

    // extract projection matrices of the stereo cameras
    ExtractProjectionMatrices(AbsolutePathCalibrationStereo, m_ProjectionMatrixStereoLeft, m_ProjectionMatrixStereoRight);
}

DatasetReaderKITTI::~DatasetReaderKITTI()
{

}

void DatasetReaderKITTI::ExtractProjectionMatrices(const std::string&       FilenameCalibration,
                                                         MatrixFloat64_3x4& ProjectionMatrixStereoLeft,
                                                         MatrixFloat64_3x4& ProjectionMatrixStereoRight)
{
    // read file
    CSVReader Reader(FilenameCalibration, " ");

    // create projection matrices
    ProjectionMatrixStereoLeft(0U, 0U) = std::stod(Reader.GetValue(0U, 1U));
    ProjectionMatrixStereoLeft(0U, 1U) = std::stod(Reader.GetValue(0U, 2U));
    ProjectionMatrixStereoLeft(0U, 2U) = std::stod(Reader.GetValue(0U, 3U));
    ProjectionMatrixStereoLeft(0U, 3U) = std::stod(Reader.GetValue(0U, 4U));
    ProjectionMatrixStereoLeft(1U, 0U) = std::stod(Reader.GetValue(0U, 5U));  // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    ProjectionMatrixStereoLeft(1U, 1U) = std::stod(Reader.GetValue(0U, 6U));  // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    ProjectionMatrixStereoLeft(1U, 2U) = std::stod(Reader.GetValue(0U, 7U));  // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    ProjectionMatrixStereoLeft(1U, 3U) = std::stod(Reader.GetValue(0U, 8U));  // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    ProjectionMatrixStereoLeft(2U, 0U) = std::stod(Reader.GetValue(0U, 9U));  // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    ProjectionMatrixStereoLeft(2U, 1U) = std::stod(Reader.GetValue(0U, 10U)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    ProjectionMatrixStereoLeft(2U, 2U) = std::stod(Reader.GetValue(0U, 11U)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    ProjectionMatrixStereoLeft(2U, 3U) = std::stod(Reader.GetValue(0U, 12U)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    ProjectionMatrixStereoRight(0U, 0U) = std::stod(Reader.GetValue(1U, 1U));
    ProjectionMatrixStereoRight(0U, 1U) = std::stod(Reader.GetValue(1U, 2U));
    ProjectionMatrixStereoRight(0U, 2U) = std::stod(Reader.GetValue(1U, 3U));
    ProjectionMatrixStereoRight(0U, 3U) = std::stod(Reader.GetValue(1U, 4U));
    ProjectionMatrixStereoRight(1U, 0U) = std::stod(Reader.GetValue(1U, 5U));  // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    ProjectionMatrixStereoRight(1U, 1U) = std::stod(Reader.GetValue(1U, 6U));  // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    ProjectionMatrixStereoRight(1U, 2U) = std::stod(Reader.GetValue(1U, 7U));  // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    ProjectionMatrixStereoRight(1U, 3U) = std::stod(Reader.GetValue(1U, 8U));  // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    ProjectionMatrixStereoRight(2U, 0U) = std::stod(Reader.GetValue(1U, 9U));  // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    ProjectionMatrixStereoRight(2U, 1U) = std::stod(Reader.GetValue(1U, 10U)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    ProjectionMatrixStereoRight(2U, 2U) = std::stod(Reader.GetValue(1U, 11U)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    ProjectionMatrixStereoRight(2U, 3U) = std::stod(Reader.GetValue(1U, 12U)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}

uint64 DatasetReaderKITTI::ExtractTimestamps(const std::filesystem::path& FileTimestampsWithPath,
                                                   ListUInt64&            ListTimestamps)
{
    // initialize number of timestamps found
    uint64 NumberOfTimestampsFound = 0;

    // open file containing the timestamps
    std::ifstream infile(FileTimestampsWithPath);

    // extract data
    std::string line;

    while(std::getline(infile, line))
    {
        float64 TimestampSeconds     = 0.0;
        uint64  TimestampNanoseconds = 0U;

        std::istringstream iss(line);

        if(!(iss >> TimestampSeconds))
        {
            break;
        }

        TimestampNanoseconds = static_cast<uint64>(TimestampSeconds * 1.0e9); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

        ListTimestamps.push_back(TimestampNanoseconds);
        NumberOfTimestampsFound++;
    }

    return NumberOfTimestampsFound;
}
