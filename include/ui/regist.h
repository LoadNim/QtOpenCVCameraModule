#ifndef REGIST_H
#define REGIST_H

#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include "keypad.h"

class RegistHomeName;
class RegistPhone;

class Regist : public QStackedWidget
{
    Q_OBJECT

public:
    Regist(QStackedWidget* parent = nullptr);
    ~Regist(){}
    void initScreen();
    void clearData();

signals:
    void nextBtnSignal(QVector<QString>);
    void prevBtnSignal();

private:
    RegistHomeName* m_registHomeName;
    RegistPhone* m_registPhone;
};

class RegistHomeName : public QWidget
{
    Q_OBJECT

public:
    RegistHomeName(QWidget* parent = nullptr);
    ~RegistHomeName(){}
    QVector<QString> getData();
    void clearData();

signals:
    void nextBtnSignal();
    void prevBtnSignal();

private:
    QVBoxLayout* m_registHomeNameLayout;
    QHBoxLayout* m_registUnitLayout;
    QHBoxLayout* m_registNumberLayout;
    QHBoxLayout* m_registNameLayout;
    QHBoxLayout* m_registBtnLayout;

    QLabel* m_guideUnit;
    QLabel* m_guideNumber;
    QLabel* m_guideName;

    QLineEdit* m_inputUnit;
    QLineEdit* m_inputNumber;
    QLineEdit* m_inputName;

    QPushButton* m_nextBtn;
    QPushButton* m_prevBtn;
};

class RegistPhone : public QWidget
{
    Q_OBJECT

public:
    RegistPhone(QWidget* parent = nullptr);
    ~RegistPhone(){}
    QString getData();
    void clearData();

signals:
    void nextBtnSignal();
    void prevBtnSignal();

private:
    QHBoxLayout* m_registPhoneLayout;
    QVBoxLayout* m_registPhoneNumberLayout;
    QHBoxLayout* m_registBtnLayout;

    QLabel* m_guidePhoneNumber;
    QLabel* m_inputPhoneNumber;

    QPushButton* m_nextBtn;
    QPushButton* m_prevBtn;

    Keypad* m_keypad;
};

#endif // REGIST_H
