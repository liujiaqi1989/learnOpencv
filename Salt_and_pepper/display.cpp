#include "display.h"
#include "ui_display.h"
#include <QFileDialog>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QPixmap>
using namespace std;
using namespace cv;

display::display(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::display)
{
    ui->setupUi(this);
}

display::~display()
{
    delete ui;
}

void salt(Mat &image, int n){
    for (int k=0;k<n;k++){
        int i=rand()%image.cols;
        int j=rand()%image.rows;
        if (image.channels()==1){
            image.at<uchar>(j,i)=255;
        }else if (image.channels()==3){
            image.at<Vec3b>(j,i)[0]=255;
            image.at<Vec3b>(j,i)[1]=255;
            image.at<Vec3b>(j,i)[2]=255;
        }
    }
}

void colorReduce(Mat &image,int div=64){
    int rt=image.rows;
    int ct=image.cols*image.channels();
    for(int i=0;i<rt;++i){
        uchar * p=image.ptr(i);
        for(int j=0;j<ct;++j){
            p[j]=p[j]/div*div+div/2;
        }
    }

}

void display::on_pushButton_clicked()
{   QString fileName=QFileDialog::getOpenFileName(this,tr("Open Image"), ",", tr("Image Files (*.png *.jpg *.jpeg *.bmp )"));
    image=imread(fileName.toLatin1().data());
    Mat clone=image.clone();
    cvtColor(clone,clone,CV_BGR2RGB);
    QImage img=QImage((const unsigned char*)(clone.data),clone.cols,clone.rows,QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label->resize(ui->label->pixmap()->size());


}

void display::on_pushButton_2_clicked()
{   Mat clone=image.clone();
    flip(clone,clone,1);
    cvtColor(clone,clone,CV_BGR2RGB);
    QImage img=QImage((const unsigned char*)(clone.data),clone.cols,clone.rows,QImage::Format_RGB888);
    ui->label_2->setPixmap(QPixmap::fromImage(img));
    ui->label_2->resize(ui->label_2->pixmap()->size());
}

void display::on_pushButton_3_clicked()
{   Mat clone=image.clone();
    Mat result;
    QString fileName=QFileDialog::getOpenFileName(this,tr("Open Image"), ",", tr("Image Files (*.png *.jpg *.jpeg *.bmp )"));
    Mat image2=imread(fileName.toLatin1().data());
    //salt(clone,3000);
    //colorReduce(clone);
    addWeighted(clone,0.7,image2,0.9,0., result);
    cvtColor(result,result,CV_BGR2RGB);
    QImage img=QImage((const unsigned char*)(result.data),result.cols,result.rows,QImage::Format_RGB888);
    ui->label_3->setPixmap(QPixmap::fromImage(img));
    ui->label_3->resize(ui->label_3->pixmap()->size());
}
