///////////////////////////////////////////////////////////////////////////////
/// \file FeatureBucketerByChance.cpp
///
/// \brief Source file containing the FeatureBucketerByChance class.
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

#include "../include/FeatureBucketerByChance.h"

FeatureBucketerByChance::FeatureBucketerByChance(const uint64 NumberOfPixelsHorizontal,
                                                 const uint64 NumberOfPixelsVertical,
                                                 const uint8  NumberOfBucketsHorizontal,
                                                 const uint8  NumberOfBucketsVertical,
                                                 const uint8  MaximumNumberOfFeaturesPerBucket,
                                                 const uint64 SeedValue) : FeatureBucketerBase(NumberOfPixelsHorizontal, NumberOfPixelsVertical, NumberOfBucketsHorizontal, NumberOfBucketsVertical, MaximumNumberOfFeaturesPerBucket),
                                                                           m_SeedValue{SeedValue}
{
    // initialize random number generator
    m_RandomNumberEngine.seed(m_SeedValue);
}

FeatureBucketerByChance::FeatureBucketerByChance(const uint64       NumberOfPixelsHorizontal,
                                                 const uint64       NumberOfPixelsVertical,
                                                 const MatrixUInt8& FeatureMask,
                                                 const uint64       SeedValue) : FeatureBucketerBase(NumberOfPixelsHorizontal, NumberOfPixelsVertical, FeatureMask),
                                                                                 m_SeedValue{SeedValue}
{
    // initialize random number generator
    m_RandomNumberEngine.seed(m_SeedValue);
}

FeatureBucketerByChance::~FeatureBucketerByChance()
{

}

void FeatureBucketerByChance::BucketFeaturesWithScheme()
{
    // bucket features by chance
    for(uint16 i_Bucket = 0; i_Bucket < m_NumberOfBuckets; i_Bucket++)
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
                }
                else
                {
                    m_RejectedIndices.push_back(CurrentIndex);
                }
            }
        }
    }
}
