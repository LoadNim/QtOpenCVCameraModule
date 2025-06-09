#include "keypad.h"

Keypad::Keypad(QWidget* parent) : QWidget(parent)
{
    QGridLayout* keypadLayout = new QGridLayout(this);
    QStringList labels = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "←", "0", "↵"};

    int idx = 0;
    for(int row = 0; row < 4; ++row){
        for(int col = 0; col < 3; ++col){
            QString label = labels[idx++];
            QPushButton* btn = new QPushButton(label, this);
            btn->setProperty("Keyvalue", label);
            connect(btn, &QPushButton::clicked, this, &Keypad::keypadBtnClicked);
            keypadLayout->addWidget(btn, row, col);

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
    setLayout(keypadLayout);
    updateBtnState();
}

void Keypad::initKeypad(int length)
{
    m_inputNum.clear();
    updateBtnState();
}

void Keypad::keypadBtnClicked()
{
    QPushButton* senderBtn = qobject_cast<QPushButton*>(sender());
    if(!senderBtn) return;
    QString value = senderBtn->property("Keyvalue").toString();

    if(value == "←"){
        m_inputNum.chop(1);
    }
    else if (value == "↵"){
        emit selectEnterBtnSignal();
    }
    else{
        if (m_inputNum.length() < 11){
            m_inputNum += value;
        }
    }
    updateBtnState();
    emit changeInputDataSignal();
}

void Keypad::updateBtnState()
{
    if(m_enterBtn){
        m_enterBtn->setEnabled(m_inputNum.length() == 11);
    }

    if(m_backspBtn){
        m_backspBtn->setEnabled(!m_inputNum.isEmpty());
    }

    bool allowMore = m_inputNum.length() < 11;
    for(QPushButton* b : m_numBtns){
        b->setEnabled(allowMore);
    }
}
