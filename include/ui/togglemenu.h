#ifndef TOGGLEMENU_H
#define TOGGLEMENU_H

#include <QStackedWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class MainMenu;
class SelectRecoMenu;

class ToggleMenu : public QStackedWidget
{
    Q_OBJECT

public:
    ToggleMenu(QStackedWidget* parent = nullptr);
    ~ToggleMenu(){}

signals:
    void selectRegistBtn();
    void selectEntryFaceBtn();
    void selectEntryQRBtn();

private:
    MainMenu* m_mainMenu;
    SelectRecoMenu* m_selectRecoMenu;
};

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    MainMenu(QWidget* parent = nullptr);
    ~MainMenu(){};

signals:
    void selectEntryBtn();
    void selectRegistBtn();

private:
    QHBoxLayout* m_mainMenuLayout;
    QPushButton* m_entryBtn;
    QPushButton* m_registBtn;
};

class SelectRecoMenu : public QWidget
{
    Q_OBJECT

public:
    SelectRecoMenu(QWidget* parent = nullptr);
    ~SelectRecoMenu(){};

signals:
    void selectEntryFaceBtn();
    void selectEntryQRBtn();
    void selectPrevBtn();

private:
    QVBoxLayout* m_SelectRecoMenuLayout;
    QHBoxLayout* m_RecoMenuBtnLayout;
    QPushButton* m_faceBtn;
    QPushButton* m_qrBtn;
    QPushButton* m_prevBtn;
};


#endif // TOGGLEMENU_H
