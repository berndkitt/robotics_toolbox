///////////////////////////////////////////////////////////////////////////////
/// \file FeatureMatcher.cpp
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

#include "../include/FeatureMatcher.h"

FeatureMatcher::FeatureMatcher(const float64 RatioDistance) : m_DescriptorMatcher{new cv::BFMatcher},
                                                              m_RatioDistance{RatioDistance},
                                                              m_ParametersSetInternally{true}
{
    // set internal attributes
    m_FeatureDetector = cv::ORB::create();
}

FeatureMatcher::FeatureMatcher(const cv::Ptr<cv::Feature2D>& FeatureDetector,
                                     cv::DescriptorMatcher*  DescriptorMatcher,
                               const float64                 RatioDistance) : m_FeatureDetector{FeatureDetector},
                                                                              m_DescriptorMatcher{DescriptorMatcher},
                                                                              m_RatioDistance{RatioDistance},
                                                                              m_ParametersSetInternally{false}
{

}

FeatureMatcher::~FeatureMatcher()
{
    if(m_ParametersSetInternally)
    {
        delete m_DescriptorMatcher;
    }
}

uint64 FeatureMatcher::FindCorrespondences(const std::vector<cv::Mat>&                    Images,
                                                 std::vector<ListColumnVectorFloat64_2d>& FeatureCorrespondences)
{
    // get number of images
    const uint64 NumberOfImages {Images.size()};

    // extract features and calculate descriptors for all images
    std::vector< std::vector<cv::KeyPoint> > ExtractedFeatures;
    std::vector<cv::Mat>                     FeatureDescriptors;

    // pre-allocate memory
    ExtractedFeatures.resize(NumberOfImages);
    FeatureDescriptors.resize(NumberOfImages);

    for(uint64 i_Image {0U}; i_Image < NumberOfImages; i_Image++)
    {
        // extract features
        m_FeatureDetector->detect(Images[i_Image], ExtractedFeatures[i_Image]);

        // calculate descriptors
        m_FeatureDetector->compute(Images[i_Image], ExtractedFeatures[i_Image], FeatureDescriptors[i_Image]);
    }

    // get number of extracted features in first image
    const uint64 NumberOfExtractedFeatures {ExtractedFeatures[0].size()};

    // find feature correspondences
    uint64 NumberOfCorrespondencesFound {0U};

    std::vector< std::vector< std::vector<cv::DMatch> > > FeatureCorrespondencesInternal;

    FeatureCorrespondencesInternal.resize(NumberOfImages);

    for(uint64 i_Image {0U}; i_Image < NumberOfImages; i_Image++)
    {
        const uint64 FirstIndex  {i_Image % NumberOfImages};
        const uint64 SecondIndex {(i_Image + 1U) % NumberOfImages};

        m_DescriptorMatcher->knnMatch(FeatureDescriptors[FirstIndex], FeatureDescriptors[SecondIndex], FeatureCorrespondencesInternal[i_Image], 2);
    }

    for(uint64 i_Feature {0U}; i_Feature < NumberOfExtractedFeatures; i_Feature++)
    {
        uint64  FeatureIndex {0U};
        boolean IsGoodMatch  {true};

        std::vector<uint64> IndexList;
        IndexList.resize(NumberOfImages);

        for(uint64 i_Image {0U}; i_Image < NumberOfImages; i_Image++)
        {
            if(i_Image == 0U)
            {
                FeatureIndex = i_Feature;
            }
            else
            {
                FeatureIndex = IndexList[i_Image - 1U];
            }

            IndexList[i_Image] = FeatureCorrespondencesInternal[i_Image][FeatureIndex][0].trainIdx;

            const float64 DistanceBest       {FeatureCorrespondencesInternal[i_Image][FeatureIndex][0].distance};
            const float64 DistanceSecondBest {FeatureCorrespondencesInternal[i_Image][FeatureIndex][1].distance};

            if(DistanceBest < (m_RatioDistance * DistanceSecondBest))
            {
                IsGoodMatch = IsGoodMatch && true; // NOLINT(readability-simplify-boolean-expr)
            }
            else
            {
                IsGoodMatch = IsGoodMatch && false; // NOLINT(readability-simplify-boolean-expr)
            }
        }

        // check if current feature correspondence is a good correspondence (i.e. "loop" over all images is closed)
        if((i_Feature == IndexList[NumberOfImages - 1U]) && IsGoodMatch)
        {
            for(uint64 i_Image {0U}; i_Image < NumberOfImages; i_Image++)
            {
                if(i_Image == 0U)
                {
                    FeatureIndex = i_Feature;
                }
                else
                {
                    FeatureIndex = IndexList[i_Image - 1U];
                }

                ColumnVectorFloat64_2d ImagePoint;
                ImagePoint << ExtractedFeatures[i_Image][FeatureIndex].pt.x, ExtractedFeatures[i_Image][FeatureIndex].pt.y;

                FeatureCorrespondences[i_Image].push_back(ImagePoint);
            }

            NumberOfCorrespondencesFound++;
        }
    }

    return NumberOfCorrespondencesFound;
}
