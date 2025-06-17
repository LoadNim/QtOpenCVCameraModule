#include "keypad.h"

#include "keypad.h"

#include "keypad.h"

Keypad::Keypad(QWidget* parent) : QWidget(parent)
{
    QGridLayout* keypadLayout = new QGridLayout(this);
    keypadLayout->setSpacing(10);  // 버튼 간 간격
    keypadLayout->setContentsMargins(0, 0, 0, 0);  // 외부 여백 제거

    QStringList labels = { "1", "2", "3",
                          "4", "5", "6",
                          "7", "8", "9",
                          "←", "0", "↵" };

    int idx = 0;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 3; ++col) {
            QString label = labels[idx++];
            QPushButton* btn = new QPushButton(label, this);

            // ✅ 기본 버튼 스타일
            btn->setMinimumSize(80, 60);
            btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            btn->setStyleSheet("font-size: 20pt;");

            // ↵ 버튼만 별도 강조
            if (label == "↵") {
                btn->setStyleSheet(R"(
                QPushButton {
                    font-size: 20pt;
                    font-weight: bold;
                    background-color: #2e7d32;
                    color: white;
                }
                QPushButton:disabled {
                    background-color: #444444;
                    color: #888888;
                }
            )");
                m_enterBtn = btn;
            }

            else if (label == "←") {
                m_backspBtn = btn;
            }
            else {
                m_numBtns.append(btn);
            }

            btn->setProperty("Keyvalue", label);
            connect(btn, &QPushButton::clicked, this, &Keypad::keypadBtnClicked);
            keypadLayout->addWidget(btn, row, col);
        }
    }

    setLayout(keypadLayout);
    updateBtnState();
}



void Keypad::initKeypad()
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
