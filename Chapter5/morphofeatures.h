#ifndef MORPHOFEATURES_H
#define MORPHOFEATURES_H
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class MorphoFeatures
{
private:
    int threshold;
    Mat cross;
    Mat diamond;
    Mat square;
    Mat x;
public:
    MorphoFeatures();
    Mat getEdges(const Mat &image);
    void applyThreshold(Mat &result);
    void setThreshold(int t);
    int getThreshold();
    Mat getCorners(const Mat &image);
    void drawOnImage(const Mat &binary, Mat &image);


};

#endif // MORPHOFEATURES_H
