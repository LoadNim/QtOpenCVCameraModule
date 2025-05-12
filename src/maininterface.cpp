#include "maininterface.h"

MainInterface::MainInterface()
{
    // 전체 윈도우 크기
    setFixedSize(800, 480);

    // 웹캠 프레임 이미지 영역
    m_label = new QLabel(this);
    m_label->setMinimumSize(400, 480);
    m_label->setStyleSheet("background-color: black;");
    m_label->setAlignment(Qt::AlignCenter);

    // 플래그 초기화 및 키패드 생성
    m_inQRMode = false;
    makeKeypad();

    // 화면에 보일 영역 설정
    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);
    m_mainLayout->addWidget(m_keypad);
    m_mainLayout->addWidget(m_label);
    setLayout(m_mainLayout);

    // QR 인식 제한시간용 타이머 설정
    m_qrTimeoutTimer = new QTimer(this);
    m_qrTimeoutTimer->setSingleShot(true);
    connect(m_qrTimeoutTimer, &QTimer::timeout, this, &MainInterface::qrTimeout);
}

void MainInterface::displayImg(QImage frameImg)
// 이미지를 화면에 표시하는 함수
{
    QPixmap pixMap = QPixmap::fromImage(frameImg);
    m_label->setPixmap(pixMap.scaled(m_label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void MainInterface::makeKeypad()
// 키패드 영역을 생성하는 함수
{
    // 키패드 영역 생성
    m_keypad = new QWidget(this);
    m_keypad->setFixedWidth(300);

    QVBoxLayout* keypadLayout = new QVBoxLayout(m_keypad);
    keypadLayout->setContentsMargins(12, 12, 12, 12);
    keypadLayout->setSpacing(18);

    // 키패드 안내 문구
    m_keypadGuide = new QLabel(m_keypad);
    m_keypadGuide->setMinimumHeight(80);
    m_keypadGuide->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_keypadGuide->setAlignment(Qt::AlignCenter);
    m_keypadGuide->setWordWrap(true);
    m_keypadGuide->setStyleSheet(R"(
        font-size: 24px;
        font-weight: bold;
        padding: 8px;
        qproperty-alignment: AlignCenter;
    )");

    // 키패드 버튼
    QGridLayout* grid = new QGridLayout();
    QStringList labels = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "←", "0", "↵"};

    int idx = 0;
    for(int row = 0; row < 4; ++row){
        for(int col = 0; col < 3; ++col){
            QString label = labels[idx++];
            QPushButton* btn = new QPushButton(label, m_keypad);
            btn->setFixedSize(70, 60);
            btn->setProperty("Keyvalue", label);
            connect(btn, &QPushButton::clicked, this, &MainInterface::keypadBtnClicked);
            grid->addWidget(btn, row, col);

            if (label == "↵"){
                m_enterBtn = btn;
            }
            else if (label == "←"){
                m_backspBtn = btn;
            }
            else{
                m_numBtns.append(btn);
            }
        }
    }
    keypadLayout->addWidget(m_keypadGuide);
    keypadLayout->addLayout(grid);

    updateGuide();
    updateBtnState();
}

void MainInterface::keypadBtnClicked()
// 버튼 클릭에 대응하는 슬롯 함수
{
    QPushButton* senderBtn = qobject_cast<QPushButton*>(sender());
    if (!senderBtn) return;
    QString value = senderBtn->property("Keyvalue").toString();

    if (value == "←"){
        m_inputPhoneNum.chop(1);
    }
    else if (value == "↵"){
        if (!m_inputPhoneNum.isEmpty()){
            m_inQRMode = true;
            updateGuide();
            updateBtnState();
            m_qrTimeoutTimer->start(10000);
            emit phoneNumberSubmit(m_inputPhoneNum);
            return;
        }
    }
    else{
        if (m_inputPhoneNum.length() < 11){
            m_inputPhoneNum += value;
        }
    }

    updateGuide();
    updateBtnState();
}

void MainInterface::updateGuide()
// 안내 문구를 갱신하는 함수
{
    if (m_inQRMode)
    // 엔터 키를 눌렀을 때 (엔터 키 비활성화 상태)
    {
        m_keypadGuide->setText("QR 인식 중입니다...");
    }
    else if (m_inputPhoneNum.isEmpty()){
        m_keypadGuide->setText("전화번호를 입력하세요(QR 전용)");
    }
    else{
        m_keypadGuide->setText(m_inputPhoneNum);
    }
}

void MainInterface::updateBtnState()
// 키패드 버튼 상태 갱신 함수
// param: bool 엔터 키 입력 여부
{
    if(m_inQRMode) {
        m_enterBtn->setEnabled(false);
        m_backspBtn->setEnabled(false);
        for (QPushButton* b : m_numBtns){
            b->setEnabled(false);
        }
        return;
    }

    if (m_enterBtn){
        m_enterBtn->setEnabled(m_inputPhoneNum.length() == 11);
    }

    if (m_backspBtn){
        m_backspBtn->setEnabled(!m_inputPhoneNum.isEmpty());
    }

    bool allowMore = m_inputPhoneNum.length() < 11;
    for (QPushButton* b : m_numBtns){
        b->setEnabled(allowMore);
    }
}

void MainInterface::resetKeypad()
{
    m_inputPhoneNum.clear();
    m_inQRMode = false;
    updateGuide();
    updateBtnState();
    emit resetRecoMode();
}

void MainInterface::qrTimeout()
{
    resetKeypad();
}

MainInterface::~MainInterface(){}
