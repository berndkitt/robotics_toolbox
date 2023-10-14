///////////////////////////////////////////////////////////////////////////////
/// \file WorldPointGeneratorCuboid.cpp
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

#include "../include/WorldPointGeneratorCuboid.h"

WorldPointGeneratorCuboid::WorldPointGeneratorCuboid(const T_ULONG NumberOfWorldPoints,
                                                     const T_REAL  MinX,
                                                     const T_REAL  MaxX,
                                                     const T_REAL  MinY,
                                                     const T_REAL  MaxY,
                                                     const T_REAL  MinZ,
                                                     const T_REAL  MaxZ,
                                                     const T_ULONG SeedValue) : WorldPointGeneratorBase(NumberOfWorldPoints, SeedValue),
                                                                                m_MinX{MinX},
                                                                                m_MaxX{MaxX},
                                                                                m_MinY{MinY},
                                                                                m_MaxY{MaxY},
                                                                                m_MinZ{MinZ},
                                                                                m_MaxZ{MaxZ}
{
    // create uniform distributions
    std::uniform_real_distribution<T_REAL> UniformDistributionX(m_MinX, m_MaxX);
    std::uniform_real_distribution<T_REAL> UniformDistributionY(m_MinY, m_MaxY);
    std::uniform_real_distribution<T_REAL> UniformDistributionZ(m_MinZ, m_MaxZ);

    // randomly generate the 3d world points
    T_ColumnVectorReal3d CurrentWorldPoint;

    for(T_ULONG i_WorldPoint = 0; i_WorldPoint < m_NumberOfWorldPoints; i_WorldPoint++)
    {
        // randomly generate the coordinates of the current 3d world point
        const T_REAL CurrentCoordinateX = UniformDistributionX(m_RandomNumberEngine);
        const T_REAL CurrentCoordinateY = UniformDistributionY(m_RandomNumberEngine);
        const T_REAL CurrentCoordinateZ = UniformDistributionZ(m_RandomNumberEngine);

        // add the current 3d world point
        CurrentWorldPoint(0) = CurrentCoordinateX;
        CurrentWorldPoint(1) = CurrentCoordinateY;
        CurrentWorldPoint(2) = CurrentCoordinateZ;

        m_ListOfWorldPoints[i_WorldPoint] = CurrentWorldPoint;
    }
}

WorldPointGeneratorCuboid::~WorldPointGeneratorCuboid()
{

}
