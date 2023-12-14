///////////////////////////////////////////////////////////////////////////////
/// \file  FeatureBucketerBase.cpp
///
/// \brief Source file containing the FeatureBucketerBase class.
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

#include "../include/FeatureBucketerBase.h"

FeatureBucketerBase::FeatureBucketerBase(const uint64 NumberOfPixelsHorizontal,
                                         const uint64 NumberOfPixelsVertical,
                                         const uint8  NumberOfBucketsHorizontal,
                                         const uint8  NumberOfBucketsVertical,
                                         const uint8  MaximumNumberOfFeaturesPerBucket) : m_NumberOfPixelsHorizontal{NumberOfPixelsHorizontal},
                                                                                          m_NumberOfPixelsVertical{NumberOfPixelsVertical},
                                                                                          m_NumberOfBucketsHorizontal{NumberOfBucketsHorizontal},
                                                                                          m_NumberOfBucketsVertical{NumberOfBucketsVertical}
{
    // compute derived attributes
    m_NumberOfBuckets = m_NumberOfBucketsHorizontal * m_NumberOfBucketsVertical; // NOLINT(cppcoreguidelines-prefer-member-initializer)

    m_FeatureMask.resize(m_NumberOfBucketsVertical, m_NumberOfBucketsHorizontal);
    m_FeatureMask.setConstant(MaximumNumberOfFeaturesPerBucket);

    m_BucketSizeHorizontal = static_cast<float64>(m_NumberOfPixelsHorizontal) / static_cast<float64>(m_NumberOfBucketsHorizontal); // NOLINT(cppcoreguidelines-prefer-member-initializer)
    m_BucketSizeVertical   = static_cast<float64>(m_NumberOfPixelsVertical)   / static_cast<float64>(m_NumberOfBucketsVertical);   // NOLINT(cppcoreguidelines-prefer-member-initializer)
}

FeatureBucketerBase::FeatureBucketerBase(const uint64       NumberOfPixelsHorizontal,
                                         const uint64       NumberOfPixelsVertical,
                                         const MatrixUInt8& FeatureMask) : m_NumberOfPixelsHorizontal{NumberOfPixelsHorizontal},
                                                                           m_NumberOfPixelsVertical{NumberOfPixelsVertical},
                                                                           m_FeatureMask{FeatureMask}
{
    // set internal attributes
    m_NumberOfBucketsHorizontal = FeatureMask.cols(); // NOLINT(cppcoreguidelines-prefer-member-initializer)
    m_NumberOfBucketsVertical   = FeatureMask.rows(); // NOLINT(cppcoreguidelines-prefer-member-initializer)

    // compute derived attributes
    m_NumberOfBuckets = m_NumberOfBucketsHorizontal * m_NumberOfBucketsVertical; // NOLINT(cppcoreguidelines-prefer-member-initializer)

    m_BucketSizeHorizontal = static_cast<float64>(m_NumberOfPixelsHorizontal) / static_cast<float64>(m_NumberOfBucketsHorizontal); // NOLINT(cppcoreguidelines-prefer-member-initializer)
    m_BucketSizeVertical   = static_cast<float64>(m_NumberOfPixelsVertical)   / static_cast<float64>(m_NumberOfBucketsVertical);   // NOLINT(cppcoreguidelines-prefer-member-initializer)
}

FeatureBucketerBase::~FeatureBucketerBase()
{

}

void FeatureBucketerBase::BucketFeatures(const ListColumnVectorFloat64_2d& ImagePoints)
{
    // clear variables
    m_SelectedIndices.clear();
    m_RejectedIndices.clear();

    // determine bucket IDs for all features
    ComputeBucketIDs(ImagePoints);

    // select feature in buckets
    BucketFeaturesWithScheme();
}

float64 FeatureBucketerBase::GetBucketSizeHorizontal() const
{
    return m_BucketSizeHorizontal;
}

float64 FeatureBucketerBase::GetBucketSizeVertical() const
{
    return m_BucketSizeVertical;
}

uint8 FeatureBucketerBase::GetNumberOfBucketsHorizontal() const
{
    return m_NumberOfBucketsHorizontal;
}

uint8 FeatureBucketerBase::GetNumberOfBucketsVertical() const
{
    return m_NumberOfBucketsVertical;
}

uint64 FeatureBucketerBase::GetNumberOfPixelsHorizontal() const
{
    return m_NumberOfPixelsHorizontal;
}

uint64 FeatureBucketerBase::GetNumberOfPixelsVertical() const
{
    return m_NumberOfPixelsVertical;
}

void FeatureBucketerBase::GetRejectedFeatures(const ListColumnVectorFloat64_2d& ImagePoints,
                                                    ListColumnVectorFloat64_2d& ImagePointsRejected) const
{
    // get number of rejected features
    const uint64 NumberOfRejectedFeatures {m_RejectedIndices.size()};

    // clear variables and pre-allocate memory
    ImagePointsRejected.clear();
    ImagePointsRejected.resize(NumberOfRejectedFeatures);

    // get rejected features
    for(uint64 i_Feature {0U}; i_Feature < NumberOfRejectedFeatures; i_Feature++)
    {
        ImagePointsRejected[i_Feature] = ImagePoints[m_RejectedIndices[i_Feature]];
    }
}

