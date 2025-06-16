#include "mainwindow.h"
#include <qmenubar.h>

#define TARGET_FPS 30   // 실행 주기 설정용 (프레임 속도)

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    resize(1024, 600);

    // 프레임 처리 흐름 핸들러 설정
    m_frameFlowHandler = new FrameFlowHandler();

    // 프레임 출력 영역 설정
    m_mainInterface = new MainInterface();
    setCentralWidget(m_mainInterface);

    // 데모용 ai 모듈 연계
    m_userverifier = new UserVerifier();

    // 타이머 생성
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [this]{
        m_mainInterface->setFrameImg(m_frameFlowHandler->flowHandling());
    });

    connect(m_mainInterface, &MainInterface::setEntryFaceMode, this, [this]{
        m_frameFlowHandler->setModes(SysMode::Entry, RecoMode::Face);
        startTimer();
    });

    connect(m_mainInterface, &MainInterface::setEntryQRMode, this, [this]{
        m_frameFlowHandler->setModes(SysMode::Entry, RecoMode::QR);
        startTimer();
    });

    connect(m_mainInterface, &MainInterface::setRegistMode, this, [this]{
        m_frameFlowHandler->setModes(SysMode::Regist, RecoMode::Face);
        startTimer();
    });

    connect(m_frameFlowHandler, &FrameFlowHandler::entryNext, this, [this]{
        statusBar()->showMessage("식별 진행중...");
        stopTimer();
        m_userverifier->entryResult();
    });

    connect(m_frameFlowHandler, &FrameFlowHandler::entryFail, this, [this]{
        statusBar()->showMessage("인식 실패...");
        m_mainInterface->initScreen();
        stopTimer();
    });

    connect(m_frameFlowHandler, &FrameFlowHandler::registNext, this, [this]{
        statusBar()->showMessage("등록 진행중...");
        m_userverifier->regist();
        stopTimer();
    });

    connect(m_frameFlowHandler, &FrameFlowHandler::registFail, this, [this]{
        statusBar()->showMessage("등록 실패...");
        m_mainInterface->initScreen();
        stopTimer();
    });

    connect(m_userverifier, &UserVerifier::doneSignal, this, [this](const QString& result){
        statusBar()->showMessage(result);
        m_mainInterface->initScreen();
    });
}

void MainWindow::startTimer()
// 타이머를 시작하는 함수
{
    if (!m_timer->isActive()){
        m_timer->start(1000 / TARGET_FPS);
    }
}

void MainWindow::stopTimer()
{
    if (m_timer->isActive()){
        m_timer->stop();
    }
}

MainWindow::~MainWindow(){
    delete m_frameFlowHandler;
}
