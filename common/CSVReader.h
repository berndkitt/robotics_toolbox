///////////////////////////////////////////////////////////////////////////////
/// \file CSVReader.h
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

#ifndef CSVREADER_H
#define CSVREADER_H

#include <string>

#include <GlobalTypesBase.h>

///////////////////////////////////////////////////////////////////////////////
/// \class CSVReader
///
/// \brief Class for reading CSV files.
///////////////////////////////////////////////////////////////////////////////
class CSVReader
{
protected:
    std::vector<std::vector<std::string>*> m_Entries; ///< Entries of the CSV file (outer vector represents the rows, inner vector represents the columns).

public:
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Constructor.
    ///
    /// \param[in] Filename          Filename including its absolute path.
    /// \param[in] Separators        Characters used to separate the entries of a row (e.g. ",", ";",...).
    /// \param[in] ExtractEmptyRows  Flag whether empty rows shall be extracted of not.
    ///////////////////////////////////////////////////////////////////////////////
    CSVReader(const std::string& Filename,
              const std::string& Separators       = ";",
              boolean            ExtractEmptyRows = false);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///////////////////////////////////////////////////////////////////////////////
    ~CSVReader();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Getter for the value at a defined position.
    ///
    /// \param[in] RowIndex    Index of the row.
    /// \param[in] ColumnIndex Index of the column.
    ///
    /// \return    Value at a defined position.
    ///////////////////////////////////////////////////////////////////////////////
    std::string GetValue(uint64 RowIndex,
                         uint64 ColumnIndex) const;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the minimum number of columns.
    ///
    /// \return Minimum number of columns.
    ///////////////////////////////////////////////////////////////////////////////
    uint64 GetMinimumNumberOfColumns() const;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Getter for the number of columns in the defined row.
    ///
    /// \param[in] RowIndex Index of the row.
    ///
    /// \return    Number of columns in the defined row.
    ///////////////////////////////////////////////////////////////////////////////
    uint64 GetNumberOfColumns(uint64 RowIndex) const;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the number of rows.
    ///
    /// \return Number of rows.
    ///////////////////////////////////////////////////////////////////////////////
    uint64 GetNumberOfRows() const;

protected:
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Removes the last character of a string.
    ///
    /// \param[in,out] String   String which shall be trimmed.
    /// \param[in]     TrimList List of characters to be removed.
    ///////////////////////////////////////////////////////////////////////////////
    static void Trim(std::string&       String,
                     const std::string& TrimList = " \t\f\v\n\r");
};

#endif // CSVREADER_H
