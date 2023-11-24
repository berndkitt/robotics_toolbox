///////////////////////////////////////////////////////////////////////////////
/// \file FeatureBucketerByOrder.h
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

#ifndef FEATUREBUCKETERBYORDER_H
#define FEATUREBUCKETERBYORDER_H

#include "FeatureBucketerBase.h"

///////////////////////////////////////////////////////////////////////////////
/// \class FeatureBucketerByOrder
///
/// \brief Feature bucketer with selection scheme "by order".
///
/// The feature bucketer divides the image into rectangular buckets and selects
/// a certain amount of features in each bucket. The features inside each
/// bucket are selected in the order they are provided.
///////////////////////////////////////////////////////////////////////////////
class FeatureBucketerByOrder : public FeatureBucketerBase
{
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
    ///////////////////////////////////////////////////////////////////////////////
    FeatureBucketerByOrder(const uint64 NumberOfPixelsHorizontal         = 1024U,
                           const uint64 NumberOfPixelsVertical           = 768U,
                           const uint8  NumberOfBucketsHorizontal        = 8U,
                           const uint8  NumberOfBucketsVertical          = 4U,
                           const uint8  MaximumNumberOfFeaturesPerBucket = 5U);

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
    ///////////////////////////////////////////////////////////////////////////////
    FeatureBucketerByOrder(const uint64       NumberOfPixelsHorizontal,
                           const uint64       NumberOfPixelsVertical,
                           const MatrixUInt8& FeatureMask);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~FeatureBucketerByOrder();

protected: // protected methods
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Core method to bucket a set of given features.
    ///
    /// This method implements the selection scheme "by order".
    ///////////////////////////////////////////////////////////////////////////////
    virtual void BucketFeaturesWithScheme();
};

#endif //FEATUREBUCKETERBYORDER_H
