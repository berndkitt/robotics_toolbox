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
#define TEST_BUCKETSIZEVERTICAL_DEFAULTCONSTRUCTOR_BYORDER_ISMATCHING        TEST   ///< Define to get a unique test name.
#define TEST_NUMBEROFBUCKETSHORIZONTAL_DEFAULTCONSTRUCTOR_BYORDER_ISMATCHING TEST   ///< Define to get a unique test name.
#define TEST_NUMBEROFBUCKETSVERTICAL_DEFAULTCONSTRUCTOR_BYORDER_ISMATCHING   TEST   ///< Define to get a unique test name.
#define TEST_NUMBEROFPIXELSHORIZONTAL_DEFAULTCONSTRUCTOR_BYORDER_ISMATCHING  TEST   ///< Define to get a unique test name.
#define TEST_NUMBEROFPIXELSVERTICAL_DEFAULTCONSTRUCTOR_BYORDER_ISMATCHING    TEST   ///< Define to get a unique test name.

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
/// \brief Test for number of buckets in horizontal direction.
///
/// Tests whether the number of buckets in horizontal direction does match
/// the expected number or not. The default constructor is used. Hence, the
/// expectation is to get 8 buckets.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFBUCKETSHORIZONTAL_DEFAULTCONSTRUCTOR_BYORDER_ISMATCHING(FeatureBucketerByOrder, Test_NumberOfBucketsHorizontal_DefaultConstructor_ByOrder_IsMatching)
{
    const uint64 NumberOfBucketsHorizontal {8U};

    FeatureBucketerByOrder FB;

    ASSERT_EQ(FB.GetNumberOfBucketsHorizontal(), NumberOfBucketsHorizontal);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of buckets in vertical direction.
///
/// Tests whether the number of buckets in vertical direction does match
/// the expected number or not. The default constructor is used. Hence, the
/// expectation is to get 4 buckets.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFBUCKETSVERTICAL_DEFAULTCONSTRUCTOR_BYORDER_ISMATCHING(FeatureBucketerByOrder, Test_NumberOfBucketsVertical_DefaultConstructor_ByOrder_IsMatching)
{
    const uint64 NumberOfBucketsVertical {4U};

    FeatureBucketerByOrder FB;

    ASSERT_EQ(FB.GetNumberOfBucketsVertical(), NumberOfBucketsVertical);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of pixels in horizontal direction.
///
/// Tests whether the number of pixels in horizontal direction does match
/// the expected number or not. The default constructor is used. Hence, the
/// expectation is to get 1024 pixels.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFPIXELSHORIZONTAL_DEFAULTCONSTRUCTOR_BYORDER_ISMATCHING(FeatureBucketerByOrder, Test_NumberOfPixelsHorizontal_DefaultConstructor_ByOrder_IsMatching)
{
    const uint64 NumberOfPixelsHorizontal {1024U};

    FeatureBucketerByOrder FB;

    ASSERT_EQ(FB.GetNumberOfPixelsHorizontal(), NumberOfPixelsHorizontal);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of pixels in vertical direction.
///
/// Tests whether the number of pixels in vertical direction does match
/// the expected number or not. The default constructor is used. Hence, the
/// expectation is to get 768 pixels.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFPIXELSVERTICAL_DEFAULTCONSTRUCTOR_BYORDER_ISMATCHING(FeatureBucketerByOrder, Test_NumberOfPixelsVertical_DefaultConstructor_ByOrder_IsMatching)
{
    const uint64 NumberOfPixelsVertical {768U};

    FeatureBucketerByOrder FB;

    ASSERT_EQ(FB.GetNumberOfPixelsVertical(), NumberOfPixelsVertical);
}
