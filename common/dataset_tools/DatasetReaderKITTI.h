///////////////////////////////////////////////////////////////////////////////
/// \file DatasetReaderKITTI.h
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

#ifndef DATASETREADERKITTI_H
#define DATASETREADERKITTI_H

#include "DatasetReaderBase.h"

///////////////////////////////////////////////////////////////////////////////
/// \class DatasetReaderKITTI
///
/// \brief Dataset reader for the KITTI dataset.
///
/// This dataset reader can be used to read the information from the KITTI
/// Visual Odometry dataset provided by the Karlsruhe Institute of Technology
/// and the Toyota Technological Institute (see
/// https://www.cvlibs.net/datasets/kitti/eval_odometry.php).
///////////////////////////////////////////////////////////////////////////////
class DatasetReaderKITTI : public DatasetReaderBase
{
public:
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Constructor.
    ///
    /// \param[in] BaseDirectory Absolute path to the base directory of the dataset.
    /// \param[in] SequenceName  Relative path to the sequence (w.r.t. the base directory).
    ///////////////////////////////////////////////////////////////////////////////
    DatasetReaderKITTI(const std::string& BaseDirectory,
                       const std::string& SequenceName);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///////////////////////////////////////////////////////////////////////////////
    ~DatasetReaderKITTI();

protected:
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief      Extracts the projection matrices from the provided file.
    ///
    /// \param[in]  FilenameCalibration         File containing calibration of the stereo camera.
    /// \param[out] ProjectionMatrixStereoLeft  Projection matrix of the left stereo camera.
    /// \param[out] ProjectionMatrixStereoRight Projection matrix of the left stereo camera.
    ///////////////////////////////////////////////////////////////////////////////
    static void ExtractProjectionMatrices(const std::string& FilenameCalibration,
                                          MatrixFloat64_3x4& ProjectionMatrixStereoLeft,
                                          MatrixFloat64_3x4& ProjectionMatrixStereoRight);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief      Extracts the timestamps from the provided file.
    ///
    /// \param[in]  FileTimestampsWithPath File containing the timestamps, including the absolute path.
    /// \param[out] ListTimestamps         List of timestamps.
    ///
    /// \return     Number of timestamps found.
    ///////////////////////////////////////////////////////////////////////////////
    static uint64 ExtractTimestamps(const std::filesystem::path& FileTimestampsWithPath,
                                    ListUInt64&                  ListTimestamps);
};

#endif // DATASETREADERKITTI_H
