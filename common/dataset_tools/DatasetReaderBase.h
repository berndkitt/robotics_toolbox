///////////////////////////////////////////////////////////////////////////////
/// \file DatasetReaderBase.h
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

#ifndef DATASETREADERBASE_H
#define DATASETREADERBASE_H

#include <filesystem>

#include "GlobalTypesDerived.h"

///////////////////////////////////////////////////////////////////////////////
/// \class DatasetReaderBase
///
/// \brief Base class for different kinds of dataset readers.
///////////////////////////////////////////////////////////////////////////////
class DatasetReaderBase
{
protected: // protected attributes
    std::filesystem::path    m_BaseDirectory;                           ///< Absolute path to the base directory of the dataset.
    std::filesystem::path    m_SequenceName;                            ///< Relative path to the sequence (w.r.t. the base directory).
    std::filesystem::path    m_RelativePathImagesStereoLeft;            ///< Relative path to the left stereo camera images (w.r.t. the sequence).
    std::filesystem::path    m_RelativePathImagesStereoRight;           ///< Relative path to the right stereo camera images (w.r.t. the sequence).
    std::filesystem::path    m_AbsolutePathImagesStereoLeft;            ///< Absolute path to the left stereo camera images.
    std::filesystem::path    m_AbsolutePathImagesStereoRight;           ///< Absolute path to the right stereo camera images.
    std::string              m_FileBasenameImagesStereoLeft;            ///< Basename of the left stereo camera images.
    std::string              m_FileBasenameImagesStereoRight;           ///< Basename of the right stereo camera images.
    std::string              m_FileExtensionImagesStereoLeft;           ///< File extension of the left stereo camera images.
    std::string              m_FileExtensionImagesStereoRight;          ///< File extension of the right stereo camera images.
    uint64                   m_NumberOfImagesStereoLeft;                ///< Number of left stereo camera images.
    uint64                   m_NumberOfImagesStereoRight;               ///< Number of right stereo camera images.
    std::vector<std::string> m_FilenamesWithPathImagesStereoLeft;       ///< List of filenames including the absolute path to the left stereo camera images.
    std::vector<std::string> m_FilenamesWithPathImagesStereoRight;      ///< List of filenames including the absolute path to the right stereo camera images.
    std::filesystem::path    m_FilenameTimestampsImagesStereoLeft;      ///< Name of the file containing the timestamps of the left stereo camera images.
    std::filesystem::path    m_FilenameTimestampsImagesStereoRight;     ///< Name of the file containing the timestamps of the right stereo camera images.
    std::filesystem::path    m_AbsolutePathTimestampsImagesStereoLeft;  ///< Absolute path to the file containing the timestamps of the left stereo camera images.
    std::filesystem::path    m_AbsolutePathTimestampsImagesStereoRight; ///< Absolute path to the file containing the timestamps of the right stereo camera images.
    ListUInt64               m_TimestampsImagesStereoLeftNanoseconds;   ///< List of timestamps of the left stereo camera images (in nanoseconds).
    ListUInt64               m_TimestampsImagesStereoRightNanoseconds;  ///< List of timestamps of the right stereo camera images (in nanoseconds).
    uint64                   m_NumberOfTimestampsStereoLeft;            ///< Number of left stereo camera images.
    uint64                   m_NumberOfTimestampsStereoRight;           ///< Number of right stereo camera images.

public: // public methods
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Constructor.
    ///
    /// \param[in] BaseDirectory Absolute path to the base directory of the dataset.
    /// \param[in] SequenceName  Relative path to the sequence (w.r.t. the base directory).
    ///////////////////////////////////////////////////////////////////////////////
    DatasetReaderBase(const std::string& BaseDirectory,
                      const std::string& SequenceName);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~DatasetReaderBase();

protected: // protected methods
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief      Extracts the list of files in a directory.
    ///
    /// \param[in]  Path                  Absolute path to the files.
    /// \param[in]  FileBasename          Basename of the files to be extracted.
    /// \param[in]  FileExtension         Extension of the files to be extracted.
    /// \param[out] ListFilenamesWithPath List of filenames found, including the absolute path.
    /// \param[out] NumberOfFilesFound    Number of files found.
    ///////////////////////////////////////////////////////////////////////////////
    static void ExtractFilesInDirectory(const std::filesystem::path&    Path,
                                        const std::string&              FileBasename,
                                        const std::string&              FileExtension,
                                              std::vector<std::string>& ListFilenamesWithPath,
                                              uint64&                   NumberOfFilesFound);
};

#endif // DATASETREADERBASE_H
