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

QRHomePurpose::QRHomePurpose(QWidget* parent) : QWidget(parent)
{
    m_qrHomePurposeLayout = new QVBoxLayout(this);
    m_qrHomePurposeUnitLayout = new QHBoxLayout(this);
    m_qrHomePurposeNumberLayout = new QHBoxLayout(this);
    m_qrHomePurposePurposeLayout = new QHBoxLayout(this);
    m_qrHomePurposeBtnLayout = new QHBoxLayout(this);

    m_guideUnit = new QLabel("동: ", this);
    m_guideNumber = new QLabel("호수: ", this);
    m_guidePurpose = new QLabel("방문목적: ", this);

    m_inputUnit = new QLineEdit(this);
    m_inputNumber = new QLineEdit(this);
    m_inputPurpose = new QLineEdit(this);

    m_nextBtn = new QPushButton("다음", this);
    m_prevBtn = new QPushButton("이전", this);

    m_qrHomePurposeUnitLayout->addWidget(m_guideUnit);
    m_qrHomePurposeUnitLayout->addWidget(m_inputUnit);
    m_qrHomePurposeNumberLayout->addWidget(m_guideNumber);
    m_qrHomePurposeNumberLayout->addWidget(m_inputNumber);
    m_qrHomePurposePurposeLayout->addWidget(m_guidePurpose);
    m_qrHomePurposePurposeLayout->addWidget(m_inputPurpose);
    m_qrHomePurposeBtnLayout->addWidget(m_nextBtn);
    m_qrHomePurposeBtnLayout->addWidget(m_prevBtn);

    m_qrHomePurposeLayout->addLayout(m_qrHomePurposeUnitLayout);
    m_qrHomePurposeLayout->addLayout(m_qrHomePurposeNumberLayout);
    m_qrHomePurposeLayout->addLayout(m_qrHomePurposePurposeLayout);
    m_qrHomePurposeLayout->addLayout(m_qrHomePurposeBtnLayout);
    setLayout(m_qrHomePurposeLayout);

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
    m_qrPhoneLayout = new QHBoxLayout(this);
    m_qrPhoneNumberLayout = new QVBoxLayout(this);
    m_qrPhoneBtnLayout = new QHBoxLayout(this);

    m_guidePhoneNumber = new QLabel("전화번호", this);
    m_inputPhoneNumber = new QLabel(this);

    m_nextBtn = new QPushButton("다음", this);
    m_nextBtn->setEnabled(false);
    m_prevBtn = new QPushButton("이전", this);
    m_keypad = new Keypad(this);

    m_qrPhoneNumberLayout->addWidget(m_guidePhoneNumber);
    m_qrPhoneNumberLayout->addWidget(m_inputPhoneNumber);
    m_qrPhoneBtnLayout->addWidget(m_nextBtn);
    m_qrPhoneBtnLayout->addWidget(m_prevBtn);
    m_qrPhoneNumberLayout->addLayout(m_qrPhoneBtnLayout);

    m_qrPhoneLayout->addWidget(m_keypad);
    m_qrPhoneLayout->addLayout(m_qrPhoneNumberLayout);
    setLayout(m_qrPhoneLayout);

    connect(m_nextBtn, &QPushButton::clicked, this, &QRPhone::nextBtnSignal);
    connect(m_prevBtn, &QPushButton::clicked, this, &QRPhone::prevBtnSignal);
    connect(m_keypad, &Keypad::changeInputDataSignal, this, [this]{
        m_inputPhoneNumber->setText(m_keypad->getNumber());
    });

    connect(m_keypad, &Keypad::selectEnterBtnSignal, this, [this]{
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
}
