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

WorldPointGeneratorBase::WorldPointGeneratorBase(const uint64 NumberOfWorldPointsToCreate,
                                                 const uint64 SeedValue) :
    m_NumberOfWorldPointsToCreate{NumberOfWorldPointsToCreate},
    m_NumberOfWorldPoints{0},
    m_SeedValue{SeedValue}
{
    m_ListOfWorldPoints.resize(m_NumberOfWorldPointsToCreate);
    m_RandomNumberEngine.seed(m_SeedValue);
}

WorldPointGeneratorBase::~WorldPointGeneratorBase()
{
}

void WorldPointGeneratorBase::GeneratePointCloud()
{
    for(auto& CurrentWorldPoint : m_ListOfWorldPoints)
    {
        CreateWorldPoint(CurrentWorldPoint);
        m_NumberOfWorldPoints++;
    }
}

uint64 WorldPointGeneratorBase::GetNumberOfWorldPoints() const
{
    return m_NumberOfWorldPoints;
}

const ListColumnVectorFloat64_3d& WorldPointGeneratorBase::GetWorldPoints() const
{
    return m_ListOfWorldPoints;
}
