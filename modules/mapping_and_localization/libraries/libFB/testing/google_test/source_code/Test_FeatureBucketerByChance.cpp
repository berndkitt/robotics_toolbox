///////////////////////////////////////////////////////////////////////////////
/// \file Test_FeatureBucketerByChance.cpp
///////////////////////////////////////////////////////////////////////////////

/*
This file is part of the Robotics Toolbox.

Copyright (C) 2023

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

#include "../../../source_code/include/FeatureBucketerByChance.h"

// definition of macros for the unit tests
#define TEST_BUCKETSIZEHORIZONTAL_DEFAULTCONSTRUCTOR_BYCHANCE_ISMATCHING      TEST  ///< Define to get a unique test name.
#define TEST_BUCKETSIZEHORIZONTAL_80_BYCHANCE_ISMATCHING                      TEST  ///< Define to get a unique test name.
#define TEST_BUCKETSIZEHORIZONTAL_250_BYCHANCE_ISMATCHING                     TEST  ///< Define to get a unique test name.
#define TEST_BUCKETSIZEVERTICAL_DEFAULTCONSTRUCTOR_BYCHANCE_ISMATCHING        TEST  ///< Define to get a unique test name.
#define TEST_BUCKETSIZEVERTICAL_50_BYCHANCE_ISMATCHING                        TEST  ///< Define to get a unique test name.
#define TEST_BUCKETSIZEVERTICAL_300_BYCHANCE_ISMATCHING                       TEST  ///< Define to get a unique test name.
#define TEST_NUMBEROFBUCKETSHORIZONTAL_DEFAULTCONSTRUCTOR_BYCHANCE_ISMATCHING TEST  ///< Define to get a unique test name.
#define TEST_NUMBEROFBUCKETSHORIZONTAL_4_BYCHANCE_ISMATCHING                  TEST  ///< Define to get a unique test name.
#define TEST_NUMBEROFBUCKETSHORIZONTAL_10_BYCHANCE_ISMATCHING                 TEST  ///< Define to get a unique test name.
#define TEST_NUMBEROFBUCKETSVERTICAL_DEFAULTCONSTRUCTOR_BYCHANCE_ISMATCHING   TEST  ///< Define to get a unique test name.
#define TEST_NUMBEROFBUCKETSVERTICAL_2_BYCHANCE_ISMATCHING                    TEST  ///< Define to get a unique test name.
#define TEST_NUMBEROFBUCKETSVERTICAL_8_BYCHANCE_ISMATCHING                    TEST  ///< Define to get a unique test name.
#define TEST_NUMBEROFPIXELSHORIZONTAL_DEFAULTCONSTRUCTOR_BYCHANCE_ISMATCHING  TEST  ///< Define to get a unique test name.
#define TEST_NUMBEROFPIXELSHORIZONTAL_800_BYCHANCE_ISMATCHING                 TEST  ///< Define to get a unique test name.
#define TEST_NUMBEROFPIXELSHORIZONTAL_1000_BYCHANCE_ISMATCHING                TEST  ///< Define to get a unique test name.
#define TEST_NUMBEROFPIXELSVERTICAL_DEFAULTCONSTRUCTOR_BYCHANCE_ISMATCHING    TEST  ///< Define to get a unique test name.
#define TEST_NUMBEROFPIXELSVERTICAL_400_BYCHANCE_ISMATCHING                   TEST  ///< Define to get a unique test name.
#define TEST_NUMBEROFPIXELSVERTICAL_600_BYCHANCE_ISMATCHING                   TEST  ///< Define to get a unique test name.

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the bucket size in horizontal direction.
///
/// Tests whether the bucket size in horizontal direction does match the
/// expected bucket size or not. The default constructor is used. Hence, the
/// expectation is to get the default bucket size.
///////////////////////////////////////////////////////////////////////////////
TEST_BUCKETSIZEHORIZONTAL_DEFAULTCONSTRUCTOR_BYCHANCE_ISMATCHING(FeatureBucketerByChance, Test_BucketSizeHorizontal_DefaultConstructor_ByChance_IsMatching)
{
    const float64 BucketSizeHorizontal {128.0};

    FeatureBucketerByChance FB;

    ASSERT_DOUBLE_EQ(FB.GetBucketSizeHorizontal(), BucketSizeHorizontal);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the bucket size in horizontal direction.
///
/// Tests whether the bucket size in horizontal direction does match the
/// expected bucket size or not. The expectation is to get a bucket size of 80
/// pixels.
///////////////////////////////////////////////////////////////////////////////
TEST_BUCKETSIZEHORIZONTAL_80_BYCHANCE_ISMATCHING(FeatureBucketerByChance, Test_BucketSizeHorizontal_80_ByChance_IsMatching)
{
    const uint64  NumberOfPixelsHorizontal  {800U};
    const uint64  NumberOfPixelsVertical    {400U};
    const uint64  NumberOfBucketsHorizontal {10U};
    const uint64  NumberOfBucketsVertical   {8U};
    const float64 BucketSizeHorizontal      {80.0};

    FeatureBucketerByChance FB(NumberOfPixelsHorizontal, NumberOfPixelsVertical, NumberOfBucketsHorizontal, NumberOfBucketsVertical);

    ASSERT_DOUBLE_EQ(FB.GetBucketSizeHorizontal(), BucketSizeHorizontal);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the bucket size in horizontal direction.
///
/// Tests whether the bucket size in horizontal direction does match the
/// expected bucket size or not. The expectation is to get a bucket size of 250
/// pixels.
///////////////////////////////////////////////////////////////////////////////
TEST_BUCKETSIZEHORIZONTAL_250_BYCHANCE_ISMATCHING(FeatureBucketerByChance, Test_BucketSizeHorizontal_250_ByChance_IsMatching)
{
    const uint64       NumberOfPixelsHorizontal  {1000U};
    const uint64       NumberOfPixelsVertical    {600U};
    const uint64       NumberOfBucketsHorizontal {4U};
    const uint64       NumberOfBucketsVertical   {2U};
    const MatrixUInt64 FeatureMask               {MatrixUInt64::Zero(NumberOfBucketsVertical, NumberOfBucketsHorizontal)};
    const float64      BucketSizeHorizontal      {250.0};

    FeatureBucketerByChance FB(NumberOfPixelsHorizontal, NumberOfPixelsVertical, FeatureMask);

    ASSERT_DOUBLE_EQ(FB.GetBucketSizeHorizontal(), BucketSizeHorizontal);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the bucket size in vertical direction.
///
/// Tests whether the bucket size in vertical direction does match the expected
/// bucket size or not. The default constructor is used. Hence, the expectation
/// is to get the default bucket size.
///////////////////////////////////////////////////////////////////////////////
TEST_BUCKETSIZEVERTICAL_DEFAULTCONSTRUCTOR_BYCHANCE_ISMATCHING(FeatureBucketerByChance, Test_BucketSizeVertical_DefaultConstructor_ByChance_IsMatching)
{
    const float64 BucketSizeVertical {192.0};

    FeatureBucketerByChance FB;

    ASSERT_DOUBLE_EQ(FB.GetBucketSizeVertical(), BucketSizeVertical);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the bucket size in vertical direction.
///
/// Tests whether the bucket size in vertical direction does match the expected
/// bucket size or not. The expectation is to get a bucket size of 50 pixels.
///////////////////////////////////////////////////////////////////////////////
TEST_BUCKETSIZEVERTICAL_50_BYCHANCE_ISMATCHING(FeatureBucketerByChance, Test_BucketSizeVertical_50_ByChance_IsMatching)
{
    const uint64  NumberOfPixelsHorizontal  {800U};
    const uint64  NumberOfPixelsVertical    {400U};
    const uint64  NumberOfBucketsHorizontal {10U};
    const uint64  NumberOfBucketsVertical   {8U};
    const float64 BucketSizeVertical        {50.0};

    FeatureBucketerByChance FB(NumberOfPixelsHorizontal, NumberOfPixelsVertical, NumberOfBucketsHorizontal, NumberOfBucketsVertical);

    ASSERT_DOUBLE_EQ(FB.GetBucketSizeVertical(), BucketSizeVertical);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the bucket size in vertical direction.
///
/// Tests whether the bucket size in vertical direction does match the expected
/// bucket size or not. The expectation is to get a bucket size of 300 pixels.
///////////////////////////////////////////////////////////////////////////////
TEST_BUCKETSIZEVERTICAL_300_BYCHANCE_ISMATCHING(FeatureBucketerByChance, Test_BucketSizeVertical_300_ByChance_IsMatching)
{
    const uint64       NumberOfPixelsHorizontal  {1000U};
    const uint64       NumberOfPixelsVertical    {600U};
    const uint64       NumberOfBucketsHorizontal {4U};
    const uint64       NumberOfBucketsVertical   {2U};
    const MatrixUInt64 FeatureMask               {MatrixUInt64::Zero(NumberOfBucketsVertical, NumberOfBucketsHorizontal)};
    const float64      BucketSizeVertical        {300.0};

    FeatureBucketerByChance FB(NumberOfPixelsHorizontal, NumberOfPixelsVertical, FeatureMask);

    ASSERT_DOUBLE_EQ(FB.GetBucketSizeVertical(), BucketSizeVertical);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of buckets in horizontal direction.
///
/// Tests whether the number of buckets in horizontal direction does match the
/// expected number or not. The default constructor is used. Hence, the
/// expectation is to get 8 buckets.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFBUCKETSHORIZONTAL_DEFAULTCONSTRUCTOR_BYCHANCE_ISMATCHING(FeatureBucketerByChance, Test_NumberOfBucketsHorizontal_DefaultConstructor_ByChance_IsMatching)
{
    const uint64 NumberOfBucketsHorizontal {8U};

    FeatureBucketerByChance FB;

    ASSERT_EQ(FB.GetNumberOfBucketsHorizontal(), NumberOfBucketsHorizontal);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of buckets in horizontal direction.
///
/// Tests whether the number of buckets in horizontal direction does match the
/// expected number or not. The expectation is to get 4 buckets.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFBUCKETSHORIZONTAL_4_BYCHANCE_ISMATCHING(FeatureBucketerByChance, Test_NumberOfBucketsHorizontal_4_ByChance_IsMatching)
{
    const uint64       NumberOfPixelsHorizontal  {1000U};
    const uint64       NumberOfPixelsVertical    {600U};
    const uint64       NumberOfBucketsHorizontal {4U};
    const uint64       NumberOfBucketsVertical   {2U};
    const MatrixUInt64 FeatureMask               {MatrixUInt64::Zero(NumberOfBucketsVertical, NumberOfBucketsHorizontal)};

    FeatureBucketerByChance FB(NumberOfPixelsHorizontal, NumberOfPixelsVertical, FeatureMask);

    ASSERT_DOUBLE_EQ(FB.GetNumberOfBucketsHorizontal(), NumberOfBucketsHorizontal);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of buckets in horizontal direction.
///
/// Tests whether the number of buckets in horizontal direction does match the
/// expected number or not. The expectation is to get 10 buckets.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFBUCKETSHORIZONTAL_10_BYCHANCE_ISMATCHING(FeatureBucketerByChance, Test_NumberOfBucketsHorizontal_10_ByChance_IsMatching)
{
    const uint64  NumberOfPixelsHorizontal  {800U};
    const uint64  NumberOfPixelsVertical    {400U};
    const uint64  NumberOfBucketsHorizontal {10U};
    const uint64  NumberOfBucketsVertical   {8U};

    FeatureBucketerByChance FB(NumberOfPixelsHorizontal, NumberOfPixelsVertical, NumberOfBucketsHorizontal, NumberOfBucketsVertical);

    ASSERT_DOUBLE_EQ(FB.GetNumberOfBucketsHorizontal(), NumberOfBucketsHorizontal);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of buckets in vertical direction.
///
/// Tests whether the number of buckets in vertical direction does match the
/// expected number or not. The default constructor is used. Hence, the
/// expectation is to get 4 buckets.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFBUCKETSVERTICAL_DEFAULTCONSTRUCTOR_BYCHANCE_ISMATCHING(FeatureBucketerByChance, Test_NumberOfBucketsVertical_DefaultConstructor_ByChance_IsMatching)
{
    const uint64 NumberOfBucketsVertical {4U};

    FeatureBucketerByChance FB;

    ASSERT_EQ(FB.GetNumberOfBucketsVertical(), NumberOfBucketsVertical);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of buckets in vertical direction.
///
/// Tests whether the number of buckets in vertical direction does match the
/// expected number or not. The expectation is to get 2 buckets.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFBUCKETSVERTICAL_2_BYCHANCE_ISMATCHING(FeatureBucketerByChance, Test_NumberOfBucketsVertical_2_ByChance_IsMatching)
{
    const uint64       NumberOfPixelsHorizontal  {1000U};
    const uint64       NumberOfPixelsVertical    {600U};
    const uint64       NumberOfBucketsHorizontal {4U};
    const uint64       NumberOfBucketsVertical   {2U};
    const MatrixUInt64 FeatureMask               {MatrixUInt64::Zero(NumberOfBucketsVertical, NumberOfBucketsHorizontal)};

    FeatureBucketerByChance FB(NumberOfPixelsHorizontal, NumberOfPixelsVertical, FeatureMask);

    ASSERT_DOUBLE_EQ(FB.GetNumberOfBucketsVertical(), NumberOfBucketsVertical);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of buckets in vertical direction.
///
/// Tests whether the number of buckets in vertical direction does match the
/// expected number or not. The expectation is to get 8 buckets.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFBUCKETSVERTICAL_8_BYCHANCE_ISMATCHING(FeatureBucketerByChance, Test_NumberOfBucketsVertical_8_ByChance_IsMatching)
{
    const uint64  NumberOfPixelsHorizontal  {800U};
    const uint64  NumberOfPixelsVertical    {400U};
    const uint64  NumberOfBucketsHorizontal {10U};
    const uint64  NumberOfBucketsVertical   {8U};

    FeatureBucketerByChance FB(NumberOfPixelsHorizontal, NumberOfPixelsVertical, NumberOfBucketsHorizontal, NumberOfBucketsVertical);

    ASSERT_DOUBLE_EQ(FB.GetNumberOfBucketsVertical(), NumberOfBucketsVertical);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of pixels in horizontal direction.
///
/// Tests whether the number of pixels in horizontal direction does match the
/// expected number or not. The default constructor is used. Hence, the
/// expectation is to get 1024 pixels.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFPIXELSHORIZONTAL_DEFAULTCONSTRUCTOR_BYCHANCE_ISMATCHING(FeatureBucketerByChance, Test_NumberOfPixelsHorizontal_DefaultConstructor_ByChance_IsMatching)
{
    const uint64 NumberOfPixelsHorizontal {1024U};

    FeatureBucketerByChance FB;

    ASSERT_EQ(FB.GetNumberOfPixelsHorizontal(), NumberOfPixelsHorizontal);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of pixels in horizontal direction.
///
/// Tests whether the number of pixels in horizontal direction does match the
/// expected number or not. The expectation is to get 800 pixels.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFPIXELSHORIZONTAL_800_BYCHANCE_ISMATCHING(FeatureBucketerByChance, Test_NumberOfPixelsHorizontal_800_ByChance_IsMatching)
{
    const uint64  NumberOfPixelsHorizontal  {800U};
    const uint64  NumberOfPixelsVertical    {400U};
    const uint64  NumberOfBucketsHorizontal {10U};
    const uint64  NumberOfBucketsVertical   {8U};

    FeatureBucketerByChance FB(NumberOfPixelsHorizontal, NumberOfPixelsVertical, NumberOfBucketsHorizontal, NumberOfBucketsVertical);

    ASSERT_DOUBLE_EQ(FB.GetNumberOfPixelsHorizontal(), NumberOfPixelsHorizontal);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of pixels in horizontal direction.
///
/// Tests whether the number of pixels in horizontal direction does match the
/// expected number or not. The expectation is to get 1000 pixels.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFPIXELSHORIZONTAL_1000_BYCHANCE_ISMATCHING(FeatureBucketerByChance, Test_NumberOfPixelsHorizontal_1000_ByChance_IsMatching)
{
    const uint64       NumberOfPixelsHorizontal  {1000U};
    const uint64       NumberOfPixelsVertical    {600U};
    const uint64       NumberOfBucketsHorizontal {4U};
    const uint64       NumberOfBucketsVertical   {2U};
    const MatrixUInt64 FeatureMask               {MatrixUInt64::Zero(NumberOfBucketsHorizontal, NumberOfBucketsVertical)};

    FeatureBucketerByChance FB(NumberOfPixelsHorizontal, NumberOfPixelsVertical, FeatureMask);

    ASSERT_DOUBLE_EQ(FB.GetNumberOfPixelsHorizontal(), NumberOfPixelsHorizontal);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of pixels in vertical direction.
///
/// Tests whether the number of pixels in vertical direction does match the
/// expected number or not. The default constructor is used. Hence, the
/// expectation is to get 768 pixels.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFPIXELSVERTICAL_DEFAULTCONSTRUCTOR_BYCHANCE_ISMATCHING(FeatureBucketerByChance, Test_NumberOfPixelsVertical_DefaultConstructor_ByChance_IsMatching)
{
    const uint64 NumberOfPixelsVertical {768U};

    FeatureBucketerByChance FB;

    ASSERT_EQ(FB.GetNumberOfPixelsVertical(), NumberOfPixelsVertical);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of pixels in vertical direction.
///
/// Tests whether the number of pixels in vertical direction does match the
/// expected number or not. The expectation is to get 400 pixels.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFPIXELSVERTICAL_400_BYCHANCE_ISMATCHING(FeatureBucketerByChance, Test_NumberOfPixelsVertical_400_ByChance_IsMatching)
{
    const uint64  NumberOfPixelsHorizontal  {800U};
    const uint64  NumberOfPixelsVertical    {400U};
    const uint64  NumberOfBucketsHorizontal {10U};
    const uint64  NumberOfBucketsVertical   {8U};

    FeatureBucketerByChance FB(NumberOfPixelsHorizontal, NumberOfPixelsVertical, NumberOfBucketsHorizontal, NumberOfBucketsVertical);

    ASSERT_DOUBLE_EQ(FB.GetNumberOfPixelsVertical(), NumberOfPixelsVertical);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of pixels in vertical direction.
///
/// Tests whether the number of pixels in vertical direction does match the
/// expected number or not. The expectation is to get 600 pixels.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFPIXELSVERTICAL_600_BYCHANCE_ISMATCHING(FeatureBucketerByChance, Test_NumberOfPixelsVertical_600_ByChance_IsMatching)
{
    const uint64       NumberOfPixelsHorizontal  {1000U};
    const uint64       NumberOfPixelsVertical    {600U};
    const uint64       NumberOfBucketsHorizontal {4U};
    const uint64       NumberOfBucketsVertical   {2U};
    const MatrixUInt64 FeatureMask               {MatrixUInt64::Zero(NumberOfBucketsHorizontal, NumberOfBucketsVertical)};

    FeatureBucketerByChance FB(NumberOfPixelsHorizontal, NumberOfPixelsVertical, FeatureMask);

    ASSERT_DOUBLE_EQ(FB.GetNumberOfPixelsVertical(), NumberOfPixelsVertical);
}