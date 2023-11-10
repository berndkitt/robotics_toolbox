///////////////////////////////////////////////////////////////////////////////
/// \file FeatureBucketer.cpp
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

#include <Tools.h>

#include "../include/FeatureBucketer.h"

FeatureBucketer::FeatureBucketer(const uint64                 NumberOfPixelsHorizontal,
                                 const uint64                 NumberOfPixelsVertical,
                                 const uint64                 NumberOfBucketsHorizontal,
                                 const uint64                 NumberOfBucketsVertical,
                                 const uint64                 MaximumNumberOfFeaturesPerBucket,
                                 const FeatureSelectionScheme SelectionScheme,
                                 const uint64                 SeedValue) : m_NumberOfPixelsHorizontal{NumberOfPixelsHorizontal},
                                                                           m_NumberOfPixelsVertical{NumberOfPixelsVertical},
                                                                           m_SelectionScheme{SelectionScheme},
                                                                           m_SeedValue{SeedValue}
{
    // set internal attributes
    m_NumberOfBucketsHorizontal = NumberOfBucketsHorizontal;
    m_NumberOfBucketsVertical   = NumberOfBucketsVertical;
    m_NumberOfSelectedIndices   = 0U;
    m_NumberOfRejectedIndices   = 0U;
    m_NumberOfValidFeatures     = 0U;
    m_NumberOfInvalidFeatures   = 0U;

    // compute derived attributes
    m_NumberOfBuckets = m_NumberOfBucketsHorizontal * m_NumberOfBucketsVertical;

    m_FeatureMask.resize(m_NumberOfBucketsVertical, m_NumberOfBucketsHorizontal);
    m_FeatureMask.setConstant(MaximumNumberOfFeaturesPerBucket);

    m_BucketSizeHorizontal = static_cast<float64>(m_NumberOfPixelsHorizontal) / static_cast<float64>(m_NumberOfBucketsHorizontal);
    m_BucketSizeVertical   = static_cast<float64>(m_NumberOfPixelsVertical)   / static_cast<float64>(m_NumberOfBucketsVertical);

    // initialize random number generator
    m_RandomNumberEngine.seed(m_SeedValue);
}

FeatureBucketer::FeatureBucketer(const uint64                 NumberOfPixelsHorizontal,
                                 const uint64                 NumberOfPixelsVertical,
                                 const MatrixUInt64&          FeatureMask,
                                 const FeatureSelectionScheme SelectionScheme,
                                 const uint64                 SeedValue) : m_NumberOfPixelsHorizontal{NumberOfPixelsHorizontal},
                                                                           m_NumberOfPixelsVertical{NumberOfPixelsVertical},
                                                                           m_SelectionScheme{SelectionScheme},
                                                                           m_SeedValue{SeedValue}
{
    // set internal attributes
    m_NumberOfBucketsHorizontal = FeatureMask.cols();
    m_NumberOfBucketsVertical   = FeatureMask.rows();
    m_NumberOfSelectedIndices   = 0U;
    m_NumberOfRejectedIndices   = 0U;
    m_NumberOfValidFeatures     = 0U;
    m_NumberOfInvalidFeatures   = 0U;

    // compute derived attributes
    m_NumberOfBuckets = m_NumberOfBucketsHorizontal * m_NumberOfBucketsVertical;

    m_FeatureMask = FeatureMask;

    m_BucketSizeHorizontal = static_cast<float64>(m_NumberOfPixelsHorizontal) / static_cast<float64>(m_NumberOfBucketsHorizontal);
    m_BucketSizeVertical   = static_cast<float64>(m_NumberOfPixelsVertical)   / static_cast<float64>(m_NumberOfBucketsVertical);

    // initialize random number generator
    m_RandomNumberEngine.seed(m_SeedValue);
}

FeatureBucketer::~FeatureBucketer()
{

}

void FeatureBucketer::BucketFeatures(const ListColumnVectorFloat64_2d& ImagePoints)
{
    // clear variables
    m_NumberOfSelectedIndices = 0U;
    m_NumberOfRejectedIndices = 0U;

    m_SelectedIndices.clear();
    m_RejectedIndices.clear();

    // determine bucket IDs for all features
    ComputeBucketIDs(ImagePoints);

    // select feature in buckets
    switch(m_SelectionScheme)
    {
        case SelectByChance:
        {
            BucketFeaturesByChance();
            break;
        }
        case SelectByOrder:
        {
            BucketFeaturesByOrder();
            break;
        }
        // no default needed as all options are covered
    }
}

