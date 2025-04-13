#include "mainwindow.h"
#include <qmenubar.h>

#define TARGET_FPS 30   // 실행 주기 설정용 (프레임 속도)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 프로그램 윈도우 설정
    setWindowTitle("QtOpenCVCamerModule");
    resize(1280, 720);

    // 인식 메뉴 구성
    m_recoMenu = menuBar()->addMenu("인식 설정");
    m_face = new QAction("안면 인식", this);
    m_qr = new QAction("QR 인식", this);
    m_recoMenu->addAction(m_face);
    m_recoMenu->addAction(m_qr);

    // 상태줄 구성
    statusBar()->showMessage("카메라 작동중...");

    // 프레임 처리 흐름 핸들러 설정
    m_frameFlowHandler = new FrameFlowHandler();

    // 프레임 출력 영역 설정
    m_label = new QLabel(this);
    setCentralWidget(m_label);

    // 타이머 설정
    m_timer = new QTimer(this);
    m_timer->start(1000 / TARGET_FPS);

    // 슬롯 함수 설정
    connect(m_timer, &QTimer::timeout, this, &MainWindow::callHandler);
    connect(m_face, &QAction::triggered, this, [=](){
        m_frameFlowHandler->setRecoMenu(RecoMode::Face);
        statusBar()->showMessage("안면 인식 작동중...");
    });
    connect(m_qr, &QAction::triggered, this, [=](){
        m_frameFlowHandler->setRecoMenu(RecoMode::QR);
        statusBar()->showMessage("QR 인식 작동중...");
    });
}

void MainWindow::callHandler()
// 프레임 하나에 대한 처리 흐름 실행
{
    displayImg(m_frameFlowHandler->flowHandling());
}

void MainWindow::displayImg(QImage frameImg)
// 이미지를 화면에 표시하는 함수
{
    QPixmap pixMap = QPixmap::fromImage(frameImg);
    m_label->setPixmap(pixMap);
}

MainWindow::~MainWindow() {
    delete m_frameFlowHandler;
}
