#include "userverifier.h"
#include <QDebug>
#include <QRegularExpression>

UserVerifier::UserVerifier()
{
    m_process = new QProcess(this);

    pythonPath = "C:/Users/ssoom/AppData/Local/Programs/Python/Python312/python.exe";

    connect(m_process, &QProcess::readyReadStandardOutput, this, [this]() {
        QString rawOutput = QString::fromLocal8Bit(m_process->readAllStandardOutput()).trimmed();
        QStringList lines = rawOutput.split(QRegularExpression("[\r\n]+"), Qt::SkipEmptyParts);
        result = lines.isEmpty() ? "" : lines.last();  // 마지막 줄이 결과값
        emit doneSignal(result);
    });

    // 에러 처리 추가
    connect(m_process, &QProcess::errorOccurred, this, [this](QProcess::ProcessError error) {
        qDebug() << "Process error:" << error;
        qDebug() << "Error string:" << m_process->errorString();
    });

    connect(m_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, [this](int exitCode, QProcess::ExitStatus exitStatus) {
                qDebug() << "Process finished with exit code:" << exitCode;
                qDebug() << "Exit status:" << exitStatus;
                if (exitCode != 0) {
                    qDebug() << "Standard error:" << m_process->readAllStandardError();
                }
            });
}

void UserVerifier::entryResult()
{
    QString scriptPath = "./AIModule/check_user.py";
    m_process->start(pythonPath, QStringList() << scriptPath);
}

void UserVerifier::regist()
{
    QString scriptPath = "./AIModule/regist_user.py";
    m_process->start(pythonPath, QStringList() << scriptPath);
}
