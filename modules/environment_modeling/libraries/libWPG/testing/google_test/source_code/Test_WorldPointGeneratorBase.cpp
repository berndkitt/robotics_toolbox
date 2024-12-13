///////////////////////////////////////////////////////////////////////////////
/// \file  Test_WorldPointGeneratorBase.cpp
///
/// \brief Source file containing the unit tests for WorldPointGeneratorBase.
///////////////////////////////////////////////////////////////////////////////

/*
This file is part of the Robotics Toolbox.

Copyright (C) 2024

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

#include <gtest/gtest.h>

#include "../../../source_code/include/WorldPointGeneratorBase.h"

// definition of macros for the unit tests
#define TEST_COPYASSIGNMENTOPERATOR_SELFASSIGNMENT TEST_F ///< Define to get a unique test name.
#define TEST_MOVEASSIGNMENTOPERATOR_SELFASSIGNMENT TEST_F ///< Define to get a unique test name.

///////////////////////////////////////////////////////////////////////////////
/// \class WorldPointGeneratorBaseDummy
///
/// \brief Class to generate 3d world points.
///
/// This is a dummy class only which enables unit tests for both, the copy
/// assignment operator and the move assignment operator, of the
/// WorldPointGeneratorBase class in case a self assignment happens.
///////////////////////////////////////////////////////////////////////////////
class WorldPointGeneratorBaseDummy : public WorldPointGeneratorBase
{
public:
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Constructor.
    ///
    /// Initializes the member variables of the class and generates a set of world
    /// points. All world points do have the same coordinates as this is a dummy
    /// class for unit tests only.
    ///
    /// \param[in] NumberOfWorldPointsToGenerate Number of 3d world points to generate.
    /// \param[in] SeedValue                     Seed value used to initialize the random number engine.
    ///////////////////////////////////////////////////////////////////////////////
    inline WorldPointGeneratorBaseDummy(const uint32 NumberOfWorldPointsToGenerate = 1000U,
                                        const uint32 SeedValue                     = 0U) :
        WorldPointGeneratorBase(NumberOfWorldPointsToGenerate, SeedValue)
    {
        GeneratePointCloud();
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Copy constructor.
    ///
    /// Copies a WorldPointGeneratorBaseDummy object.
    ///
    /// \param[in] Src Source object to copy.
    ///////////////////////////////////////////////////////////////////////////////
    inline WorldPointGeneratorBaseDummy(const WorldPointGeneratorBaseDummy& Src) :
        WorldPointGeneratorBase{Src}
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Move constructor.
    ///
    /// Moves a WorldPointGeneratorBaseDummy object.
    ///
    /// \param[in] Src Source object to move.
    ///////////////////////////////////////////////////////////////////////////////
    inline WorldPointGeneratorBaseDummy(WorldPointGeneratorBaseDummy&& Src) noexcept :
        WorldPointGeneratorBase{std::move(Src)}
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///////////////////////////////////////////////////////////////////////////////
    ~WorldPointGeneratorBaseDummy() override = default;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Copy assignment operator.
    ///
    /// Copies a WorldPointGeneratorBaseDummy object by assigning it to a new
    /// object. The if-condition for a self assignment is not present by design as
    /// this enables testing the copy assignment operator of the base class.
    ///
    /// \param[in] Rhs Source object to copy.
    ///
    /// \return Copied object.
    ///////////////////////////////////////////////////////////////////////////////
    inline WorldPointGeneratorBaseDummy& operator=(const WorldPointGeneratorBaseDummy& Rhs) // NOLINT(cert-oop54-cpp)
    {
        WorldPointGeneratorBase::operator=(Rhs);

        return *this;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Move assignment operator.
    ///
    /// Moves a WorldPointGeneratorBaseDummy object by assigning it to a new
    /// object. The if-condition for a self assignment is not present by design as
    /// this enables testing the move assignment operator of the base class.
    ///
    /// \param[in] Rhs Source object to move.
    ///
    /// \return Moved object.
    ///////////////////////////////////////////////////////////////////////////////
    inline WorldPointGeneratorBaseDummy& operator=(WorldPointGeneratorBaseDummy&& Rhs) noexcept
    {
        WorldPointGeneratorBase::operator=(std::move(Rhs));

        return *this;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Generates a single world point.
    ///
    /// The function generates a 3d world point with predefined coordinates as this
    /// is a dummy class for unit tests only.
    ///
    /// \param[out] WorldPoint Generated 3d world point.
    ///////////////////////////////////////////////////////////////////////////////
    inline void GenerateWorldPoint(ColumnVectorFloat64_3d& WorldPoint) override
    {
        WorldPoint(0) = 0.0;
        WorldPoint(1) = 1.0;
        WorldPoint(2) = 2.0; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    }
};

class Test_WorldPointGeneratorBase : public testing::Test
{
public:
    inline void CompareWorldPointGenerators(const WorldPointGeneratorBaseDummy& WorldPointGenerator1,
                                            const WorldPointGeneratorBaseDummy& WorldPointGenerator2)
    {
        const ListColumnVectorFloat64_3d& WorldPoints1 = WorldPointGenerator1.GetWorldPoints();
        const ListColumnVectorFloat64_3d& WorldPoints2 = WorldPointGenerator2.GetWorldPoints();

        ASSERT_EQ(WorldPointGenerator1.GetNumberOfWorldPoints(), WorldPointGenerator2.GetNumberOfWorldPoints());

        for(uint64 i_WorldPoint{0U}; i_WorldPoint < WorldPointGenerator1.GetNumberOfWorldPoints(); i_WorldPoint++)
        {
            const ColumnVectorFloat64_3d& CurrentWorldPoint1 = WorldPoints1[i_WorldPoint];
            const ColumnVectorFloat64_3d& CurrentWorldPoint2 = WorldPoints2[i_WorldPoint];

            ASSERT_EQ(CurrentWorldPoint1(0, 0), CurrentWorldPoint2(0, 0));
            ASSERT_EQ(CurrentWorldPoint1(1, 0), CurrentWorldPoint2(1, 0));
            ASSERT_EQ(CurrentWorldPoint1(2, 0), CurrentWorldPoint2(2, 0));
        }
    }
};

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the copy assignment operator (self assignment).
///
/// Tests whether or not the number of world points as well as the coordinates
/// of the world points match in case the copy assignment operator is being
/// called.
///////////////////////////////////////////////////////////////////////////////
TEST_COPYASSIGNMENTOPERATOR_SELFASSIGNMENT(Test_WorldPointGeneratorBase, Test_CopyAssignmentOperator_SelfAssignment)
{
    // prepare test
    const uint32 NumberOfWorldPointsToGenerate{10U};

    WorldPointGeneratorBaseDummy WPG(NumberOfWorldPointsToGenerate);

    // call function under test
    WPG = WPG;

    // run tests
    CompareWorldPointGenerators(WPG, WPG);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the move assignment operator (self assignment).
///
/// Tests whether or not the number of world points as well as the coordinates
/// of the world points match in case the move assignment operator is being
/// called.
///////////////////////////////////////////////////////////////////////////////
TEST_MOVEASSIGNMENTOPERATOR_SELFASSIGNMENT(Test_WorldPointGeneratorBase, Test_MoveAssignmentOperator_SelfAssignment)
{
    // prepare test
    const uint32 NumberOfWorldPointsToGenerate{10U};

    WorldPointGeneratorBaseDummy WPG(NumberOfWorldPointsToGenerate);

    // call function under test
    WPG = std::move(WPG);

    // run tests
    CompareWorldPointGenerators(WPG, WPG);
}
