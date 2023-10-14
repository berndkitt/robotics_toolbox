///////////////////////////////////////////////////////////////////////////////
/// \file WorldPointGeneratorBase.cpp
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

WorldPointGeneratorBase::~WorldPointGeneratorBase()
{

}

T_ULONG WorldPointGeneratorBase::GetNumberOfWorldPoints() const
{
    return m_NumberOfWorldPoints;
}

const T_ListColumnVectorReal3d& WorldPointGeneratorBase::GetWorldPoints() const
{
    return m_ListOfWorldPoints;
}

WorldPointGeneratorBase::WorldPointGeneratorBase(const T_ULONG NumberOfWorldPoints,
                                                 const T_ULONG SeedValue) : m_NumberOfWorldPoints{NumberOfWorldPoints},
                                                                            m_SeedValue{SeedValue}
{
    // pre-allocate memory
    m_ListOfWorldPoints.resize(m_NumberOfWorldPoints);

    // initialize random number generator
    m_RandomNumberEngine.seed(m_SeedValue);
}
