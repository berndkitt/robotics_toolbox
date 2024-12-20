////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file WorldPointGeneratorBase.cpp
///
/// \brief Source file containing the WorldPointGeneratorBase class.
////////////////////////////////////////////////////////////////////////////////////////////////////

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

WorldPointGeneratorBase::WorldPointGeneratorBase(const uint32 NumberOfWorldPointsToGenerate, // NOLINT(cert-msc32-c, cert-msc51-cpp)
                                                 const uint32 SeedValue) :
    m_NumberOfWorldPoints{0U},
    m_ListOfWorldPoints(NumberOfWorldPointsToGenerate, ColumnVectorFloat64_3d::Zero())
{
    m_RandomNumberEngine.seed(SeedValue);
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

WorldPointGeneratorBase::WorldPointGeneratorBase(const WorldPointGeneratorBase& Src) :
    m_RandomNumberEngine{Src.m_RandomNumberEngine},
    m_NumberOfWorldPoints{Src.m_NumberOfWorldPoints},
    m_ListOfWorldPoints{Src.m_ListOfWorldPoints}
{
}

WorldPointGeneratorBase::WorldPointGeneratorBase(WorldPointGeneratorBase&& Src) noexcept :
    m_RandomNumberEngine{Src.m_RandomNumberEngine},
    m_NumberOfWorldPoints{Src.m_NumberOfWorldPoints},
    m_ListOfWorldPoints{std::move(Src.m_ListOfWorldPoints)}
{
}

WorldPointGeneratorBase& WorldPointGeneratorBase::operator=(const WorldPointGeneratorBase& Rhs)
{
    if(this != &Rhs)
    {
        m_RandomNumberEngine  = Rhs.m_RandomNumberEngine;
        m_NumberOfWorldPoints = Rhs.m_NumberOfWorldPoints;
        m_ListOfWorldPoints   = Rhs.m_ListOfWorldPoints;
    }

    return *this;
}

WorldPointGeneratorBase& WorldPointGeneratorBase::operator=(WorldPointGeneratorBase&& Rhs) noexcept
{
    if(this != &Rhs)
    {
        m_RandomNumberEngine  = Rhs.m_RandomNumberEngine;
        m_NumberOfWorldPoints = Rhs.m_NumberOfWorldPoints;
        m_ListOfWorldPoints   = std::move(Rhs.m_ListOfWorldPoints);
    }

    return *this;
}

// cppcheck-suppress[unusedFunction]
void WorldPointGeneratorBase::GeneratePointCloud()
{
    for(auto& CurrentWorldPoint : m_ListOfWorldPoints)
    {
        GenerateWorldPoint(CurrentWorldPoint);
        m_NumberOfWorldPoints++;
    }
}
