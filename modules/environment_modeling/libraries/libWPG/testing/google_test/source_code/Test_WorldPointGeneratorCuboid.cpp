///////////////////////////////////////////////////////////////////////////////
/// \file Test_WorldPointGeneratorCuboid.cpp
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
#define TEST_NUMBER_OF_WORLD_POINTS_DEFAULT_CONSTRUCTOR_IS_FITTING TEST ///< Define to get a unique test name.
#define TEST_NUMBER_OF_WORLD_POINTS_50_IS_FITTING                  TEST ///< Define to get a unique test name.
#define TEST_NUMBER_OF_WORLD_POINTS_100_IS_FITTING                 TEST ///< Define to get a unique test name.
#define TEST_WORLD_POINT_0_DEFAULT_CONSTRUCTOR_IS_FITTING          TEST ///< Define to get a unique test name.
#define TEST_WORLD_POINT_4_DEFAULT_CONSTRUCTOR_IS_FITTING          TEST ///< Define to get a unique test name.
#define TEST_WORLD_POINT_0_SEED_10_IS_FITTING                      TEST ///< Define to get a unique test name.
#define TEST_WORLD_POINT_4_SEED_10_IS_FITTING                      TEST ///< Define to get a unique test name.
#define TEST_WORLD_POINTS_IN_RANGE                                 TEST ///< Define to get a unique test name.

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the number of world points.
///
/// Tests whether the number of world points does match the expected number of
/// world points or not. The default constructor is used. Hence, the
/// expectation is to get the default number of world points.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBER_OF_WORLD_POINTS_DEFAULT_CONSTRUCTOR_IS_FITTING(WorldPointGeneratorCuboid, Test_Number_Of_World_Points_Default_Constructor_Is_Fitting)
{
    WorldPointGeneratorCuboid WPG;

    ASSERT_EQ(WPG.GetNumberOfWorldPoints(), 1000);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the number of world points.
///
/// Tests whether the number of world points does match the expected number of
/// world points or not. The expectation is to get 50 world points.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBER_OF_WORLD_POINTS_50_IS_FITTING(WorldPointGeneratorCuboid, Test_Number_Of_World_Points_50_Is_Fitting)
{
    WorldPointGeneratorCuboid WPG(50);

    ASSERT_EQ(WPG.GetNumberOfWorldPoints(), 50);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the number of world points.
///
/// Tests whether the number of world points does match the expected number of
/// world points or not. The expectation is to get 100 world points.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBER_OF_WORLD_POINTS_100_IS_FITTING(WorldPointGeneratorCuboid, Test_Number_Of_World_Points_100_Is_Fitting)
{
    WorldPointGeneratorCuboid WPG(100);

    ASSERT_EQ(WPG.GetNumberOfWorldPoints(), 100);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the coordinates of a world point.
///
/// Tests whether the coordinates of the 0th world point match the expected
/// coordinates or not. The default constructor is used to create the world
/// points.
///////////////////////////////////////////////////////////////////////////////
TEST_WORLD_POINT_0_DEFAULT_CONSTRUCTOR_IS_FITTING(WorldPointGeneratorCuboid, Test_World_Point_0_Default_Constructor_Is_Fitting)
{
    WorldPointGeneratorCuboid WPG;

    const T_ColumnVectorReal3d WorldPoint = WPG.GetWorldPoints()[0];

    const T_REAL ValueX = WorldPoint(0);
    const T_REAL ValueY = WorldPoint(1);
    const T_REAL ValueZ = WorldPoint(2);

    ASSERT_DOUBLE_EQ(ValueX, 0.92844616516682632);
    ASSERT_DOUBLE_EQ(ValueY, 1.3770629770263931);
    ASSERT_DOUBLE_EQ(ValueZ, 26.164531739725408);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the coordinates of a world point.
///
/// Tests whether the coordinates of the 4th world point match the expected
/// coordinates or not. The default constructor is used to create the world
/// points.
///////////////////////////////////////////////////////////////////////////////
TEST_WORLD_POINT_4_DEFAULT_CONSTRUCTOR_IS_FITTING(WorldPointGeneratorCuboid, Test_World_Point_4_Default_Constructor_Is_Fitting)
{
    WorldPointGeneratorCuboid WPG;

    const T_ColumnVectorReal3d WorldPoint = WPG.GetWorldPoints()[4];

    const T_REAL ValueX = WorldPoint(0);
    const T_REAL ValueY = WorldPoint(1);
    const T_REAL ValueZ = WorldPoint(2);

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
TEST_WORLD_POINT_0_SEED_10_IS_FITTING(WorldPointGeneratorCuboid, Test_World_Point_0_Seed_10_Is_Fitting)
{
    WorldPointGeneratorCuboid WPG(1000, -5.0, 5.0, -2.0, 2.0, 3.0, 30.0, 10);

    const T_ColumnVectorReal3d WorldPoint = WPG.GetWorldPoints()[0];

    const T_REAL ValueX = WorldPoint(0);
    const T_REAL ValueY = WorldPoint(1);
    const T_REAL ValueZ = WorldPoint(2);

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
TEST_WORLD_POINT_4_SEED_10_IS_FITTING(WorldPointGeneratorCuboid, Test_World_Point_4_Seed_10_Is_Fitting)
{
    WorldPointGeneratorCuboid WPG(1000, -5.0, 5.0, -2.0, 2.0, 3.0, 30.0, 10);

    const T_ColumnVectorReal3d WorldPoint = WPG.GetWorldPoints()[4];

    const T_REAL ValueX = WorldPoint(0);
    const T_REAL ValueY = WorldPoint(1);
    const T_REAL ValueZ = WorldPoint(2);

    ASSERT_DOUBLE_EQ(ValueX, -1.6392841678952141);
    ASSERT_DOUBLE_EQ(ValueY, 1.5632661213280561);
    ASSERT_DOUBLE_EQ(ValueZ, 8.3492889972265729);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the location of the generated world points.
///
/// Tests whether the location of the generated world points is within the
/// predefined size of the cuboid. Hence, a big number of world points is
/// and the location of each world point is checked against the size of the
/// cuboid.
///////////////////////////////////////////////////////////////////////////////
TEST_WORLD_POINTS_IN_RANGE(WorldPointGeneratorCuboid, Test_World_Points_In_Range)
{
    const T_ULONG NumberOfWorldPoints = 1000000;
    const T_REAL MinX                 = -5.0;
    const T_REAL MaxX                 = 5.0;
    const T_REAL MinY                 = -2.0;
    const T_REAL MaxY                 = 2.0;
    const T_REAL MinZ                 = 3.0;
    const T_REAL MaxZ                 = 30.0;

    WorldPointGeneratorCuboid WPG(NumberOfWorldPoints, MinX, MaxX, MinY, MaxY, MinZ, MaxZ);

    const T_ListColumnVectorReal3d WorldPoints = WPG.GetWorldPoints();

    T_ULONG NumberOfPointsOutOfRange = NumberOfWorldPoints;

    for(T_ULONG i_WorldPoint = 0; i_WorldPoint < NumberOfWorldPoints; i_WorldPoint++)
    {
        const T_ColumnVectorReal3d CurrentWorldPoint = WorldPoints[i_WorldPoint];

        const T_REAL CurrentCoordinateX = CurrentWorldPoint(0);
        const T_REAL CurrentCoordinateY = CurrentWorldPoint(1);
        const T_REAL CurrentCoordinateZ = CurrentWorldPoint(2);

        T_BOOL XCoordinateIsInRange = ((CurrentCoordinateX > MinX) && (CurrentCoordinateX < MaxX));
        T_BOOL YCoordinateIsInRange = ((CurrentCoordinateY > MinY) && (CurrentCoordinateY < MaxY));
        T_BOOL ZCoordinateIsInRange = ((CurrentCoordinateZ > MinZ) && (CurrentCoordinateZ < MaxZ));

        if(XCoordinateIsInRange && YCoordinateIsInRange && ZCoordinateIsInRange)
        {
            NumberOfPointsOutOfRange--;
        }
    }

    ASSERT_EQ(NumberOfPointsOutOfRange, 0);
}
