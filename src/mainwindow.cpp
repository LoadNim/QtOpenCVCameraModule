#include "mainwindow.h"
#include <qmenubar.h>

#define TARGET_FPS 30   // 실행 주기 설정용 (프레임 속도)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 프레임 처리 흐름 핸들러 설정
    m_frameFlowHandler = new FrameFlowHandler();

    // 프레임 출력 영역 설정
    m_mainInterface = new MainInterface();
    setCentralWidget(m_mainInterface);

    // 타이머 설정
    m_timer = new QTimer(this);
    m_timer->start(1000 / TARGET_FPS);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::callHandler);

    // 번호 입력 대응
    connect(m_mainInterface, &MainInterface::phoneNumberSubmit, this, [=](const QString& number) {
        m_frameFlowHandler->setRecoMenu(RecoMode::QR);     // QR 모드 전환
    });

    // 인식 모드 리셋 대응
    connect(m_mainInterface, &MainInterface::resetRecoMode, this, [=](){
        m_frameFlowHandler->setRecoMenu(RecoMode::Face);
    });
}

void MainWindow::callHandler()
// 프레임 하나에 대한 처리 흐름 실행
{
    m_mainInterface->displayImg(m_frameFlowHandler->flowHandling());
}

MainWindow::~MainWindow() {
    delete m_frameFlowHandler;
}
