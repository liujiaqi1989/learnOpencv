#include <QCoreApplication>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat image=imread("/home/jiaqi/Pictures/lena.jpg");
    cout<<"size: "<<image.size().height<<", "<<image.size().width<<endl;
    namedWindow("Original Image");
    imshow("Original Image", image);
    waitKey(0);

    Mat result;
    flip(image,result,0);
    namedWindow("Output Image");
    imshow("Output Image", result);
    waitKey(0);

    return 0;
}