float64 FeatureBucketer::GetBucketSizeHorizontal() const
{
    return m_BucketSizeHorizontal;
}

float64 FeatureBucketer::GetBucketSizeVertical() const
{
    return m_BucketSizeVertical;
}

uint64 FeatureBucketer::GetNumberOfBucketsHorizontal() const
{
    return m_NumberOfBucketsHorizontal;
}

uint64 FeatureBucketer::GetNumberOfBucketsVertical() const
{
    return m_NumberOfBucketsVertical;
}

uint64 FeatureBucketer::GetNumberOfPixelsHorizontal() const
{
    return m_NumberOfPixelsHorizontal;
}

uint64 FeatureBucketer::GetNumberOfPixelsVertical() const
{
    return m_NumberOfPixelsVertical;
}

const ListUInt64& FeatureBucketer::GetRejectedIndices() const
{
    return m_RejectedIndices;
}

const ListUInt64& FeatureBucketer::GetSelectedIndices() const
{
    return m_SelectedIndices;
}

void FeatureBucketer::BucketFeaturesByChance()
{
    // bucket features by chance
    for(uint64 i_Bucket = 0; i_Bucket < m_NumberOfBuckets; i_Bucket++)
    {
        // get maximum number of features in current bucket
        const uint64 MaximumNumberOfFeaturesInCurrentBucket {m_FeatureMask(i_Bucket)};

        // get number of features in current bucket
        const uint64 NumberOfFeaturesInCurrentBucket {m_FeatureIndices[i_Bucket].size()};

        // select features
        if(NumberOfFeaturesInCurrentBucket <= MaximumNumberOfFeaturesInCurrentBucket)
        {
            // collect selected features (all are selected)
            for(uint64 i_Feature {0U}; i_Feature < NumberOfFeaturesInCurrentBucket; i_Feature++)
            {
                const uint64 CurrentFeatureIndex = m_FeatureIndices[i_Bucket][i_Feature];

                m_SelectedIndices.push_back(CurrentFeatureIndex);
                m_NumberOfSelectedIndices++;
            }
        }
        else
        {
            // create uniform distribution
            std::uniform_int_distribution<uint64> UniformDistribution(0U, NumberOfFeaturesInCurrentBucket - 1U);

            // randomly chose feature indices for current bucket
            uint64     FeatureCounter = 0;
            ListUInt64 ChosenIndices;

            ChosenIndices.resize(MaximumNumberOfFeaturesInCurrentBucket);

            while(FeatureCounter < MaximumNumberOfFeaturesInCurrentBucket)
            {
                // randomly chose index
                const uint64 RandomNumber {UniformDistribution(m_RandomNumberEngine)};
                const uint64 ChosenIndex  {m_FeatureIndices[i_Bucket][RandomNumber]};

                // check whether the chosen index is already an entity of the list
                if(!Tools::IsMember(ChosenIndices, ChosenIndex))
                {
                    ChosenIndices[FeatureCounter] = ChosenIndex;
                    FeatureCounter++;
                }
            }

            // store selected and rejected indices
            for(uint64 i_Feature {0U}; i_Feature < NumberOfFeaturesInCurrentBucket; i_Feature++)
            {
                const uint64 CurrentIndex {m_FeatureIndices[i_Bucket][i_Feature]};

                if(Tools::IsMember(ChosenIndices, CurrentIndex))
                {
                    m_SelectedIndices.push_back(CurrentIndex);
                    m_NumberOfSelectedIndices++;
                }
                else
                {
                    m_RejectedIndices.push_back(CurrentIndex);
                    m_NumberOfRejectedIndices++;
                }
            }
        }
    }
}

