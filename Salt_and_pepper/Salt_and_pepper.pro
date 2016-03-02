#-------------------------------------------------
#
# Project created by QtCreator 2016-02-05T18:50:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Salt_and_pepper
TEMPLATE = app


SOURCES += main.cpp\
        display.cpp

HEADERS  += display.h

FORMS    += display.ui

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_calib3d -lopencv_contrib -lopencv_core\
 -lopencv_features2d -lopencv_flann -lopencv_gpu\
 -lopencv_highgui -lopencv_imgproc -lopencv_legacy\
 -lopencv_ml -lopencv_nonfree -lopencv_objdetect\
 -lopencv_ocl -lopencv_photo -lopencv_stitching\
 -lopencv_superres -lopencv_ts -lopencv_video\
 -lopencv_videostab
