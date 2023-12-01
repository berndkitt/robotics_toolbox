///////////////////////////////////////////////////////////////////////////////
/// \file CSVReader.cpp
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

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/foreach.hpp>
#include <boost/typeof/std/utility.hpp>

#include "CSVReader.h"

CSVReader::CSVReader(const std::string& Filename,
                     const std::string& Separators,
                           boolean      ExtractEmptyRows)
{
    // read file
    std::ifstream File(Filename.c_str());

    // check whether the file exists or not
    if(!File.good())
    {
        throw std::invalid_argument("File " + Filename + " does not exist.");
    }

    // read file row by row
    std::string CurrentRow;
    auto*       CurrentRowSplit = new std::vector<std::string>; // NOLINT(cppcoreguidelines-owning-memory)

    while(!File.eof())
    {
        // get current row
        std::getline(File, CurrentRow);

        // remove last character of the current row
        Trim(CurrentRow);

        // split current row into parts (if not empty)
        if(CurrentRow.length() > 0U)
        {
            // split current row into parts (defined by the separators)
            boost::algorithm::split(*CurrentRowSplit, CurrentRow, boost::algorithm::is_any_of(Separators));
        }

        // save current row
        if((CurrentRow.length() > 0U) || (ExtractEmptyRows))
        {
            m_Entries.push_back(CurrentRowSplit);

            CurrentRowSplit = new std::vector<std::string>; // NOLINT(cppcoreguidelines-owning-memory)
        }
    }
}

CSVReader::~CSVReader()
{
    // delete storage data for entries row by row
    BOOST_FOREACH(std::vector<std::string>* CurrentRow, m_Entries)
    {
        delete CurrentRow; // NOLINT(cppcoreguidelines-owning-memory)
    }
}

std::string CSVReader::GetValue(uint64 RowIndex,
                                uint64 ColumnIndex) const
{
    // check whether the row index is in range or not
    if(RowIndex >= m_Entries.size())
    {
        throw std::out_of_range("RowIndex is out of range.");
    }

    // check whether the column index is in range or not
    if(ColumnIndex >= m_Entries[RowIndex]->size())
    {
        throw std::out_of_range("ColumnIndex is out of range.");
    }

    // return value at the defined position
    return (*m_Entries[RowIndex])[ColumnIndex];
}

uint64 CSVReader::GetMinimumNumberOfColumns() const
{
    uint64 MinColumns = std::numeric_limits<uint64>::max();

    for(BOOST_AUTO(Row, m_Entries.begin()); Row != m_Entries.end(); ++Row)
    {
        MinColumns = std::min(MinColumns, static_cast<uint64>((**Row).size()));
    }

    // return minimum number of columns
    return MinColumns;
}

uint64 CSVReader::GetNumberOfColumns(uint64 RowIndex) const
{
    // check whether the row index is in range or not
    if(RowIndex >= m_Entries.size())
    {
        throw std::out_of_range("RowIndex is out of range.");
    }

    // return number of columns in specified row
    return m_Entries[RowIndex]->size();
}

uint64 CSVReader::GetNumberOfRows() const
{
    return m_Entries.size();
}

void CSVReader::Trim(      std::string& String,
                     const std::string& TrimList)
{
    // find index of last character which is not part of the trim list
    const uint64 IndexFound {String.find_last_not_of(TrimList)};

    // remove last character of the string
    if(IndexFound != std::string::npos)
    {
        String.erase(IndexFound + 1U);
    }
}
