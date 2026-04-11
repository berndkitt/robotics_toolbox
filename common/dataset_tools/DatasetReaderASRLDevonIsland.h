///////////////////////////////////////////////////////////////////////////////
/// \file DatasetReaderASRLDevonIsland.h
///////////////////////////////////////////////////////////////////////////////

/*
This file is part of the Robotics Toolbox.

Copyright (C) 2024

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

#ifndef DATASETREADERASRLDEVONISLAND_H
#define DATASETREADERASRLDEVONISLAND_H

#include "DatasetReaderBase.h"

///////////////////////////////////////////////////////////////////////////////
/// \enum  ASRLImageType
///
/// \brief Defines the image type to use.
///////////////////////////////////////////////////////////////////////////////
enum ASRLImageType
{
    ASRLColor, ///< Use color images of the dataset.
    ASRLGrey   ///< Use grey images of the dataset.
};

///////////////////////////////////////////////////////////////////////////////
/// \class DatasetReaderASRLDevonIsland
///
/// \brief Dataset reader for the ASRL Devon Island Rover Navigation dataset.
///
/// This dataset reader can be used to read the information from the "Devon
/// Island Rover Navigation" dataset provided by the Autonomous Space Robotics
/// Laboratory (ASRL) of the University of Toronto (see
/// http://asrl.utias.utoronto.ca/datasets/devon-island-rover-navigation/rover-traverse.html).
///////////////////////////////////////////////////////////////////////////////
class DatasetReaderASRLDevonIsland : public DatasetReaderBase
{
public:
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Constructor.
    ///
    /// \param[in] BaseDirectory Absolute path to the base directory of the dataset.
    /// \param[in] SequenceName  Relative path to the sequence (w.r.t. the base directory).
    ///////////////////////////////////////////////////////////////////////////////
    DatasetReaderASRLDevonIsland(const std::string&  BaseDirectory,
                                 const std::string&  SequenceName,
                                 const ASRLImageType ImageType);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///////////////////////////////////////////////////////////////////////////////
    ~DatasetReaderASRLDevonIsland();

protected:
    ASRLImageType m_ImageType; ///< Image type to be used (either color or grey).

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Extracts the timestamps from the provided file.
    ///
    /// \param[in] TimestampParts Parts of the timestamp (years, months, days, hours, minutes, seconds, milliseconds).
    ///
    /// \return    Timestamp in nanoseconds.
    ///////////////////////////////////////////////////////////////////////////////
    static uint64 ConvertTimestampIntoNanoSeconds(const std::vector<std::string>& TimestampParts);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief      Extracts the timestamps from the provided file.
    ///
    /// \param[in]  FileTimestampsWithPath File containing the timestamps, including the absolute path.
    /// \param[out] ListTimestamps         List of timestamps.
    ///
    /// \return     Number of timestamps found.
    ///////////////////////////////////////////////////////////////////////////////
    uint64 ExtractTimestamps(const std::filesystem::path& FileTimestampsWithPath,
                             ListUInt64&                  ListTimestamps);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief      Filter the timestamps to get the relevant timestamps only.
    ///
    /// \param[in]  ListTimestampsAll List containing all timestamps of the dataset.
    /// \param[out] ListTimestamps    List of timestamps.
    ///
    /// \return     Number of timestamps found.
    ///////////////////////////////////////////////////////////////////////////////
    uint64 FilterTimestamps(const ListUInt64& ListTimestampsAll,
                            ListUInt64&       ListTimestamps) const;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief      Sets the projection matrices based on the known values.
    ///
    /// \param[out] ProjectionMatrixStereoLeft  Projection matrix of the left stereo camera.
    /// \param[out] ProjectionMatrixStereoRight Projection matrix of the left stereo camera.
    ///////////////////////////////////////////////////////////////////////////////
    void SetProjectionMatrices(MatrixFloat64_3x4& ProjectionMatrixStereoLeft,
                               MatrixFloat64_3x4& ProjectionMatrixStereoRight);
};

#endif // DATASETREADERASRLDEVONISLAND_H
