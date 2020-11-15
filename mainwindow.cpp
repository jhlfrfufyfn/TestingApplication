#include <QObject>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "quizwindow.h"
#include "userinfowindow.h"
#include "authorizationwindow.h"
#include "constants.h"
#include "menuwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , currentState(MENU)
    , currentUser(new User("","","",QDate(2000,01,01),this))
    , stackedWidget(new QStackedWidget(this))
{
    this->setWindowState(Qt::WindowMaximized);

    setCentralWidget(stackedWidget);
    MenuWindow *menuWindow = new MenuWindow(this);

    stackedWidget->addWidget(menuWindow);

    stackedWidget->setCurrentIndex(0);

    connect(menuWindow, &MenuWindow::changeUserButtonPressed, this, &MainWindow::createUserInfoWindow);
    connect(menuWindow, &MenuWindow::quitButtonPressed, this, &QApplication::quit);
}

MainWindow::~MainWindow()
{
}

User *MainWindow::getUser() const
{
    return currentUser;
}

void MainWindow::createUserInfoWindow()
{
    UserInfoWindow* userWindow = new UserInfoWindow(this);
    connect(userWindow, &UserInfoWindow::sendUserInfo, this, &MainWindow::changeUserInfo);
    userWindow->exec();
}

MainWindow::State MainWindow::getNextState()const{

}

void MainWindow::setNextState(MainWindow::State newState)
{
    currentState = newState;
}

void MainWindow::changeWindowType()
{
    currentState = getNextState();
    updateWindowLayout();
}

void MainWindow::changeUserInfo(const QString& surName, const QString& name, const QString& secondName, const QDate& date)
{
    currentUser->setInfo(surName, name, secondName, date);
}

void MainWindow::updateWindowLayout()
{
    stackedWidget->setCurrentIndex((int)currentState);
}

void MainWindow::createQuizWindowConnections(QuizWindow* quizWindow)
{
    connect(quizWindow, &QuizWindow::goToNextMode, currentUser, &User::saveToFile);
    connect(quizWindow, &QuizWindow::goToNextMode, this, &MainWindow::changeWindowType);
    //connect(quizWindow, &QuizWindow::sendWindowResults, this->currentUser->results, &QuizResult::integrateResults);
}


