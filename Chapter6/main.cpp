#include <QCoreApplication>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "laplacianzc.h"
using namespace std;
using namespace cv;


int main()
{
    Mat image=imread("/home/jiaqi/Pictures/images/boldt.jpg",0);
    namedWindow("Original Image");
    imshow("Original Image", image);
    Mat result;
    blur(image,result,Size(5,5));
    namedWindow("Blured Image");
    imshow("Blured Image",result);
    GaussianBlur(image,result,Size(5,5),1.5);
    namedWindow("GBlured Image");
    imshow("GBlured Image",result);
    medianBlur(image,result,5);
    namedWindow("MBlured Image");
    imshow("MBlured Image",result);
    Mat sobelX,sobelY;
    Sobel(image,sobelX,CV_8U,1,0,3,0.4,128);
    Sobel(image,sobelY,CV_8U,0,1,3,0.4,128);
    namedWindow("Sobel Image1");
    imshow("Sobel Image1",sobelX);
    namedWindow("Sobel Image2");
    imshow("Sobel Image2",sobelY);

    Sobel(image,sobelX,CV_16S,1,0);
    Sobel(image,sobelY,CV_16S,0,1);
    Mat sobel;
    sobel=abs(sobelX)+abs(sobelY);
    double sobmin, sobmax;
    minMaxLoc(sobel,&sobmin,&sobmax);
    Mat sobelImage;
    sobel.convertTo(sobelImage,CV_8U,-255./sobmax,255);
    namedWindow("Sobelimage");
    imshow("Sobelimage", sobelImage);
    Mat sobelThresholded;
    threshold(sobelImage, sobelThresholded, 190, 255, cv::THRESH_BINARY);
    namedWindow("Timage");
    imshow("Timage",sobelThresholded);

    LaplacianZC laplacian;
    laplacian.setAperture(7);
    Mat flap=laplacian.computeLaplacian(image);
    Mat laplace=laplacian.getLaplacianImage();
    namedWindow("Laplacian Image (7x7)");
    imshow("Laplacian Image (7x7)",laplace);
    Mat zeros;
    zeros= laplacian.getZeroCrossingsWithSobel(50);
        cv::namedWindow("Zero-crossings (2)");
        cv::imshow("Zero-crossings (2)",zeros);





    waitKey(0);
    return 0;
}
