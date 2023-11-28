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

#include <opencv2/core/core.hpp>

#include "../GlobalTypesDerived.h"

///////////////////////////////////////////////////////////////////////////////
/// \struct ImageInformation
///
/// \brief  Container for the image information.
///////////////////////////////////////////////////////////////////////////////
struct ImageInformation
{
    boolean     IsValid;                    ///< Flag whether the information is valid or not.
    uint64      Timestamp;                  ///< Timestamp of the image in nanoseconds.
    std::string FilenameWithAbsolutePath;   ///< Filename of the image including its absolute path.
    cv::Mat     ImageGrayscale;             ///< Grayscale image.
};

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
    uint32                   m_HeightImagesStereo;                      ///< Height of the stereo camera images.
    uint32                   m_WidthImagesStereo;                       ///< Width of the stereo camera images.

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

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the height of the stereo camera images.
    ///
    /// \return Height of the stereo camera images.
    ///////////////////////////////////////////////////////////////////////////////
    uint32 GetImageHeightStereoImages() const;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief      Getter for the information of the left stereo camera image.
    ///
    /// \param[in]  Index Index of the image.
    /// \param[out] Index Image information of the left stereo camera image.
    ///////////////////////////////////////////////////////////////////////////////
    void GetImageInformationStereoLeft(uint64            Index,
                                       ImageInformation& ImageInformation) const;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief      Getter for the information of the right stereo camera image.
    ///
    /// \param[in]  Index Index of the image.
    /// \param[out] Index Image information of the right stereo camera image.
    ///////////////////////////////////////////////////////////////////////////////
    void GetImageInformationStereoRight(uint64            Index,
                                        ImageInformation& ImageInformation) const;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the width of the stereo camera images.
    ///
    /// \return Width of the stereo camera images.
    ///////////////////////////////////////////////////////////////////////////////
    uint32 GetImageWidthStereoImages() const;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the number of frames in the dataset.
    ///
    /// \return Number of frames in the dataset.
    ///////////////////////////////////////////////////////////////////////////////
    uint64 GetNumberOfFrames() const;

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

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief      Extracts the dimensions of the image.
    ///
    /// \param[in]  FilenameImage Filename of the image including its absolute path.
    /// \param[out] ImageHeight   Height of the image.
    /// \param[out] ImageWidth    Width of the image.
    ///////////////////////////////////////////////////////////////////////////////
    static void ExtractImagesDimensions(const std::string& FilenameImage,
                                              uint32&      ImageHeight,
                                              uint32&      ImageWidth);
};

#endif // DATASETREADERBASE_H
