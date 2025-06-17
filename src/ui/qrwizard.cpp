#include "qrwizard.h"

QRWizard::QRWizard(QStackedWidget* parent) : QStackedWidget(parent)
{
    m_qrHomePurpose = new QRHomePurpose(this);
    m_qrPhone = new QRPhone(this);

    addWidget(m_qrHomePurpose);
    addWidget(m_qrPhone);
    setCurrentWidget(m_qrHomePurpose);

    connect(m_qrHomePurpose, &QRHomePurpose::nextBtnSignal, this, [this]{
        setCurrentWidget(m_qrPhone);
    });

    connect(m_qrHomePurpose, &QRHomePurpose::prevBtnSignal, this, [this]{
        clearData();
        emit prevBtnSignal();
    });

    connect(m_qrPhone, &QRPhone::nextBtnSignal, this, [this]{
        QVector<QString> data = m_qrHomePurpose->getData();
        data.push_back(m_qrPhone->getData());
        clearData();
        emit nextBtnSignal(data);
    });

    connect(m_qrPhone, &QRPhone::prevBtnSignal, this, [this]{
        setCurrentWidget(m_qrHomePurpose);
    });
}

void QRWizard::clearData()
{
    m_qrHomePurpose->clearData();
    m_qrPhone->clearData();
}

void QRWizard::initScreen()
{
    setCurrentWidget(m_qrHomePurpose);

}

QRHomePurpose::QRHomePurpose(QWidget* parent) : QWidget(parent)
{
    // 상위 레이아웃
    m_qrHomePurposeLayout = new QVBoxLayout(this);

    // 개별 항목 레이아웃
    m_qrHomePurposeUnitLayout = new QHBoxLayout();
    m_qrHomePurposeNumberLayout = new QHBoxLayout();
    m_qrHomePurposePurposeLayout = new QHBoxLayout();
    m_qrHomePurposeBtnLayout = new QHBoxLayout();

    // 라벨
    m_guideUnit = new QLabel("동", this);
    m_guideNumber = new QLabel("호수", this);
    m_guidePurpose = new QLabel("방문목적", this);

    m_guideUnit->setFixedWidth(100);
    m_guideNumber->setFixedWidth(100);
    m_guidePurpose->setFixedWidth(100);

    // 입력창
    m_inputUnit = new QLineEdit(this);
    m_inputNumber = new QLineEdit(this);
    m_inputPurpose = new QLineEdit(this);

    // ✅ 입력창 크기 키우기
    m_inputUnit->setMinimumHeight(60);
    m_inputNumber->setMinimumHeight(60);
    m_inputPurpose->setMinimumHeight(60);

    // 버튼
    m_nextBtn = new QPushButton("다음", this);
    m_prevBtn = new QPushButton("이전", this);
    // → 버튼은 크기 조정 안 함 (기본값 유지)

    // 각 항목 정렬
    m_qrHomePurposeUnitLayout->addWidget(m_guideUnit);
    m_qrHomePurposeUnitLayout->addWidget(m_inputUnit);

    m_qrHomePurposeNumberLayout->addWidget(m_guideNumber);
    m_qrHomePurposeNumberLayout->addWidget(m_inputNumber);

    m_qrHomePurposePurposeLayout->addWidget(m_guidePurpose);
    m_qrHomePurposePurposeLayout->addWidget(m_inputPurpose);

    m_qrHomePurposeBtnLayout->addWidget(m_nextBtn);
    m_qrHomePurposeBtnLayout->addWidget(m_prevBtn);

    // 최종 배치
    m_qrHomePurposeLayout->addLayout(m_qrHomePurposeUnitLayout);
    m_qrHomePurposeLayout->addSpacing(20);
    m_qrHomePurposeLayout->addLayout(m_qrHomePurposeNumberLayout);
    m_qrHomePurposeLayout->addSpacing(20);
    m_qrHomePurposeLayout->addLayout(m_qrHomePurposePurposeLayout);

    // ✅ 버튼을 방문목적 아래로 이동
    m_qrHomePurposeLayout->addSpacing(20);
    m_qrHomePurposeLayout->addLayout(m_qrHomePurposeBtnLayout);

    // 중간 공간을 아래로 밀기
    m_qrHomePurposeLayout->addStretch();

    setLayout(m_qrHomePurposeLayout);

    // 시그널 연결
    connect(m_nextBtn, &QPushButton::clicked, this, &QRHomePurpose::nextBtnSignal);
    connect(m_prevBtn, &QPushButton::clicked, this, &QRHomePurpose::prevBtnSignal);
}
QVector<QString> QRHomePurpose::getData()
{
    QVector<QString> inputData;
    inputData.push_back(m_inputUnit->text());
    inputData.push_back(m_inputNumber->text());
    inputData.push_back(m_inputPurpose->text());
    return inputData;
}

void QRHomePurpose::clearData()
{
    m_inputUnit->clear();
    m_inputNumber->clear();
    m_inputPurpose->clear();
}

QRPhone::QRPhone(QWidget* parent) : QWidget(parent)
{
    // 좌우 레이아웃 (전체)
    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    // 왼쪽 키패드
    m_keypad = new Keypad(this);

    // 전화번호 라벨
    m_guidePhoneNumber = new QLabel("전화번호", this);
    m_guidePhoneNumber->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_guidePhoneNumber->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // 전화번호 출력
    m_inputPhoneNumber = new QLabel(this);
    m_inputPhoneNumber->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_inputPhoneNumber->setStyleSheet("font-size: 22pt;");
    m_inputPhoneNumber->setMinimumHeight(50);
    m_inputPhoneNumber->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // 버튼
    m_nextBtn = new QPushButton("다음", this);
    m_prevBtn = new QPushButton("이전", this);
    m_nextBtn->setEnabled(false);
    m_nextBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_prevBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // 버튼 수평 배치
    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(10);
    btnLayout->addWidget(m_nextBtn);
    btnLayout->addWidget(m_prevBtn);

    // 오른쪽 수직 레이아웃: 전화번호 + 출력 + 버튼
    QVBoxLayout* numberDisplayLayout = new QVBoxLayout();
    numberDisplayLayout->setAlignment(Qt::AlignTop);
    numberDisplayLayout->addWidget(m_guidePhoneNumber);
    numberDisplayLayout->addWidget(m_inputPhoneNumber);
    numberDisplayLayout->addSpacing(30);  // 출력과 버튼 사이 간격
    numberDisplayLayout->addLayout(btnLayout);
    numberDisplayLayout->addStretch();    // 아래 공간 밀어냄

    // 전체 좌우 배치
    mainLayout->addWidget(m_keypad);
    mainLayout->addLayout(numberDisplayLayout);
    setLayout(mainLayout);

    // 시그널 연결
    connect(m_nextBtn, &QPushButton::clicked, this, &QRPhone::nextBtnSignal);
    connect(m_prevBtn, &QPushButton::clicked, this, &QRPhone::prevBtnSignal);

    connect(m_keypad, &Keypad::changeInputDataSignal, this, [this] {
        m_inputPhoneNumber->setText(m_keypad->getNumber());
    });

    connect(m_keypad, &Keypad::selectEnterBtnSignal, this, [this] {
        m_nextBtn->setEnabled(true);
    });
}




QString QRPhone::getData()
{
    return m_inputPhoneNumber->text();
}

void QRPhone::clearData()
{
    m_inputPhoneNumber->clear();
    m_keypad->initKeypad();
}
