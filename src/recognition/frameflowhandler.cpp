#include "frameflowhandler.h"

FrameFlowHandler::FrameFlowHandler()
{
    m_camManager = new CamManager();
    m_recognizer = new Recognizer();
    m_recoMode = RecoMode::Face;
    m_detected = false;
    m_firstDetectedTime = 0;
    m_lastDetectedTime = 0;
}

QImage FrameFlowHandler::flowHandling()
// 프레임 흐름을 처리하는 함수
// return: QImage 프레임 이미지
{
    m_frameImg = m_camManager->frameCapture();
    m_originFrameImg = m_frameImg.clone();

    bool detected = false;
    switch (m_recoMode) {
    case RecoMode::Face:
        detected = m_recognizer->faceDetect(m_frameImg);
        break;
    case RecoMode::QR:
        detected = m_recognizer->qrDetect(m_frameImg);
        break;
    default:
        // 검출 사용 안함
        break;
    }

    detectHandling(detected);
    m_frameProcessor.convertColor(m_frameImg);
    return m_frameProcessor.matToQImage(m_frameImg);
}

void FrameFlowHandler::setModes(SysMode sysMode, RecoMode recoMode)
// 시스템 모드, 검출 모듈 모드 설정용
// param: int 모드 값, int 모드 값
{
    m_sysMode = sysMode;
    m_recoMode = recoMode;
}

void FrameFlowHandler::detectHandling(bool detected)
// 검출 시간을 바탕으로 오탐을 판단하는 함수
// 500ms 이상 감지가 끊기면 오탐으로 판단
// 3000ms 이상 감지가 지속되면 이미지를 저장하는 함수를 호출
// param: bool 감지 여부
{
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    constexpr qint64 lostImgMs = 500;
    constexpr qint64 saveImgMs = 3000;

    if (detected)
    {
        if(!m_detected)
        // 처음 감지 되었을 때
        {
            m_detected = true;
            m_firstDetectedTime = now;
        }
        m_lastDetectedTime = now;
    }
    else if(m_detected && now - m_lastDetectedTime > lostImgMs)
    // 500ms 이상 감지가 끊겼을 때
    {
        m_detected = false;
        qDebug() << "감지가 끊겼습니다.";
    }

    if(m_detected && m_lastDetectedTime - m_firstDetectedTime >= saveImgMs)
    // 3000ms 이상 감지가 지속되었을 때
    {
        m_frameProcessor.saveImg(m_originFrameImg);
        m_detected = false;
    }
}

FrameFlowHandler::~FrameFlowHandler()
{
    delete m_camManager;
}
