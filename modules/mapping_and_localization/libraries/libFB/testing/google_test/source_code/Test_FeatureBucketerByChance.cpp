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
#define TEST_NUMBEROFINDICES_8_SELECTED_0_REJECTED_BYCHANCE_ISMATCHING        TEST  ///< Define to get a unique test name.
#define TEST_NUMBEROFINDICES_16_SELECTED_8_REJECTED_BYCHANCE_ISMATCHING       TEST  ///< Define to get a unique test name.
#define TEST_NUMBEROFPIXELSHORIZONTAL_DEFAULTCONSTRUCTOR_BYCHANCE_ISMATCHING  TEST  ///< Define to get a unique test name.
#define TEST_NUMBEROFPIXELSHORIZONTAL_800_BYCHANCE_ISMATCHING                 TEST  ///< Define to get a unique test name.
#define TEST_NUMBEROFPIXELSHORIZONTAL_1000_BYCHANCE_ISMATCHING                TEST  ///< Define to get a unique test name.
#define TEST_NUMBEROFPIXELSVERTICAL_DEFAULTCONSTRUCTOR_BYCHANCE_ISMATCHING    TEST  ///< Define to get a unique test name.
#define TEST_NUMBEROFPIXELSVERTICAL_400_BYCHANCE_ISMATCHING                   TEST  ///< Define to get a unique test name.
#define TEST_NUMBEROFPIXELSVERTICAL_600_BYCHANCE_ISMATCHING                   TEST  ///< Define to get a unique test name.
#define TEST_REJECTEDFEATURE_3_SEED_0_BYCHANCE_ISMATCHING                     TEST  ///< Define to get a unique test name.
#define TEST_REJECTEDFEATURE_3_SEED_127_BYCHANCE_ISMATCHING                   TEST  ///< Define to get a unique test name.
#define TEST_SELECTEDFEATURE_0_SEED_0_BYCHANCE_ISMATCHING                     TEST  ///< Define to get a unique test name.
#define TEST_SELECTEDFEATURE_0_SEED_127_BYCHANCE_ISMATCHING                   TEST  ///< Define to get a unique test name.

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

    FeatureBucketerByChance Bucketer;

    ASSERT_DOUBLE_EQ(Bucketer.GetBucketSizeHorizontal(), BucketSizeHorizontal);
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

    FeatureBucketerByChance Bucketer(NumberOfPixelsHorizontal, NumberOfPixelsVertical, NumberOfBucketsHorizontal, NumberOfBucketsVertical);

    ASSERT_DOUBLE_EQ(Bucketer.GetBucketSizeHorizontal(), BucketSizeHorizontal);
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

    FeatureBucketerByChance Bucketer(NumberOfPixelsHorizontal, NumberOfPixelsVertical, FeatureMask);

    ASSERT_DOUBLE_EQ(Bucketer.GetBucketSizeHorizontal(), BucketSizeHorizontal);
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

    FeatureBucketerByChance Bucketer;

    ASSERT_DOUBLE_EQ(Bucketer.GetBucketSizeVertical(), BucketSizeVertical);
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

    FeatureBucketerByChance Bucketer(NumberOfPixelsHorizontal, NumberOfPixelsVertical, NumberOfBucketsHorizontal, NumberOfBucketsVertical);

    ASSERT_DOUBLE_EQ(Bucketer.GetBucketSizeVertical(), BucketSizeVertical);
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

    FeatureBucketerByChance Bucketer(NumberOfPixelsHorizontal, NumberOfPixelsVertical, FeatureMask);

    ASSERT_DOUBLE_EQ(Bucketer.GetBucketSizeVertical(), BucketSizeVertical);
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

    FeatureBucketerByChance Bucketer;

    ASSERT_EQ(Bucketer.GetNumberOfBucketsHorizontal(), NumberOfBucketsHorizontal);
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

    FeatureBucketerByChance Bucketer(NumberOfPixelsHorizontal, NumberOfPixelsVertical, FeatureMask);

    ASSERT_DOUBLE_EQ(Bucketer.GetNumberOfBucketsHorizontal(), NumberOfBucketsHorizontal);
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

    FeatureBucketerByChance Bucketer(NumberOfPixelsHorizontal, NumberOfPixelsVertical, NumberOfBucketsHorizontal, NumberOfBucketsVertical);

    ASSERT_DOUBLE_EQ(Bucketer.GetNumberOfBucketsHorizontal(), NumberOfBucketsHorizontal);
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

    FeatureBucketerByChance Bucketer;

    ASSERT_EQ(Bucketer.GetNumberOfBucketsVertical(), NumberOfBucketsVertical);
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

    FeatureBucketerByChance Bucketer(NumberOfPixelsHorizontal, NumberOfPixelsVertical, FeatureMask);

    ASSERT_DOUBLE_EQ(Bucketer.GetNumberOfBucketsVertical(), NumberOfBucketsVertical);
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

    FeatureBucketerByChance Bucketer(NumberOfPixelsHorizontal, NumberOfPixelsVertical, NumberOfBucketsHorizontal, NumberOfBucketsVertical);

    ASSERT_DOUBLE_EQ(Bucketer.GetNumberOfBucketsVertical(), NumberOfBucketsVertical);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of selected and rejected indices.
