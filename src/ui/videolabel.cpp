#include "videolabel.h"

VideoLabel::VideoLabel(QWidget* parent) : QLabel(parent)
{
    setStyleSheet("background-color: black;");
    setAlignment(Qt::AlignCenter);
}

void VideoLabel::displayFrame(QImage frameImg)
// 이미지를 화면에 표시하는 함수
{
    QPixmap pixMap = QPixmap::fromImage(frameImg);
    setPixmap(pixMap.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}
