#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include "opencv2/nonfree/nonfree.hpp"

#include "harrisdetector.h"

int main()
{
    // Read input image
    cv::Mat image= cv::imread("/home/jiaqi/Pictures/images/church01.jpg",0);
    if (!image.data)
        return 0;

    // Display the image
    cv::namedWindow("Original Image");
    cv::imshow("Original Image",image);

    // Detect Harris Corners
    cv::Mat cornerStrength;
    cv::cornerHarris(image,cornerStrength,
                  3,     // neighborhood size
                     3,     // aperture size
                     0.01); // Harris parameter

   // threshold the corner strengths
    cv::Mat harrisCorners;
    double threshold= 0.0001;
    cv::threshold(cornerStrength,harrisCorners,
                 threshold,255,cv::THRESH_BINARY_INV);

    // Display the corners
    cv::namedWindow("Harris Corner Map");
    cv::imshow("Harris Corner Map",harrisCorners);

    // Create Harris detector instance
    HarrisDetector harris;
    // Compute Harris values
    harris.detect(image);
    // Detect Harris corners
    std::vector<cv::Point> pts;
    harris.getCorners(pts,0.01);
    // Draw Harris corners
    harris.drawOnImage(image,pts);

    // Display the corners
    cv::namedWindow("Harris Corners");
    cv::imshow("Harris Corners",image);

    cv::Mat image1=cv::imread("/home/jiaqi/Pictures/images/church01.jpg",0);

    std::vector<cv::Point2f> corners;
    cv::goodFeaturesToTrack(image1,corners,500,0.01,10);
    std::vector<cv::Point2f>::const_iterator it= corners.begin();
        while (it!=corners.end()) {

            // draw a circle at each corner location
            cv::circle(image1,*it,3,cv::Scalar(255,255,255),2);
            ++it;
        }

        // Display the corners
        cv::namedWindow("Good Features to Track");
        cv::imshow("Good Features to Track",image1);

    image=cv::imread("/home/jiaqi/Pictures/images/church01.jpg",0);
    std::vector<cv::KeyPoint> keypoints;
    keypoints.clear();
    cv::FastFeatureDetector fast(40);
    fast.detect(image,keypoints);

    cv::drawKeypoints(image,keypoints,image,cv::Scalar(255,255,255),cv::DrawMatchesFlags::DRAW_OVER_OUTIMG);

        // Display the corners
    cv::namedWindow("FAST Features");
    cv::imshow("FAST Features",image);

    image=cv::imread("/home/jiaqi/Pictures//images/church03.jpg",0);
    keypoints.clear();
    cv::SurfFeatureDetector surf(2500);
    surf.detect(image,keypoints);
    cv::Mat featureImage;
    cv::drawKeypoints(image,keypoints,featureImage,cv::Scalar(255,255,255),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

        // Display the corners
    cv::namedWindow("SURF Features");
    cv::imshow("SURF Features",featureImage);

    image=cv::imread("/home/jiaqi/Pictures/images/church01.jpg",0);
    keypoints.clear();
        // Construct the SURF feature detector object
        cv::SiftFeatureDetector sift(
            0.03,  // feature threshold
            10.);  // threshold to reduce
                   // sensitivity to lines

        // Detect the SURF features
        sift.detect(image,keypoints);

        cv::drawKeypoints(image,keypoints,featureImage,cv::Scalar(255,255,255),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

        // Display the corners
        cv::namedWindow("SIFT Features");
        cv::imshow("SIFT Features",featureImage);


    cv::waitKey(0);
    return 0;
}
