///////////////////////////////////////////////////////////////////////////////
/// \file WorldPointGeneratorBase.h
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
/// The world point generator can be used to generate a point cloud containing
/// a predefined amount of randomly generated 3d world points. The shape of the
/// point cloud depends on the class derived from the base class (e.g., points
/// inside a cuboid,...).
///////////////////////////////////////////////////////////////////////////////
class WorldPointGeneratorBase
{
public:
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Constructor.
    ///
    /// Initializes the member variables of the class and allocates memory for the
    /// 3d world points.
    ///
    /// \param[in] NumberOfWorldPointsToGenerate Number of 3d world points to generate.
    /// \param[in] SeedValue                     Seed value used to initialize the random number engine.
    ///////////////////////////////////////////////////////////////////////////////
    WorldPointGeneratorBase(const uint32 NumberOfWorldPointsToGenerate = 1000U,
                            const uint32 SeedValue                     = 0U);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Getter for the number of 3d world points.
    ///
    /// \return Number of 3d world points.
    ///////////////////////////////////////////////////////////////////////////////
    uint32 GetNumberOfWorldPoints() const;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Getter for the list containing the 3d world points.
    ///
    /// \return List containing the 3d world points.
    ///////////////////////////////////////////////////////////////////////////////
    const ListColumnVectorFloat64_3d& GetWorldPoints() const;

protected:
    std::mt19937 m_RandomNumberEngine; ///< Random number engine used to generate the 3d world points.

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Copy constructor.
    ///
    /// Copies a WorldPointGeneratorBase object.
    ///
    /// \param[in] Src Source object to copy.
    ///////////////////////////////////////////////////////////////////////////////
    WorldPointGeneratorBase(const WorldPointGeneratorBase& Src);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Move constructor.
    ///
    /// Moves a WorldPointGeneratorBase object.
    ///
    /// \param[in] Src Source object to move.
    ///////////////////////////////////////////////////////////////////////////////
    WorldPointGeneratorBase(WorldPointGeneratorBase&& Src) noexcept;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~WorldPointGeneratorBase() = default;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Copy assignment operator.
    ///
    /// Copies a WorldPointGeneratorBase object by assigning it to a new object.
    ///
    /// \param[in] Rhs Source object to copy.
    ///
    /// \return Copied object.
    ///////////////////////////////////////////////////////////////////////////////
    WorldPointGeneratorBase& operator=(const WorldPointGeneratorBase& Rhs);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Move assignment operator.
    ///
    /// Moves a WorldPointGeneratorBase object by assigning it to a new object.
    ///
    /// \param[in] Rhs Source object to move.
    ///
    /// \return Moved object.
    ///////////////////////////////////////////////////////////////////////////////
    WorldPointGeneratorBase& operator=(WorldPointGeneratorBase&& Rhs) noexcept;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Generates the point cloud.
    ///
    /// The function loops over the list of 3d world points and randomly generates
    /// a point by calling the GenerateWorldPoint method.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void GeneratePointCloud();

private:
    uint32                     m_NumberOfWorldPoints; ///< Number of generated 3d world points.
    ListColumnVectorFloat64_3d m_ListOfWorldPoints;   ///< List containing the generated 3d world points.

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Generates a single world point.
    ///
    /// The function randomly generates a single 3d world point based on the
    /// underlying shape of the point cloud. The function needs to be implemented
    /// in the derived class.
    ///
    /// \param[out] WorldPoint Randomly generated 3d world point.
    ///////////////////////////////////////////////////////////////////////////////
    virtual void GenerateWorldPoint(ColumnVectorFloat64_3d& WorldPoint) = 0;
};

#endif // WORLDPOINTGENERATORBASE_H
