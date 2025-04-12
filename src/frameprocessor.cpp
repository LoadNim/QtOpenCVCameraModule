#include "frameprocessor.h"

FrameProcessor::FrameProcessor() {}

void FrameProcessor::convertColor(cv::Mat& matImg)
// QImage 변환을 위해, cv::Mat 이미지 색공간을 RGB에서 BGR로 변환하는 함수
// param: cv::Mat 카메라 프레임 이미지
// 원본 cv::Mat을 직접 수정한다.
{
    cv::cvtColor(matImg, matImg, cv::COLOR_BGR2RGB);
}

QImage FrameProcessor::matToQImage(const cv::Mat& matImg)
// cv::Mat 이미지를 QImage로 변환하여 반환하는 함수
// param:  cv::Mat 카메라 프레임 이미지
// return: QImage 화면 출력용 이미지
{
    return QImage(matImg.data, matImg.cols, matImg.rows,
                  matImg.step, QImage::Format_RGB888);
}

FrameProcessor::~FrameProcessor() {}
