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

#include "DatasetReaderBase.h"

DatasetReaderBase::DatasetReaderBase(const std::string& BaseDirectory,
                                     const std::string& SequenceName) : m_BaseDirectory{BaseDirectory},
                                                                        m_SequenceName{SequenceName},
                                                                        m_NumberOfImagesStereoLeft{0U},
                                                                        m_NumberOfImagesStereoRight{0U},
                                                                        m_NumberOfTimestampsStereoLeft{0U},
                                                                        m_NumberOfTimestampsStereoRight{0U}
{

}

DatasetReaderBase::~DatasetReaderBase()
{

}

void DatasetReaderBase::ExtractFilesInDirectory(const std::filesystem::path&    Path,
                                                const std::string&              FileBasename,
                                                const std::string&              FileExtension,
                                                      std::vector<std::string>& ListFilenamesWithPath,
                                                      uint64&                   NumberOfFilesFound)
{
    // check whether the provided path exists or not
    if(!exists(Path) || !is_directory(Path))
    {
        throw std::invalid_argument("Directory " + Path.string() + " does not exist.");
    }

    // get files in the directory (i.e. iterate over all files)
    std::filesystem::directory_iterator DirectoryIterator(Path);

    for(const auto& FilenameWithPath: DirectoryIterator)
    {
        // get filename of current file
        const std::string Filename {FilenameWithPath.path().filename()};

        // check whether the name of the current file starts with specified basename and ends with specified extension
        const boolean HasCorrectBasename  {Filename.find(FileBasename) == 0};
        const boolean HasCorrectExtension {Filename.find(FileExtension) == Filename.length() - FileExtension.length()};

        if(HasCorrectBasename && HasCorrectExtension)
        {
            ListFilenamesWithPath.push_back(Path / Filename);
        }
    }

    // sort filenames found
    std::sort(ListFilenamesWithPath.begin(),ListFilenamesWithPath.end());

    // get number of files found
    NumberOfFilesFound = ListFilenamesWithPath.size();

    // check whether files were found in the specified directory or not
    if(NumberOfFilesFound == 0)
    {
        throw std::invalid_argument("Directory " + Path.string() + " does not contain files matching the conditions.");
    }
}
