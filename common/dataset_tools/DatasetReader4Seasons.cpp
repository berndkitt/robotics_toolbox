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
}

DatasetReader4Seasons::~DatasetReader4Seasons()
{

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
