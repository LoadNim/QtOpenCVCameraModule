#include "regist.h"

Regist::Regist(QStackedWidget* parent) : QStackedWidget(parent)
{
    m_registHomeName = new RegistHomeName(this);
    m_registPhone = new RegistPhone(this);

    addWidget(m_registHomeName);
    addWidget(m_registPhone);
    setCurrentWidget(m_registHomeName);

    connect(m_registHomeName, &RegistHomeName::nextBtnSignal, this, [this]{
        setCurrentWidget(m_registPhone);
    });

    connect(m_registHomeName, &RegistHomeName::prevBtnSignal, this, [this]{
        clearData();
        emit prevBtnSignal();
    });

    connect(m_registPhone, &RegistPhone::nextBtnSignal, this, [this]{
        QVector<QString> data = m_registHomeName->getData();
        data.push_back(m_registPhone->getData());
        clearData();
        emit nextBtnSignal(data);
    });

    connect(m_registPhone, &RegistPhone::prevBtnSignal, this, [this]{
        setCurrentWidget(m_registHomeName);
    });
}

void Regist::clearData()
{
    m_registHomeName->clearData();
    m_registPhone->clearData();
}

void Regist::initScreen()
{
    setCurrentWidget(m_registHomeName);
}

RegistHomeName::RegistHomeName(QWidget* parent) : QWidget(parent)
{
    // 상위 레이아웃
    m_registHomeNameLayout = new QVBoxLayout(this);

    // 개별 항목 레이아웃
    m_registUnitLayout = new QHBoxLayout();
    m_registNumberLayout = new QHBoxLayout();
    m_registNameLayout = new QHBoxLayout();
    m_registBtnLayout = new QHBoxLayout();

    // 라벨
    m_guideUnit = new QLabel("동", this);
    m_guideNumber = new QLabel("호수", this);
    m_guideName = new QLabel("이름", this);

    m_guideUnit->setFixedWidth(100);
    m_guideNumber->setFixedWidth(100);
    m_guideName->setFixedWidth(100);

    // 입력창
    m_inputUnit = new QLineEdit(this);
    m_inputNumber = new QLineEdit(this);
    m_inputName = new QLineEdit(this);

    m_inputUnit->setMinimumHeight(60);
    m_inputNumber->setMinimumHeight(60);
    m_inputName->setMinimumHeight(60);

    // 버튼
    m_nextBtn = new QPushButton("다음", this);
    m_prevBtn = new QPushButton("이전", this);
    m_nextBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_prevBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // 항목 배치
    m_registUnitLayout->addWidget(m_guideUnit);
    m_registUnitLayout->addWidget(m_inputUnit);

    m_registNumberLayout->addWidget(m_guideNumber);
    m_registNumberLayout->addWidget(m_inputNumber);

    m_registNameLayout->addWidget(m_guideName);
    m_registNameLayout->addWidget(m_inputName);

    m_registBtnLayout->addWidget(m_nextBtn);
    m_registBtnLayout->addWidget(m_prevBtn);

    // 최종 레이아웃 배치
    m_registHomeNameLayout->addLayout(m_registUnitLayout);
    m_registHomeNameLayout->addSpacing(20);
    m_registHomeNameLayout->addLayout(m_registNumberLayout);
    m_registHomeNameLayout->addSpacing(20);
    m_registHomeNameLayout->addLayout(m_registNameLayout);
    m_registHomeNameLayout->addSpacing(20);
    m_registHomeNameLayout->addLayout(m_registBtnLayout);
    m_registHomeNameLayout->addStretch();

    setLayout(m_registHomeNameLayout);

    // 시그널 연결
    connect(m_nextBtn, &QPushButton::clicked, this, &RegistHomeName::nextBtnSignal);
    connect(m_prevBtn, &QPushButton::clicked, this, &RegistHomeName::prevBtnSignal);
}



QVector<QString> RegistHomeName::getData()
{
    QVector<QString> inputData;
    inputData.push_back(m_inputUnit->text());
    inputData.push_back(m_inputNumber->text());
    inputData.push_back(m_inputName->text());
    return inputData;
}

void RegistHomeName::clearData()
{
    m_inputUnit->clear();
    m_inputNumber->clear();
    m_inputName->clear();
}

RegistPhone::RegistPhone(QWidget* parent) : QWidget(parent)
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

    // 오른쪽 수직 레이아웃: 전화번호 안내, 입력, 버튼
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
    connect(m_nextBtn, &QPushButton::clicked, this, &RegistPhone::nextBtnSignal);
    connect(m_prevBtn, &QPushButton::clicked, this, &RegistPhone::prevBtnSignal);

    connect(m_keypad, &Keypad::changeInputDataSignal, this, [this] {
        m_inputPhoneNumber->setText(m_keypad->getNumber());
    });

    connect(m_keypad, &Keypad::selectEnterBtnSignal, this, [this] {
        m_nextBtn->setEnabled(true);
    });
}


QString RegistPhone::getData()
{
    return m_inputPhoneNumber->text();
}

void RegistPhone::clearData()
{
    m_inputPhoneNumber->clear();
    m_keypad->initKeypad();
}
