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
    m_AbsolutePathImagesStereoLeft            = m_BaseDirectory / m_SequenceName / RelativePathImagesStereoLeft;
    m_AbsolutePathImagesStereoRight           = m_BaseDirectory / m_SequenceName / RelativePathImagesStereoRight;
    m_AbsolutePathTimestampsImagesStereoLeft  = m_BaseDirectory / m_SequenceName / FilenameTimestampsImagesStereo;
    m_AbsolutePathTimestampsImagesStereoRight = m_BaseDirectory / m_SequenceName / FilenameTimestampsImagesStereo;

    // extract filenames of the stereo camera images
    FileInterface FileInterfaceImagesStereoLeft(m_AbsolutePathImagesStereoLeft, FileBasenameImagesStereo, FileExtensionImagesStereo);
    FileInterface FileInterfaceImagesStereoRight(m_AbsolutePathImagesStereoRight, FileBasenameImagesStereo, FileExtensionImagesStereo);

    m_NumberOfImagesStereoLeft  = FileInterfaceImagesStereoLeft.GetNumberOfFiles();
    m_NumberOfImagesStereoRight = FileInterfaceImagesStereoRight.GetNumberOfFiles();

    m_FilenamesWithPathImagesStereoLeft  = FileInterfaceImagesStereoLeft.GetListOfFilenamesWithPath();
    m_FilenamesWithPathImagesStereoRight = FileInterfaceImagesStereoRight.GetListOfFilenamesWithPath();

    // extract timestamps of the stereo camera images
    m_NumberOfTimestampsStereoLeft  = ExtractTimestamps(m_AbsolutePathTimestampsImagesStereoLeft,  m_TimestampsImagesStereoLeftNanoseconds);
    m_NumberOfTimestampsStereoRight = ExtractTimestamps(m_AbsolutePathTimestampsImagesStereoRight, m_TimestampsImagesStereoRightNanoseconds);

    // extract image dimensions
    DatasetReaderBase::ExtractImagesDimensions(m_FilenamesWithPathImagesStereoLeft[0], m_HeightImagesStereo, m_WidthImagesStereo);

    // extract projection matrices of the stereo cameras
    std::filesystem::path AbsolutePathCalibrationStereo = m_BaseDirectory / m_SequenceName / FilenameCalibrationStereo;

    ExtractProjectionMatrices(AbsolutePathCalibrationStereo, m_ProjectionMatrixStereoLeft, m_ProjectionMatrixStereoRight);
}

DatasetReaderKITTI::~DatasetReaderKITTI()
{

}

void DatasetReaderKITTI::ExtractProjectionMatrices(const std::string&       FilenameCalibration,
                                                         MatrixFloat64_3x4& ProjectionMatrixStereoLeft,
                                                         MatrixFloat64_3x4& ProjectionMatrixStereoRight)
{
    CSVReader Reader(FilenameCalibration, " ");

    ProjectionMatrixStereoLeft(0, 0) = std::stod(Reader.GetValue(0, 1));
    ProjectionMatrixStereoLeft(0, 1) = std::stod(Reader.GetValue(0, 2));
    ProjectionMatrixStereoLeft(0, 2) = std::stod(Reader.GetValue(0, 3));
    ProjectionMatrixStereoLeft(0, 3) = std::stod(Reader.GetValue(0, 4));
    ProjectionMatrixStereoLeft(1, 0) = std::stod(Reader.GetValue(0, 5));
    ProjectionMatrixStereoLeft(1, 1) = std::stod(Reader.GetValue(0, 6));
    ProjectionMatrixStereoLeft(1, 2) = std::stod(Reader.GetValue(0, 7));
    ProjectionMatrixStereoLeft(1, 3) = std::stod(Reader.GetValue(0, 8));
    ProjectionMatrixStereoLeft(2, 0) = std::stod(Reader.GetValue(0, 9));
    ProjectionMatrixStereoLeft(2, 1) = std::stod(Reader.GetValue(0, 10));
    ProjectionMatrixStereoLeft(2, 2) = std::stod(Reader.GetValue(0, 11));
    ProjectionMatrixStereoLeft(2, 3) = std::stod(Reader.GetValue(0, 12));

    ProjectionMatrixStereoRight(0, 0) = std::stod(Reader.GetValue(1, 1));
    ProjectionMatrixStereoRight(0, 1) = std::stod(Reader.GetValue(1, 2));
    ProjectionMatrixStereoRight(0, 2) = std::stod(Reader.GetValue(1, 3));
    ProjectionMatrixStereoRight(0, 3) = std::stod(Reader.GetValue(1, 4));
    ProjectionMatrixStereoRight(1, 0) = std::stod(Reader.GetValue(1, 5));
    ProjectionMatrixStereoRight(1, 1) = std::stod(Reader.GetValue(1, 6));
    ProjectionMatrixStereoRight(1, 2) = std::stod(Reader.GetValue(1, 7));
    ProjectionMatrixStereoRight(1, 3) = std::stod(Reader.GetValue(1, 8));
    ProjectionMatrixStereoRight(2, 0) = std::stod(Reader.GetValue(1, 9));
    ProjectionMatrixStereoRight(2, 1) = std::stod(Reader.GetValue(1, 10));
    ProjectionMatrixStereoRight(2, 2) = std::stod(Reader.GetValue(1, 11));
    ProjectionMatrixStereoRight(2, 3) = std::stod(Reader.GetValue(1, 12));
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
