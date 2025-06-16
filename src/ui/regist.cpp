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
    m_registHomeNameLayout = new QVBoxLayout(this);
    m_registUnitLayout = new QHBoxLayout(this);
    m_registNumberLayout = new QHBoxLayout(this);
    m_registNameLayout = new QHBoxLayout(this);
    m_registBtnLayout = new QHBoxLayout(this);

    m_guideUnit = new QLabel("동: ", this);
    m_guideNumber = new QLabel("호수: ", this);
    m_guideName = new QLabel("이름: ", this);

    m_inputUnit = new QLineEdit(this);
    m_inputNumber = new QLineEdit(this);
    m_inputName = new QLineEdit(this);

    m_nextBtn = new QPushButton("다음", this);
    m_prevBtn = new QPushButton("이전", this);

    m_registUnitLayout->addWidget(m_guideUnit);
    m_registUnitLayout->addWidget(m_inputUnit);
    m_registNumberLayout->addWidget(m_guideNumber);
    m_registNumberLayout->addWidget(m_inputNumber);
    m_registNameLayout->addWidget(m_guideName);
    m_registNameLayout->addWidget(m_inputName);
    m_registBtnLayout->addWidget(m_nextBtn);
    m_registBtnLayout->addWidget(m_prevBtn);

    m_registHomeNameLayout->addLayout(m_registUnitLayout);
    m_registHomeNameLayout->addLayout(m_registNumberLayout);
    m_registHomeNameLayout->addLayout(m_registNameLayout);
    m_registHomeNameLayout->addLayout(m_registBtnLayout);
    setLayout(m_registHomeNameLayout);

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
    m_registPhoneLayout = new QHBoxLayout(this);
    m_registPhoneNumberLayout = new QVBoxLayout(this);
    m_registBtnLayout = new QHBoxLayout(this);

    m_guidePhoneNumber = new QLabel("전화번호", this);
    m_inputPhoneNumber = new QLabel(this);

    m_nextBtn = new QPushButton("다음", this);
    m_nextBtn->setEnabled(false);
    m_prevBtn = new QPushButton("이전", this);
    m_keypad = new Keypad(this);

    m_registPhoneNumberLayout->addWidget(m_guidePhoneNumber);
    m_registPhoneNumberLayout->addWidget(m_inputPhoneNumber);
    m_registBtnLayout->addWidget(m_nextBtn);
    m_registBtnLayout->addWidget(m_prevBtn);
    m_registPhoneNumberLayout->addLayout(m_registBtnLayout);

    m_registPhoneLayout->addWidget(m_keypad);
    m_registPhoneLayout->addLayout(m_registPhoneNumberLayout);
    setLayout(m_registPhoneLayout);

    connect(m_nextBtn, &QPushButton::clicked, this, &RegistPhone::nextBtnSignal);
    connect(m_prevBtn, &QPushButton::clicked, this, &RegistPhone::prevBtnSignal);
    connect(m_keypad, &Keypad::changeInputDataSignal, this, [this]{
        m_inputPhoneNumber->setText(m_keypad->getNumber());
    });

    connect(m_keypad, &Keypad::selectEnterBtnSignal, this, [this]{
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
