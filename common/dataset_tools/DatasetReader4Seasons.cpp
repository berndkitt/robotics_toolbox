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
    const std::filesystem::path AbsolutePathImagesStereoLeft                {m_BaseDirectory / m_SequenceName / RelativePathImagesStereoLeft};
    const std::filesystem::path AbsolutePathImagesStereoRight               {m_BaseDirectory / m_SequenceName / RelativePathImagesStereoRight};
    const std::filesystem::path AbsolutePathTimestampsImagesStereoLeft      {m_BaseDirectory / m_SequenceName / FilenameTimestampsImagesStereo};
    const std::filesystem::path AbsolutePathTimestampsImagesStereoRight     {m_BaseDirectory / m_SequenceName / FilenameTimestampsImagesStereo};
    const std::filesystem::path AbsolutePathIntrinsicCalibrationStereoLeft  {m_BaseDirectory / RelativePathCalibration / FilenameIntrinsicCalibrationLeft};
    const std::filesystem::path AbsolutePathIntrinsicCalibrationStereoRight {m_BaseDirectory / RelativePathCalibration / FilenameIntrinsicCalibrationRight};
    const std::filesystem::path AbsolutePathExtrinsicCalibrationStereo      {m_BaseDirectory / RelativePathCalibration / FilenameExtrinsicCalibration};

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
    ExtractProjectionMatrices(AbsolutePathIntrinsicCalibrationStereoLeft, AbsolutePathIntrinsicCalibrationStereoRight, AbsolutePathExtrinsicCalibrationStereo, m_ProjectionMatrixStereoLeft, m_ProjectionMatrixStereoRight);
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
    // read files
    CSVReader ReaderIntrinsicLeft(FilenameIntrinsicCalibrationLeft, " ");
    CSVReader ReaderIntrinsicRight(FilenameIntrinsicCalibrationRight, " ");
    CSVReader ReaderExtrinsic(FilenameExtrinsicCalibration, " ");

    // extract data
    const uint64 ColumnIndexFocalLengthHorizontal    {1U};
    const uint64 ColumnIndexFocalLengthVertical      {2U};
    const uint64 ColumnIndexPrincipalPointHorizontal {3U};
    const uint64 ColumnIndexPrincipalPointVertical   {4U};
    const uint64 ColumnIndexBaseline                 {3U};

    const float64 FocalLengthHorizontalLeft    = std::stod(ReaderIntrinsicLeft.GetValue(0U, ColumnIndexFocalLengthHorizontal));
    const float64 FocalLengthVerticalLeft      = std::stod(ReaderIntrinsicLeft.GetValue(0U, ColumnIndexFocalLengthVertical));
    const float64 PrincipalPointHorizontalLeft = std::stod(ReaderIntrinsicLeft.GetValue(0U, ColumnIndexPrincipalPointHorizontal));
    const float64 PrincipalPointVerticalLeft   = std::stod(ReaderIntrinsicLeft.GetValue(0U, ColumnIndexPrincipalPointVertical));

    const float64 FocalLengthHorizontalRight    = std::stod(ReaderIntrinsicRight.GetValue(0U, ColumnIndexFocalLengthHorizontal));
    const float64 FocalLengthVerticalRight      = std::stod(ReaderIntrinsicRight.GetValue(0U, ColumnIndexFocalLengthVertical));
    const float64 PrincipalPointHorizontalRight = std::stod(ReaderIntrinsicRight.GetValue(0U, ColumnIndexPrincipalPointHorizontal));
    const float64 PrincipalPointVerticalRight   = std::stod(ReaderIntrinsicRight.GetValue(0U, ColumnIndexPrincipalPointVertical));

    const float64 Baseline = -std::stod(ReaderExtrinsic.GetValue(0U, ColumnIndexBaseline));

    // create projection matrices
    ProjectionMatrixStereoLeft.setZero();
    ProjectionMatrixStereoRight.setZero();

    ProjectionMatrixStereoLeft(0U, 0U) = FocalLengthHorizontalLeft;
    ProjectionMatrixStereoLeft(0U, 2U) = PrincipalPointHorizontalLeft;
    ProjectionMatrixStereoLeft(1U, 1U) = FocalLengthVerticalLeft;
    ProjectionMatrixStereoLeft(1U, 2U) = PrincipalPointVerticalLeft;
    ProjectionMatrixStereoLeft(2U, 2U) = 1.0;

    ProjectionMatrixStereoRight(0U, 0U) = FocalLengthHorizontalRight;
    ProjectionMatrixStereoRight(0U, 2U) = PrincipalPointHorizontalRight;
    ProjectionMatrixStereoRight(0U, 3U) = -FocalLengthHorizontalRight * Baseline;
    ProjectionMatrixStereoRight(1U, 1U) = FocalLengthVerticalRight;
    ProjectionMatrixStereoRight(1U, 2U) = PrincipalPointVerticalRight;
    ProjectionMatrixStereoRight(2U, 2U) = 1.0;
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