void FeatureBucketer::BucketFeaturesByOrder()
{
    // bucket features in the order they are provided in the list
    for(uint64 i_Bucket {0U}; i_Bucket < m_NumberOfBuckets; i_Bucket++)
    {
        // get maximum number of features in current bucket
        const uint64 MaximumNumberOfFeaturesInCurrentBucket {m_FeatureMask(i_Bucket)};

        // get number of features in current bucket
        const uint64 NumberOfFeaturesInCurrentBucket {m_FeatureIndices[i_Bucket].size()};

        // select features
        if(NumberOfFeaturesInCurrentBucket <= MaximumNumberOfFeaturesInCurrentBucket)
        {
            // collect selected features (all are selected)
            for(uint64 i_Feature {0U}; i_Feature < NumberOfFeaturesInCurrentBucket; i_Feature++)
            {
                const uint64 CurrentFeatureIndex {m_FeatureIndices[i_Bucket][i_Feature]};

                m_SelectedIndices.push_back(CurrentFeatureIndex);
                m_NumberOfSelectedIndices++;
            }
        }
        else
        {
            // collect selected features
            for(uint64 i_Feature {0U}; i_Feature < MaximumNumberOfFeaturesInCurrentBucket; i_Feature++)
            {
                const uint64 CurrentFeatureIndex {m_FeatureIndices[i_Bucket][i_Feature]};

                m_SelectedIndices.push_back(CurrentFeatureIndex);
                m_NumberOfSelectedIndices++;
            }

            // collect rejected features
            for(uint64 i_Feature {MaximumNumberOfFeaturesInCurrentBucket}; i_Feature < NumberOfFeaturesInCurrentBucket; i_Feature++)
            {
                const uint64 CurrentFeatureIndex {m_FeatureIndices[i_Bucket][i_Feature]};

                m_RejectedIndices.push_back(CurrentFeatureIndex);
                m_NumberOfRejectedIndices++;
            }
        }
    }
}

boolean FeatureBucketer::ComputeBucketID(const float64 CoordinateImagePointHorizontal,
                                         const float64 CoordinateImagePointVertical,
                                               uint64& BucketID) const
{
    // check whether the current feature is visible in the image or not
    boolean BucketIDIsValid {false};

    const boolean ImagePointIsVisibleHorizontal {((CoordinateImagePointHorizontal >= 0.0) && (CoordinateImagePointHorizontal < static_cast<float32>(m_NumberOfPixelsHorizontal)))};
    const boolean ImagePointIsVisibleVertical   {((CoordinateImagePointVertical   >= 0.0) && (CoordinateImagePointVertical   < static_cast<float32>(m_NumberOfPixelsVertical)))};

    if(ImagePointIsVisibleHorizontal && ImagePointIsVisibleVertical)
    {
        // compute bucket IDs in horizontal and vertical direction
        const uint64 BucketIDHorizontal {static_cast<uint64>(CoordinateImagePointHorizontal / m_BucketSizeHorizontal)};
        const uint64 BucketIDVertical   {static_cast<uint64>(CoordinateImagePointVertical   / m_BucketSizeVertical)};

        // compute bucket ID
        BucketID = BucketIDVertical * m_NumberOfBucketsHorizontal + BucketIDHorizontal;

        // make bucket ID valid
        BucketIDIsValid = true;
    }

    // return whether the bucket ID is valid or not
    return BucketIDIsValid;
}

void FeatureBucketer::ComputeBucketIDs(const ListColumnVectorFloat64_2d& ImagePoints)
{
    // get number of image points
    const uint64 NumberOfImagePoints {ImagePoints.size()};

    // clear variables and pre-allocate memory
    m_NumberOfValidFeatures   = 0U;
    m_NumberOfInvalidFeatures = 0U;

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
        uint64  BucketID        {m_NumberOfBuckets}; // initialized with the invalid bucket ID
        boolean BucketIDIsValid {false};

        BucketIDIsValid = ComputeBucketID(CoordinateImagePointHorizontal,
                                          CoordinateImagePointVertical,
                                          BucketID); // bucket ID is changed internally if bucket ID is valid

        // store data
        m_BucketIDs[i_ImagePoint]       = BucketID;
        m_BucketIDIsValid[i_ImagePoint] = BucketIDIsValid;

        m_FeatureIndices[BucketID].push_back(i_ImagePoint);

        if(BucketIDIsValid)
        {
            m_NumberOfValidFeatures++;
        }
        else
        {
            m_NumberOfInvalidFeatures++;
        }
    }
}
