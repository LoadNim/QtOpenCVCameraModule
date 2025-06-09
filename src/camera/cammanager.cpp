#include "cammanager.h"

CamManager::CamManager()
{
    // 카메라 연동
    m_cam.open(0);
    if(!m_cam.isOpened())
    {
        qDebug() << "카메라가 연동되지 않았습니다.";
        return;
    }

    // 카메라 해상도 설정
    m_cam.set(cv::CAP_PROP_FRAME_WIDTH, 1920);
    m_cam.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);
}

cv::Mat CamManager::frameCapture()
// cv::VideoCapture 객체로부터
// cv::Mat 형식의 프레임을 캡쳐하여 반환한다.
{
    cv::Mat temp;
    m_cam >> temp;
    return temp;
}

CamManager::~CamManager()
{
    if(m_cam.isOpened())
        m_cam.release();
}
