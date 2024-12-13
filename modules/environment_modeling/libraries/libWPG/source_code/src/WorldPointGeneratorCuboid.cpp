///////////////////////////////////////////////////////////////////////////////
/// \file  WorldPointGeneratorCuboid.cpp
///
/// \brief Source file containing the WorldPointGeneratorCuboid class.
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

WorldPointGeneratorCuboid::WorldPointGeneratorCuboid(const uint32  NumberOfWorldPointsToGenerate,
                                                     const float64 MinX,
                                                     const float64 MaxX,
                                                     const float64 MinY,
                                                     const float64 MaxY,
                                                     const float64 MinZ,
                                                     const float64 MaxZ,
                                                     const uint32  SeedValue) :
    WorldPointGeneratorBase(NumberOfWorldPointsToGenerate, SeedValue),
    m_UniformDistributionX(MinX, MaxX),
    m_UniformDistributionY(MinY, MaxY),
    m_UniformDistributionZ(MinZ, MaxZ)
{
    GeneratePointCloud();
}

WorldPointGeneratorCuboid::WorldPointGeneratorCuboid(const WorldPointGeneratorCuboid& Src) :
    WorldPointGeneratorBase{Src},
    m_UniformDistributionX{Src.m_UniformDistributionX},
    m_UniformDistributionY{Src.m_UniformDistributionY},
    m_UniformDistributionZ{Src.m_UniformDistributionZ}
{
}

WorldPointGeneratorCuboid::WorldPointGeneratorCuboid(WorldPointGeneratorCuboid&& Src) noexcept :
    WorldPointGeneratorBase{std::move(Src)},
    m_UniformDistributionX{Src.m_UniformDistributionX},
    m_UniformDistributionY{Src.m_UniformDistributionY},
    m_UniformDistributionZ{Src.m_UniformDistributionZ}
{
}

WorldPointGeneratorCuboid& WorldPointGeneratorCuboid::operator=(const WorldPointGeneratorCuboid& Rhs)
{
    if(this != &Rhs)
    {
        WorldPointGeneratorBase::operator=(Rhs);
        m_UniformDistributionX = Rhs.m_UniformDistributionX;
        m_UniformDistributionY = Rhs.m_UniformDistributionY;
        m_UniformDistributionZ = Rhs.m_UniformDistributionZ;
    }

    return *this;
}

WorldPointGeneratorCuboid& WorldPointGeneratorCuboid::operator=(WorldPointGeneratorCuboid&& Rhs) noexcept
{
    if(this != &Rhs)
    {
        WorldPointGeneratorBase::operator=(std::move(Rhs));
        m_UniformDistributionX = Rhs.m_UniformDistributionX; // NOLINT(bugprone-use-after-move)
        m_UniformDistributionY = Rhs.m_UniformDistributionY;
        m_UniformDistributionZ = Rhs.m_UniformDistributionZ;
    }

    return *this;
}

void WorldPointGeneratorCuboid::GenerateWorldPoint(ColumnVectorFloat64_3d& WorldPoint)
{
    const float64 CurrentCoordinateX{m_UniformDistributionX(m_RandomNumberEngine)};
    const float64 CurrentCoordinateY{m_UniformDistributionY(m_RandomNumberEngine)};
    const float64 CurrentCoordinateZ{m_UniformDistributionZ(m_RandomNumberEngine)};

    WorldPoint(0) = CurrentCoordinateX;
    WorldPoint(1) = CurrentCoordinateY;
    WorldPoint(2) = CurrentCoordinateZ;
}
