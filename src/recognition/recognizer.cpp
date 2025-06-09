#include "recognizer.h"

Recognizer::Recognizer()
{
    // 안면 인식 모델 로드
    if(!m_faceModel.load("C:/opencv/build/etc/haarcascades/haarcascade_frontalface_default.xml"))
    {
        qDebug() << "Haarcascade 경로 오류";
        return;
    }
}

bool Recognizer::faceDetect(cv::Mat& frame)
// 안면 영역 검출 후, 초록색 사각형으로 표시
// param: cv::Mat 프레임 이미지
// return: bool 검출 여부
{
    cv::Mat gray;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);      // 그레이 스케일 변환
    cv::equalizeHist(gray, gray);                       // 대비 향상 목적 히스토그램 평탄화

    std::vector<cv::Rect> faces;                        // 검출된 안면 영역 좌표
    m_faceModel.detectMultiScale                        // 안면 검출
        (gray, faces, 1.05, 2, 0, cv::Size(100, 100));

    for (const auto& rect : faces) {                    // 검출된 영역에 사각형 표시
        cv::rectangle(frame, rect, cv::Scalar(0, 255, 0), 2);
    }

    return !faces.empty();
}

bool Recognizer::qrDetect(cv::Mat& frame)
// QR 검출 후, 파란색 사각형으로 테두리를 표시
// param: cv::Mat 프레임 이미지
// return: bool 검출 여부
{
    std::vector<cv::Point> qrPoints;                    // 검출된 QR의 꼭짓점 좌표
    m_decodedQR =                                       // QR 검출 및 디코딩
        m_qrModel.detectAndDecode(frame, qrPoints);

    if (qrPoints.empty()){
        m_decodedQR.clear();
    }

    bool detect = !qrPoints.empty();
    if (detect) {                                       // 검출 영역에 사각형 표시
        std::vector<std::vector<cv::Point>> contours{qrPoints};
        cv::polylines(frame, contours, true, cv::Scalar(255, 0, 0), 2);
    }

    return detect;
}

QString Recognizer::getDecodedQR()
// 디코딩 된 QR 문자열 값을 반환하는 함수
// return: QString 디코딩 된 QR 문자열
{
    return QString::fromStdString(m_decodedQR);
}

Recognizer::~Recognizer(){}
