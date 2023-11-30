///////////////////////////////////////////////////////////////////////////////
/// \file FileInterface.cpp
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

#include <algorithm>
#include <filesystem>
#include <iostream>

#include "FileInterface.h"

FileInterface::FileInterface(const std::string& Path,
                             const std::string& FileBasename,
                             const std::string& FileExtension,
                                   boolean      ShowListOfFiles) : m_Path{Path},
                                                                   m_FileBasename{FileBasename},
                                                                   m_FileExtension{FileExtension},
                                                                   m_NumberOfFiles{0U}
{
    // check if defined path is available
    if(!exists(m_Path) || !is_directory(m_Path))
    {
        throw std::invalid_argument("Directory " + m_Path.string() + " does not exist.");
    }

    // get filenames (i.e. iterate through all files in the directory)
    std::filesystem::directory_iterator DirectoryIterator(m_Path);

    for(const auto& FilenameWithPath: DirectoryIterator)
    {
        // get filename of current file
        const std::string Filename {FilenameWithPath.path().filename()};

        // check whether the name of the current file starts with specified basename and ends with specified extension
        const boolean HasCorrectBasename  {Filename.find(FileBasename) == 0};
        const boolean HasCorrectExtension {Filename.find(FileExtension) == Filename.length() - FileExtension.length()};

        if(HasCorrectBasename && HasCorrectExtension)
        {
            m_ListFilenamesWithPath.push_back(m_Path / Filename);
        }
    }

    // sort filenames
    std::sort(m_ListFilenamesWithPath.begin(), m_ListFilenamesWithPath.end());

    // set number of files
    m_NumberOfFiles = static_cast<uint64>(m_ListFilenamesWithPath.size());

    // check whether files were found in the specified directory or not
    if(m_NumberOfFiles == 0U)
    {
        throw std::invalid_argument("Directory " + m_Path.string() + " does not contain files matching the conditions.");
    }

    // show list of files found in the specified directory
    if(ShowListOfFiles)
    {
        for(uint64 i_File {0U}; i_File < m_NumberOfFiles; i_File++)
        {
            // print filename
            std::cout << "Found file: " << m_ListFilenamesWithPath[i_File] << std::endl;
        }
    }
}

FileInterface::~FileInterface()
{

}

std::string FileInterface::GetFilename(uint64 Index) const
{
    // check if index is in range
    if(Index >= m_NumberOfFiles)
    {
        throw std::out_of_range("Index " + std::to_string(Index) + " is out of range.");
    }

    // get filename
    std::filesystem::path FilenameWithPath(m_ListFilenamesWithPath[Index]);

    // return filename
    return FilenameWithPath.filename();
}

std::string FileInterface::GetFilenameWithPath(uint64 Index) const
{
    // check if index is in range
    if(Index >= m_NumberOfFiles)
    {
        throw std::out_of_range("Index " + std::to_string(Index) + " is out of range.");
    }

    // return filename with path
    return m_ListFilenamesWithPath[Index];
}

const std::vector<std::string>& FileInterface::GetListOfFilenamesWithPath() const
{
    return m_ListFilenamesWithPath;
}

uint64 FileInterface::GetNumberOfFiles() const
{
    return m_NumberOfFiles;
}
