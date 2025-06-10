#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include <QStackedWidget>
#include <QVector>
#include <QString>

#include "togglemenu.h"
#include "regist.h"
#include "qrwizard.h"
#include "videolabel.h"

class MainInterface : public QStackedWidget
{
    Q_OBJECT

public:
    MainInterface(QWidget* parent = nullptr);
    ~MainInterface(){}
    void setFrameImg(QImage frame);

signals:
    void setEntryFaceMode();
    void setEntryQRMode();
    void setRegistMode();

private:
    ToggleMenu* m_toggleMenu;
    Regist* m_regist;
    QRWizard* m_qrWizard;
    VideoLabel* m_videoLable;
};

#endif // MAININTERFACE_H
