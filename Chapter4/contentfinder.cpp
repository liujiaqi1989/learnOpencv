#include "contentfinder.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>

contentfinder::contentfinder()
{
threshold=-1.0f;
ranges[0]=hranges;
ranges[1]=hranges;
ranges[2]=hranges;
}

void contentfinder::setThreshold(float t){
    threshold=t;
}
float contentfinder::getThreshold(){
    return threshold;
}
void contentfinder::setHistogram(const Mat &h){
    histogram=h;
    normalize(histogram,histogram,1.0);
}
Mat contentfinder::find(const Mat &image, float minValue, float maxValue, int *channels, int dim){
    Mat result;
    hranges[0]=minValue;
    hranges[1]=maxValue;
    for (int i=0;i<dim;i++){
        this->channels[i]=channels[i];
        calcBackProject(&image,1,channels,histogram,result,ranges,255.0);
        if(threshold>0.0){
            cv::threshold(result,result,255*threshold,255,THRESH_BINARY);
        }

    }
     return result;
}

Mat contentfinder::find(const Mat& image) {

        Mat result;

        hranges[0]= 0.0;	// range [0,255]
        hranges[1]= 255.0;
        channels[0]= 0;		// the three channels
        channels[1]= 1;
        channels[2]= 2;

        calcBackProject(&image,
                      1,            // one image
                      channels,     // vector specifying what histogram dimensions belong to what image channels
                      histogram,    // the histogram we are using
                      result,       // the resulting back projection image
                      ranges,       // the range of values, for each dimension
                      255.0         // the scaling factor is chosen such that a histogram value of 1 maps to 255
           );



        // Threshold back projection to obtain a binary image
        if (threshold>0.0)
           cv::threshold(result, result, 255*threshold, 255, THRESH_BINARY);

        return result;
    }
