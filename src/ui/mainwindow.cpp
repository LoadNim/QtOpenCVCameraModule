#include "mainwindow.h"
#include <qmenubar.h>

#define TARGET_FPS 30   // 실행 주기 설정용 (프레임 속도)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(1024, 600);

    // 프레임 처리 흐름 핸들러 설정
    m_frameFlowHandler = new FrameFlowHandler();

    // 프레임 출력 영역 설정
    m_mainInterface = new MainInterface();
    setCentralWidget(m_mainInterface);
}

MainWindow::~MainWindow() {
    delete m_frameFlowHandler;
}
