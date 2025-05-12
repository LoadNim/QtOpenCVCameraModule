#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QString>
#include <QPushButton>
#include <QTimer>

class MainInterface : public QWidget
{
    Q_OBJECT

public:
    MainInterface();
    ~MainInterface();
    void displayImg(QImage);                // 이미지를 화면에 표시하는 함수
    void makeKeypad();                      // 키패드를 생성하는 함수
    void updateGuide();                     // 안내 문구 갱신 함수
    void updateBtnState();                  // 키패드 버튼 상태 갱신 함수
    void resetKeypad();                     // 키패드 및 전화번호 리셋 함수
    void qrTimeout();                       // QR 인식 제한시간 초과를 처리하는 함수

private:
    QLabel* m_label;                        // 프레임 이미지가 출력되는 영역
    QHBoxLayout* m_mainLayout;              // 화면에 보이는 영역

    QWidget* m_keypad;                      // 키패드 영역 (안내 문구 + 버튼)
    QLabel* m_keypadGuide;                  // 안내문구
    QString m_inputPhoneNum;                // 입력된 전화번호가 저장될 문자열

    QPushButton* m_enterBtn;                // 엔터 버튼
    QPushButton* m_backspBtn;               // 백 스페이스 버튼
    QVector<QPushButton*> m_numBtns;        // 숫자 버튼 벡터
    bool m_inQRMode;                        // 엔터키 입력 플래그 변수

    QTimer* m_qrTimeoutTimer;               // QR 인식 제한시간

signals:
    void phoneNumberSubmit(const QString&); // 엔터키를 눌렀을 때의 시그널
    void resetRecoMode();                   // 얼굴 인식으로 인식모드 초기화

private slots:
    void keypadBtnClicked();                // 버튼 클릭 처리 슬롯 함수
};

#endif // MAININTERFACE_H
