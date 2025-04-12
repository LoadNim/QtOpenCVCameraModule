#ifndef FRAMEFLOWHANDLER_H
#define FRAMEFLOWHANDLER_H

#include "cammanager.h"
#include "frameprocessor.h"

class FrameFlowHandler
{
public:
    FrameFlowHandler();
    ~FrameFlowHandler();
    QImage flowHandling();              // 프레임 흐름을 처리하는 함수

private:
    cv::Mat m_frameImg;                 // 카메라 프레임 이미지
    CamManager* m_camManager;           // 카메라 관리 객체
    FrameProcessor m_frameProcessor;    // 프레임 이미지 처리 객체
};

#endif // FRAMEFLOWHANDLER_H
