#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <QStackedWidget>
#include <QDebug>

#include "ui_mainwindow.h"
#include "userinfowindow.h"
#include "constants.h"
#include "menuwindow.h"
#include "choosequizwindow.h"

#include "motivationreliefquizwindow.h"
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setUser(User user);
    User* getUser()const;


    State getNextState()const;

public slots:
    void changeUserInfo(const QString& surName, const QString& name, const QString& secondName, const QDate& date);
    void openUserInfoWindow();
    void openChooseTestWindow();
    void openMenuWindow();
    void setNextState(State);
    void openEndWindow();

private:
    void updateWindowLayout();
    void createQuizWindowConnections(MotivationReliefQuizWindow*);

private:
    State currentState;

    User* currentUser;
    QStackedWidget *stackedWidget;

};
#endif // MAINWINDOW_H
