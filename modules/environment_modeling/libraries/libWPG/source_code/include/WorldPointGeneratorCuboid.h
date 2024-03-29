///////////////////////////////////////////////////////////////////////////////
/// \file  WorldPointGeneratorCuboid.h
///
/// \brief Header file containing the WorldPointGeneratorCuboid class.
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

#ifndef WORLDPOINTGENERATORCUBOID_H
#define WORLDPOINTGENERATORCUBOID_H

#include "WorldPointGeneratorBase.h"

///////////////////////////////////////////////////////////////////////////////
/// \class WorldPointGeneratorCuboid
///
/// \brief Generator for 3d world points inside a cuboid.
///
/// Generator which randomly generates a given number of 3d world points inside
/// a cuboid of predefined extend.
///////////////////////////////////////////////////////////////////////////////
class WorldPointGeneratorCuboid : public WorldPointGeneratorBase
{
protected:
    const float64 m_MinX; ///< Smallest value of the 3d world points inside the cuboid in X-direction.
    const float64 m_MaxX; ///< Largest value of the 3d world points inside the cuboid in X-direction.
    const float64 m_MinY; ///< Smallest value of the 3d world points inside the cuboid in Y-direction.
    const float64 m_MaxY; ///< Largest value of the 3d world points inside the cuboid in Y-direction.
    const float64 m_MinZ; ///< Smallest value of the 3d world points inside the cuboid in Z-direction.
    const float64 m_MaxZ; ///< Largest value of the 3d world points inside the cuboid in Z-direction.

public:
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Constructor.
    ///
    /// \param[in] NumberOfWorldPoints Number of 3d world points.
    /// \param[in] MinX                Smallest value of the 3d world points inside the cuboid in X-direction.
    /// \param[in] MaxX                Largest value of the 3d world points inside the cuboid in X-direction.
    /// \param[in] MinY                Smallest value of the 3d world points inside the cuboid in Y-direction.
    /// \param[in] MaxY                Largest value of the 3d world points inside the cuboid in Y-direction.
    /// \param[in] MinZ                Smallest value of the 3d world points inside the cuboid in Z-direction.
    /// \param[in] MaxZ                Largest value of the 3d world points inside the cuboid in Z-direction.
    /// \param[in] SeedValue           Seed value used to initialize the random number engine.
    ///////////////////////////////////////////////////////////////////////////////
    WorldPointGeneratorCuboid(const uint64  NumberOfWorldPoints = 1000U,
                              const float64 MinX                = -5.0,
                              const float64 MaxX                = 5.0,
                              const float64 MinY                = -2.0,
                              const float64 MaxY                = 2.0,
                              const float64 MinZ                = 3.0,
                              const float64 MaxZ                = 30.0,
                              const uint64  SeedValue           = 0U);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~WorldPointGeneratorCuboid();
};

#endif // WORLDPOINTGENERATORCUBOID_H
