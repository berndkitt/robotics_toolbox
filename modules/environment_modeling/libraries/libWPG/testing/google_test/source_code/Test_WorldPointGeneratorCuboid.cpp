///////////////////////////////////////////////////////////////////////////////
/// \file  Test_WorldPointGeneratorCuboid.cpp
///
/// \brief Source file containing the unit tests for WorldPointGeneratorCuboid.
///////////////////////////////////////////////////////////////////////////////

/*
This file is part of the Robotics Toolbox.

Copyright (C) 2022

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
#include <tuple>

#include "../../../source_code/include/WorldPointGeneratorCuboid.h"

// definition of macros for the unit tests
#define TEST_COPYCONSTRUCTOR                       TEST_F ///< Define to get a unique test name.
#define TEST_MOVECONSTRUCTOR                       TEST_F ///< Define to get a unique test name.
#define TEST_COPYASSIGNMENTOPERATOR                TEST_F ///< Define to get a unique test name.
#define TEST_COPYASSIGNMENTOPERATOR_SELFASSIGNMENT TEST_F ///< Define to get a unique test name.
#define TEST_MOVEASSIGNMENTOPERATOR                TEST_F ///< Define to get a unique test name.
#define TEST_MOVEASSIGNMENTOPERATOR_SELFASSIGNMENT TEST_F ///< Define to get a unique test name.
#define TEST_NUMBEROFWORLDPOINTS_ISMATCHING        TEST_P ///< Define to get a unique test name.
#define TEST_WORLDPOINTCOORDINATE_ISMATCHING       TEST_P ///< Define to get a unique test name.
#define TEST_WORLDPOINTS_INRANGE                   TEST_F ///< Define to get a unique test name.

class TestWorldPointGeneratorCuboid : public testing::Test
{
public:
    inline static void CompareWorldPointGenerators(const WorldPointGeneratorCuboid& WorldPointGenerator1,
                                                   const WorldPointGeneratorCuboid& WorldPointGenerator2)
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
/// \class TestWorldPointGeneratorCuboidParameterizedWorldPointNumber
///
/// \brief Parameterized test class.
///////////////////////////////////////////////////////////////////////////////
class TestWorldPointGeneratorCuboidParameterizedWorldPointNumber : public testing::TestWithParam<uint32>
{
protected:
    uint32 m_NumberOfWorldPointsToGenerate{0U}; ///< Number of 3d world points to generate.
};

///////////////////////////////////////////////////////////////////////////////
/// \class TestWorldPointGeneratorCuboidParameterizedWorldPointCoordinate
///
/// \brief Parameterized test class.
///////////////////////////////////////////////////////////////////////////////
class TestWorldPointGeneratorCuboidParameterizedWorldPointCoordinate : public testing::TestWithParam<std::tuple<uint32, uint32, uint32, float64, float64, float64>>
{
protected:
    uint32  m_NumberOfWorldPointsToGenerate{0U}; ///< Number of 3d world points to generate.
    uint32  m_Seed{0U};                          ///< Seed value used to initialize the random number engine.
    uint32  m_Index{0U};                         ///< Index of the 3d world point to test.
    float64 m_ValueExpectedX{0.0};               ///< Expected X-coordinate of the 3d world point.
    float64 m_ValueExpectedY{0.0};               ///< Expected Y-coordinate of the 3d world point.
    float64 m_ValueExpectedZ{0.0};               ///< Expected Z-coordinate of the 3d world point.

    const float64 m_MinX{-5.0}; ///< Smallest value of the 3d world points inside the cuboid in X-direction.
    const float64 m_MaxX{5.0};  ///< Largest value of the 3d world points inside the cuboid in X-direction.
    const float64 m_MinY{-2.0}; ///< Smallest value of the 3d world points inside the cuboid in Y-direction.
    const float64 m_MaxY{2.0};  ///< Largest value of the 3d world points inside the cuboid in Y-direction.
    const float64 m_MinZ{3.0};  ///< Smallest value of the 3d world points inside the cuboid in Z-direction.
    const float64 m_MaxZ{30.0}; ///< Largest value of the 3d world points inside the cuboid in Z-direction.
};

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the copy constructor.
///
/// Tests whether or not the number of world points as well as the coordinates
/// of the world points match in case the copy constructor is being called.
///////////////////////////////////////////////////////////////////////////////
TEST_COPYCONSTRUCTOR(TestWorldPointGeneratorCuboid, Test_CopyConstructor)
{
    // prepare test
    const uint32 NumberOfWorldPointsToGenerate1{10U};

    WorldPointGeneratorCuboid WPG1(NumberOfWorldPointsToGenerate1);

    // call function under test
    const WorldPointGeneratorCuboid WPG2(WPG1); // NOLINT(performance-unnecessary-copy-initialization)

    // run tests
    CompareWorldPointGenerators(WPG1, WPG2);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the move constructor.
///
/// Tests whether or not the number of world points as well as the coordinates
/// of the first and last world point match in case the move constructor is
/// being called.
///////////////////////////////////////////////////////////////////////////////
TEST_MOVECONSTRUCTOR(TestWorldPointGeneratorCuboid, Test_MoveConstructor)
{
    // prepare test
    const uint32 NumberOfWorldPointsToGenerate{10U};

    WorldPointGeneratorCuboid WPG1(NumberOfWorldPointsToGenerate);

    const ListColumnVectorFloat64_3d& WorldPoints1 = WPG1.GetWorldPoints();

    const ColumnVectorFloat64_3d WorldPoint1_First = WorldPoints1[0];
    const ColumnVectorFloat64_3d WorldPoint1_Last  = WorldPoints1[NumberOfWorldPointsToGenerate - 1U];

    // call function under test
    WorldPointGeneratorCuboid WPG2(std::move(WPG1));

    // run tests
    const ListColumnVectorFloat64_3d& WorldPoints2 = WPG2.GetWorldPoints();

    const ColumnVectorFloat64_3d WorldPoint2_First = WorldPoints2[0];                                  // NOLINT(performance-unnecessary-copy-initialization)
    const ColumnVectorFloat64_3d WorldPoint2_Last  = WorldPoints2[NumberOfWorldPointsToGenerate - 1U]; // NOLINT(performance-unnecessary-copy-initialization)

    ASSERT_EQ(WPG2.GetNumberOfWorldPoints(), NumberOfWorldPointsToGenerate);

    ASSERT_EQ(WorldPoint2_First(0, 0), WorldPoint1_First(0, 0));
    ASSERT_EQ(WorldPoint2_First(1, 0), WorldPoint1_First(1, 0));
    ASSERT_EQ(WorldPoint2_First(2, 0), WorldPoint1_First(2, 0));

    ASSERT_EQ(WorldPoint2_Last(0, 0), WorldPoint1_Last(0, 0));
    ASSERT_EQ(WorldPoint2_Last(1, 0), WorldPoint1_Last(1, 0));
    ASSERT_EQ(WorldPoint2_Last(2, 0), WorldPoint1_Last(2, 0));
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the copy assignment operator.
///
/// Tests whether or not the number of world points as well as the coordinates
/// of the world points match in case the copy assignment operator is being
/// called.
///////////////////////////////////////////////////////////////////////////////
TEST_COPYASSIGNMENTOPERATOR(TestWorldPointGeneratorCuboid, Test_CopyAssignmentOperator)
{
    // prepare test
    const uint32 NumberOfWorldPointsToGenerate1{10U};
    const uint32 NumberOfWorldPointsToGenerate2{20U};

    WorldPointGeneratorCuboid WPG1(NumberOfWorldPointsToGenerate1);
    WorldPointGeneratorCuboid WPG2(NumberOfWorldPointsToGenerate2);

    // call function under test
    WPG2 = WPG1;

    // run tests
    CompareWorldPointGenerators(WPG1, WPG2);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the copy assignment operator (self assignment).
///
/// Tests whether or not the number of world points as well as the coordinates
/// of the world points match in case the copy assignment operator is being
/// called.
///////////////////////////////////////////////////////////////////////////////
TEST_COPYASSIGNMENTOPERATOR_SELFASSIGNMENT(TestWorldPointGeneratorCuboid, Test_CopyAssignmentOperator_SelfAssignment)
{
    // prepare test
    const uint32 NumberOfWorldPointsToGenerate{10U};

    WorldPointGeneratorCuboid WPG(NumberOfWorldPointsToGenerate);

    // call function under test
    WPG = WPG;

    // run tests
    CompareWorldPointGenerators(WPG, WPG);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the move assignment operator.
///
/// Tests whether or not the number of world points as well as the coordinates
/// of the first and last world point match in case the move assignment
/// operator is being called.
///////////////////////////////////////////////////////////////////////////////
TEST_MOVEASSIGNMENTOPERATOR(TestWorldPointGeneratorCuboid, Test_MoveAssignmentOperator)
{
    // prepare test
    const uint32 NumberOfWorldPointsToGenerate1{10U};
    const uint32 NumberOfWorldPointsToGenerate2{20U};

    WorldPointGeneratorCuboid WPG1(NumberOfWorldPointsToGenerate1);
    WorldPointGeneratorCuboid WPG2(NumberOfWorldPointsToGenerate2);

    const ListColumnVectorFloat64_3d& WorldPoints1 = WPG1.GetWorldPoints();

    const ColumnVectorFloat64_3d WorldPoint1_First = WorldPoints1[0];
    const ColumnVectorFloat64_3d WorldPoint1_Last  = WorldPoints1[NumberOfWorldPointsToGenerate1 - 1U];

    // call function under test
    WPG2 = std::move(WPG1);

    // run tests
    const ListColumnVectorFloat64_3d& WorldPoints2 = WPG2.GetWorldPoints();

    const ColumnVectorFloat64_3d WorldPoint2_First = WorldPoints2[0];
    const ColumnVectorFloat64_3d WorldPoint2_Last  = WorldPoints2[NumberOfWorldPointsToGenerate1 - 1U];

    ASSERT_EQ(WPG2.GetNumberOfWorldPoints(), NumberOfWorldPointsToGenerate1);

    ASSERT_EQ(WorldPoint2_First(0, 0), WorldPoint1_First(0, 0));
    ASSERT_EQ(WorldPoint2_First(1, 0), WorldPoint1_First(1, 0));
    ASSERT_EQ(WorldPoint2_First(2, 0), WorldPoint1_First(2, 0));

    ASSERT_EQ(WorldPoint2_Last(0, 0), WorldPoint1_Last(0, 0));
    ASSERT_EQ(WorldPoint2_Last(1, 0), WorldPoint1_Last(1, 0));
    ASSERT_EQ(WorldPoint2_Last(2, 0), WorldPoint1_Last(2, 0));
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the move assignment operator (self assignment).
///
/// Tests whether or not the number of world points as well as the coordinates
/// of the world points match in case the move assignment operator is being
/// called.
///////////////////////////////////////////////////////////////////////////////
TEST_MOVEASSIGNMENTOPERATOR_SELFASSIGNMENT(TestWorldPointGeneratorCuboid, Test_MoveAssignmentOperator_SelfAssignment)
{
    // prepare test
    const uint32 NumberOfWorldPointsToGenerate{10U};

    WorldPointGeneratorCuboid WPG(NumberOfWorldPointsToGenerate);

    // call function under test
    WPG = std::move(WPG);

    // run tests
    CompareWorldPointGenerators(WPG, WPG); // NOLINT(bugprone-use-after-move)
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the number of world points.
///
/// This parameterized test checks for different configurations of the
/// parameter "NumberOfWorldPointsToGenerate" whether the number of actually
/// generated world points match the expected value or not.
///////////////////////////////////////////////////////////////////////////////
INSTANTIATE_TEST_SUITE_P(TestWorldPointNumber,
                         TestWorldPointGeneratorCuboidParameterizedWorldPointNumber,
                         // List of parameters: NumberOfWorldPointsToGenerate
                         testing::Values(1000U, // NumberOfWorldPointsToGenerate matches the value of the default constructor
                                         50U,
                                         100U));

TEST_NUMBEROFWORLDPOINTS_ISMATCHING(TestWorldPointGeneratorCuboidParameterizedWorldPointNumber, Test_NumberOfWorldPoints_IsMatching)
{
    // prepare test
    m_NumberOfWorldPointsToGenerate = GetParam();

    // call function under test
    WorldPointGeneratorCuboid WPG(m_NumberOfWorldPointsToGenerate);

    // run tests
    ASSERT_EQ(WPG.GetNumberOfWorldPoints(), m_NumberOfWorldPointsToGenerate);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the coordinates of a world point.
///
/// This parameterized test checks for different configurations of
/// "NumberOfWorldPointsToGenerate", "Seed", and "Index" whether the
/// coordinates of the generated world point match the expected values or not.
///////////////////////////////////////////////////////////////////////////////
INSTANTIATE_TEST_SUITE_P(TestWorldPointCoordinate,
                         TestWorldPointGeneratorCuboidParameterizedWorldPointCoordinate,
                         // List of parameters: NumberOfWorldPointsToGenerate, Seed, Index, ValueExpectedX, ValueExpectedY, ValueExpectedZ
                         testing::Values(std::tuple(1000U, 0U, 0U, 0.92844616516682632, 1.3770629770263931, 26.164531739725408), // NumberOfWorldPointsToGenerate and Seed match the values of the default constructor
                                         std::tuple(1000U, 0U, 4U, -1.0721520670502338, 1.3443150761775642, 12.109696364476806), // NumberOfWorldPointsToGenerate and Seed match the values of the default constructor
                                         std::tuple(1000U, 10U, 0U, -2.0123884133731003, -0.02164028676156704, 14.961403547811438),
                                         std::tuple(1000U, 10U, 4U, -1.6392841678952141, 1.5632661213280561, 8.3492889972265729)));

TEST_WORLDPOINTCOORDINATE_ISMATCHING(TestWorldPointGeneratorCuboidParameterizedWorldPointCoordinate, Test_WorldPointCoordinate_IsMatching)
{
    // prepare test
    std::tie(m_NumberOfWorldPointsToGenerate, m_Seed, m_Index, m_ValueExpectedX, m_ValueExpectedY, m_ValueExpectedZ) = GetParam();

    WorldPointGeneratorCuboid WPG(m_NumberOfWorldPointsToGenerate, m_MinX, m_MaxX, m_MinY, m_MaxY, m_MinZ, m_MaxZ, m_Seed);

    // call function under test
    const ColumnVectorFloat64_3d WorldPoint{WPG.GetWorldPoints()[m_Index]};

    // run tests
    const float64 ValueX{WorldPoint(0)};
    const float64 ValueY{WorldPoint(1)};
    const float64 ValueZ{WorldPoint(2)};

    ASSERT_DOUBLE_EQ(ValueX, m_ValueExpectedX);
    ASSERT_DOUBLE_EQ(ValueY, m_ValueExpectedY);
    ASSERT_DOUBLE_EQ(ValueZ, m_ValueExpectedZ);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the location of the generated world points.
///
/// Tests whether the location of the generated world points is within the
/// predefined size of the cuboid. Hence, a big number of world points is
/// generated and the location of each world point is checked against the size
/// of the cuboid.
///////////////////////////////////////////////////////////////////////////////
TEST_WORLDPOINTS_INRANGE(TestWorldPointGeneratorCuboid, Test_WorldPoints_InRange)
{
    // prepare test
    const uint32  NumberOfWorldPointsToGenerate{1000U};
    const float64 MinX{-5.0};
    const float64 MaxX{5.0};
    const float64 MinY{-2.0};
    const float64 MaxY{2.0};
    const float64 MinZ{3.0};
    const float64 MaxZ{30.0};

    WorldPointGeneratorCuboid WPG(NumberOfWorldPointsToGenerate, MinX, MaxX, MinY, MaxY, MinZ, MaxZ);

    // call function under test
    const ListColumnVectorFloat64_3d& WorldPoints{WPG.GetWorldPoints()};

    // run tests
    uint32 NumberOfPointsOutOfRange = NumberOfWorldPointsToGenerate;

    for(uint32 i_WorldPoint{0U}; i_WorldPoint < NumberOfWorldPointsToGenerate; i_WorldPoint++)
    {
        const ColumnVectorFloat64_3d& CurrentWorldPoint{WorldPoints[i_WorldPoint]};

        const float64 CurrentCoordinateX{CurrentWorldPoint(0)};
        const float64 CurrentCoordinateY{CurrentWorldPoint(1)};
        const float64 CurrentCoordinateZ{CurrentWorldPoint(2)};

        const boolean XCoordinateIsInRange{((CurrentCoordinateX > MinX) && (CurrentCoordinateX < MaxX))};
        const boolean YCoordinateIsInRange{((CurrentCoordinateY > MinY) && (CurrentCoordinateY < MaxY))};
        const boolean ZCoordinateIsInRange{((CurrentCoordinateZ > MinZ) && (CurrentCoordinateZ < MaxZ))};

        if(XCoordinateIsInRange && YCoordinateIsInRange && ZCoordinateIsInRange)
        {
            NumberOfPointsOutOfRange--;
        }
    }

    ASSERT_EQ(NumberOfPointsOutOfRange, 0U);
}
