#ifndef USERVERIFIER_H
#define USERVERIFIER_H

#include <QObject>
#include <QProcess>
#include <QString>

class UserVerifier : public QObject
{
    Q_OBJECT

public:
    UserVerifier();
    ~UserVerifier(){}
    void entryResult();         // 얼굴 식별용
    void regist();              // 등록 파일 실행용

signals:
    void doneSignal(QString result);     // 식별 결과 signal

private:
    QProcess* m_process;        // 프로세스
    QString result;             // 유사도 기록용
    QString pythonPath;
};

#endif // USERVERIFIER_H
