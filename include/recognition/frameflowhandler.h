#ifndef FRAMEFLOWHANDLER_H
#define FRAMEFLOWHANDLER_H

#include "cammanager.h"
#include "frameprocessor.h"
#include "recognizer.h"
#include <QDir>

class FrameFlowHandler : public QObject
{
    Q_OBJECT

public:
    FrameFlowHandler();
    ~FrameFlowHandler();
    QImage flowHandling();                          // 프레임 흐름을 처리하는 함수
    void setModes(SysMode, RecoMode);               // 검출 모듈 모드 설정용 함수
    bool updateDetectionState(bool, qint64);
    bool isValidDetection(qint64) const;
    bool isLostDetection(qint64, qint64) const;
    void handleAccessDetection(bool detected);
    void handleRegistrationDetection(bool detected);
    void saveRegistImg();

signals:
    void entryNext();
    void entryFail();
    void registNext();
    void registFail();

private:
    cv::Mat m_frameImg;                             // 카메라 프레임 이미지
    cv::Mat m_originFrameImg;                       // 카메라 프레임 이미지 원본
    CamManager* m_camManager;                       // 카메라 관리 객체
    Recognizer* m_recognizer;                       // 검출 모듈 객체
    FrameProcessor m_frameProcessor;                // 프레임 이미지 처리 객체
    SysMode m_sysMode;                              // 시스템 모드 설정용
    RecoMode m_recoMode;                            // 검출 모듈 모드 설정용
    bool m_detected;                                // 객체가 감지가 되었는지 안되었는지 여부
    qint64 m_firstDetectedTime;                     // 객체가 처음 감지된 시간
    qint64 m_lastDetectedTime;                      // 객체가 마지막으로 감지된 시간
    QVector<cv::Mat> m_registrationBuffer;
};

#endif // FRAMEFLOWHANDLER_H
