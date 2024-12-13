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

#include "../../../source_code/include/WorldPointGeneratorCuboid.h"

// definition of macros for the unit tests
#define TEST_COPYCONSTRUCTOR                                   TEST ///< Define to get a unique test name.
#define TEST_MOVECONSTRUCTOR                                   TEST ///< Define to get a unique test name.
#define TEST_COPYASSIGNMENTOPERATOR                            TEST ///< Define to get a unique test name.
#define TEST_COPYASSIGNMENTOPERATOR_SELFASSIGNMENT             TEST ///< Define to get a unique test name.
#define TEST_MOVEASSIGNMENTOPERATOR                            TEST ///< Define to get a unique test name.
#define TEST_MOVEASSIGNMENTOPERATOR_SELFASSIGNMENT             TEST ///< Define to get a unique test name.
#define TEST_NUMBEROFWORLDPOINTS_DEFAULTCONSTRUCTOR_ISMATCHING TEST ///< Define to get a unique test name.
#define TEST_NUMBEROFWORLDPOINTS_50_ISMATCHING                 TEST ///< Define to get a unique test name.
#define TEST_NUMBEROFWORLDPOINTS_100_ISMATCHING                TEST ///< Define to get a unique test name.
#define TEST_WORLDPOINT_0_DEFAULTCONSTRUCTOR_ISMATCHING        TEST ///< Define to get a unique test name.
#define TEST_WORLDPOINT_4_DEFAULTCONSTRUCTOR_ISMATCHING        TEST ///< Define to get a unique test name.
#define TEST_WORLDPOINT_0_SEED_10_ISMATCHING                   TEST ///< Define to get a unique test name.
#define TEST_WORLDPOINT_4_SEED_10_ISMATCHING                   TEST ///< Define to get a unique test name.
#define TEST_WORLDPOINTS_INRANGE                               TEST ///< Define to get a unique test name.

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the copy constructor.
///
/// Tests whether or not the number of world points as well as the coordinates
/// of the world points match in case the copy constructor is being called.
///////////////////////////////////////////////////////////////////////////////
TEST_COPYCONSTRUCTOR(WorldPointGeneratorCuboid, Test_CopyConstructor)
{
    const uint32 NumberOfWorldPointsToCreate1{10U};

    WorldPointGeneratorCuboid WPG1(NumberOfWorldPointsToCreate1);
    WorldPointGeneratorCuboid WPG2(WPG1);

    const ListColumnVectorFloat64_3d& WorldPoints1 = WPG1.GetWorldPoints();
    const ListColumnVectorFloat64_3d& WorldPoints2 = WPG2.GetWorldPoints();

    ASSERT_EQ(WPG2.GetNumberOfWorldPoints(), WPG1.GetNumberOfWorldPoints());

    for(uint64 i_WorldPoint{0U}; i_WorldPoint < NumberOfWorldPointsToCreate1; i_WorldPoint++)
    {
        const ColumnVectorFloat64_3d& CurrentWorldPoint1 = WorldPoints1[i_WorldPoint];
        const ColumnVectorFloat64_3d& CurrentWorldPoint2 = WorldPoints2[i_WorldPoint];

        ASSERT_EQ(CurrentWorldPoint2(0, 0), CurrentWorldPoint1(0, 0));
        ASSERT_EQ(CurrentWorldPoint2(1, 0), CurrentWorldPoint1(1, 0));
        ASSERT_EQ(CurrentWorldPoint2(2, 0), CurrentWorldPoint1(2, 0));
    }
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the move constructor.
///
/// Tests whether or not the number of world points as well as the coordinates
/// of the first and last world point match in case the move constructor is
/// being called.
///////////////////////////////////////////////////////////////////////////////
TEST_MOVECONSTRUCTOR(WorldPointGeneratorCuboid, Test_MoveConstructor)
{
    const uint32 NumberOfWorldPointsToCreate{10U};

    WorldPointGeneratorCuboid WPG1(NumberOfWorldPointsToCreate);

    const ListColumnVectorFloat64_3d& WorldPoints1 = WPG1.GetWorldPoints();

    const ColumnVectorFloat64_3d WorldPoint1_First = WorldPoints1[0];
    const ColumnVectorFloat64_3d WorldPoint1_Last  = WorldPoints1[NumberOfWorldPointsToCreate - 1U];

    WorldPointGeneratorCuboid WPG2(std::move(WPG1));

    const ListColumnVectorFloat64_3d& WorldPoints2 = WPG2.GetWorldPoints();

    const ColumnVectorFloat64_3d WorldPoint2_First = WorldPoints2[0];
    const ColumnVectorFloat64_3d WorldPoint2_Last  = WorldPoints2[NumberOfWorldPointsToCreate - 1U];

    ASSERT_EQ(WPG2.GetNumberOfWorldPoints(), NumberOfWorldPointsToCreate);

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
TEST_COPYASSIGNMENTOPERATOR(WorldPointGeneratorCuboid, Test_CopyAssignmentOperator)
{
    const uint32 NumberOfWorldPointsToCreate1{10U};
    const uint32 NumberOfWorldPointsToCreate2{20U};

    WorldPointGeneratorCuboid WPG1(NumberOfWorldPointsToCreate1);
    WorldPointGeneratorCuboid WPG2(NumberOfWorldPointsToCreate2);

    WPG2 = WPG1;

    const ListColumnVectorFloat64_3d& WorldPoints1 = WPG1.GetWorldPoints();
    const ListColumnVectorFloat64_3d& WorldPoints2 = WPG2.GetWorldPoints();

    ASSERT_EQ(WPG2.GetNumberOfWorldPoints(), WPG1.GetNumberOfWorldPoints());

    for(uint64 i_WorldPoint{0U}; i_WorldPoint < NumberOfWorldPointsToCreate1; i_WorldPoint++)
    {
        const ColumnVectorFloat64_3d& CurrentWorldPoint1 = WorldPoints1[i_WorldPoint];
        const ColumnVectorFloat64_3d& CurrentWorldPoint2 = WorldPoints2[i_WorldPoint];

        ASSERT_EQ(CurrentWorldPoint2(0, 0), CurrentWorldPoint1(0, 0));
        ASSERT_EQ(CurrentWorldPoint2(1, 0), CurrentWorldPoint1(1, 0));
        ASSERT_EQ(CurrentWorldPoint2(2, 0), CurrentWorldPoint1(2, 0));
    }
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the copy assignment operator (self assignment).
///
/// Tests whether or not the number of world points as well as the coordinates
/// of the world points match in case the copy assignment operator is being
/// called.
///////////////////////////////////////////////////////////////////////////////
TEST_COPYASSIGNMENTOPERATOR_SELFASSIGNMENT(WorldPointGeneratorCuboid, Test_CopyAssignmentOperator_SelfAssignment)
{
    const uint32 NumberOfWorldPointsToCreate{10U};

    WorldPointGeneratorCuboid WPG(NumberOfWorldPointsToCreate);

    WPG = WPG;

    const ListColumnVectorFloat64_3d& WorldPoints = WPG.GetWorldPoints();

    ASSERT_EQ(WPG.GetNumberOfWorldPoints(), NumberOfWorldPointsToCreate);

    for(uint64 i_WorldPoint{0U}; i_WorldPoint < NumberOfWorldPointsToCreate; i_WorldPoint++)
    {
        const ColumnVectorFloat64_3d& CurrentWorldPoint = WorldPoints[i_WorldPoint];

        ASSERT_EQ(CurrentWorldPoint(0, 0), CurrentWorldPoint(0, 0));
        ASSERT_EQ(CurrentWorldPoint(1, 0), CurrentWorldPoint(1, 0));
        ASSERT_EQ(CurrentWorldPoint(2, 0), CurrentWorldPoint(2, 0));
    }
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the move assignment operator.
///
/// Tests whether or not the number of world points as well as the coordinates
/// of the first and last world point match in case the move assignment
/// operator is being called.
///////////////////////////////////////////////////////////////////////////////
TEST_MOVEASSIGNMENTOPERATOR(WorldPointGeneratorCuboid, Test_MoveAssignmentOperator)
{
    const uint32 NumberOfWorldPointsToCreate1{10U};
    const uint32 NumberOfWorldPointsToCreate2{20U};

    WorldPointGeneratorCuboid WPG1(NumberOfWorldPointsToCreate1);
    WorldPointGeneratorCuboid WPG2(NumberOfWorldPointsToCreate2);

    const ListColumnVectorFloat64_3d& WorldPoints1 = WPG1.GetWorldPoints();

    const ColumnVectorFloat64_3d WorldPoint1_First = WorldPoints1[0];
    const ColumnVectorFloat64_3d WorldPoint1_Last  = WorldPoints1[NumberOfWorldPointsToCreate1 - 1U];

    WPG2 = std::move(WPG1);

    const ListColumnVectorFloat64_3d& WorldPoints2 = WPG2.GetWorldPoints();

    const ColumnVectorFloat64_3d WorldPoint2_First = WorldPoints2[0];
    const ColumnVectorFloat64_3d WorldPoint2_Last  = WorldPoints2[NumberOfWorldPointsToCreate1 - 1U];

    ASSERT_EQ(WPG2.GetNumberOfWorldPoints(), NumberOfWorldPointsToCreate1);

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
TEST_MOVEASSIGNMENTOPERATOR_SELFASSIGNMENT(WorldPointGeneratorCuboid, Test_MoveAssignmentOperator_SelfAssignment)
{
    const uint32 NumberOfWorldPointsToCreate{10U};

    WorldPointGeneratorCuboid WPG(NumberOfWorldPointsToCreate);

    WPG = std::move(WPG);

    const ListColumnVectorFloat64_3d& WorldPoints = WPG.GetWorldPoints();

    ASSERT_EQ(WPG.GetNumberOfWorldPoints(), NumberOfWorldPointsToCreate);

    for(uint64 i_WorldPoint{0U}; i_WorldPoint < NumberOfWorldPointsToCreate; i_WorldPoint++)
    {
        const ColumnVectorFloat64_3d& CurrentWorldPoint = WorldPoints[i_WorldPoint];

        ASSERT_EQ(CurrentWorldPoint(0, 0), CurrentWorldPoint(0, 0));
        ASSERT_EQ(CurrentWorldPoint(1, 0), CurrentWorldPoint(1, 0));
        ASSERT_EQ(CurrentWorldPoint(2, 0), CurrentWorldPoint(2, 0));
    }
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the number of world points.
///
/// Tests whether the number of world points does match the expected number of
/// world points or not. The default constructor is used. Hence, the
/// expectation is to get the default number of world points, which is 1000.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFWORLDPOINTS_DEFAULTCONSTRUCTOR_ISMATCHING(WorldPointGeneratorCuboid, Test_NumberOfWorldPoints_DefaultConstructor_IsMatching)
{
    const uint32 NumberOfWorldPointsToCreate{1000U};

    WorldPointGeneratorCuboid WPG;

    ASSERT_EQ(WPG.GetNumberOfWorldPoints(), NumberOfWorldPointsToCreate);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the number of world points.
///
/// Tests whether the number of world points does match the expected number of
/// world points or not. The expectation is to get 50 world points.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFWORLDPOINTS_50_ISMATCHING(WorldPointGeneratorCuboid, Test_NumberOfWorldPoints_50_IsMatching)
{
    const uint32 NumberOfWorldPointsToCreate{50U};

    WorldPointGeneratorCuboid WPG(NumberOfWorldPointsToCreate);

    ASSERT_EQ(WPG.GetNumberOfWorldPoints(), NumberOfWorldPointsToCreate);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the number of world points.
///
/// Tests whether the number of world points does match the expected number of
/// world points or not. The expectation is to get 100 world points.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFWORLDPOINTS_100_ISMATCHING(WorldPointGeneratorCuboid, Test_NumberOfWorldPoints_100_IsMatching)
{
    const uint32 NumberOfWorldPointsToCreate{100U};

    WorldPointGeneratorCuboid WPG(NumberOfWorldPointsToCreate);

    ASSERT_EQ(WPG.GetNumberOfWorldPoints(), NumberOfWorldPointsToCreate);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the coordinates of a world point.
///
/// Tests whether the coordinates of the 0th world point match the expected
/// coordinates or not. The default constructor is used to generate the world
/// points.
///////////////////////////////////////////////////////////////////////////////
TEST_WORLDPOINT_0_DEFAULTCONSTRUCTOR_ISMATCHING(WorldPointGeneratorCuboid, Test_WorldPoint_0_DefaultConstructor_IsMatching)
{
    WorldPointGeneratorCuboid WPG;

    const ColumnVectorFloat64_3d WorldPoint{WPG.GetWorldPoints()[0]};

    const float64 ValueX{WorldPoint(0)};
    const float64 ValueY{WorldPoint(1)};
    const float64 ValueZ{WorldPoint(2)};

    ASSERT_DOUBLE_EQ(ValueX, 0.92844616516682632);
    ASSERT_DOUBLE_EQ(ValueY, 1.3770629770263931);
    ASSERT_DOUBLE_EQ(ValueZ, 26.164531739725408);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the coordinates of a world point.
///
/// Tests whether the coordinates of the 4th world point match the expected
/// coordinates or not. The default constructor is used to generate the world
/// points.
///////////////////////////////////////////////////////////////////////////////
TEST_WORLDPOINT_4_DEFAULTCONSTRUCTOR_ISMATCHING(WorldPointGeneratorCuboid, Test_WorldPoint_4_DefaultConstructor_IsMatching)
{
    WorldPointGeneratorCuboid WPG;

    const ColumnVectorFloat64_3d WorldPoint{WPG.GetWorldPoints()[4]};

    const float64 ValueX{WorldPoint(0)};
    const float64 ValueY{WorldPoint(1)};
    const float64 ValueZ{WorldPoint(2)};

    ASSERT_DOUBLE_EQ(ValueX, -1.0721520670502338);
    ASSERT_DOUBLE_EQ(ValueY, 1.3443150761775642);
    ASSERT_DOUBLE_EQ(ValueZ, 12.109696364476806);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the coordinates of a world point.
///
/// Tests whether the coordinates of the 0th world point match the expected
/// coordinates or not. The seed value 10 is used to initialize the generation
/// of the world coordinates.
///////////////////////////////////////////////////////////////////////////////
TEST_WORLDPOINT_0_SEED_10_ISMATCHING(WorldPointGeneratorCuboid, Test_WorldPoint_0_Seed_10_IsMatching)
{
    const uint32  NumberOfWorldPointsToCreate{1000U};
    const float64 MinX{-5.0};
    const float64 MaxX{5.0};
    const float64 MinY{-2.0};
    const float64 MaxY{2.0};
    const float64 MinZ{3.0};
    const float64 MaxZ{30.0};
    const uint32  Seed{10U};

    WorldPointGeneratorCuboid WPG(NumberOfWorldPointsToCreate, MinX, MaxX, MinY, MaxY, MinZ, MaxZ, Seed);

    const ColumnVectorFloat64_3d WorldPoint{WPG.GetWorldPoints()[0]};

    const float64 ValueX{WorldPoint(0)};
    const float64 ValueY{WorldPoint(1)};
    const float64 ValueZ{WorldPoint(2)};

    ASSERT_DOUBLE_EQ(ValueX, -2.0123884133731003);
    ASSERT_DOUBLE_EQ(ValueY, -0.02164028676156704);
    ASSERT_DOUBLE_EQ(ValueZ, 14.961403547811438);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the coordinates of a world point.
///
/// Tests whether the coordinates of the 4th world point match the expected
/// coordinates or not. The seed value 10 is used to initialize the generation
/// of the world coordinates.
///////////////////////////////////////////////////////////////////////////////
TEST_WORLDPOINT_4_SEED_10_ISMATCHING(WorldPointGeneratorCuboid, Test_WorldPoint_4_Seed_10_IsMatching)
{
    const uint32  NumberOfWorldPointsToCreate{1000U};
    const float64 MinX{-5.0};
    const float64 MaxX{5.0};
    const float64 MinY{-2.0};
    const float64 MaxY{2.0};
    const float64 MinZ{3.0};
    const float64 MaxZ{30.0};
    const uint32  Seed{10U};

    WorldPointGeneratorCuboid WPG(NumberOfWorldPointsToCreate, MinX, MaxX, MinY, MaxY, MinZ, MaxZ, Seed);

    const ColumnVectorFloat64_3d WorldPoint{WPG.GetWorldPoints()[4]};

    const float64 ValueX{WorldPoint(0)};
    const float64 ValueY{WorldPoint(1)};
    const float64 ValueZ{WorldPoint(2)};

    ASSERT_DOUBLE_EQ(ValueX, -1.6392841678952141);
    ASSERT_DOUBLE_EQ(ValueY, 1.5632661213280561);
    ASSERT_DOUBLE_EQ(ValueZ, 8.3492889972265729);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the location of the generated world points.
///
/// Tests whether the location of the generated world points is within the
/// predefined size of the cuboid. Hence, a big number of world points is
/// generated and the location of each world point is checked against the size
/// of the cuboid.
///////////////////////////////////////////////////////////////////////////////
TEST_WORLDPOINTS_INRANGE(WorldPointGeneratorCuboid, Test_WorldPoints_InRange)
{
    const uint32  NumberOfWorldPointsToCreate{1000U};
    const float64 MinX{-5.0};
    const float64 MaxX{5.0};
    const float64 MinY{-2.0};
    const float64 MaxY{2.0};
    const float64 MinZ{3.0};
    const float64 MaxZ{30.0};

    WorldPointGeneratorCuboid WPG(NumberOfWorldPointsToCreate, MinX, MaxX, MinY, MaxY, MinZ, MaxZ);

    const ListColumnVectorFloat64_3d& WorldPoints{WPG.GetWorldPoints()};

    uint32 NumberOfPointsOutOfRange = NumberOfWorldPointsToCreate;

    for(uint32 i_WorldPoint{0U}; i_WorldPoint < NumberOfWorldPointsToCreate; i_WorldPoint++)
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
