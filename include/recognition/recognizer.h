#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include <opencv2/opencv.hpp>
#include <QDebug>

enum class SysMode{
    Regist = 0,
    Entry = 1
};

enum class RecoMode{
    Face = 0,
    QR = 1
};

class Recognizer
{
public:
    Recognizer();
    ~Recognizer();
    bool faceDetect(cv::Mat&);          // 안면을 검출하는 함수
    bool qrDetect(cv::Mat&);            // QR을 검출하는 함수
    QString getDecodedQR();             // 디코딩 된 QR 문자열 값을 반환하는 함수

private:
    cv::CascadeClassifier m_faceModel;  // 얼굴 감지하는 모델
    cv::QRCodeDetector m_qrModel;       // QR 감지하는 모델
    std::string m_decodedQR;            // 디코딩 된 QR 문자열 값
};

#endif // RECOGNIZER_H
