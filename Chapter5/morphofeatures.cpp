#include "morphofeatures.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

MorphoFeatures::MorphoFeatures()
{
    threshold=-1;
    cross=Mat(5,5,CV_8U,Scalar(0));
    diamond=Mat(5,5,CV_8U,Scalar(1));
    x=Mat(5,5,CV_8U,Scalar(0));
    square=Mat(5,5,CV_8U,cv::Scalar(1));
    for (int i=0;i<5;i++){
        cross.at<uchar>(2,i)=1;
        cross.at<uchar>(i,2)=1;
    }

    diamond.at<uchar>(0,0)=0;
    diamond.at<uchar>(0,1)=0;
    diamond.at<uchar>(1,0)=0;
    diamond.at<uchar>(4,4)=0;
    diamond.at<uchar>(3,4)=0;
    diamond.at<uchar>(4,3)=0;
    diamond.at<uchar>(4,0)=0;
    diamond.at<uchar>(4,1)=0;
    diamond.at<uchar>(3,0)=0;
    diamond.at<uchar>(0,4)=0;
    diamond.at<uchar>(0,3)=0;
    diamond.at<uchar>(1,4)=0;

    for (int i=0;i<5;i++){
        x.at<uchar>(i,i)=1;
        x.at<uchar>(4-i,i)=1;
    }
}
//MorphoFeatures::MorphoFeatures() : threshold(-1), cross(5,5,CV_8U,cv::Scalar(0)),
//                                       diamond(5,5,CV_8U,cv::Scalar(1)),
//                                       square(5,5,CV_8U,cv::Scalar(1)),
//                                       x(5,5,CV_8U,cv::Scalar(0)){

//         // Creating the cross-shaped structuring element
//         for (int i=0; i<5; i++) {

//             cross.at<uchar>(2,i)= 1;
//             cross.at<uchar>(i,2)= 1;
//         }

//         // Creating the diamond-shaped structuring element
//         diamond.at<uchar>(0,0)= 0;
//         diamond.at<uchar>(0,1)= 0;
//         diamond.at<uchar>(1,0)= 0;
//         diamond.at<uchar>(4,4)= 0;
//         diamond.at<uchar>(3,4)= 0;
//         diamond.at<uchar>(4,3)= 0;
//         diamond.at<uchar>(4,0)= 0;
//         diamond.at<uchar>(4,1)= 0;
//         diamond.at<uchar>(3,0)= 0;
//         diamond.at<uchar>(0,4)= 0;
//         diamond.at<uchar>(0,3)= 0;
//         diamond.at<uchar>(1,4)= 0;

//         // Creating the x-shaped structuring element
//         for (int i=0; i<5; i++) {

//             x.at<uchar>(i,i)= 1;
//             x.at<uchar>(4-i,i)= 1;
//         }
//     }

Mat MorphoFeatures::getEdges(const Mat &image){
    Mat result;
    morphologyEx(image,result,MORPH_GRADIENT,Mat());
    applyThreshold(result);
    return result;
}

void MorphoFeatures::applyThreshold(Mat &result){
    if (threshold>0){
        cv::threshold(result,result,threshold,255,THRESH_BINARY);
    }
}

void MorphoFeatures::setThreshold(int t){

         threshold= t;
     }

int MorphoFeatures::getThreshold(){

         return threshold;
     }

Mat MorphoFeatures::getCorners(const Mat &image){
    Mat result;
    dilate(image,result,cross);
    erode(result,result,diamond);
    Mat result2;
    dilate(image,result2,x);
    erode(result2,result2,square);
    absdiff(result2,result,result);
    applyThreshold(result);
    return result;

}

void MorphoFeatures::drawOnImage(const Mat &binary, Mat &image){
     Mat_<uchar>::const_iterator it= binary.begin<uchar>();
     Mat_<uchar>::const_iterator itend= binary.end<uchar>();

             // for each pixel
     for (int i=0; it!= itend; ++it,++i) {
            if (!*it)
            circle(image,cv::Point(i%image.step,i/image.step),5,cv::Scalar(255,0,0));
      }
 }

