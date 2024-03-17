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
/// \brief Class to create 3d world points inside a cuboid.
///
/// The world point generator can be used to create a point cloud containing a
/// predefined amount of randomly created 3d world points. The 3d world points
/// created will be located inside a cuboid of predefined extend.
///////////////////////////////////////////////////////////////////////////////
class WorldPointGeneratorCuboid : public WorldPointGeneratorBase
{
private:
    std::uniform_real_distribution<float64> m_UniformDistributionX; ///< Uniform distribution for X-coordinate of the 3d world points.
    std::uniform_real_distribution<float64> m_UniformDistributionY; ///< Uniform distribution for Y-coordinate of the 3d world points.
    std::uniform_real_distribution<float64> m_UniformDistributionZ; ///< Uniform distribution for Z-coordinate of the 3d world points.

public:
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Constructor.
    ///
    /// Initializes the member variables of the class and creates uniform
    /// distributions in X-, Y-, and Z-direction which will be used to create the
    /// 3d world points inside the cuboid.
    /// After creating the object of the class, the function GeneratePointCloud
    /// needs to be called. Otherwise, the number of 3d world points will be 0 and
    /// the list of 3d world points will only contain points with the coordinates
    /// (0.0, 0.0, 0.0).
    ///
    /// \startuml
    /// start
    /// :Initialize WorldPointGeneratorBase class;
    /// :Create uniform distribution m_UniformDistributionX in the range [MinX, MaxX];
    /// :Create uniform distribution m_UniformDistributionY in the range [MinY, MaxY];
    /// :Create uniform distribution m_UniformDistributionZ in the range [MinZ, MaxZ];
    /// stop
    /// \enduml
    ///
    /// \param[in] NumberOfWorldPointsToCreate Number of 3d world points.
    /// \param[in] MinX                        Smallest value of the 3d world points inside the cuboid in X-direction.
    /// \param[in] MaxX                        Largest value of the 3d world points inside the cuboid in X-direction.
    /// \param[in] MinY                        Smallest value of the 3d world points inside the cuboid in Y-direction.
    /// \param[in] MaxY                        Largest value of the 3d world points inside the cuboid in Y-direction.
    /// \param[in] MinZ                        Smallest value of the 3d world points inside the cuboid in Z-direction.
    /// \param[in] MaxZ                        Largest value of the 3d world points inside the cuboid in Z-direction.
    /// \param[in] SeedValue                   Seed value used to initialize the random number engine.
    ///////////////////////////////////////////////////////////////////////////////
    WorldPointGeneratorCuboid(const uint64  NumberOfWorldPointsToCreate = 1000U,
                              const float64 MinX                        = -5.0,
                              const float64 MaxX                        = 5.0,
                              const float64 MinY                        = -2.0,
                              const float64 MaxY                        = 2.0,
                              const float64 MinZ                        = 3.0,
                              const float64 MaxZ                        = 30.0,
                              const uint64  SeedValue                   = 0U);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Creates a single world point.
    ///
    /// The function randomly creates a single 3d world point inside a cuboid of
    /// predefined extend.
    ///
    /// \param[out] WorldPoint Randomly created 3d world point.
    ///////////////////////////////////////////////////////////////////////////////
    virtual void CreateWorldPoint(ColumnVectorFloat64_3d& WorldPoint) override;
};

#endif // WORLDPOINTGENERATORCUBOID_H
