#include <QCoreApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "colordetector.h"
using namespace cv;


int main()
{
//    QCoreApplication a(argc, argv);

//    return a.exec();
    ColorDetector cdetect;
    Mat image=imread("/home/jiaqi/Pictures/images/boldt.jpg");
    cdetect.setTargetColor(130,190,230);
    namedWindow("original");
    imshow("original",image);

    namedWindow("result");
    imshow("result", cdetect.process(image));
    waitKey(0);
    return 0;


}
