///////////////////////////////////////////////////////////////////////////////
/// \file DatasetReaderASRL.cpp
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

#include "DatasetReaderASRL.h"
#include "../CSVReader.h"
#include "../FileInterface.h"

DatasetReaderASRL::DatasetReaderASRL(const std::string& BaseDirectory,
                                     const std::string& SequenceName) : DatasetReaderBase(BaseDirectory, SequenceName)
{
    // set information which is specific for the dataset
    const std::filesystem::path RelativePathImagesStereoLeft("images/left");
    const std::filesystem::path RelativePathImagesStereoRight("images/right");
    const std::filesystem::path FileBasenameImagesStereo("");
    const std::filesystem::path FileExtensionImagesStereo(".png");
    const std::filesystem::path FilenameTimestampsImagesStereo("timestamps_images.txt");
    const std::filesystem::path FilenameCalibrationStereo("camera_parameters.txt");

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
    std::filesystem::path AbsolutePathCalibrationStereo = m_BaseDirectory / FilenameCalibrationStereo;

    ExtractProjectionMatrices(AbsolutePathCalibrationStereo, m_ProjectionMatrixStereoLeft, m_ProjectionMatrixStereoRight);
}

DatasetReaderASRL::~DatasetReaderASRL()
{

}

void DatasetReaderASRL::ExtractProjectionMatrices(const std::string&       FilenameCalibration,
                                                        MatrixFloat64_3x4& ProjectionMatrixStereoLeft,
                                                        MatrixFloat64_3x4& ProjectionMatrixStereoRight)
{
    CSVReader Reader(FilenameCalibration, " ");

    const float64 FocalLength              = std::stod(Reader.GetValue(2, 2));
    const float64 PrincipalPointHorizontal = std::stod(Reader.GetValue(3, 1));
    const float64 PrincipalPointVertical   = std::stod(Reader.GetValue(4, 1));
    const float64 Baseline                 = std::stod(Reader.GetValue(5, 1));

    ProjectionMatrixStereoLeft(0, 0) = FocalLength;
    ProjectionMatrixStereoLeft(0, 1) = 0.0;
    ProjectionMatrixStereoLeft(0, 2) = PrincipalPointHorizontal;
    ProjectionMatrixStereoLeft(0, 3) = 0.0;
    ProjectionMatrixStereoLeft(1, 0) = 0.0;
    ProjectionMatrixStereoLeft(1, 1) = FocalLength;
    ProjectionMatrixStereoLeft(1, 2) = PrincipalPointVertical;
    ProjectionMatrixStereoLeft(1, 3) = 0.0;
    ProjectionMatrixStereoLeft(2, 0) = 0.0;
    ProjectionMatrixStereoLeft(2, 1) = 0.0;
    ProjectionMatrixStereoLeft(2, 2) = 1.0;
    ProjectionMatrixStereoLeft(2, 3) = 0.0;

    ProjectionMatrixStereoRight(0, 0) = FocalLength;
    ProjectionMatrixStereoRight(0, 1) = 0.0;
    ProjectionMatrixStereoRight(0, 2) = PrincipalPointHorizontal;
    ProjectionMatrixStereoRight(0, 3) = -FocalLength * Baseline;
    ProjectionMatrixStereoRight(1, 0) = 0.0;
    ProjectionMatrixStereoRight(1, 1) = FocalLength;
    ProjectionMatrixStereoRight(1, 2) = PrincipalPointVertical;
    ProjectionMatrixStereoRight(1, 3) = 0.0;
    ProjectionMatrixStereoRight(2, 0) = 0.0;
    ProjectionMatrixStereoRight(2, 1) = 0.0;
    ProjectionMatrixStereoRight(2, 2) = 1.0;
    ProjectionMatrixStereoRight(2, 3) = 0.0;
}

uint64 DatasetReaderASRL::ExtractTimestamps(const std::filesystem::path& FileTimestampsWithPath,
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
        uint64 Vertex               = 0U;
        uint64 TimestampNanoseconds = 0U;
        char   Delimiter            = ' ';

        std::istringstream iss(line);

        if(!(iss >> Vertex >> Delimiter >> TimestampNanoseconds) && !(Delimiter == ','))
        {
            break;
        }

        ListTimestamps.push_back(TimestampNanoseconds);
        NumberOfTimestampsFound++;
    }

    return NumberOfTimestampsFound;
}
