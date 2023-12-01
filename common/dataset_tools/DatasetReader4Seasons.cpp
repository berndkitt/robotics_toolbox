///////////////////////////////////////////////////////////////////////////////
/// \file DatasetReader4Seasons.cpp
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

#include "DatasetReader4Seasons.h"
#include "../CSVReader.h"
#include "../FileInterface.h"

DatasetReader4Seasons::DatasetReader4Seasons(const std::string& BaseDirectory,
                                             const std::string& SequenceName) : DatasetReaderBase(BaseDirectory, SequenceName)
{
    // set information which is specific for the dataset
    const std::filesystem::path RelativePathImagesStereoLeft("undistorted_images/cam0");
    const std::filesystem::path RelativePathImagesStereoRight("undistorted_images/cam1");
    const std::filesystem::path FileBasenameImagesStereo("");
    const std::filesystem::path FileExtensionImagesStereo(".png");
    const std::filesystem::path FilenameTimestampsImagesStereo("times.txt");
    const std::filesystem::path RelativePathCalibration("calibration");
    const std::filesystem::path FilenameIntrinsicCalibrationLeft("undistorted_calib_0.txt");
    const std::filesystem::path FilenameIntrinsicCalibrationRight("undistorted_calib_1.txt");
    const std::filesystem::path FilenameExtrinsicCalibration("undistorted_calib_stereo.txt");

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
    std::filesystem::path AbsolutePathIntrinsicCalibrationLeft  = m_BaseDirectory / RelativePathCalibration / FilenameIntrinsicCalibrationLeft;
    std::filesystem::path AbsolutePathIntrinsicCalibrationRight = m_BaseDirectory / RelativePathCalibration / FilenameIntrinsicCalibrationRight;
    std::filesystem::path AbsolutePathExtrinsicCalibration      = m_BaseDirectory / RelativePathCalibration / FilenameExtrinsicCalibration;

    ExtractProjectionMatrices(AbsolutePathIntrinsicCalibrationLeft, AbsolutePathIntrinsicCalibrationRight, AbsolutePathExtrinsicCalibration, m_ProjectionMatrixStereoLeft, m_ProjectionMatrixStereoRight);
}

DatasetReader4Seasons::~DatasetReader4Seasons()
{

}

void DatasetReader4Seasons::ExtractProjectionMatrices(const std::string&       FilenameIntrinsicCalibrationLeft,
                                                      const std::string&       FilenameIntrinsicCalibrationRight,
                                                      const std::string&       FilenameExtrinsicCalibration,
                                                            MatrixFloat64_3x4& ProjectionMatrixStereoLeft,
                                                            MatrixFloat64_3x4& ProjectionMatrixStereoRight)
{
    CSVReader ReaderIntrinsicLeft(FilenameIntrinsicCalibrationLeft, " ");
    CSVReader ReaderIntrinsicRight(FilenameIntrinsicCalibrationRight, " ");
    CSVReader ReaderExtrinsic(FilenameExtrinsicCalibration, " ");

    const float64 FocalLengthHorizontalLeft     = std::stod(ReaderIntrinsicLeft.GetValue(0, 1));
    const float64 FocalLengthVerticalLeft       = std::stod(ReaderIntrinsicLeft.GetValue(0, 2));
    const float64 PrincipalPointHorizontalLeft  = std::stod(ReaderIntrinsicLeft.GetValue(0, 3));
    const float64 PrincipalPointVerticalLeft    = std::stod(ReaderIntrinsicLeft.GetValue(0, 4));
    const float64 FocalLengthHorizontalRight    = std::stod(ReaderIntrinsicRight.GetValue(0, 1));
    const float64 FocalLengthVerticalRight      = std::stod(ReaderIntrinsicRight.GetValue(0, 2));
    const float64 PrincipalPointHorizontalRight = std::stod(ReaderIntrinsicRight.GetValue(0, 3));
    const float64 PrincipalPointVerticalRight   = std::stod(ReaderIntrinsicRight.GetValue(0, 4));
    const float64 Baseline                      = -std::stod(ReaderExtrinsic.GetValue(0, 3));

    ProjectionMatrixStereoLeft(0, 0) = FocalLengthHorizontalLeft;
    ProjectionMatrixStereoLeft(0, 1) = 0.0;
    ProjectionMatrixStereoLeft(0, 2) = PrincipalPointHorizontalLeft;
    ProjectionMatrixStereoLeft(0, 3) = 0.0;
    ProjectionMatrixStereoLeft(1, 0) = 0.0;
    ProjectionMatrixStereoLeft(1, 1) = FocalLengthVerticalLeft;
    ProjectionMatrixStereoLeft(1, 2) = PrincipalPointVerticalLeft;
    ProjectionMatrixStereoLeft(1, 3) = 0.0;
    ProjectionMatrixStereoLeft(2, 0) = 0.0;
    ProjectionMatrixStereoLeft(2, 1) = 0.0;
    ProjectionMatrixStereoLeft(2, 2) = 1.0;
    ProjectionMatrixStereoLeft(2, 3) = 0.0;

    ProjectionMatrixStereoRight(0, 0) = FocalLengthHorizontalRight;
    ProjectionMatrixStereoRight(0, 1) = 0.0;
    ProjectionMatrixStereoRight(0, 2) = PrincipalPointHorizontalRight;
    ProjectionMatrixStereoRight(0, 3) = -FocalLengthHorizontalRight * Baseline;
    ProjectionMatrixStereoRight(1, 0) = 0.0;
    ProjectionMatrixStereoRight(1, 1) = FocalLengthVerticalRight;
    ProjectionMatrixStereoRight(1, 2) = PrincipalPointVerticalRight;
    ProjectionMatrixStereoRight(1, 3) = 0.0;
    ProjectionMatrixStereoRight(2, 0) = 0.0;
    ProjectionMatrixStereoRight(2, 1) = 0.0;
    ProjectionMatrixStereoRight(2, 2) = 1.0;
    ProjectionMatrixStereoRight(2, 3) = 0.0;
}

uint64 DatasetReader4Seasons::ExtractTimestamps(const std::filesystem::path& FileTimestampsWithPath,
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
        uint64  FrameID              = 0U;
        float64 TimestampSeconds     = 0.0;
        uint64  TimestampNanoseconds = 0U;
        float64 ExposureTime         = 0.0;
        char    Delimiter            = ' ';

        std::istringstream iss(line);

        if(!(iss >> FrameID >> Delimiter >> TimestampSeconds >> Delimiter >> ExposureTime))
        {
            break;
        }

        TimestampNanoseconds = static_cast<uint64>(TimestampSeconds * 1.0e9); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

        ListTimestamps.push_back(TimestampNanoseconds);
        NumberOfTimestampsFound++;
    }

    return NumberOfTimestampsFound;
}
