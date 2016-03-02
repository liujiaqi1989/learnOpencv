#ifndef DISPLAY_H
#define DISPLAY_H

#include <QMainWindow>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


namespace Ui {
class display;
}

class display : public QMainWindow
{
    Q_OBJECT

public:
    explicit display(QWidget *parent = 0);
    ~display();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::display *ui;
    cv::Mat image;
};

#endif // DISPLAY_H
