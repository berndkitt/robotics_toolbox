///////////////////////////////////////////////////////////////////////////////
/// \file FeatureBucketerByChance.h
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

#ifndef FEATUREBUCKETERBYCHANCE_H
#define FEATUREBUCKETERBYCHANCE_H

#include <Tools.h>

#include "FeatureBucketerBase.h"

///////////////////////////////////////////////////////////////////////////////
/// \class FeatureBucketerByChance
///
/// \brief Feature bucketer with selection scheme "by chance".
///
/// The feature bucketer divides the image into rectangular buckets and selects
/// a certain amount of features in each bucket. The features inside each
/// bucket are selected by chance.
///////////////////////////////////////////////////////////////////////////////
class FeatureBucketerByChance : public FeatureBucketerBase
{
protected: // protected attributes
          std::mt19937 m_RandomNumberEngine;    ///< Random number engine used to select the image points.
    const uint64       m_SeedValue;             ///< Seed value used to initialize the random number engine.

public: // public methods
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Constructor.
    ///
    /// This constructor can be used if the maximum amount of features inside each
    /// bucket is equal for all buckets.
    ///
    /// \param[in] NumberOfPixelsHorizontal         Number of pixels in horizontal direction.
    /// \param[in] NumberOfPixelsVertical           Number of pixels in vertical direction.
    /// \param[in] NumberOfBucketsHorizontal        Number of buckets in horizontal direction.
    /// \param[in] NumberOfBucketsVertical          Number of buckets in vertical direction.
    /// \param[in] MaximumNumberOfFeaturesPerBucket Maximum number of selected features in each bucket.
    /// \param[in] SeedValue                        Seed value used to initialize the random number engine.
    ///////////////////////////////////////////////////////////////////////////////
    FeatureBucketerByChance(const uint64 NumberOfPixelsHorizontal         = 1024U,
                            const uint64 NumberOfPixelsVertical           = 768U,
                            const uint64 NumberOfBucketsHorizontal        = 8U,
                            const uint64 NumberOfBucketsVertical          = 4U,
                            const uint64 MaximumNumberOfFeaturesPerBucket = 5U,
                            const uint64 SeedValue                        = 0U);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Constructor.
    ///
    /// This constructor can be used if the maximum amount of features inside each
    /// bucket shall be different. The amount of features inside each bucket is
    /// defined by the feature mask.
    ///
    /// \param[in] NumberOfPixelsHorizontal Number of pixels in horizontal direction.
    /// \param[in] NumberOfPixelsVertical   Number of pixels in vertical direction.
    /// \param[in] FeatureMask              Mask defining the buckets and the number of features in each bucket.
    /// \param[in] SeedValue                Seed value used to initialize the random number engine.
    ///////////////////////////////////////////////////////////////////////////////
    FeatureBucketerByChance(const uint64        NumberOfPixelsHorizontal,
                            const uint64        NumberOfPixelsVertical,
                            const MatrixUInt64& FeatureMask,
                            const uint64        SeedValue                = 0U);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~FeatureBucketerByChance();

protected: // protected methods
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Core method to bucket a set of given features.
    ///
    /// This method implements the selection scheme "by chance".
    ///////////////////////////////////////////////////////////////////////////////
    virtual void BucketFeaturesWithScheme();
};

#endif //FEATUREBUCKETERBYCHANCE_H
