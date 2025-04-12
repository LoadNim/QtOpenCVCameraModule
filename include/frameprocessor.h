#ifndef FRAMEPROCESSOR_H
#define FRAMEPROCESSOR_H

#include <opencv2/opencv.hpp>
#include <QImage>

class FrameProcessor
{
public:
    FrameProcessor();
    ~FrameProcessor();
    void convertColor(cv::Mat&);            // 색공간을 변환하는 함수
    QImage matToQImage(const cv::Mat&);     // cv::Mat 이미지를 QImage 변환해서 반환하는 함수
};

#endif // FRAMEPROCESSOR_H
