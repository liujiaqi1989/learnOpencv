#ifndef LAPLACIANZC_H
#define LAPLACIANZC_H
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class LaplacianZC
{
private:
    Mat img;
    Mat laplace;
    int aperture;

public:
    LaplacianZC():aperture(3){};
    void setAperture(int a){
        aperture=a;
    }
    Mat computeLaplacian(const Mat &image){
        Laplacian(image,laplace,CV_32F,aperture);
        img=image.clone();
        return laplace;
    }
    Mat getLaplacianImage(double scale=-1.0){
        if(scale<0){
            double lapmin, lapmax;
            minMaxLoc(laplace,&lapmin,&lapmax);
            scale=127/max(-lapmin,lapmax);
        }
        Mat laplaceImage;
        laplace.convertTo(laplaceImage,CV_8U,scale,128);

        return laplaceImage;
    }

    Mat getZeroCrossingsWithSobel(float threshold) {

              Mat sx;
              Sobel(img,sx,CV_32F,1,0,1);
              Mat sy;
              Sobel(img,sy,CV_32F,0,1,1);

              // Create the iterators
              Mat_<float>::const_iterator it= laplace.begin<float>()+laplace.step1();
              Mat_<float>::const_iterator itend= laplace.end<float>();
              Mat_<float>::const_iterator itup= laplace.begin<float>();
              Mat_<float>::const_iterator itx= sx.begin<float>()+sx.step1();
              Mat_<float>::const_iterator ity= sy.begin<float>()+sy.step1();

              // Binary image initialize to white
              Mat binary(laplace.size(),CV_8U,cv::Scalar(255));
              Mat_<uchar>::iterator itout= binary.begin<uchar>()+binary.step1();

              for ( ; it!= itend; ++it, ++itup, ++itout, ++itx, ++ity) {

                  // if the product of two adjacent pixel is negative
                  // then there is a sign change
                  if (*it * *(it-1) < 0.0 && fabs(*ity) > threshold)
                      *itout= 0; // horizontal zero-crossing
                  else if (*it * *itup < 0.0 && fabs(*ity) > threshold)
                      *itout= 0; // vertical zero-crossing
              }

              return binary;
          }

};

#endif // LAPLACIANZC_H
