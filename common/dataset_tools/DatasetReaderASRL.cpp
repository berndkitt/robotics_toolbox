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

#include "../CSVReader.h"
#include "../FileInterface.h"
#include "DatasetReaderASRL.h"

DatasetReaderASRL::DatasetReaderASRL(const std::string& BaseDirectory,
                                     const std::string& SequenceName) :
    DatasetReaderBase(BaseDirectory, SequenceName)
{
    // set information which is specific for the dataset
    const std::filesystem::path RelativePathImagesStereoLeft("images/left");
    const std::filesystem::path RelativePathImagesStereoRight("images/right");
    const std::filesystem::path FileBasenameImagesStereo("");
    const std::filesystem::path FileExtensionImagesStereo(".png");
    const std::filesystem::path FilenameTimestampsImagesStereo("timestamps_images.txt");
    const std::filesystem::path FilenameCalibrationStereo("camera_parameters.txt");

    // create absolute paths to stereo camera information
    const std::filesystem::path AbsolutePathImagesStereoLeft{m_BaseDirectory / m_SequenceName / RelativePathImagesStereoLeft};
    const std::filesystem::path AbsolutePathImagesStereoRight{m_BaseDirectory / m_SequenceName / RelativePathImagesStereoRight};
    const std::filesystem::path AbsolutePathTimestampsImagesStereoLeft{m_BaseDirectory / m_SequenceName / FilenameTimestampsImagesStereo};
    const std::filesystem::path AbsolutePathTimestampsImagesStereoRight{m_BaseDirectory / m_SequenceName / FilenameTimestampsImagesStereo};
    const std::filesystem::path AbsolutePathCalibrationStereo{m_BaseDirectory / FilenameCalibrationStereo};

    // extract filenames of the stereo camera images
    FileInterface FileInterfaceImagesStereoLeft(AbsolutePathImagesStereoLeft, FileBasenameImagesStereo, FileExtensionImagesStereo);
    FileInterface FileInterfaceImagesStereoRight(AbsolutePathImagesStereoRight, FileBasenameImagesStereo, FileExtensionImagesStereo);

    m_NumberOfImagesStereoLeft  = FileInterfaceImagesStereoLeft.GetNumberOfFiles();
    m_NumberOfImagesStereoRight = FileInterfaceImagesStereoRight.GetNumberOfFiles();

    m_FilenamesWithPathImagesStereoLeft  = FileInterfaceImagesStereoLeft.GetListOfFilenamesWithPath();
    m_FilenamesWithPathImagesStereoRight = FileInterfaceImagesStereoRight.GetListOfFilenamesWithPath();

    // extract timestamps of the stereo camera images
    m_NumberOfTimestampsStereoLeft  = ExtractTimestamps(AbsolutePathTimestampsImagesStereoLeft, m_TimestampsImagesStereoLeftNanoseconds);
    m_NumberOfTimestampsStereoRight = ExtractTimestamps(AbsolutePathTimestampsImagesStereoRight, m_TimestampsImagesStereoRightNanoseconds);

    // extract image dimensions
    DatasetReaderBase::ExtractImagesDimensions(m_FilenamesWithPathImagesStereoLeft[0], m_HeightImagesStereo, m_WidthImagesStereo);

    // extract projection matrices of the stereo cameras
    ExtractProjectionMatrices(AbsolutePathCalibrationStereo, m_ProjectionMatrixStereoLeft, m_ProjectionMatrixStereoRight);
}

DatasetReaderASRL::~DatasetReaderASRL()
{
}

void DatasetReaderASRL::ExtractProjectionMatrices(const std::string& FilenameCalibration,
                                                  MatrixFloat64_3x4& ProjectionMatrixStereoLeft,
                                                  MatrixFloat64_3x4& ProjectionMatrixStereoRight)
{
    // read file
    CSVReader Reader(FilenameCalibration, " ");

    // extract data
    const uint64 ColumnIndexFocalLengthHorizontal{2U};
    const uint64 ColumnIndexPrincipalPointHorizontal{1U};
    const uint64 ColumnIndexPrincipalPointVertical{1U};
    const uint64 ColumnIndexBaseline{1U};
    const uint64 RowIndexFocalLengthHorizontal{2U};
    const uint64 RowIndexPrincipalPointHorizontal{3U};
    const uint64 RowIndexPrincipalPointVertical{4U};
    const uint64 RowIndexBaseline{5U};

    const float64 FocalLength              = std::stod(Reader.GetValue(RowIndexFocalLengthHorizontal, ColumnIndexFocalLengthHorizontal));
    const float64 PrincipalPointHorizontal = std::stod(Reader.GetValue(RowIndexPrincipalPointHorizontal, ColumnIndexPrincipalPointHorizontal));
    const float64 PrincipalPointVertical   = std::stod(Reader.GetValue(RowIndexPrincipalPointVertical, ColumnIndexPrincipalPointVertical));
    const float64 Baseline                 = std::stod(Reader.GetValue(RowIndexBaseline, ColumnIndexBaseline));

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

uint64 DatasetReaderASRL::ExtractTimestamps(const std::filesystem::path& FileTimestampsWithPath,
                                            ListUInt64&                  ListTimestamps)
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
