#ifndef WATERSHEDSEGMENTER_H
#define WATERSHEDSEGMENTER_H
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;


class WatershedSegmenter
{
private:
    Mat markers;
public:
    //WatershedSegmenter();
    void setMarkers(const Mat &markerImage){
        markerImage.convertTo(markers,CV_32S);
    }
    Mat process(const Mat &image){
        watershed(image,markers);
        return markers;
    }
    Mat getSegmentation() {

            Mat tmp;
            // all segment with label higher than 255
            // will be assigned value 255
            markers.convertTo(tmp,CV_8U);

            return tmp;
          }

          // Return watershed in the form of an image
     Mat getWatersheds() {

            Mat tmp;
            markers.convertTo(tmp,CV_8U,255,255);

            return tmp;
          }
};

#endif // WATERSHEDSEGMENTER_H
