#include "maininterface.h"

MainInterface::MainInterface(QWidget* parent) : QStackedWidget(parent)
{
    m_toggleMenu = new ToggleMenu(this);
    m_regist = new Regist(this);
    m_qrWizard = new QRWizard(this);
    m_videoLable = new VideoLabel(this);

    addWidget(m_toggleMenu);
    addWidget(m_regist);
    addWidget(m_qrWizard);
    addWidget(m_videoLable);
    setCurrentWidget(m_toggleMenu);

    connect(m_toggleMenu, &ToggleMenu::selectRegistBtn, this, [this]{
        setCurrentWidget(m_regist);
    });

    connect(m_toggleMenu, &ToggleMenu::selectEntryFaceBtn, this, [this]{
        emit setEntryFaceMode();
        setCurrentWidget(m_videoLable);
    });

    connect(m_toggleMenu, &ToggleMenu::selectEntryQRBtn, this, [this]{
        setCurrentWidget(m_qrWizard);
    });

    connect(m_regist, &Regist::nextBtnSignal, this, [this](QVector<QString> data){
        emit setRegistMode();
        setCurrentWidget(m_videoLable);
    });

    connect(m_regist, &Regist::prevBtnSignal, this, [this]{
        setCurrentWidget(m_toggleMenu);
    });

    connect(m_qrWizard, &QRWizard::nextBtnSignal, this, [this](QVector<QString> data){
        emit setEntryQRMode();
        setCurrentWidget(m_videoLable);
    });

    connect(m_qrWizard, &QRWizard::prevBtnSignal, this, [this]{
        setCurrentWidget(m_toggleMenu);
    });
}

void MainInterface::setFrameImg(QImage img)
{
    m_videoLable->displayFrame(img);
}

void MainInterface::goFirstScreen()
{
    setCurrentWidget(m_toggleMenu);
}
