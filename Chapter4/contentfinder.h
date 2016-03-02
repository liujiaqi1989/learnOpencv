#ifndef CONTENTFINDER_H
#define CONTENTFINDER_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace cv;

class contentfinder
{
private:
    float hranges[2];
    const float*ranges[3];
    int channels[3];
    float threshold;
    Mat histogram;
public:
    contentfinder();
    void setThreshold(float t);
    float getThreshold();
    void setHistogram(const Mat &h);
    Mat find(const Mat &image,float minValue, float maxValue,int *channels,int dim);
    Mat find(const Mat& image);
};

#endif // CONTENTFINDER_H
