#include "mainwindow.h"

#include <QApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    // qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    // qputenv("QML2_IMPORT_PATH", QByteArray("C:/Qt/6.9.0/msvc2022_64/qml"));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
