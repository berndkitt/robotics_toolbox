///////////////////////////////////////////////////////////////////////////////
/// \file FeatureMatcher.h
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

#ifndef FEATUREMATCHER_H
#define FEATUREMATCHER_H

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>

#include <GlobalTypesDerived.h>

///////////////////////////////////////////////////////////////////////////////
/// \class FeatureMatcher
///
/// \brief Class for creating feature correspondences between images.
///////////////////////////////////////////////////////////////////////////////
class FeatureMatcher
{
protected: // protected attributes
    cv::Ptr<cv::Feature2D> m_FeatureDetector;           ///< Detector for the features and extractor for the descriptors.
    cv::DescriptorMatcher* m_DescriptorMatcher;         ///< Matcher for the feature descriptors.
    float64                m_RatioDistance;             ///< Ratio between first and second best distance to consider a match to be a good one.
    boolean                m_ParametersSetInternally;   ///< Flag defining whether the class members have been set internally or not.

public: // public methods
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Constructor.
    ///
    /// \param[in] RatioDistance Ratio between first and second best distance to consider a match to be a good one.
    ///////////////////////////////////////////////////////////////////////////////
    FeatureMatcher(const float64 RatioDistance = 0.7);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief     Constructor.
    ///
    /// \param[in] FeatureDetector   Detector for the features and extractor for the descriptors.
    /// \param[in] DescriptorMatcher Matcher for the feature descriptors.
    /// \param[in] RatioDistance     Ratio between first and second best distance to consider a match to be a good one.
    ///////////////////////////////////////////////////////////////////////////////
    FeatureMatcher(const cv::Ptr<cv::Feature2D>& FeatureDetector,
                         cv::DescriptorMatcher*  DescriptorMatcher,
                   const float64                 RatioDistance     = 0.7);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///////////////////////////////////////////////////////////////////////////////
    ~FeatureMatcher();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief      Find feature correspondences in the images.
    ///
    /// \param[in]  Images                 List of images where feature correspondences shall be found.
    /// \param[out] FeatureCorrespondences Image coordinate of the feature correspondences in all images.
    ///
    /// \return     Number of feature correspondences found.
    ///////////////////////////////////////////////////////////////////////////////
    uint64 FindCorrespondences(const std::vector<cv::Mat>&                    Images,
                                     std::vector<ListColumnVectorFloat64_2d>& FeatureCorrespondences);
};

#endif // FEATUREMATCHER_H
