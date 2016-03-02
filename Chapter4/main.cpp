#include <QCoreApplication>
#include <iostream>
#include "histogram1d.h"
#include "colorhistogram.h"
#include "contentfinder.h"

using namespace std;
using namespace cv;


//int main()
//{
//   Mat image=imread("/home/jiaqi/Pictures/images/group.jpg",0);
//   histogram1d h;
//   Mat histo=h.getHistogram(image);

//   for(int i=0;i<256;++i){
//       cout<<"Value: "<<i<<"="<<histo.at<float>(i)<<endl;
//   }
//namedWindow("Histogram");
//imshow("Histogram",h.stretch(image,100));
//Mat result;
//result=h.stretch(image,100);
//namedWindow("Histogram2");
//imshow("Histogram2",h.getHistogramImage(result));
//namedWindow("Histogram3");
//imshow("Histogram3",h.equlize(image));
//namedWindow("Histogram4");
//imshow("Histogram4",h.getHistogramImage(h.equlize(image)));
//waitKey(0);



//Mat thresholded;
//threshold(image,thresholded,60,255,THRESH_BINARY);
//namedWindow("Thresholded");
//imshow("Thresholded",thresholded);

//waitKey(0);


//    Mat image=imread("/home/jiaqi/Pictures/images/group.jpg");
//    colorhistogram h;
//    Mat histo=h.getcolorhistogram(image);
//    for(int i=0;i<256;++i){
//           cout<<"Value: "<<i<<"="<<histo.at<float>(i)<<endl;
//       }
//    namedWindow("Histogram");
//    imshow("Histogram",h.getHistogramImage(image));

//return 0;

//}


int main(){
    ColorHistogram hc;
    Mat color=imread("/home/jiaqi/Pictures/images/waves.jpg");
    color=hc.colorReduce(color,32);
    Mat imageROI=color(Rect(0,0,165,75));
    namedWindow("original");
    imshow("original",imageROI);
    waitKey(0);
    Mat hist=hc.getabHistogram(imageROI);
    contentfinder finder;
    finder.setHistogram(hist);
    finder.setThreshold(0.05f);
    Mat result=finder.find(color);
namedWindow("Result");
imshow("Result",result);
waitKey(0);
return 0;
}
