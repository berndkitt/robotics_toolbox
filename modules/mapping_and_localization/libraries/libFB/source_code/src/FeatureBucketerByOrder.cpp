///////////////////////////////////////////////////////////////////////////////
/// \file FeatureBucketerByOrder.cpp
///
/// \brief Source file containing the FeatureBucketerByOrder class.
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

#include "../include/FeatureBucketerByOrder.h"

FeatureBucketerByOrder::FeatureBucketerByOrder(const uint64 NumberOfPixelsHorizontal,
                                               const uint64 NumberOfPixelsVertical,
                                               const uint8  NumberOfBucketsHorizontal,
                                               const uint8  NumberOfBucketsVertical,
                                               const uint8  MaximumNumberOfFeaturesPerBucket) : FeatureBucketerBase(NumberOfPixelsHorizontal, NumberOfPixelsVertical, NumberOfBucketsHorizontal, NumberOfBucketsVertical, MaximumNumberOfFeaturesPerBucket)
{

}

FeatureBucketerByOrder::FeatureBucketerByOrder(const uint64       NumberOfPixelsHorizontal,
                                               const uint64       NumberOfPixelsVertical,
                                               const MatrixUInt8& FeatureMask) : FeatureBucketerBase(NumberOfPixelsHorizontal, NumberOfPixelsVertical, FeatureMask)
{

}

FeatureBucketerByOrder::~FeatureBucketerByOrder()
{

}

void FeatureBucketerByOrder::BucketFeaturesWithScheme()
{
    // bucket features in the order they are provided in the list
    for(uint16 i_Bucket {0U}; i_Bucket < m_NumberOfBuckets; i_Bucket++)
    {
        // get maximum number of features in current bucket
        const uint8 MaximumNumberOfFeaturesInCurrentBucket {m_FeatureMask(i_Bucket)};

        // get number of features in current bucket
        const uint64 NumberOfFeaturesInCurrentBucket {m_FeatureIndices[i_Bucket].size()};

        // select features
        if(NumberOfFeaturesInCurrentBucket <= MaximumNumberOfFeaturesInCurrentBucket)
        {
            // collect selected features (all are selected)
            SelectAllFeaturesInBucket(i_Bucket, NumberOfFeaturesInCurrentBucket);
        }
        else
        {
            // collect selected features
            for(uint8 i_Feature {0U}; i_Feature < MaximumNumberOfFeaturesInCurrentBucket; i_Feature++)
            {
                const uint64 CurrentFeatureIndex {m_FeatureIndices[i_Bucket][i_Feature]};

                m_SelectedIndices.push_back(CurrentFeatureIndex);
            }

            // collect rejected features
            for(uint8 i_Feature {MaximumNumberOfFeaturesInCurrentBucket}; i_Feature < NumberOfFeaturesInCurrentBucket; i_Feature++)
            {
                const uint64 CurrentFeatureIndex {m_FeatureIndices[i_Bucket][i_Feature]};

                m_RejectedIndices.push_back(CurrentFeatureIndex);
            }
        }
    }
}
