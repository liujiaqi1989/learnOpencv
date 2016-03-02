#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "linefinder.h"


#define PI 3.1415926

using namespace cv;
using namespace std;

int main()
{

        cv::Mat image= cv::imread("/home/jiaqi/Pictures/images/road.jpg",0);
        if (!image.data)
            return 0;

        // Display the image
        cv::namedWindow("Original Image");
        cv::imshow("Original Image",image);



        // Apply Canny algorithm
        cv::Mat contours;
        cv::Canny(image,contours,125,350);
        cv::Mat contoursInv;
        cv::threshold(contours,contoursInv,128,255,cv::THRESH_BINARY_INV);

        // Display the image of contours
        cv::namedWindow("Canny Contours");
        cv::imshow("Canny Contours",contoursInv);

        // Create a test image
        cv::Mat test(200,200,CV_8U,cv::Scalar(0));
        cv::line(test,cv::Point(100,0),cv::Point(200,200),cv::Scalar(255));
        cv::line(test,cv::Point(0,50),cv::Point(200,200),cv::Scalar(255));
        cv::line(test,cv::Point(0,200),cv::Point(200,0),cv::Scalar(255));
        cv::line(test,cv::Point(200,0),cv::Point(0,200),cv::Scalar(255));
        cv::line(test,cv::Point(100,0),cv::Point(100,200),cv::Scalar(255));
        cv::line(test,cv::Point(0,100),cv::Point(200,100),cv::Scalar(255));

        // Display the test image
        cv::namedWindow("Test Image");
        cv::imshow("Test Image",test);
        cv::imwrite("test.bmp",test);

        // Hough tranform for line detection
        std::vector<cv::Vec2f> lines;
        cv::HoughLines(contours,lines,1,PI/180,60);

        // Draw the lines
        cv::Mat result(contours.rows,contours.cols,CV_8U,cv::Scalar(255));
        image.copyTo(result);

        std::cout << "Lines detected: " << lines.size() << std::endl;

        std::vector<cv::Vec2f>::const_iterator it= lines.begin();
        while (it!=lines.end()) {

            float rho= (*it)[0];   // first element is distance rho
            float theta= (*it)[1]; // second element is angle theta

            if (theta < PI/4. || theta > 3.*PI/4.) { // ~vertical line

                // point of intersection of the line with first row
                cv::Point pt1(rho/cos(theta),0);
                // point of intersection of the line with last row
                cv::Point pt2((rho-result.rows*sin(theta))/cos(theta),result.rows);
                // draw a white line
                cv::line( result, pt1, pt2, cv::Scalar(255), 1);

            } else { // ~horizontal line

                // point of intersection of the line with first column
                cv::Point pt1(0,rho/sin(theta));
                // point of intersection of the line with last column
                cv::Point pt2(result.cols,(rho-result.cols*cos(theta))/sin(theta));
                // draw a white line
                cv::line( result, pt1, pt2, cv::Scalar(255), 1);
            }

            std::cout << "line: (" << rho << "," << theta << ")\n";

            ++it;
        }

        // Display the detected line image
        cv::namedWindow("Detected Lines with Hough");
        cv::imshow("Detected Lines with Hough",result);

        // Create LineFinder instance
        LineFinder ld;

        // Set probabilistic Hough parameters
        ld.setLineLengthAndGap(100,20);
        ld.setMinVote(80);

        // Detect lines
        std::vector<cv::Vec4i> li= ld.findLines(contours);
        ld.drawDetectedLines(image);
        cv::namedWindow("Detected Lines with HoughP");
        cv::imshow("Detected Lines with HoughP",image);

        //Detect circles
        image=imread("/home/jiaqi/Pictures/images/chariot.jpg",0);
        cv::GaussianBlur(image,image,cv::Size(5,5),1.5);
            std::vector<cv::Vec3f> circles;
            cv::HoughCircles(image, circles, CV_HOUGH_GRADIENT,
                2,   // accumulator resolution (size of the image / 2)
                50,  // minimum distance between two circles
                200, // Canny high threshold
                100, // minimum number of votes
                25, 100); // min and max radius

            std::cout << "Circles: " << circles.size() << std::endl;

            // Draw the circles

            std::vector<cv::Vec3f>::const_iterator itc= circles.begin();

            while (itc!=circles.end()) {

              cv::circle(image,
                  cv::Point((*itc)[0], (*itc)[1]), // circle centre
                  (*itc)[2], // circle radius
                  cv::Scalar(255), // color
                  2); // thickness

              ++itc;
            }

            cv::namedWindow("Detected Circles");
            cv::imshow("Detected Circles",image);




        cv::waitKey(0);



    return 0;
}
