#include "colordetector.h"
#include<opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
using namespace cv;


         ColorDetector::ColorDetector(){
             minDist=100;
             target[0]=target[1]=target[2]=0;

         }


    void ColorDetector::setColorDistanceThreshold(int distance){
        if (distance<0){
            distance=0;
        }
        minDist=distance;
    }
    int ColorDetector::getColorDistanceThreshold(){
        return minDist;
    }
    void ColorDetector::setTargetColor(uchar red, uchar green, uchar blue){
        target[2]=red;
        target[1]=green;
        target[0]=blue;
    }
    void ColorDetector::setTargetColor(Vec3b Target){
        target=Target;
    }
    Vec3b ColorDetector::getTargetColor(){
        return target;
    }

Mat ColorDetector::process(const Mat &image){
    int cl=image.cols*image.channels();
    result.create(image.rows,image.cols,CV_8U);
    for (int i=0;i<image.rows;++i){
        const uchar *p=image.ptr<uchar>(i);
        uchar *q=result.ptr<uchar>(i);
        for(int j=0;j<cl;j=j+3){
            int dist=abs(p[j]-target[0])+abs(p[j+1]-target[1])+abs(p[j+2]-target[2]);
            if (dist<minDist){
                q[j/3]=255;
            }else{
               q[j/3]=0;
            }
        }
    }
    return result;
}

