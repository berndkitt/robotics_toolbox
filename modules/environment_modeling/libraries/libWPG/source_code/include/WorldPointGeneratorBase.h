///////////////////////////////////////////////////////////////////////////////
/// \file  WorldPointGeneratorBase.h
///
/// \brief Header file containing the WorldPointGeneratorBase class.
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

#ifndef WORLDPOINTGENERATORBASE_H
#define WORLDPOINTGENERATORBASE_H

#include <random>

#include <GlobalTypesDerived.h>

///////////////////////////////////////////////////////////////////////////////
/// \class WorldPointGeneratorBase
///
/// \brief Base class for different kinds of world point generators.
///
/// The world point generator can be used to create a point cloud containing a
/// predefined amount of randomly created 3d world points. The shape of the
/// point cloud depends on the class derived from the base class (e.g., points
/// inside a cuboid,...).
///////////////////////////////////////////////////////////////////////////////
class WorldPointGeneratorBase
{
private:
    const uint64               m_NumberOfWorldPointsToCreate; ///< Number of 3d world points to create.
    uint64                     m_NumberOfWorldPoints;         ///< Number of created 3d world points.
    ListColumnVectorFloat64_3d m_ListOfWorldPoints;           ///< List containing the created 3d world points.
    const uint64               m_SeedValue;                   ///< Seed value used to initialize the random number engine.

protected:
    std::mt19937 m_RandomNumberEngine; ///< Random number engine used to generate the 3d world points.

public:
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Constructor.
    ///
    /// \param[in] NumberOfWorldPointsToCreate Number of 3d world points to create.
    /// \param[in] SeedValue                   Seed value used to initialize the random number engine.
    ///////////////////////////////////////////////////////////////////////////////
    WorldPointGeneratorBase(const uint64 NumberOfWorldPointsToCreate = 1000U,
                            const uint64 SeedValue                   = 0U);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~WorldPointGeneratorBase();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Generate the point cloud.
    ///////////////////////////////////////////////////////////////////////////////
    void GeneratePointCloud();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the number of 3d world points.
    ///
    /// \return Number of 3d world points.
    ///////////////////////////////////////////////////////////////////////////////
    uint64 GetNumberOfWorldPoints() const;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the list containing the 3d world points.
    ///
    /// \return List containing the 3d world points.
    ///////////////////////////////////////////////////////////////////////////////
    const ListColumnVectorFloat64_3d& GetWorldPoints() const;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Create a single world point.
    ///
    /// This function randomly creates a single 3d world point based on the
    /// underlying shape of the point cloud. The function needs to be implemented
    /// in the derived class.
    ///
    /// \param[out] WorldPoint Randomly created 3d world point.
    ///////////////////////////////////////////////////////////////////////////////
    virtual void CreateWorldPoint(ColumnVectorFloat64_3d& WorldPoint) = 0;
};

#endif // WORLDPOINTGENERATORBASE_H
