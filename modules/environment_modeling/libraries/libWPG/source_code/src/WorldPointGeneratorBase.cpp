///////////////////////////////////////////////////////////////////////////////
/// \file  WorldPointGeneratorBase.cpp
///
/// \brief Source file containing the WorldPointGeneratorBase class.
///////////////////////////////////////////////////////////////////////////////

/*
This file is part of the Robotics Toolbox.

Copyright (C) 2021

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

#include "../include/WorldPointGeneratorBase.h"

WorldPointGeneratorBase::WorldPointGeneratorBase(const uint32 NumberOfWorldPointsToCreate, // NOLINT(cert-msc32-c, cert-msc51-cpp)
                                                 const uint32 SeedValue) :
    m_NumberOfWorldPoints{0},
    m_ListOfWorldPoints(NumberOfWorldPointsToCreate, ColumnVectorFloat64_3d::Zero())
{
    m_RandomNumberEngine.seed(SeedValue);
}

// cppcheck-suppress[unusedFunction]
void WorldPointGeneratorBase::GeneratePointCloud()
{
    for(auto& CurrentWorldPoint : m_ListOfWorldPoints)
    {
        CreateWorldPoint(CurrentWorldPoint);
        m_NumberOfWorldPoints++;
    }
}

// cppcheck-suppress[unusedFunction]
uint32 WorldPointGeneratorBase::GetNumberOfWorldPoints() const
{
    return m_NumberOfWorldPoints;
}

// cppcheck-suppress[unusedFunction]
const ListColumnVectorFloat64_3d& WorldPointGeneratorBase::GetWorldPoints() const
{
    return m_ListOfWorldPoints;
}
