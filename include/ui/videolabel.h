#ifndef VIDEOLABEL_H
#define VIDEOLABEL_H

#include <QLabel>
#include <QPixmap>

class VideoLabel : public QLabel
{
    Q_OBJECT

public:

    VideoLabel(QWidget* parent = nullptr);
    ~VideoLabel(){}
    void displayFrame(QImage frameImg);
};

#endif // VIDEOLABEL_H
