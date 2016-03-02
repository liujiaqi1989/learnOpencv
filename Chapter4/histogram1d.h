#ifndef HISTOGRAM1D_H
#define HISTOGRAM1D_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace cv;

class histogram1d
{
private:
    int histsize[1];
    float hranges[2];
    const float* ranges[1];
    int channels[1];
public:
    histogram1d();
    Mat getHistogram(const Mat &image);
    Mat getHistogramImage(const Mat &image);
    Mat applyLookUp(const Mat &image, const Mat &lookup);
    Mat stretch(const Mat &image, int minValue=0);
    Mat equlize(const Mat &image);

};

#endif // HISTOGRAM1D_H
