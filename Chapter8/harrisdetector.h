#ifndef HARRISDETECTOR_H
#define HARRISDETECTOR_H
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

class HarrisDetector
{
private:
    Mat cornerStrength;
    Mat cornerTh;
    Mat localMax;
    int neighbourhood;
    int aperture;
    double k;
    double maxStrength;
    double threshold;
    int nonMaxSize;
    Mat kernel;
public:
    HarrisDetector():neighbourhood(3), aperture(3),k(0.01),maxStrength(0.0),threshold(0.01),nonMaxSize(3){
        setLocalMaxWindowSize(nonMaxSize);
    }
    void setLocalMaxWindowSize(int size){
        nonMaxSize=size;
        kernel.create(nonMaxSize,nonMaxSize,CV_8U);
    }
    void detect(const Mat &image){
        cornerHarris(image,cornerStrength,neighbourhood,aperture,k);
        double minStrength;
        minMaxLoc(cornerStrength,&minStrength,&maxStrength);
        Mat dilated;
        dilate(cornerStrength,dilated,Mat());
        compare(cornerStrength,dilated,localMax,CMP_EQ);
    }
    Mat getCornerMap(double qualityLevel){
        Mat cornerMap;
        threshold=qualityLevel*maxStrength;
        cv::threshold(cornerStrength,cornerTh,threshold,255,THRESH_BINARY);
        cornerTh.convertTo(cornerMap,CV_8U);
        bitwise_and(cornerMap,localMax,cornerMap);
        return cornerMap;
    }
    void getCorners(std::vector<cv::Point> &points, double qualityLevel) {

             // Get the corner map
             cv::Mat cornerMap= getCornerMap(qualityLevel);
             // Get the corners
             getCorners(points, cornerMap);
         }

         // Get the feature points vector from the computed corner map
      void getCorners(std::vector<cv::Point> &points, const cv::Mat& cornerMap) {

             // Iterate over the pixels to obtain all feature points
             for( int y = 0; y < cornerMap.rows; y++ ) {

                 const uchar* rowPtr = cornerMap.ptr<uchar>(y);

                 for( int x = 0; x < cornerMap.cols; x++ ) {

                     // if it is a feature point
                     if (rowPtr[x]) {

                         points.push_back(cv::Point(x,y));
                     }
                 }
             }
         }
      \
      // Draw circles at feature point locations on an image
           void drawOnImage(cv::Mat &image, const std::vector<cv::Point> &points, cv::Scalar color= cv::Scalar(255,255,255), int radius=3, int thickness=2) {

               std::vector<cv::Point>::const_iterator it= points.begin();

               // for all corners
               while (it!=points.end()) {

                   // draw a circle at each corner location
                   cv::circle(image,*it,radius,color,thickness);
                   ++it;
               }
           }
};

#endif // HARRISDETECTOR_H
