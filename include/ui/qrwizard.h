#ifndef QRWIZARD_H
#define QRWIZARD_H

#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include "keypad.h"

class QRHomePurpose;
class QRPhone;

class QRWizard : public QStackedWidget
{
    Q_OBJECT

public:
    QRWizard(QStackedWidget* parent = nullptr);
    ~QRWizard(){}
    void initScreen();
    void clearData();

signals:
    void nextBtnSignal(QVector<QString>);
    void prevBtnSignal();

private:
    QRHomePurpose* m_qrHomePurpose;
    QRPhone* m_qrPhone;
};

class QRHomePurpose : public QWidget
{
    Q_OBJECT

public:
    QRHomePurpose(QWidget* parent = nullptr);
    ~QRHomePurpose(){}
    QVector<QString> getData();
    void clearData();

signals:
    void nextBtnSignal();
    void prevBtnSignal();

private:
    QVBoxLayout* m_qrHomePurposeLayout;
    QHBoxLayout* m_qrHomePurposeUnitLayout;
    QHBoxLayout* m_qrHomePurposeNumberLayout;
    QHBoxLayout* m_qrHomePurposePurposeLayout;
    QHBoxLayout* m_qrHomePurposeBtnLayout;

    QLabel* m_guideUnit;
    QLabel* m_guideNumber;
    QLabel* m_guidePurpose;

    QLineEdit* m_inputUnit;
    QLineEdit* m_inputNumber;
    QLineEdit* m_inputPurpose;

    QPushButton* m_nextBtn;
    QPushButton* m_prevBtn;
};

class QRPhone : public QWidget
{
    Q_OBJECT

public:
    QRPhone(QWidget* parent = nullptr);
    ~QRPhone(){}
    QString getData();
    void clearData();

signals:
    void nextBtnSignal();
    void prevBtnSignal();

private:
    QHBoxLayout* m_qrPhoneLayout;
    QVBoxLayout* m_qrPhoneNumberLayout;
    QHBoxLayout* m_qrPhoneBtnLayout;

    QLabel* m_guidePhoneNumber;
    QLabel* m_inputPhoneNumber;

    QPushButton* m_nextBtn;
    QPushButton* m_prevBtn;

    Keypad* m_keypad;
};

#endif // QRWIZARD_H
