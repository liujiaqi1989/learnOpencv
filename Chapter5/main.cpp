#include <QCoreApplication>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;


int main()
{
    Mat image=imread("/home/jiaqi/Pictures/images/binary.bmp");
    Mat eroded;
    erode(image,eroded,Mat());
    namedWindow("Eroded Image");
    imshow("Eroded Image",eroded);

    Mat dilated;
    dilate(image,dilated,Mat());
    namedWindow("Dilated Image");
    imshow("Dialted Image",dilated);

    waitKey(0);


    return 0;
}
