///////////////////////////////////////////////////////////////////////////////
/// \file FileInterface.h
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

#ifndef FILEINTERFACE_H
#define FILEINTERFACE_H

#include <filesystem>
#include <string>

#include <GlobalTypesBase.h>

///////////////////////////////////////////////////////////////////////////////
/// \class FileInterface
///
/// \brief Class for accessing files in a directory.
///////////////////////////////////////////////////////////////////////////////
class FileInterface
{
protected:
    std::filesystem::path    m_Path;                  ///< Path of the directory containing the files.
    std::filesystem::path    m_FileBasename;          ///< Basename of the files.
    std::filesystem::path    m_FileExtension;         ///< Extension of the files.
    std::vector<std::string> m_ListFilenamesWithPath; ///< List containing the filenames including their paths.
    uint64                   m_NumberOfFiles;         ///< Number of files.

public:
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Constructor.
    ///
    /// \param[in] Path            Path of the directory containing the files.
    /// \param[in] FileBasename    Basename of the files.
    /// \param[in] FileExtension   Extension of the files.
    /// \param[in] ShowListOfFiles Flag whether the list of files found shall be shown or not.
    ///////////////////////////////////////////////////////////////////////////////
    FileInterface(const std::string& Path,
                  const std::string& FileBasename,
                  const std::string& FileExtension,
                  boolean            ShowListOfFiles = false);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///////////////////////////////////////////////////////////////////////////////
    ~FileInterface();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Getter for the filename.
    ///
    /// \param[in] Index Index of the file.
    ///
    /// \return    Name of the file.
    ///////////////////////////////////////////////////////////////////////////////
    std::string GetFilename(uint64 Index) const;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Getter for the filename including its path.
    ///
    /// \param[in] Index Index of the file.
    ///
    /// \return    Name of the file including its path.
    ///////////////////////////////////////////////////////////////////////////////
    std::string GetFilenameWithPath(uint64 Index) const;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the list of filenames including their paths.
    ///
    /// \return List of filenames including their path.
    ///////////////////////////////////////////////////////////////////////////////
    const std::vector<std::string>& GetListOfFilenamesWithPath() const;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the number of files.
    ///
    /// \return Number of files.
    ///////////////////////////////////////////////////////////////////////////////
    uint64 GetNumberOfFiles() const;
};

#endif // FILEINTERFACE_H
