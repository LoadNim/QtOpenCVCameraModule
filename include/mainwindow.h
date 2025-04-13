#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPixmap>
#include <QLabel>
#include "frameflowhandler.h"

#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>

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

    // 중간 보고용 GUI 구성 (정식 버전 아님)
    QMenu* m_recoMenu;                      // 인식 방법 선택 메뉴
    QAction* m_face;                        // 안면 인식 설정용
    QAction* m_qr;                          // QR 인식 설정용

private slots:
    void callHandler();                     // 핸들러 함수 호출
};
#endif // MAINWINDOW_H
