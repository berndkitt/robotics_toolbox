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
    uint64                     m_NumberOfWorldPoints; ///< Number of created 3d world points.
    ListColumnVectorFloat64_3d m_ListOfWorldPoints;   ///< List containing the created 3d world points.

protected:
    std::mt19937 m_RandomNumberEngine; ///< Random number engine used to generate the 3d world points.

public:
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Constructor.
    ///
    /// Initializes the member variables of the class and allocates memory for the
    /// 3d world points.
    ///
    /// \startuml
    /// start
    /// :Initialize m_NumberOfWorldPoints with 0;
    /// :Allocate memory for m_ListOfWorldPoints and set all points to (0.0, 0.0, 0.0);
    /// :Initialize m_RandomNumberEngine with SeedValue;
    /// stop
    /// \enduml
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
    /// \brief Generates the point cloud.
    ///
    /// The function loops over the list of 3d world points and randomly creates a
    /// point by calling the CreateWorldPoint method. This method needs to be
    /// implemented in the derived class.
    ///
    /// \startuml
    /// start
    /// repeat :For all points in m_ListOfWorldPoints;
    ///     :Create and store world point;
    ///     :Increment m_NumberOfWorldPoints;
    /// repeat while (Next point)
    /// stop
    /// \enduml
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
    /// \brief Creates a single world point.
    ///
    /// The function randomly creates a single 3d world point based on the
    /// underlying shape of the point cloud. The function needs to be implemented
    /// in the derived class.
    ///
    /// \param[out] WorldPoint Randomly created 3d world point.
    ///////////////////////////////////////////////////////////////////////////////
    virtual void CreateWorldPoint(ColumnVectorFloat64_3d& WorldPoint) = 0;
};

#endif // WORLDPOINTGENERATORBASE_H
