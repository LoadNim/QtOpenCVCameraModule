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
    switch(m_sysMode){
    case SysMode::Entry:
        if(m_recoMode == RecoMode::Face){
            detected = m_recognizer->faceDetect(m_frameImg);
        }
        else{
            detected = m_recognizer->qrDetect(m_frameImg);
        }
        handleAccessDetection(detected);
        break;

    default:
        detected = m_recognizer->faceDetect(m_frameImg);
        handleRegistrationDetection(detected);
        break;
    }

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

bool FrameFlowHandler::updateDetectionState(bool detected, qint64 now)
// 탐지 여부를 갱신하며, 오탐 여부에 따라 공통으로 수행하는 동작을 실행하는 함수
// param: bool 감지 여부, qint64: 현재 시간
// return: bool 탐지 여부
{
    constexpr qint64 lostImgMs = 500;

    if (detected) {
        if (!m_detected) {
            m_detected = true;
            m_firstDetectedTime = now;
        }
        m_lastDetectedTime = now;
    }
    else if (isLostDetection(now, lostImgMs)) {
        m_detected = false;
        m_registrationBuffer.clear();  // 등록 단계 실패 대비
        qDebug() << "감지가 끊겼습니다. 버퍼 초기화됨.";
        if(m_sysMode == SysMode::Entry){
            emit entryFail();
        }
        else{
            emit registFail();
        }
    }

    return m_detected;
}

bool FrameFlowHandler::isValidDetection(qint64 thresholdMs) const
// 지속 시간을 기준값과 비교해 참 여부를 반환하는 함수
// param: qint64 지속시간
// return: bool 지속시간 충족 여부
{
    return m_detected && (m_lastDetectedTime - m_firstDetectedTime >= thresholdMs);
}

bool FrameFlowHandler::isLostDetection(qint64 now, qint64 lostMs) const
// 감지가 끊긴 시간을 기준값과 비교해 참 여부를 반환하는 함수
// param: qint64 지속시간
// return: bool 감지 끊긴 시간 충족 여부
{
    return m_detected && (now - m_lastDetectedTime > lostMs);
}

void FrameFlowHandler::handleAccessDetection(bool detected)
// 출입을 목적으로 하는 사용자의 탐지 여부를 핸들링 하며, 이미지를 저장하는 함수
// param: bool 감지 여부
{
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    constexpr qint64 saveImgMs = 3000;

    updateDetectionState(detected, now);  // 상태 갱신만, 반환값은 불필요

    if (isValidDetection(saveImgMs)) {
        m_frameProcessor.saveImg(m_originFrameImg);
        m_detected = false;
        emit entryNext();
    }
}

void FrameFlowHandler::handleRegistrationDetection(bool detected)
// 등록을 목적으로 하는 사용자의 탐지 여부를 핸들링 하며, 이미지 컨테이너를 반환하는 함수
// param: bool 감지 여부
// return: QVector<cv::Mat> 탐지 이미지 컨테이너 (90장)
{
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    constexpr qint64 saveImgMs = 3000;

    bool active = updateDetectionState(detected, now);

    if (active)
        m_registrationBuffer.append(m_originFrameImg.clone());
    if (isValidDetection(saveImgMs)) {
        saveRegistImg();
        m_registrationBuffer.clear();
        m_detected = false;
        emit registNext();
    }
}

void FrameFlowHandler::saveRegistImg()
{
    QString folderName = QString("LastRegistImg");
    QString savePath = QDir().filePath(folderName);
    QDir dir(savePath);

    if (dir.exists()) {
        QStringList files = dir.entryList(QDir::Files);
        for (const QString& file : files) {
            dir.remove(file);  // 파일 삭제
        }
    } else {
        QDir().mkpath(savePath);  // 폴더가 없으면 생성
    }

    for(int i = 0; i < m_registrationBuffer.size(); ++i){
        QString fileName = QString("img_%1.jpg").arg(i, 3, 10, QLatin1Char('0'));
        QString fullPath = dir.filePath(fileName);
        m_frameProcessor.saveImg(m_registrationBuffer[i], fullPath);
    }
}

FrameFlowHandler::~FrameFlowHandler()
{
    delete m_camManager;
}
