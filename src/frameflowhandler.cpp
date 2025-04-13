#include "frameflowhandler.h"

FrameFlowHandler::FrameFlowHandler()
{
    m_camManager = new CamManager();
    m_recognizer = new Recognizer();
    m_recoMenu = RecoMode::None;
}

QImage FrameFlowHandler::flowHandling()
// 프레임 흐름을 처리하는 함수
// return: QImage 프레임 이미지
{
    m_frameImg = m_camManager->frameCapture();

    switch (m_recoMenu) {
    case RecoMode::Face:
        m_recognizer->faceDetect(m_frameImg);
        break;
    case RecoMode::QR:
        m_recognizer->qrDetect(m_frameImg);
        break;
    default:
        // 검출 사용 안함
        break;
    }

    m_frameProcessor.convertColor(m_frameImg);
    return m_frameProcessor.matToQImage(m_frameImg);
}

void FrameFlowHandler::setRecoMenu(RecoMode mode)
// 검출 모듈 모드 설정용 함수
// param: int 모드 값
{
    m_recoMenu = mode;
}

FrameFlowHandler::~FrameFlowHandler()
{
    delete m_camManager;
}
