#include "mainwindow.h"

#define TARGET_FPS 30   // 실행 주기 설정용 (프레임 속도)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 프로그램 윈도우 설정
    setWindowTitle("QtOpenCVCamerModule");
    resize(1280, 720);

    // 프레임 처리 흐름 핸들러 설정
    m_frameFlowHandler = new FrameFlowHandler();

    // 프레임 출력 영역 설정
    m_label = new QLabel(this);
    setCentralWidget(m_label);

    // 타이머 및 슬롯 함수 설정
    m_timer = new QTimer(this);
    m_timer->start(1000 / TARGET_FPS);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::callHandler);
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
