///////////////////////////////////////////////////////////////////////////////
/// \file FeatureBucketerVisualizer.cpp
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

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "../include/FeatureBucketerVisualizer.h"

FeatureBucketerVisualizer::FeatureBucketerVisualizer(const FeatureColorMode ColorMode,
                                                     const boolean          DrawGrid,
                                                     const uint64           PointRadius,
                                                     const sint64           PointThickness,
                                                     const uint64           LineThickness,
                                                     const sint64           Delay) : m_ColorMode{ColorMode},
                                                                                     m_DrawGrid{DrawGrid},
                                                                                     m_PointRadius{PointRadius},
                                                                                     m_PointThickness{PointThickness},
                                                                                     m_LineThickness{LineThickness},
                                                                                     m_Delay{Delay}
{
    // set default drawing colors
    m_ColorGrid     = cv::Scalar(0,   255, 255); // BGR -> yellow // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    m_ColorSelected = cv::Scalar(0,   255, 0);   // BGR -> green  // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    m_ColorRejected = cv::Scalar(0,   0,   255); // BGR -> red    // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    m_ColorAll      = cv::Scalar(255, 255, 0);   // BGR -> cyan   // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}

FeatureBucketerVisualizer::~FeatureBucketerVisualizer()
{

}

void FeatureBucketerVisualizer::SaveBucketingResult(const FeatureBucketerBase&        Bucketer,
                                                    const cv::Mat&                    BackgroundImage,
                                                    const ListColumnVectorFloat64_2d& ImagePoints,
                                                    const std::string&                Filename) const
{
    // clone input image
    cv::Mat BucketingImage = BackgroundImage.clone();

    // create bucketing image
    CreateBucketingImage(Bucketer, BackgroundImage, ImagePoints, BucketingImage);

    // save bucketing image
    cv::imwrite(Filename, BucketingImage);
}

void FeatureBucketerVisualizer::VisualizeBucketingResult(const FeatureBucketerBase&        Bucketer,
                                                         const cv::Mat&                    BackgroundImage,
                                                         const ListColumnVectorFloat64_2d& ImagePoints) const
{
    // clone input image
    cv::Mat BucketingImage = BackgroundImage.clone();

    // create bucketing image
    CreateBucketingImage(Bucketer, BackgroundImage, ImagePoints, BucketingImage);

    // show bucketing image
    cv::namedWindow("bucketing result");
    cv::imshow("bucketing result", BucketingImage);
    cv::waitKey(m_Delay);
    cv::destroyWindow("bucketing result");
}

void FeatureBucketerVisualizer::CreateBucketingImage(const FeatureBucketerBase&        Bucketer,
                                                     const cv::Mat&                    BackgroundImage,
                                                     const ListColumnVectorFloat64_2d& ImagePoints,
                                                           cv::Mat&                    BucketingImage) const
{
    // get selected and rejected indices
    const ListUInt64 SelectedIndices {Bucketer.GetSelectedIndices()};
    const ListUInt64 Rejectedindices {Bucketer.GetRejectedIndices()};

    // get number of selected and rejected indices
    const uint64 NumberOfSelectedIndices {SelectedIndices.size()};
    const uint64 NumberOfRejectedIndices {Rejectedindices.size()};

    // get selected and rejected image points
    ListColumnVectorFloat64_2d ImagePointsRejected;
    ListColumnVectorFloat64_2d ImagePointsSelected;

    Bucketer.GetRejectedFeatures(ImagePoints, ImagePointsRejected);
    Bucketer.GetSelectedFeatures(ImagePoints, ImagePointsSelected);

    // get number of provided features
    const uint64 NumberOfFeatures {ImagePoints.size()};

    // get image dimensions
    const uint64 ImageWidth  {static_cast<uint64>(BackgroundImage.cols)};
    const uint64 ImageHeight {static_cast<uint64>(BackgroundImage.rows)};

    // get used image dimensions during feature bucketing
    const uint64 ImageWidthBucketing  {Bucketer.GetNumberOfPixelsHorizontal()};
    const uint64 ImageHeightBucketing {Bucketer.GetNumberOfPixelsVertical()};

    // check plausibility
    const boolean FeaturesPlausible  {(NumberOfFeatures == (NumberOfSelectedIndices + NumberOfRejectedIndices))};
    const boolean ImageSizePlausible {((ImageWidth == ImageWidthBucketing) && (ImageHeight == ImageHeightBucketing))};

    // create bucketing image
    if(FeaturesPlausible && ImageSizePlausible)
    {
        // draw features depending on selected mode
        switch(m_ColorMode)
        {
            case SelectedOnly:
            {
                DrawFeatures(ImagePointsSelected, m_ColorSelected, BucketingImage);

                break;
            }
            case RejectedOnly:
            {
                DrawFeatures(ImagePointsRejected, m_ColorRejected, BucketingImage);

                break;
            }
            case AllFeatures:
            {
                DrawFeatures(ImagePointsRejected, m_ColorAll, BucketingImage);
                DrawFeatures(ImagePointsSelected, m_ColorAll, BucketingImage);

                break;
            }
            case AllFeaturesColored:
            {
                DrawFeatures(ImagePointsRejected, m_ColorRejected, BucketingImage);
                DrawFeatures(ImagePointsSelected, m_ColorSelected, BucketingImage);

                break;
            }
            case NoFeatures:
            {
                // do nothing
                break;
            }
            // no default needed as all options are covered
        }

        // draw grid
        if(m_DrawGrid)
        {
            // get bucket information
            const uint64  NumberOfBucketsHorizontal {Bucketer.GetNumberOfBucketsHorizontal()};
            const uint64  NumberOfBucketsVertical   {Bucketer.GetNumberOfBucketsVertical()};
            const float64 BucketSizeHorizontal      {Bucketer.GetBucketSizeHorizontal()};
            const float64 BucketSizeVertical        {Bucketer.GetBucketSizeVertical()};

            DrawGrid(NumberOfBucketsHorizontal, NumberOfBucketsVertical, BucketSizeHorizontal, BucketSizeVertical, BucketingImage);
        }
    }
}

void FeatureBucketerVisualizer::DrawFeatures(const ListColumnVectorFloat64_2d& ImagePointsToDraw,
                                             const cv::Scalar&                 FeatureColor,
                                                   cv::Mat&                    BucketingImage) const
{
    // get number of features to draw
    const uint64 NumberOfFeaturesToDraw {ImagePointsToDraw.size()};

    // draw features
    for(uint64 i_Feature {0U}; i_Feature < NumberOfFeaturesToDraw; i_Feature++)
    {
        // get coordinates of current feature
        const float64 CoordinateHorizontal {ImagePointsToDraw[i_Feature](0)};
        const float64 CoordinateVertical   {ImagePointsToDraw[i_Feature](1)};

        // draw point
        const cv::Point CurrentPoint(CoordinateHorizontal, CoordinateVertical);

        cv::circle(BucketingImage, CurrentPoint, m_PointRadius, FeatureColor, m_PointThickness);
    }
}

void FeatureBucketerVisualizer::DrawGrid(uint64   NumberOfBucketsHorizontal,
                                         uint64   NumberOfBucketsVertical,
                                         float64  BucketSizeHorizontal,
                                         float64  BucketSizeVertical,
                                         cv::Mat& BucketingImage) const
{
    // get image dimensions
    const uint64 ImageWidth  {static_cast<uint64>(BucketingImage.cols)};
    const uint64 ImageHeight {static_cast<uint64>(BucketingImage.rows)};

    // compute offset
    const float64 Offset {static_cast<float64>(m_LineThickness) * 0.5};

    // plot horizontal lines
    for(uint64 i_Line {0U}; i_Line < (NumberOfBucketsVertical + 1U); i_Line++)
    {
        // get vertical coordinate of the line
        float64 CoordinateVertical {static_cast<float64>(i_Line) * BucketSizeVertical};

        if(i_Line == 0U)
        {
            CoordinateVertical += Offset;
        }
        else if(i_Line == NumberOfBucketsVertical)
        {
            CoordinateVertical -= Offset;
        }
        else
        {
            // do nothing
        }

        // define start and end point of the line
        const cv::Point LeftPoint(0U, CoordinateVertical);
        const cv::Point RightPoint(ImageWidth - 1U, CoordinateVertical);

        // draw horizontal line
        cv::line(BucketingImage, LeftPoint, RightPoint, m_ColorGrid, m_LineThickness);
    }

    // plot vertical lines
    for(uint64 i_Line {0U}; i_Line < (NumberOfBucketsHorizontal + 1U); i_Line++)
    {
        // get horizontal coordinate of the line
        float64 CoordinateHorizontal {static_cast<float64>(i_Line) * BucketSizeHorizontal};

        if(i_Line == 0U)
        {
            CoordinateHorizontal += Offset;
        }
        else if(i_Line == NumberOfBucketsHorizontal)
        {
            CoordinateHorizontal -= Offset;
        }
        else
        {
            // do nothing
        }

        // define start and end point of the line
        const cv::Point TopPoint(CoordinateHorizontal, 0U);
        const cv::Point BottomPoint(CoordinateHorizontal, ImageHeight - 1U);

        // draw horizontal line
        cv::line(BucketingImage, TopPoint, BottomPoint, m_ColorGrid, m_LineThickness);
    }
}
