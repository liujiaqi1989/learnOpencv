#ifndef COLORDETECTOR_H
#define COLORDETECTOR_H
#include<opencv2/opencv.hpp>

using namespace cv;

class ColorDetector
{
private:
    int minDist;
    Vec3b target;
    Mat result;

public:
    ColorDetector();
    void setColorDistanceThreshold(int distance);
    int getColorDistanceThreshold();
    void setTargetColor(uchar red, uchar green, uchar blue);
    void setTargetColor(Vec3b Target);
    Vec3b getTargetColor();
    Mat process(const Mat &image);
};

#endif // COLORDETECTOR_H
