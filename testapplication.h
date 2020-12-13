#pragma once
#include <QObject>
#include <QMainWindow>
#include <QStackedWidget>
#include <QDebug>

#include "userinfowindow.h"
#include "constants.h"
#include "menuwindow.h"
#include "choosequizwindow.h"
#include "motivationreliefquizwindow.h"
#include "statisticswindow.h"
#include "itoquizwindow.h"
#include "endquizwindow.h"

#include "motivationreliefquizwindow.h"
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class TestApplication : public QMainWindow
{
    Q_OBJECT

public:
    TestApplication(QWidget *parent = nullptr);
    ~TestApplication();

    void setUser(User user);
    User* getUser()const;

    State getNextState()const;

public slots:
    void createNewUser(const QString& surName, const QString& name, const QString& secondName, const QDate& date);
    void createExistingUser(User* user);
    void openUserInfoWindow();
    void openChooseTestWindow();
    void openMenuWindow();
    void setNextState(State);
    void openEndWindow();
    void openStatisticsWindow();
    void clearMrTestResult();

private:
    void updateWindowLayout();

    void createMotivationalReliefQuizWindowConnections(MotivationReliefQuizWindow*);
    void createMenuWindowConnections(MenuWindow*,StatisticsWindow*);
    void createChooseQuizWindowConnections(ChooseQuizWindow*);
    void createStatisticsWindowConnections(StatisticsWindow*);
    void createEndQuizWindowConnections(EndQuizWindow*);
    void createItoQuizWindowConnections(ItoQuizWindow*);

private:
    State currentState;
    User currentUser;
    QStackedWidget *stackedWidget;
};