const ListUInt64& FeatureBucketerBase::GetRejectedIndices() const
{
    return m_RejectedIndices;
}

void FeatureBucketerBase::GetSelectedFeatures(const ListColumnVectorFloat64_2d& ImagePoints,
                                                    ListColumnVectorFloat64_2d& ImagePointsSelected) const
{
    // get number of selected features
    const uint64 NumberOfSelectedFeatures {m_SelectedIndices.size()};

    // clear variables and pre-allocate memory
    ImagePointsSelected.clear();
    ImagePointsSelected.resize(NumberOfSelectedFeatures);

    // get selected features
    for(uint64 i_Feature {0U}; i_Feature < NumberOfSelectedFeatures; i_Feature++)
    {
        ImagePointsSelected[i_Feature] = ImagePoints[m_SelectedIndices[i_Feature]];
    }
}

const ListUInt64& FeatureBucketerBase::GetSelectedIndices() const
{
    return m_SelectedIndices;
}

boolean FeatureBucketerBase::ComputeBucketID(const float64 CoordinateImagePointHorizontal,
                                             const float64 CoordinateImagePointVertical,
                                                   uint16& BucketID) const
{
    // check whether the current feature is visible in the image or not
    boolean BucketIDIsValid {false};

    const boolean ImagePointIsVisibleHorizontal {((CoordinateImagePointHorizontal >= 0.0) && (CoordinateImagePointHorizontal < static_cast<float32>(m_NumberOfPixelsHorizontal)))};
    const boolean ImagePointIsVisibleVertical   {((CoordinateImagePointVertical   >= 0.0) && (CoordinateImagePointVertical   < static_cast<float32>(m_NumberOfPixelsVertical)))};

    if(ImagePointIsVisibleHorizontal && ImagePointIsVisibleVertical)
    {
        // compute bucket IDs in horizontal and vertical direction
        const uint8 BucketIDHorizontal {static_cast<uint8>(CoordinateImagePointHorizontal / m_BucketSizeHorizontal)};
        const uint8 BucketIDVertical   {static_cast<uint8>(CoordinateImagePointVertical   / m_BucketSizeVertical)};

        // compute bucket ID
        BucketID = BucketIDVertical * m_NumberOfBucketsHorizontal + BucketIDHorizontal;

        // make bucket ID valid
        BucketIDIsValid = true;
    }

    // return whether the bucket ID is valid or not
    return BucketIDIsValid;
}

void FeatureBucketerBase::ComputeBucketIDs(const ListColumnVectorFloat64_2d& ImagePoints)
{
    // get number of image points
    const uint64 NumberOfImagePoints {ImagePoints.size()};

    // clear variables and pre-allocate memory
    m_BucketIDs.clear();
    m_BucketIDIsValid.clear();
    m_FeatureIndices.clear();

    m_BucketIDs.resize(NumberOfImagePoints);
    m_BucketIDIsValid.resize(NumberOfImagePoints);
    m_FeatureIndices.resize(m_NumberOfBuckets + 1U); // last entry used for invalid features

    // compute bucket ID for all features
    for(uint64 i_ImagePoint {0U}; i_ImagePoint < NumberOfImagePoints; i_ImagePoint++)
    {
        // get image coordinate of the current feature
        const float64 CoordinateImagePointHorizontal {ImagePoints[i_ImagePoint](0)};
        const float64 CoordinateImagePointVertical   {ImagePoints[i_ImagePoint](1)};

        // compute bucket ID for current feature
        uint16  BucketID        {m_NumberOfBuckets}; // initialized with the invalid bucket ID
        boolean BucketIDIsValid {false};

        BucketIDIsValid = ComputeBucketID(CoordinateImagePointHorizontal,
                                          CoordinateImagePointVertical,
                                          BucketID); // bucket ID is changed internally if bucket ID is valid

        // store data
        m_BucketIDs[i_ImagePoint]       = BucketID;
        m_BucketIDIsValid[i_ImagePoint] = BucketIDIsValid;

        m_FeatureIndices[BucketID].push_back(i_ImagePoint);
    }
}

void FeatureBucketerBase::SelectAllFeaturesInBucket(const uint16 BucketID,
                                                    const uint64 NumberOfFeaturesInCurrentBucket)
{
    // select all feature in the current bucket
    for(uint64 i_Feature {0U}; i_Feature < NumberOfFeaturesInCurrentBucket; i_Feature++)
    {
        const uint64 CurrentFeatureIndex = m_FeatureIndices[BucketID][i_Feature];

        m_SelectedIndices.push_back(CurrentFeatureIndex);
    }
}
