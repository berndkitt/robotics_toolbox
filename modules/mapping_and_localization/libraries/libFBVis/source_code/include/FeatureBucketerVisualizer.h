///////////////////////////////////////////////////////////////////////////////
/// \file FeatureBucketerVisualizer.h
///
/// \brief Header file containing the FeatureBucketerVisualizer class.
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

#ifndef FEATUREBUCKETERVISUALIZER_H
#define FEATUREBUCKETERVISUALIZER_H

#include <string>

#include <opencv2/core/core.hpp>

#include "../../../libFB/source_code/include/FeatureBucketerBase.h"

///////////////////////////////////////////////////////////////////////////////
/// \enum  FeatureColorMode
///
/// \brief Defines the color mode used to visualize the features.
///////////////////////////////////////////////////////////////////////////////
enum FeatureColorMode
{
    SelectedOnly,       ///< Plot only the selected features in the specified color.
    RejectedOnly,       ///< Plot only the rejected features in the specified color.
    AllFeatures,        ///< Plot all features (same color used for selected and rejected features).
    AllFeaturesColored, ///< Plot all features (different colors used for selected and rejected features).
    NoFeatures          ///< Do not plot the features (i.e. only the image).
};

///////////////////////////////////////////////////////////////////////////////
/// \class FeatureBucketerVisualizer
///
/// \brief Visualizer for the bucketing result.
///////////////////////////////////////////////////////////////////////////////
class FeatureBucketerVisualizer
{
protected: // protected attributes
    const FeatureColorMode m_ColorMode;         ///< Color mode used to visualize the features.
    const boolean          m_DrawGrid;          ///< Flag whether the grid is drawn or not.
    const sint32           m_PointRadius;       ///< Radius of the drawn points.
    const sint32           m_PointThickness;    ///< Thickness of the drawn points (negative means filled circle).
    const sint32           m_LineThickness;     ///< Thickness of the lines of the grid.
    const sint32           m_Delay;             ///< Delay how long the image is shown on the screen.
          cv::Scalar       m_ColorGrid;         ///< Color of the lines of the grid.
          cv::Scalar       m_ColorSelected;     ///< Color of the selected features.
          cv::Scalar       m_ColorRejected;     ///< Color of the rejected features.
          cv::Scalar       m_ColorAll;          ///< Color of all features.

public: // public methods
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Constructor.
    ///
    /// \param[in] ColorMode      Color mode used to visualize the features.
    /// \param[in] DrawGrid       Flag whether the grid is drawn or not.
    /// \param[in] PointRadius    Radius of the drawn points.
    /// \param[in] PointThickness Thickness of the drawn points (negative means filled circle).
    /// \param[in] LineThickness  Thickness of the lines of the grid.
    /// \param[in] Delay          Delay how long the image is shown on the screen.
    ///////////////////////////////////////////////////////////////////////////////
    FeatureBucketerVisualizer(const FeatureColorMode ColorMode      = AllFeaturesColored,
                              const boolean          DrawGrid       = true,
                              const sint32           PointRadius    = 4,
                              const sint32           PointThickness = -1,
                              const sint32           LineThickness  = 3,
                              const sint32           Delay          = 0);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///////////////////////////////////////////////////////////////////////////////
    ~FeatureBucketerVisualizer();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Save the bucketing result.
    ///
    /// \param[in] Bucketer        Feature bucketer used to bucket the features.
    /// \param[in] BackgroundImage Image used as background.
    /// \param[in] ImagePoints     List containing all image points.
    /// \param[in] Filename        Filename of the output image.
    ///////////////////////////////////////////////////////////////////////////////
    void SaveBucketingResult(const FeatureBucketerBase&        Bucketer,
                             const cv::Mat&                    BackgroundImage,
                             const ListColumnVectorFloat64_2d& ImagePoints,
                             const std::string&                Filename) const;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Visualize the bucketing result.
    ///
    /// \param[in] Bucketer        Feature bucketer used to bucket the features.
    /// \param[in] BackgroundImage Image used as background.
    /// \param[in] ImagePoints     List containing all image points.
    ///////////////////////////////////////////////////////////////////////////////
    void VisualizeBucketingResult(const FeatureBucketerBase&        Bucketer,
                                  const cv::Mat&                    BackgroundImage,
                                  const ListColumnVectorFloat64_2d& ImagePoints) const;

protected: // protected methods
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief         Create image showing the bucketing result.
    // /
    /// \param[in]     Bucketer        Feature bucketer used to bucket the features.
    /// \param[in]     BackgroundImage Image used as background.
    /// \param[in]     ImagePoints     List containing all image points.
    /// \param[in,out] BucketingImage  Image showing the bucketing result.
    ///////////////////////////////////////////////////////////////////////////////
    void CreateBucketingImage(const FeatureBucketerBase&        Bucketer,
                              const cv::Mat&                    BackgroundImage,
                              const ListColumnVectorFloat64_2d& ImagePoints,
                                    cv::Mat&                    BucketingImage) const;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief         Draw features into the bucketing image.
    ///
    /// \param[in]     ImagePointsToDraw List containing the image points to draw.
    /// \param[in]     FeatureColor      Color used to draw the features.
    /// \param[in,out] BucketingImage    Image showing the bucketing result.
    ///////////////////////////////////////////////////////////////////////////////
    void DrawFeatures(const ListColumnVectorFloat64_2d& ImagePointsToDraw,
                      const cv::Scalar&                 FeatureColor,
                            cv::Mat&                    BucketingImage) const;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief         Draw grid into the bucketing image.
    ///
    /// \param[in]     NumberOfBucketsHorizontal Number of buckets in horizontal direction.
    /// \param[in]     NumberOfBucketsVertical   Number of buckets in vertical direction.
    /// \param[in]     BucketSizeHorizontal      Size of each bucket in horizontal direction.
    /// \param[in]     BucketSizeVertical        Size of each bucket in vertical direction.
    /// \param[in,out] BucketingImage            Image showing the bucketing result.
    ///////////////////////////////////////////////////////////////////////////////
    void DrawGrid(const uint8    NumberOfBucketsHorizontal,
                  const uint8    NumberOfBucketsVertical,
                  const float64  BucketSizeHorizontal,
                  const float64  BucketSizeVertical,
                        cv::Mat& BucketingImage) const;
};

#endif // FEATUREBUCKETERVISUALIZER_H
