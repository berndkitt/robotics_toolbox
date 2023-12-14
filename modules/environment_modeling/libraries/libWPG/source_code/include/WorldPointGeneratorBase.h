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
///////////////////////////////////////////////////////////////////////////////
class WorldPointGeneratorBase
{
protected: // protected attributes
    const uint64                     m_NumberOfWorldPoints; ///< Number of 3d world points.
          ListColumnVectorFloat64_3d m_ListOfWorldPoints;   ///< List containing the 3d world points.
          std::mt19937               m_RandomNumberEngine;  ///< Random number engine used to generate the 3d world points.
    const uint64                     m_SeedValue;           ///< Seed value used to initialize the random number engine.

public: // public methods
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~WorldPointGeneratorBase();

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

protected: // protected methods
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Constructor.
    ///
    /// \param[in] NumberOfWorldPoints Number of 3d world points.
    /// \param[in] SeedValue           Seed value used to initialize the random number engine.
    ///
    /// \remark    Protected constructor to prevent creating objects of that class.
    ///////////////////////////////////////////////////////////////////////////////
    WorldPointGeneratorBase(const uint64 NumberOfWorldPoints = 1000U,
                            const uint64 SeedValue           = 0U);
};

#endif // WORLDPOINTGENERATORBASE_H
