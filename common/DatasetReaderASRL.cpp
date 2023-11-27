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

DatasetReaderASRL::DatasetReaderASRL(const std::string BaseDirectory,
                                     const std::string SequenceName) : DatasetReaderBase(BaseDirectory, SequenceName)
{
    // set information for the stereo camera information
    m_RelativePathImagesStereoLeft        = "images/left/";
    m_RelativePathImagesStereoRight       = "images/right";
    m_FileBasenameImagesStereoLeft        = "";
    m_FileBasenameImagesStereoRight       = "";
    m_FileExtensionImagesStereoLeft       = ".png";
    m_FileExtensionImagesStereoRight      = ".png";
    m_FilenameTimestampsImagesStereoLeft  = "timestamps_images.txt";
    m_FilenameTimestampsImagesStereoRight = "timestamps_images.txt";

    // create absolute paths to stereo camera information
    m_AbsolutePathImagesStereoLeft            = m_BaseDirectory / m_SequenceName / m_RelativePathImagesStereoLeft;
    m_AbsolutePathImagesStereoRight           = m_BaseDirectory / m_SequenceName / m_RelativePathImagesStereoRight;
    m_AbsolutePathTimestampsImagesStereoLeft  = m_BaseDirectory / m_SequenceName / m_FilenameTimestampsImagesStereoLeft;
    m_AbsolutePathTimestampsImagesStereoRight = m_BaseDirectory / m_SequenceName / m_FilenameTimestampsImagesStereoRight;

    // extract filenames of the stereo camera images
    ExtractFilesInDirectory(m_AbsolutePathImagesStereoLeft,  m_FileBasenameImagesStereoLeft,  m_FileExtensionImagesStereoLeft,  m_FilenamesWithPathImagesStereoLeft,  m_NumberOfImagesStereoLeft);
    ExtractFilesInDirectory(m_AbsolutePathImagesStereoRight, m_FileBasenameImagesStereoRight, m_FileExtensionImagesStereoRight, m_FilenamesWithPathImagesStereoRight, m_NumberOfImagesStereoRight);

    // extract timestamps of the stereo camera images
    m_NumberOfTimestampsStereoLeft  = ExtractTimestamps(m_AbsolutePathTimestampsImagesStereoLeft,  m_TimestampsImagesStereoLeftNanoseconds);
    m_NumberOfTimestampsStereoRight = ExtractTimestamps(m_AbsolutePathTimestampsImagesStereoRight, m_TimestampsImagesStereoRightNanoseconds);
}

DatasetReaderASRL::~DatasetReaderASRL()
{

}

uint64 DatasetReaderASRL::ExtractTimestamps(const std::filesystem::path FileTimestampsWithPath,
                                                  ListUInt64&           ListTimestamps)
{
    // initialize number of timestamps found
    uint64 NumberOfTimestampsFound = 0;

    // open file containing the timestamps
    std::ifstream infile(FileTimestampsWithPath);

    // extract data
    std::string line;

    while(std::getline(infile, line))
    {
        uint64 Vertex;
        uint64 TimestampNanoseconds;
        char   Delimiter;

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
