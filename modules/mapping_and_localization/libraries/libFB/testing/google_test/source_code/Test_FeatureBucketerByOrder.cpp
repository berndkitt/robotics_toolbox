///////////////////////////////////////////////////////////////////////////////
/// \file Test_FeatureBucketerByOrder.cpp
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

#include "../../../source_code/include/FeatureBucketerByOrder.h"

// definition of macros for the unit tests
#define TEST_BUCKETSIZEHORIZONTAL_DEFAULTCONSTRUCTOR_BYORDER_ISMATCHING      TEST   ///< Define to get a unique test name.
#define TEST_BUCKETSIZEHORIZONTAL_80_BYORDER_ISMATCHING                      TEST   ///< Define to get a unique test name.
#define TEST_BUCKETSIZEHORIZONTAL_250_BYORDER_ISMATCHING                     TEST   ///< Define to get a unique test name.
#define TEST_BUCKETSIZEVERTICAL_DEFAULTCONSTRUCTOR_BYORDER_ISMATCHING        TEST   ///< Define to get a unique test name.
#define TEST_BUCKETSIZEVERTICAL_50_BYORDER_ISMATCHING                        TEST   ///< Define to get a unique test name.
#define TEST_BUCKETSIZEVERTICAL_300_BYORDER_ISMATCHING                       TEST   ///< Define to get a unique test name.
#define TEST_NUMBEROFBUCKETSHORIZONTAL_DEFAULTCONSTRUCTOR_BYORDER_ISMATCHING TEST   ///< Define to get a unique test name.
#define TEST_NUMBEROFBUCKETSHORIZONTAL_4_BYORDER_ISMATCHING                  TEST   ///< Define to get a unique test name.
#define TEST_NUMBEROFBUCKETSHORIZONTAL_10_BYORDER_ISMATCHING                 TEST   ///< Define to get a unique test name.
#define TEST_NUMBEROFBUCKETSVERTICAL_DEFAULTCONSTRUCTOR_BYORDER_ISMATCHING   TEST   ///< Define to get a unique test name.
#define TEST_NUMBEROFBUCKETSVERTICAL_2_BYORDER_ISMATCHING                    TEST   ///< Define to get a unique test name.
#define TEST_NUMBEROFBUCKETSVERTICAL_8_BYORDER_ISMATCHING                    TEST   ///< Define to get a unique test name.
#define TEST_NUMBEROFPIXELSHORIZONTAL_DEFAULTCONSTRUCTOR_BYORDER_ISMATCHING  TEST   ///< Define to get a unique test name.
#define TEST_NUMBEROFPIXELSHORIZONTAL_800_BYORDER_ISMATCHING                 TEST   ///< Define to get a unique test name.
#define TEST_NUMBEROFPIXELSHORIZONTAL_1000_BYORDER_ISMATCHING                TEST   ///< Define to get a unique test name.
#define TEST_NUMBEROFPIXELSVERTICAL_DEFAULTCONSTRUCTOR_BYORDER_ISMATCHING    TEST   ///< Define to get a unique test name.
#define TEST_NUMBEROFPIXELSVERTICAL_400_BYORDER_ISMATCHING                   TEST   ///< Define to get a unique test name.
#define TEST_NUMBEROFPIXELSVERTICAL_600_BYORDER_ISMATCHING                   TEST   ///< Define to get a unique test name.

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the bucket size in horizontal direction.
///
/// Tests whether the bucket size in horizontal direction does match the
/// expected bucket size or not. The default constructor is used. Hence, the
/// expectation is to get the default bucket size.
///////////////////////////////////////////////////////////////////////////////
TEST_BUCKETSIZEHORIZONTAL_DEFAULTCONSTRUCTOR_BYORDER_ISMATCHING(FeatureBucketerByOrder, Test_BucketSizeHorizontal_DefaultConstructor_ByOrder_IsMatching)
{
    const float64 BucketSizeHorizontal {128.0};

    FeatureBucketerByOrder FB;

    ASSERT_DOUBLE_EQ(FB.GetBucketSizeHorizontal(), BucketSizeHorizontal);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the bucket size in horizontal direction.
///
/// Tests whether the bucket size in horizontal direction does match the
/// expected bucket size or not. The expectation is to get a bucket size of 80
/// pixels.
///////////////////////////////////////////////////////////////////////////////
TEST_BUCKETSIZEHORIZONTAL_80_BYORDER_ISMATCHING(FeatureBucketerByOrder, Test_BucketSizeHorizontal_80_ByOrder_IsMatching)
{
    const uint64  NumberOfPixelsHorizontal  {800U};
    const uint64  NumberOfPixelsVertical    {400U};
    const uint64  NumberOfBucketsHorizontal {10U};
    const uint64  NumberOfBucketsVertical   {8U};
    const float64 BucketSizeHorizontal      {80.0};

    FeatureBucketerByOrder FB(NumberOfPixelsHorizontal, NumberOfPixelsVertical, NumberOfBucketsHorizontal, NumberOfBucketsVertical);

    ASSERT_DOUBLE_EQ(FB.GetBucketSizeHorizontal(), BucketSizeHorizontal);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the bucket size in horizontal direction.
///
/// Tests whether the bucket size in horizontal direction does match the
/// expected bucket size or not. The expectation is to get a bucket size of 250
/// pixels.
///////////////////////////////////////////////////////////////////////////////
TEST_BUCKETSIZEHORIZONTAL_250_BYORDER_ISMATCHING(FeatureBucketerByOrder, Test_BucketSizeHorizontal_250_ByOrder_IsMatching)
{
    const uint64       NumberOfPixelsHorizontal  {1000U};
    const uint64       NumberOfPixelsVertical    {600U};
    const uint64       NumberOfBucketsHorizontal {4U};
    const uint64       NumberOfBucketsVertical   {2U};
    const MatrixUInt64 FeatureMask               {MatrixUInt64::Zero(NumberOfBucketsVertical, NumberOfBucketsHorizontal)};
    const float64      BucketSizeHorizontal      {250.0};

    FeatureBucketerByOrder FB(NumberOfPixelsHorizontal, NumberOfPixelsVertical, FeatureMask);

    ASSERT_DOUBLE_EQ(FB.GetBucketSizeHorizontal(), BucketSizeHorizontal);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the bucket size in vertical direction.
///
/// Tests whether the bucket size in vertical direction does match the expected
/// bucket size or not. The default constructor is used. Hence, the expectation
/// is to get the default bucket size.
///////////////////////////////////////////////////////////////////////////////
TEST_BUCKETSIZEVERTICAL_DEFAULTCONSTRUCTOR_BYORDER_ISMATCHING(FeatureBucketerByOrder, Test_BucketSizeVertical_DefaultConstructor_ByOrder_IsMatching)
{
    const float64 BucketSizeVertical {192.0};

    FeatureBucketerByOrder FB;

    ASSERT_DOUBLE_EQ(FB.GetBucketSizeVertical(), BucketSizeVertical);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the bucket size in vertical direction.
///
/// Tests whether the bucket size in vertical direction does match the expected
/// bucket size or not. The expectation is to get a bucket size of 50 pixels.
///////////////////////////////////////////////////////////////////////////////
TEST_BUCKETSIZEVERTICAL_50_BYORDER_ISMATCHING(FeatureBucketerByOrder, Test_BucketSizeVertical_50_ByOrder_IsMatching)
{
    const uint64  NumberOfPixelsHorizontal  {800U};
    const uint64  NumberOfPixelsVertical    {400U};
    const uint64  NumberOfBucketsHorizontal {10U};
    const uint64  NumberOfBucketsVertical   {8U};
    const float64 BucketSizeVertical        {50.0};

    FeatureBucketerByOrder FB(NumberOfPixelsHorizontal, NumberOfPixelsVertical, NumberOfBucketsHorizontal, NumberOfBucketsVertical);

    ASSERT_DOUBLE_EQ(FB.GetBucketSizeVertical(), BucketSizeVertical);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the bucket size in vertical direction.
///
/// Tests whether the bucket size in vertical direction does match the expected
/// bucket size or not. The expectation is to get a bucket size of 300 pixels.
///////////////////////////////////////////////////////////////////////////////
TEST_BUCKETSIZEVERTICAL_300_BYORDER_ISMATCHING(FeatureBucketerByOrder, Test_BucketSizeVertical_300_ByOrder_IsMatching)
{
    const uint64       NumberOfPixelsHorizontal  {1000U};
    const uint64       NumberOfPixelsVertical    {600U};
    const uint64       NumberOfBucketsHorizontal {4U};
    const uint64       NumberOfBucketsVertical   {2U};
    const MatrixUInt64 FeatureMask               {MatrixUInt64::Zero(NumberOfBucketsVertical, NumberOfBucketsHorizontal)};
    const float64      BucketSizeVertical        {300.0};

    FeatureBucketerByOrder FB(NumberOfPixelsHorizontal, NumberOfPixelsVertical, FeatureMask);

    ASSERT_DOUBLE_EQ(FB.GetBucketSizeVertical(), BucketSizeVertical);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of buckets in horizontal direction.
///
/// Tests whether the number of buckets in horizontal direction does match the
/// expected number or not. The default constructor is used. Hence, the
/// expectation is to get 8 buckets.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFBUCKETSHORIZONTAL_DEFAULTCONSTRUCTOR_BYORDER_ISMATCHING(FeatureBucketerByOrder, Test_NumberOfBucketsHorizontal_DefaultConstructor_ByOrder_IsMatching)
{
    const uint64 NumberOfBucketsHorizontal {8U};

    FeatureBucketerByOrder FB;

    ASSERT_EQ(FB.GetNumberOfBucketsHorizontal(), NumberOfBucketsHorizontal);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of buckets in horizontal direction.
///
/// Tests whether the number of buckets in horizontal direction does match the
/// expected number or not. The expectation is to get 4 buckets.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFBUCKETSHORIZONTAL_4_BYORDER_ISMATCHING(FeatureBucketerByOrder, Test_NumberOfBucketsHorizontal_4_ByOrder_IsMatching)
{
    const uint64       NumberOfPixelsHorizontal  {1000U};
    const uint64       NumberOfPixelsVertical    {600U};
    const uint64       NumberOfBucketsHorizontal {4U};
    const uint64       NumberOfBucketsVertical   {2U};
    const MatrixUInt64 FeatureMask               {MatrixUInt64::Zero(NumberOfBucketsVertical, NumberOfBucketsHorizontal)};

    FeatureBucketerByOrder FB(NumberOfPixelsHorizontal, NumberOfPixelsVertical, FeatureMask);

    ASSERT_DOUBLE_EQ(FB.GetNumberOfBucketsHorizontal(), NumberOfBucketsHorizontal);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of buckets in horizontal direction.
///
/// Tests whether the number of buckets in horizontal direction does match the
/// expected number or not. The expectation is to get 10 buckets.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFBUCKETSHORIZONTAL_10_BYORDER_ISMATCHING(FeatureBucketerByOrder, Test_NumberOfBucketsHorizontal_10_ByOrder_IsMatching)
{
    const uint64  NumberOfPixelsHorizontal  {800U};
    const uint64  NumberOfPixelsVertical    {400U};
    const uint64  NumberOfBucketsHorizontal {10U};
    const uint64  NumberOfBucketsVertical   {8U};

    FeatureBucketerByOrder FB(NumberOfPixelsHorizontal, NumberOfPixelsVertical, NumberOfBucketsHorizontal, NumberOfBucketsVertical);

    ASSERT_DOUBLE_EQ(FB.GetNumberOfBucketsHorizontal(), NumberOfBucketsHorizontal);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of buckets in vertical direction.
///
/// Tests whether the number of buckets in vertical direction does match the
/// expected number or not. The default constructor is used. Hence, the
/// expectation is to get 4 buckets.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFBUCKETSVERTICAL_DEFAULTCONSTRUCTOR_BYORDER_ISMATCHING(FeatureBucketerByOrder, Test_NumberOfBucketsVertical_DefaultConstructor_ByOrder_IsMatching)
{
    const uint64 NumberOfBucketsVertical {4U};

    FeatureBucketerByOrder FB;

    ASSERT_EQ(FB.GetNumberOfBucketsVertical(), NumberOfBucketsVertical);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of buckets in vertical direction.
///
/// Tests whether the number of buckets in vertical direction does match the
/// expected number or not. The expectation is to get 2 buckets.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFBUCKETSVERTICAL_2_BYORDER_ISMATCHING(FeatureBucketerByOrder, Test_NumberOfBucketsVertical_2_ByOrder_IsMatching)
{
    const uint64       NumberOfPixelsHorizontal  {1000U};
    const uint64       NumberOfPixelsVertical    {600U};
    const uint64       NumberOfBucketsHorizontal {4U};
    const uint64       NumberOfBucketsVertical   {2U};
    const MatrixUInt64 FeatureMask               {MatrixUInt64::Zero(NumberOfBucketsVertical, NumberOfBucketsHorizontal)};

    FeatureBucketerByOrder FB(NumberOfPixelsHorizontal, NumberOfPixelsVertical, FeatureMask);

    ASSERT_DOUBLE_EQ(FB.GetNumberOfBucketsVertical(), NumberOfBucketsVertical);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of buckets in vertical direction.
///
/// Tests whether the number of buckets in vertical direction does match the
/// expected number or not. The expectation is to get 8 buckets.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFBUCKETSVERTICAL_8_BYORDER_ISMATCHING(FeatureBucketerByOrder, Test_NumberOfBucketsVertical_8_ByOrder_IsMatching)
{
    const uint64  NumberOfPixelsHorizontal  {800U};
    const uint64  NumberOfPixelsVertical    {400U};
    const uint64  NumberOfBucketsHorizontal {10U};
    const uint64  NumberOfBucketsVertical   {8U};

    FeatureBucketerByOrder FB(NumberOfPixelsHorizontal, NumberOfPixelsVertical, NumberOfBucketsHorizontal, NumberOfBucketsVertical);

    ASSERT_DOUBLE_EQ(FB.GetNumberOfBucketsVertical(), NumberOfBucketsVertical);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of pixels in horizontal direction.
///
/// Tests whether the number of pixels in horizontal direction does match the
/// expected number or not. The default constructor is used. Hence, the
/// expectation is to get 1024 pixels.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFPIXELSHORIZONTAL_DEFAULTCONSTRUCTOR_BYORDER_ISMATCHING(FeatureBucketerByOrder, Test_NumberOfPixelsHorizontal_DefaultConstructor_ByOrder_IsMatching)
{
    const uint64 NumberOfPixelsHorizontal {1024U};

    FeatureBucketerByOrder FB;

    ASSERT_EQ(FB.GetNumberOfPixelsHorizontal(), NumberOfPixelsHorizontal);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of pixels in horizontal direction.
///
/// Tests whether the number of pixels in horizontal direction does match the
/// expected number or not. The expectation is to get 800 pixels.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFPIXELSHORIZONTAL_800_BYORDER_ISMATCHING(FeatureBucketerByOrder, Test_NumberOfPixelsHorizontal_800_ByOrder_IsMatching)
{
    const uint64  NumberOfPixelsHorizontal  {800U};
    const uint64  NumberOfPixelsVertical    {400U};
    const uint64  NumberOfBucketsHorizontal {10U};
    const uint64  NumberOfBucketsVertical   {8U};

    FeatureBucketerByOrder FB(NumberOfPixelsHorizontal, NumberOfPixelsVertical, NumberOfBucketsHorizontal, NumberOfBucketsVertical);

    ASSERT_DOUBLE_EQ(FB.GetNumberOfPixelsHorizontal(), NumberOfPixelsHorizontal);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of pixels in horizontal direction.
///
/// Tests whether the number of pixels in horizontal direction does match the
/// expected number or not. The expectation is to get 1000 pixels.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFPIXELSHORIZONTAL_1000_BYORDER_ISMATCHING(FeatureBucketerByOrder, Test_NumberOfPixelsHorizontal_1000_ByOrder_IsMatching)
{
    const uint64       NumberOfPixelsHorizontal  {1000U};
    const uint64       NumberOfPixelsVertical    {600U};
    const uint64       NumberOfBucketsHorizontal {4U};
    const uint64       NumberOfBucketsVertical   {2U};
    const MatrixUInt64 FeatureMask               {MatrixUInt64::Zero(NumberOfBucketsHorizontal, NumberOfBucketsVertical)};

    FeatureBucketerByOrder FB(NumberOfPixelsHorizontal, NumberOfPixelsVertical, FeatureMask);

    ASSERT_DOUBLE_EQ(FB.GetNumberOfPixelsHorizontal(), NumberOfPixelsHorizontal);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of pixels in vertical direction.
///
/// Tests whether the number of pixels in vertical direction does match the
/// expected number or not. The default constructor is used. Hence, the
/// expectation is to get 768 pixels.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFPIXELSVERTICAL_DEFAULTCONSTRUCTOR_BYORDER_ISMATCHING(FeatureBucketerByOrder, Test_NumberOfPixelsVertical_DefaultConstructor_ByOrder_IsMatching)
{
    const uint64 NumberOfPixelsVertical {768U};

    FeatureBucketerByOrder FB;

    ASSERT_EQ(FB.GetNumberOfPixelsVertical(), NumberOfPixelsVertical);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of pixels in vertical direction.
///
/// Tests whether the number of pixels in vertical direction does match the
/// expected number or not. The expectation is to get 400 pixels.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFPIXELSVERTICAL_400_BYORDER_ISMATCHING(FeatureBucketerByOrder, Test_NumberOfPixelsVertical_400_ByOrder_IsMatching)
{
    const uint64  NumberOfPixelsHorizontal  {800U};
    const uint64  NumberOfPixelsVertical    {400U};
    const uint64  NumberOfBucketsHorizontal {10U};
    const uint64  NumberOfBucketsVertical   {8U};

    FeatureBucketerByOrder FB(NumberOfPixelsHorizontal, NumberOfPixelsVertical, NumberOfBucketsHorizontal, NumberOfBucketsVertical);

    ASSERT_DOUBLE_EQ(FB.GetNumberOfPixelsVertical(), NumberOfPixelsVertical);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of pixels in vertical direction.
///
/// Tests whether the number of pixels in vertical direction does match the
/// expected number or not. The expectation is to get 600 pixels.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFPIXELSVERTICAL_600_BYORDER_ISMATCHING(FeatureBucketerByOrder, Test_NumberOfPixelsVertical_600_ByOrder_IsMatching)
{
    const uint64       NumberOfPixelsHorizontal  {1000U};
    const uint64       NumberOfPixelsVertical    {600U};
    const uint64       NumberOfBucketsHorizontal {4U};
    const uint64       NumberOfBucketsVertical   {2U};
    const MatrixUInt64 FeatureMask               {MatrixUInt64::Zero(NumberOfBucketsHorizontal, NumberOfBucketsVertical)};

    FeatureBucketerByOrder FB(NumberOfPixelsHorizontal, NumberOfPixelsVertical, FeatureMask);

    ASSERT_DOUBLE_EQ(FB.GetNumberOfPixelsVertical(), NumberOfPixelsVertical);
}
