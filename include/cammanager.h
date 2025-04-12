#ifndef CAMMANAGER_H
#define CAMMANAGER_H

#include <opencv2/opencv.hpp>
#include <QDebug>

class CamManager
{
public:
    CamManager();
    ~CamManager();
    cv::Mat frameCapture();     // 현재 프레임을 캡쳐해서 반환하는 함수

private:
    cv::VideoCapture m_cam;     // OpenCV 카메라 객체
};

#endif // CAMMANAGER_H
