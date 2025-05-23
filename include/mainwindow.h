#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "frameflowhandler.h"
#include "maininterface.h"

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

private:
    QTimer* m_timer;                        // 프레임 반복 실행용 타이머
    FrameFlowHandler* m_frameFlowHandler;   // 프레임 처리 흐름 핸들러
    MainInterface* m_mainInterface;         // 인터페이스를 관리하는 포인터

private slots:
    void callHandler();                     // 핸들러 함수 호출
};
#endif // MAINWINDOW_H
