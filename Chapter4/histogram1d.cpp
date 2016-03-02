#include "histogram1d.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>

using namespace std;
using namespace cv;


histogram1d::histogram1d()
{
    histsize[0]=256;
    hranges[0]=0.0;
    hranges[1]=255.0;
    ranges[0]=hranges;
    channels[0]=0;
}

Mat histogram1d::getHistogram(const Mat &image){
    Mat hist;
    calcHist(&image,1,channels,Mat(),hist,1,histsize,ranges);
    return hist;
}

Mat histogram1d::getHistogramImage(const Mat &image){
    Mat hist=getHistogram(image);
    double maxVal=0;
    double minVal=0;
    minMaxLoc(hist, &minVal, &maxVal,0, 0);
    Mat histImg(histsize[0],histsize[0],CV_8U, Scalar(255));
    int hpt=static_cast<int>(0.9*histsize[0]);
    for(int h=0;h<histsize[0];h++){
        float binVal=hist.at<float>(h);
        int intensity=static_cast<int>(binVal*hpt/maxVal);
        line(histImg,Point(h,histsize[0]), Point(h,histsize[0]-intensity),Scalar::all(0));
    }
return histImg;
}

Mat histogram1d::applyLookUp(const Mat &image, const Mat &lookup){
    Mat result;
    LUT(image,lookup,result);
    return result;
}

Mat histogram1d::stretch(const Mat &image, int minValue){
    Mat hist=getHistogram(image);
    int imin=0;
    for(;imin<histsize[0];imin++){
        cout<<hist.at<float>(imin)<<endl;
        if (hist.at<float>(imin)>minValue)
            break;
    }
    int imax=histsize[0]-1;
    for(;imax>=0;imax--){
        if (hist.at<float>(imax)>minValue)
            break;
    }
    int dim(256);
    Mat lookup(1,&dim,CV_8U);
    for (int i=0;i<256;i++){
        if(i<imin) lookup.at<uchar>(i)=0;
        else if (i>imax) lookup.at<uchar>(i)=255;
        else lookup.at<uchar>(i)=static_cast<uchar>(255.0*(i-imin)/(imax-imin)+0.5);
    }
Mat result;
result=applyLookUp(image,lookup);
return result;
}

Mat histogram1d::equlize(const Mat &image){
    Mat result;
    equalizeHist(image,result);
    return result;
}
