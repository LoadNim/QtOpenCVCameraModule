#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include <opencv2/opencv.hpp>
#include <QDebug>

enum class RecoMode{
    None = 0,
    Face = 1,
    QR = 2
};

class Recognizer
{
public:
    Recognizer();
    ~Recognizer();
    bool faceDetect(cv::Mat&);          // 안면을 검출하는 함수
    bool qrDetect(cv::Mat&);            // QR을 검출하는 함수

private:
    cv::CascadeClassifier m_faceModel;  // 얼굴 감지하는 모델
    cv::QRCodeDetector m_qrModel;       // QR 감지하는 모델
};

#endif // RECOGNIZER_H
