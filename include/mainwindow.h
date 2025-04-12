#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include "frameflowhandler.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void displayImg(QImage);                // 이미지를 화면에 표시하는 함수

private:
    QTimer* m_timer;                        // 프레임 반복 실행용 타이머
    QLabel* m_label;                        // 프레임이 출력되는 영역
    FrameFlowHandler* m_frameFlowHandler;   // 프레임 처리 흐름 핸들러

private slots:
    void callHandler();
};
#endif // MAINWINDOW_H
