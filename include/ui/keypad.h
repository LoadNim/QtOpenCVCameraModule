#ifndef KEYPAD_H
#define KEYPAD_H

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QGridLayout>

class Keypad : public QWidget
{
    Q_OBJECT

public:
    Keypad(QWidget* parent = nullptr);
    ~Keypad(){}
    void initKeypad();
    void updateBtnState();
    QString getNumber() const {return m_inputNum;}

signals:
    void changeInputDataSignal();
    void selectEnterBtnSignal();

private:
    QString m_inputNum;
    QVector<QPushButton*> m_numBtns;
    QPushButton* m_enterBtn;
    QPushButton* m_backspBtn;

private slots:
    void keypadBtnClicked();
};

#endif // KEYPAD_H
