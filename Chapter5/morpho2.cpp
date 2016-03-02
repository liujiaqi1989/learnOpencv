#include <QCoreApplication>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "morphofeatures.h"
using namespace cv;


int main(){
    Mat image=imread("/home/jiaqi/Pictures/images/building.jpg",0);
    namedWindow("Image");
    imshow("Image",image);
    MorphoFeatures morpho;
    morpho.setThreshold(40);
    Mat edges;
    edges=morpho.getEdges(image);
    namedWindow("Edge Image");
    imshow("Edge Image",edges);


    morpho.setThreshold(-1);
    Mat corners;
    corners= morpho.getCorners(image);
    morphologyEx(corners,corners,MORPH_TOPHAT,Mat());
    cv::threshold(corners, corners, 40, 255, THRESH_BINARY_INV);
    namedWindow("Corners");
    imshow("Corners",corners);
    morpho.drawOnImage(corners,image);
    namedWindow("Corners on Image");
    imshow("Corners on Image",image);


    waitKey(0);



    return 0;
}
