///////////////////////////////////////////////////////////////////////////////
/// \file FeatureBucketer.h
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

#ifndef FEATUREBUCKETER_H
#define FEATUREBUCKETER_H

#include <random>

#include <GlobalTypesDerived.h>

///////////////////////////////////////////////////////////////////////////////
/// \enum  FeatureSelectionScheme
///
/// \brief Defines the selection scheme which is used to select the features in the buckets.
///////////////////////////////////////////////////////////////////////////////
enum FeatureSelectionScheme
{
    SelectByChance, ///< Features are selected by chance.
    SelectByOrder   ///< Features are selected in the order they are provided.
};

///////////////////////////////////////////////////////////////////////////////
/// \class FeatureBucketer
///
/// \brief Divides an image into rectangular buckets and selects a certain
///        number of features in each bucket.
///
/// The feature bucketer divides the image into rectangular buckets and selects
/// a certain amount of features in each bucket. There are two selection
/// schemes available. The first one selects the features inside each bucket by
/// chance, the second selects the features in each bucket in the order they
/// are provided.
///////////////////////////////////////////////////////////////////////////////
class FeatureBucketer
{
protected: // protected attributes
    const uint64                  m_NumberOfPixelsHorizontal;  ///< Number of pixels in horizontal direction.
    const uint64                  m_NumberOfPixelsVertical;    ///< Number of pixels in vertical direction.
          uint64                  m_NumberOfBucketsHorizontal; ///< Number of buckets in horizontal direction.
          uint64                  m_NumberOfBucketsVertical;   ///< Number of buckets in vertical direction.
          uint64                  m_NumberOfBuckets;           ///< Total number of buckets.
          MatrixUInt64            m_FeatureMask;               ///< Mask defining the buckets and the number of features in each bucket.
          float64                 m_BucketSizeHorizontal;      ///< Size of each bucket in horizontal direction.
          float64                 m_BucketSizeVertical;        ///< Size of each bucket in vertical direction.
    const FeatureSelectionScheme  m_SelectionScheme;           ///< Selection scheme used to select the features in the buckets.
          ListUInt64              m_SelectedIndices;           ///< List containing the indices of the selected features.
          ListUInt64              m_RejectedIndices;           ///< List containing the indices of the rejected features.
          ListUInt64              m_BucketIDs;                 ///< List containing the bucket IDs for all provided features.
          ListBoolean             m_BucketIDIsValid;           ///< List defining whether the bucket ID is valid or not.
          std::vector<ListUInt64> m_FeatureIndices;            ///< List containing the feature indices for all buckets (contains one entry more than buckets; last entry used for invalid features).
          uint64                  m_NumberOfSelectedIndices;   ///< Number of features which have been selected.
          uint64                  m_NumberOfRejectedIndices;   ///< Number of features which have been rejected.
          uint64                  m_NumberOfValidFeatures;     ///< Number of valid features.
          uint64                  m_NumberOfInvalidFeatures;   ///< Number of invalid features.
          std::mt19937            m_RandomNumberEngine;        ///< Random number engine used to select the image points.
    const uint64                  m_SeedValue;                 ///< Seed value used to initialize the random number engine.

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
    /// \param[in] SelectionScheme                  Selection scheme used to select the features in the buckets.
    /// \param[in] SeedValue                        Seed value used to initialize the random number engine.
    ///////////////////////////////////////////////////////////////////////////////
    FeatureBucketer(const uint64                 NumberOfPixelsHorizontal         = 1024U,
                    const uint64                 NumberOfPixelsVertical           = 768U,
                    const uint64                 NumberOfBucketsHorizontal        = 8U,
                    const uint64                 NumberOfBucketsVertical          = 4U,
                    const uint64                 MaximumNumberOfFeaturesPerBucket = 5U,
                    const FeatureSelectionScheme SelectionScheme                  = SelectByChance,
                    const uint64                 SeedValue                        = 0U);

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
    /// \param[in] SelectionScheme          Selection scheme used to select the features in the buckets.
    /// \param[in] SeedValue                Seed value used to initialize the random number engine.
    ///////////////////////////////////////////////////////////////////////////////
    FeatureBucketer(const uint64                 NumberOfPixelsHorizontal,
                    const uint64                 NumberOfPixelsVertical,
                    const MatrixUInt64&          FeatureMask,
                    const FeatureSelectionScheme SelectionScheme          = SelectByChance,
                    const uint64                 SeedValue                = 0U);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///////////////////////////////////////////////////////////////////////////////
    ~FeatureBucketer();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Bucket a set of given features.
    ///
    /// \param[in] ImagePoints List containing all image points which shall be distributed into the buckets.
    ///////////////////////////////////////////////////////////////////////////////
    void BucketFeatures(const ListColumnVectorFloat64_2d& ImagePoints);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the size of each bucket in horizontal direction.
    ///
    /// \return Size of each bucket in horizontal direction.
    ///////////////////////////////////////////////////////////////////////////////
    float64 GetBucketSizeHorizontal() const;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the size of each bucket in vertical direction.
    ///
    /// \return Size of each bucket in vertical direction.
    ///////////////////////////////////////////////////////////////////////////////
    float64 GetBucketSizeVertical() const;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the number of buckets in horizontal direction.
    ///
    /// \return Number of buckets in horizontal direction.
    ///////////////////////////////////////////////////////////////////////////////
    uint64 GetNumberOfBucketsHorizontal() const;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the number of buckets in vertical direction.
    ///
    /// \return Number of buckets in vertical direction.
    ///////////////////////////////////////////////////////////////////////////////
    uint64 GetNumberOfBucketsVertical() const;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the number of pixels in horizontal direction.
    ///
    /// \return Number of pixels in horizontal direction.
    ///////////////////////////////////////////////////////////////////////////////
    uint64 GetNumberOfPixelsHorizontal() const;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the number of pixels in vertical direction.
    ///
    /// \return Number of pixels in vertical direction.
    ///////////////////////////////////////////////////////////////////////////////
    uint64 GetNumberOfPixelsVertical() const;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the list of indices of the rejected features.
    ///
    /// \return List of rejected feature indices.
    ///////////////////////////////////////////////////////////////////////////////
    const ListUInt64& GetRejectedIndices() const;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief  Getter for the list of indices of the selected features.
    ///
    /// \return List of selected feature indices.
    ///////////////////////////////////////////////////////////////////////////////
    const ListUInt64& GetSelectedIndices() const;

protected: // protected methods
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Selects the features in each bucket by chance.
    ///////////////////////////////////////////////////////////////////////////////
    void BucketFeaturesByChance();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Selects the features in each bucket in the order they are provided.
    ///////////////////////////////////////////////////////////////////////////////
    void BucketFeaturesByOrder();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief      Computes the bucket ID for a single feature.
    ///
    /// \param[in]  CoordinateImagePointHorizontal Horizontal position of the feature in the image.
    /// \param[in]  CoordinateImagePointVertical   Vertical position of the feature in the image.
    /// \param[out] BucketID                       ID of the bucket from top left to bottom right.
    ///
    /// \return     Flag whether the ID is valid or not.
    ///////////////////////////////////////////////////////////////////////////////
    boolean ComputeBucketID(const float64 CoordinateImagePointHorizontal,
                            const float64 CoordinateImagePointVertical,
                                  uint64& BucketID) const;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Computes the bucket IDs for all features.
    ///
    /// \param[in] ImagePoints List containing all image points which shall be distributed into the buckets.
    ///////////////////////////////////////////////////////////////////////////////
    void ComputeBucketIDs(const ListColumnVectorFloat64_2d& ImagePoints);
};

#endif // FEATUREBUCKETER_H
