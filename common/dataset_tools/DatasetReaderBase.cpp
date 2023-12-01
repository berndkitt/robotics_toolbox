///////////////////////////////////////////////////////////////////////////////
/// \file DatasetReaderBase.cpp
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

#include <opencv2/highgui/highgui.hpp>

#include "DatasetReaderBase.h"

DatasetReaderBase::DatasetReaderBase(const std::string& BaseDirectory,
                                     const std::string& SequenceName) : m_BaseDirectory{BaseDirectory},
                                                                        m_SequenceName{SequenceName},
                                                                        m_NumberOfImagesStereoLeft{0U},
                                                                        m_NumberOfImagesStereoRight{0U},
                                                                        m_NumberOfTimestampsStereoLeft{0U},
                                                                        m_NumberOfTimestampsStereoRight{0U},
                                                                        m_HeightImagesStereo{0U},
                                                                        m_WidthImagesStereo{0U}
{

}

DatasetReaderBase::~DatasetReaderBase()
{

}

uint32 DatasetReaderBase::GetImageHeightStereoImages() const
{
    return m_HeightImagesStereo;
}

void DatasetReaderBase::GetImageInformationStereoLeft(uint64            Index,
                                                      ImageInformation& ImageInformation) const
{
    // collect image information
    ImageInformation.IsValid                  = true;
    ImageInformation.Timestamp                = m_TimestampsImagesStereoLeftNanoseconds[Index];
    ImageInformation.FilenameWithAbsolutePath = m_FilenamesWithPathImagesStereoLeft[Index];
    ImageInformation.ImageGrayscale           = cv::imread(ImageInformation.FilenameWithAbsolutePath, cv::IMREAD_GRAYSCALE);
}

void DatasetReaderBase::GetImageInformationStereoRight(uint64            Index,
                                                       ImageInformation& ImageInformation) const
{
    // collect image information
    ImageInformation.IsValid                  = true;
    ImageInformation.Timestamp                = m_TimestampsImagesStereoRightNanoseconds[Index];
    ImageInformation.FilenameWithAbsolutePath = m_FilenamesWithPathImagesStereoRight[Index];
    ImageInformation.ImageGrayscale           = cv::imread(ImageInformation.FilenameWithAbsolutePath, cv::IMREAD_GRAYSCALE);
}

uint32 DatasetReaderBase::GetImageWidthStereoImages() const
{
    return m_WidthImagesStereo;
}

uint64 DatasetReaderBase::GetNumberOfFrames() const
{
    // get number of frames (based on the list of the left stereo camera images)
    uint64 NumberOfFrames {m_FilenamesWithPathImagesStereoLeft.size()};

    return NumberOfFrames;
}

const MatrixFloat64_3x4& DatasetReaderBase::GetProjectionMatrixStereoLeft() const
{
    return m_ProjectionMatrixStereoLeft;
}

const MatrixFloat64_3x4& DatasetReaderBase::GetProjectionMatrixStereoRight() const
{
    return m_ProjectionMatrixStereoRight;
}

void DatasetReaderBase::ExtractImagesDimensions(const std::string& FilenameImage,
                                                      uint32&      ImageHeight,
                                                      uint32&      ImageWidth)
{
    // read first stereo camera image (left camera)
    const cv::Mat Image {cv::imread(FilenameImage, cv::IMREAD_COLOR)};

    // get image dimensions
    ImageHeight = Image.rows;
    ImageWidth  = Image.cols;
}