///
/// Tests whether the numbers of selected and rejected indices match the
/// expected numbers or not. The image points are created in a way that all
/// points will be selected and no point will be rejected.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFINDICES_8_SELECTED_0_REJECTED_BYCHANCE_ISMATCHING(FeatureBucketerByChance, Test_NumberOfIndices_8_Selected_0_Rejected_ByChance_IsMatching)
{
    const uint64 NumberOfPixelsHorizontal         {600U};
    const uint64 NumberOfPixelsVertical           {200U};
    const uint64 NumberOfBucketsHorizontal        {4U};
    const uint64 NumberOfBucketsVertical          {2U};
    const uint64 MaximumNumberOfFeaturesPerBucket {1U};
    const uint64 SeedValue                        {0U};
    const uint64 NumberOfSelectedIndicesExpected  {8U};
    const uint64 NumberOfRejectedIndicesExpected  {0U};

    FeatureBucketerByChance Bucketer(NumberOfPixelsHorizontal, NumberOfPixelsVertical, NumberOfBucketsHorizontal, NumberOfBucketsVertical, MaximumNumberOfFeaturesPerBucket, SeedValue);

    ListColumnVectorFloat64_2d ImagePoints;

    const float64 BucketSizeHorizontal {Bucketer.GetBucketSizeHorizontal()};
    const float64 BucketSizeVertical   {Bucketer.GetBucketSizeVertical()};

    for(uint64 i_Row {0U}; i_Row < NumberOfBucketsVertical; i_Row++)
    {
        const float64 CoordinateVertical {BucketSizeVertical * (0.5 + static_cast<float64>(i_Row))};

        for(uint64 i_Column {0U}; i_Column < NumberOfBucketsHorizontal; i_Column++)
        {
            const float64 CoordinateHorizontal {BucketSizeHorizontal * (0.5 + static_cast<float64>(i_Column))};

            ColumnVectorFloat64_2d ImagePoint(CoordinateHorizontal, CoordinateVertical);

            ImagePoints.push_back(ImagePoint);
        }
    }

    Bucketer.BucketFeatures(ImagePoints);

    const uint64 NumberOfSelectedIndices {Bucketer.GetSelectedIndices().size()};
    const uint64 NumberOfRejectedIndices {Bucketer.GetRejectedIndices().size()};

    ASSERT_EQ(NumberOfSelectedIndices, NumberOfSelectedIndicesExpected);
    ASSERT_EQ(NumberOfRejectedIndices, NumberOfRejectedIndicesExpected);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for number of selected and rejected indices.
///
/// Tests whether the numbers of selected and rejected indices match the
/// expected numbers or not. The image points are created in a way that 16
/// points will be selected and 8 points will be rejected.
///////////////////////////////////////////////////////////////////////////////
TEST_NUMBEROFINDICES_16_SELECTED_8_REJECTED_BYCHANCE_ISMATCHING(FeatureBucketerByChance, Test_NumberOfIndices_16_Selected_8_Rejected_ByChance_IsMatching)
{
    const uint64 NumberOfPixelsHorizontal         {600U};
    const uint64 NumberOfPixelsVertical           {200U};
    const uint64 NumberOfBucketsHorizontal        {4U};
    const uint64 NumberOfBucketsVertical          {2U};
    const uint64 MaximumNumberOfFeaturesPerBucket {2U};
    const uint64 SeedValue                        {0U};
    const uint64 NumberOfSelectedIndicesExpected  {16U};
    const uint64 NumberOfRejectedIndicesExpected  {8U};

    FeatureBucketerByChance Bucketer(NumberOfPixelsHorizontal, NumberOfPixelsVertical, NumberOfBucketsHorizontal, NumberOfBucketsVertical, MaximumNumberOfFeaturesPerBucket, SeedValue);

    ListColumnVectorFloat64_2d ImagePoints;

    const uint64  NumberOfFeaturesPerBucket {3U};
    const float64 PixelOffset               {2.0};
    const float64 BucketSizeHorizontal      {Bucketer.GetBucketSizeHorizontal()};
    const float64 BucketSizeVertical        {Bucketer.GetBucketSizeVertical()};

    for(uint64 i_ImagePoint {0U}; i_ImagePoint < NumberOfFeaturesPerBucket; i_ImagePoint++)
    {
        for(uint64 i_Row {0U}; i_Row < NumberOfBucketsVertical; i_Row++)
        {
            const float64 CoordinateVertical {BucketSizeVertical * (0.5 + static_cast<float64>(i_Row)) + static_cast<float64>(i_ImagePoint) * PixelOffset};

            for(uint64 i_Column {0U}; i_Column < NumberOfBucketsHorizontal; i_Column++)
            {
                const float64 CoordinateHorizontal {BucketSizeHorizontal * (0.5 + static_cast<float64>(i_Column)) + static_cast<float64>(i_ImagePoint) * PixelOffset};

                ColumnVectorFloat64_2d ImagePoint(CoordinateHorizontal, CoordinateVertical);

                ImagePoints.push_back(ImagePoint);
            }
        }
    }

    Bucketer.BucketFeatures(ImagePoints);

    const uint64 NumberOfSelectedIndices {Bucketer.GetSelectedIndices().size()};
    const uint64 NumberOfRejectedIndices {Bucketer.GetRejectedIndices().size()};

    ASSERT_EQ(NumberOfSelectedIndices, NumberOfSelectedIndicesExpected);
    ASSERT_EQ(NumberOfRejectedIndices, NumberOfRejectedIndicesExpected);
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

    FeatureBucketerByChance Bucketer;

    ASSERT_EQ(Bucketer.GetNumberOfPixelsHorizontal(), NumberOfPixelsHorizontal);
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

    FeatureBucketerByChance Bucketer(NumberOfPixelsHorizontal, NumberOfPixelsVertical, NumberOfBucketsHorizontal, NumberOfBucketsVertical);

    ASSERT_DOUBLE_EQ(Bucketer.GetNumberOfPixelsHorizontal(), NumberOfPixelsHorizontal);
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

    FeatureBucketerByChance Bucketer(NumberOfPixelsHorizontal, NumberOfPixelsVertical, FeatureMask);

    ASSERT_DOUBLE_EQ(Bucketer.GetNumberOfPixelsHorizontal(), NumberOfPixelsHorizontal);
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

    FeatureBucketerByChance Bucketer;

    ASSERT_EQ(Bucketer.GetNumberOfPixelsVertical(), NumberOfPixelsVertical);
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

    FeatureBucketerByChance Bucketer(NumberOfPixelsHorizontal, NumberOfPixelsVertical, NumberOfBucketsHorizontal, NumberOfBucketsVertical);

    ASSERT_DOUBLE_EQ(Bucketer.GetNumberOfPixelsVertical(), NumberOfPixelsVertical);
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

    FeatureBucketerByChance Bucketer(NumberOfPixelsHorizontal, NumberOfPixelsVertical, FeatureMask);

    ASSERT_DOUBLE_EQ(Bucketer.GetNumberOfPixelsVertical(), NumberOfPixelsVertical);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the coordinate of the first rejected feature.
///
/// Tests whether the image coordinates of the first rejected feature are
/// matching the expected coordinates or not. The seed value 0 is used to
/// initialize the selection of the features in each bucket.
///////////////////////////////////////////////////////////////////////////////
TEST_REJECTEDFEATURE_3_SEED_0_BYCHANCE_ISMATCHING(FeatureBucketerByChance, Test_RejectedFeature_3_Seed_0_ByChance_IsMatching)
{
    const uint64 NumberOfPixelsHorizontal         {600U};
    const uint64 NumberOfPixelsVertical           {200U};
    const uint64 NumberOfBucketsHorizontal        {4U};
    const uint64 NumberOfBucketsVertical          {2U};
    const uint64 MaximumNumberOfFeaturesPerBucket {3U};
    const uint64 SeedValue                        {0U};

    FeatureBucketerByChance Bucketer(NumberOfPixelsHorizontal, NumberOfPixelsVertical, NumberOfBucketsHorizontal, NumberOfBucketsVertical, MaximumNumberOfFeaturesPerBucket, SeedValue);

    ListColumnVectorFloat64_2d ImagePoints;

    const uint64  NumberOfFeaturesPerBucket {8U};
    const float64 PixelOffset               {2.0};
    const float64 BucketSizeHorizontal      {Bucketer.GetBucketSizeHorizontal()};
    const float64 BucketSizeVertical        {Bucketer.GetBucketSizeVertical()};

    for(uint64 i_ImagePoint {0U}; i_ImagePoint < NumberOfFeaturesPerBucket; i_ImagePoint++)
    {
        for(uint64 i_Row {0U}; i_Row < NumberOfBucketsVertical; i_Row++)
        {
            const float64 CoordinateVertical {BucketSizeVertical * (0.5 + static_cast<float64>(i_Row)) + static_cast<float64>(i_ImagePoint) * PixelOffset};

            for(uint64 i_Column {0U}; i_Column < NumberOfBucketsHorizontal; i_Column++)
            {
                const float64 CoordinateHorizontal {BucketSizeHorizontal * (0.5 + static_cast<float64>(i_Column)) + static_cast<float64>(i_ImagePoint) * PixelOffset};

                ColumnVectorFloat64_2d ImagePoint(CoordinateHorizontal, CoordinateVertical);

                ImagePoints.push_back(ImagePoint);
            }
        }
    }

    Bucketer.BucketFeatures(ImagePoints);

    ListColumnVectorFloat64_2d RejectedImagePoints;

    Bucketer.GetRejectedFeatures(ImagePoints, RejectedImagePoints);

    const float64 CoordinateX {RejectedImagePoints[3](0)};
    const float64 CoordinateY {RejectedImagePoints[3](1)};

    ASSERT_DOUBLE_EQ(CoordinateX, 81.0);
    ASSERT_DOUBLE_EQ(CoordinateY, 56.0);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the coordinate of the first rejected feature.
///
/// Tests whether the image coordinates of the first rejected feature are
/// matching the expected coordinates or not. The seed value 127 is used to
/// initialize the selection of the features in each bucket.
///////////////////////////////////////////////////////////////////////////////
TEST_REJECTEDFEATURE_3_SEED_127_BYCHANCE_ISMATCHING(FeatureBucketerByChance, Test_RejectedFeature_3_Seed_127_ByChance_IsMatching)
{
    const uint64 NumberOfPixelsHorizontal         {600U};
    const uint64 NumberOfPixelsVertical           {200U};
    const uint64 NumberOfBucketsHorizontal        {4U};
    const uint64 NumberOfBucketsVertical          {2U};
    const uint64 MaximumNumberOfFeaturesPerBucket {3U};
    const uint64 SeedValue                        {127U};

    FeatureBucketerByChance Bucketer(NumberOfPixelsHorizontal, NumberOfPixelsVertical, NumberOfBucketsHorizontal, NumberOfBucketsVertical, MaximumNumberOfFeaturesPerBucket, SeedValue);

    ListColumnVectorFloat64_2d ImagePoints;

    const uint64  NumberOfFeaturesPerBucket {8U};
    const float64 PixelOffset               {2.0};
    const float64 BucketSizeHorizontal      {Bucketer.GetBucketSizeHorizontal()};
    const float64 BucketSizeVertical        {Bucketer.GetBucketSizeVertical()};

    for(uint64 i_ImagePoint {0U}; i_ImagePoint < NumberOfFeaturesPerBucket; i_ImagePoint++)
    {
        for(uint64 i_Row {0U}; i_Row < NumberOfBucketsVertical; i_Row++)
        {
            const float64 CoordinateVertical {BucketSizeVertical * (0.5 + static_cast<float64>(i_Row)) + static_cast<float64>(i_ImagePoint) * PixelOffset};

            for(uint64 i_Column {0U}; i_Column < NumberOfBucketsHorizontal; i_Column++)
            {
                const float64 CoordinateHorizontal {BucketSizeHorizontal * (0.5 + static_cast<float64>(i_Column)) + static_cast<float64>(i_ImagePoint) * PixelOffset};

                ColumnVectorFloat64_2d ImagePoint(CoordinateHorizontal, CoordinateVertical);

                ImagePoints.push_back(ImagePoint);
            }
        }
    }

    Bucketer.BucketFeatures(ImagePoints);

    ListColumnVectorFloat64_2d RejectedImagePoints;

    Bucketer.GetRejectedFeatures(ImagePoints, RejectedImagePoints);

    const float64 CoordinateX {RejectedImagePoints[3](0)};
    const float64 CoordinateY {RejectedImagePoints[3](1)};

    ASSERT_DOUBLE_EQ(CoordinateX, 87.0);
    ASSERT_DOUBLE_EQ(CoordinateY, 62.0);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the coordinate of the first selected feature.
///
/// Tests whether the image coordinates of the first selected feature are
/// matching the expected coordinates or not. The seed value 0 is used to
/// initialize the selection of the features in each bucket.
///////////////////////////////////////////////////////////////////////////////
TEST_SELECTEDFEATURE_0_SEED_0_BYCHANCE_ISMATCHING(FeatureBucketerByChance, Test_SelectedFeature_0_Seed_0_ByChance_IsMatching)
{
    const uint64 NumberOfPixelsHorizontal         {600U};
    const uint64 NumberOfPixelsVertical           {200U};
    const uint64 NumberOfBucketsHorizontal        {4U};
    const uint64 NumberOfBucketsVertical          {2U};
    const uint64 MaximumNumberOfFeaturesPerBucket {3U};
    const uint64 SeedValue                        {0U};

    FeatureBucketerByChance Bucketer(NumberOfPixelsHorizontal, NumberOfPixelsVertical, NumberOfBucketsHorizontal, NumberOfBucketsVertical, MaximumNumberOfFeaturesPerBucket, SeedValue);

    ListColumnVectorFloat64_2d ImagePoints;

    const uint64  NumberOfFeaturesPerBucket {8U};
    const float64 PixelOffset               {2.0};
    const float64 BucketSizeHorizontal      {Bucketer.GetBucketSizeHorizontal()};
    const float64 BucketSizeVertical        {Bucketer.GetBucketSizeVertical()};

    for(uint64 i_ImagePoint {0U}; i_ImagePoint < NumberOfFeaturesPerBucket; i_ImagePoint++)
    {
        for(uint64 i_Row {0U}; i_Row < NumberOfBucketsVertical; i_Row++)
        {
            const float64 CoordinateVertical {BucketSizeVertical * (0.5 + static_cast<float64>(i_Row)) + static_cast<float64>(i_ImagePoint) * PixelOffset};

            for(uint64 i_Column {0U}; i_Column < NumberOfBucketsHorizontal; i_Column++)
            {
                const float64 CoordinateHorizontal {BucketSizeHorizontal * (0.5 + static_cast<float64>(i_Column)) + static_cast<float64>(i_ImagePoint) * PixelOffset};

                ColumnVectorFloat64_2d ImagePoint(CoordinateHorizontal, CoordinateVertical);

                ImagePoints.push_back(ImagePoint);
            }
        }
    }

    Bucketer.BucketFeatures(ImagePoints);

    ListColumnVectorFloat64_2d SelectedImagePoints;

    Bucketer.GetSelectedFeatures(ImagePoints, SelectedImagePoints);

    const float64 CoordinateX {SelectedImagePoints[0](0)};
    const float64 CoordinateY {SelectedImagePoints[0](1)};

    ASSERT_DOUBLE_EQ(CoordinateX, 83.0);
    ASSERT_DOUBLE_EQ(CoordinateY, 58.0);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Test for the coordinate of the first selected feature.
///
/// Tests whether the image coordinates of the first selected feature are
/// matching the expected coordinates or not. The seed value 127 is used to
/// initialize the selection of the features in each bucket.
///////////////////////////////////////////////////////////////////////////////
TEST_SELECTEDFEATURE_0_SEED_127_BYCHANCE_ISMATCHING(FeatureBucketerByChance, Test_SelectedFeature_0_Seed_127_ByChance_IsMatching)
{
    const uint64 NumberOfPixelsHorizontal         {600U};
    const uint64 NumberOfPixelsVertical           {200U};
    const uint64 NumberOfBucketsHorizontal        {4U};
    const uint64 NumberOfBucketsVertical          {2U};
    const uint64 MaximumNumberOfFeaturesPerBucket {3U};
    const uint64 SeedValue                        {127U};

    FeatureBucketerByChance Bucketer(NumberOfPixelsHorizontal, NumberOfPixelsVertical, NumberOfBucketsHorizontal, NumberOfBucketsVertical, MaximumNumberOfFeaturesPerBucket, SeedValue);

    ListColumnVectorFloat64_2d ImagePoints;

    const uint64  NumberOfFeaturesPerBucket {8U};
    const float64 PixelOffset               {2.0};
    const float64 BucketSizeHorizontal      {Bucketer.GetBucketSizeHorizontal()};
    const float64 BucketSizeVertical        {Bucketer.GetBucketSizeVertical()};

    for(uint64 i_ImagePoint {0U}; i_ImagePoint < NumberOfFeaturesPerBucket; i_ImagePoint++)
    {
        for(uint64 i_Row {0U}; i_Row < NumberOfBucketsVertical; i_Row++)
        {
            const float64 CoordinateVertical {BucketSizeVertical * (0.5 + static_cast<float64>(i_Row)) + static_cast<float64>(i_ImagePoint) * PixelOffset};

            for(uint64 i_Column {0U}; i_Column < NumberOfBucketsHorizontal; i_Column++)
            {
                const float64 CoordinateHorizontal {BucketSizeHorizontal * (0.5 + static_cast<float64>(i_Column)) + static_cast<float64>(i_ImagePoint) * PixelOffset};

                ColumnVectorFloat64_2d ImagePoint(CoordinateHorizontal, CoordinateVertical);

                ImagePoints.push_back(ImagePoint);
            }
        }
    }

    Bucketer.BucketFeatures(ImagePoints);

    ListColumnVectorFloat64_2d SelectedImagePoints;

    Bucketer.GetSelectedFeatures(ImagePoints, SelectedImagePoints);

    const float64 CoordinateX {SelectedImagePoints[0](0)};
    const float64 CoordinateY {SelectedImagePoints[0](1)};

    ASSERT_DOUBLE_EQ(CoordinateX, 77.0);
    ASSERT_DOUBLE_EQ(CoordinateY, 52.0);
}
