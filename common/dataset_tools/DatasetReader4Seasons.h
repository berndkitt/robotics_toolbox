///////////////////////////////////////////////////////////////////////////////
/// \file DatasetReader4Seasons.h
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

#ifndef DATASETREADER4SEASONS_H
#define DATASETREADER4SEASONS_H

#include "DatasetReaderBase.h"

///////////////////////////////////////////////////////////////////////////////
/// \class DatasetReader4Seasons
///
/// \brief Dataset reader for the 4Seasons datasets.
///
/// This dataset reader can be used to read the information from the "4Seasons"
/// datasets provided by the Technical University of Munich and Artisense (see
/// https://www.4seasons-dataset.com/).
///////////////////////////////////////////////////////////////////////////////
class DatasetReader4Seasons : public DatasetReaderBase
{
public: // public methods
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Constructor.
    ///
    /// \param[in] BaseDirectory Absolute path to the base directory of the dataset.
    /// \param[in] SequenceName  Relative path to the sequence (w.r.t. the base directory).
    ///////////////////////////////////////////////////////////////////////////////
    DatasetReader4Seasons(const std::string& BaseDirectory,
                          const std::string& SequenceName);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///////////////////////////////////////////////////////////////////////////////
    ~DatasetReader4Seasons();

protected: // protected methods
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Extracts the timestamps from the provided file.
    ///
    /// \param[in] FileTimestampsWithPath File containing the timestamps, including the absolute path.
    /// \param[in] ListTimestamps         List of timestamps.
    ///
    /// \return    Number of timestamps found.
    ///////////////////////////////////////////////////////////////////////////////
    static uint64 ExtractTimestamps(const std::filesystem::path& FileTimestampsWithPath,
                                          ListUInt64&            ListTimestamps);
};

#endif // DATASETREADER4SEASONS_H
