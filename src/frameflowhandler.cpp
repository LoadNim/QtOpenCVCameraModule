#include "frameflowhandler.h"

FrameFlowHandler::FrameFlowHandler()
{
    m_camManager = new CamManager();
}

QImage FrameFlowHandler::flowHandling()
// 프레임 흐름을 처리하는 함수
// return: QImage 프레임 이미지
{
    m_frameImg = m_camManager->frameCapture();
    m_frameProcessor.convertColor(m_frameImg);
    return m_frameProcessor.matToQImage(m_frameImg);
}

FrameFlowHandler::~FrameFlowHandler()
{
    delete m_camManager;
}
