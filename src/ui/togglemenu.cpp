#include "togglemenu.h"

ToggleMenu::ToggleMenu(QStackedWidget* parent) : QStackedWidget(parent)
{
    m_mainMenu = new MainMenu(this);
    m_selectRecoMenu = new SelectRecoMenu(this);

    addWidget(m_mainMenu);
    addWidget(m_selectRecoMenu);
    setCurrentWidget(m_mainMenu);

    connect(m_mainMenu, &MainMenu::selectEntryBtn, this, [this]{
        setCurrentWidget(m_selectRecoMenu);
    });

    connect(m_selectRecoMenu, &SelectRecoMenu::selectPrevBtn, this, [this]{
        setCurrentWidget(m_mainMenu);
    });

    connect(m_mainMenu, &MainMenu::selectRegistBtn, this, &ToggleMenu::selectRegistBtn);
    connect(m_selectRecoMenu, &SelectRecoMenu::selectEntryFaceBtn, this, &ToggleMenu::selectEntryFaceBtn);
    connect(m_selectRecoMenu, &SelectRecoMenu::selectEntryQRBtn, this, &ToggleMenu::selectEntryQRBtn);
}

void ToggleMenu::initScreen()
{
    setCurrentWidget(m_mainMenu);
}

MainMenu::MainMenu(QWidget* parent) : QWidget(parent)
{
    m_mainMenuLayout = new QHBoxLayout(this);
    m_entryBtn = new QPushButton("출입" ,this);
    m_registBtn = new QPushButton("등록", this);

    m_entryBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_registBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_mainMenuLayout->addWidget(m_entryBtn);
    m_mainMenuLayout->addWidget(m_registBtn);
    setLayout(m_mainMenuLayout);

    connect(m_entryBtn, &QPushButton::clicked, this, &MainMenu::selectEntryBtn);
    connect(m_registBtn, &QPushButton::clicked, this, &MainMenu::selectRegistBtn);
}

SelectRecoMenu::SelectRecoMenu(QWidget* parent) : QWidget(parent)
{
    m_SelectRecoMenuLayout = new QVBoxLayout(this);
    m_RecoMenuBtnLayout = new QHBoxLayout(this);
    m_faceBtn = new QPushButton("안면", this);
    m_qrBtn = new QPushButton("QR", this);
    m_prevBtn = new QPushButton("이전", this);

    // 버튼 확장 설정
    m_faceBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_qrBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_RecoMenuBtnLayout->addWidget(m_faceBtn);
    m_RecoMenuBtnLayout->addWidget(m_qrBtn);
    m_SelectRecoMenuLayout->addLayout(m_RecoMenuBtnLayout);
    m_SelectRecoMenuLayout->addWidget(m_prevBtn);
    setLayout(m_SelectRecoMenuLayout);

    connect(m_faceBtn, &QPushButton::clicked, this, &SelectRecoMenu::selectEntryFaceBtn);
    connect(m_qrBtn, &QPushButton::clicked, this, &SelectRecoMenu::selectEntryQRBtn);
    connect(m_prevBtn, &QPushButton::clicked, this, &SelectRecoMenu::selectPrevBtn);
}
