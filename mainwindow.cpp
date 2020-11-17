#include "mainwindow.h"
#include "motivationreliefquizwindow.h"
#include "endquizwindow.h"
#include <typeinfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , currentState(MENU)
    , currentUser(new User("","","",QDate(2000,01,01),this))
    , stackedWidget(new QStackedWidget(this))
{
    this->setWindowTitle("Тестирование");
    this->setWindowState(Qt::WindowMaximized);

    setCentralWidget(stackedWidget);
    MenuWindow *menuWindow = new MenuWindow(this);
    ChooseQuizWindow* chQuizWindow = new ChooseQuizWindow(this);
    MotivationReliefQuizWindow* mrQuizWindow = new MotivationReliefQuizWindow(this);
    EndQuizWindow* endQuizWindow = new EndQuizWindow(this);

    stackedWidget->addWidget(menuWindow);
    stackedWidget->addWidget(chQuizWindow);
    stackedWidget->addWidget(mrQuizWindow);
    stackedWidget->addWidget(endQuizWindow);

    stackedWidget->setCurrentIndex(State::MENU);

    connect(menuWindow, &MenuWindow::changeUserButtonPressed, this, &MainWindow::openUserInfoWindow);
    connect(menuWindow, &MenuWindow::quitButtonPressed, this, &QApplication::quit);
    connect(menuWindow, &MenuWindow::testButtonPressed, this, &MainWindow::openChooseTestWindow);

    connect(chQuizWindow, &ChooseQuizWindow::backToMenuButtonPressed, this, &MainWindow::openMenuWindow);
    connect(chQuizWindow, &ChooseQuizWindow::quizChosen, this, &MainWindow::setNextState);

    connect(mrQuizWindow, &MotivationReliefQuizWindow::goToNextState, this->currentUser, &User::saveToFile);
    connect(mrQuizWindow, &MotivationReliefQuizWindow::goToNextState, this, &MainWindow::openEndWindow);
    connect(mrQuizWindow, &MotivationReliefQuizWindow::sendWindowResults, this->getUser()->results, &MotivationReliefQuizResult::integrateResults);

    connect(endQuizWindow, &EndQuizWindow::returnToMenuButtonPressed, this, &MainWindow::openMenuWindow);

    openUserInfoWindow();
}

MainWindow::~MainWindow()
{
}

User *MainWindow::getUser() const
{
    return currentUser;
}

void MainWindow::openUserInfoWindow()
{
    UserInfoWindow* userWindow = new UserInfoWindow(this);
    connect(userWindow, &UserInfoWindow::sendUserInfo, this, &MainWindow::changeUserInfo);
    userWindow->open();
}

void MainWindow::openChooseTestWindow()
{
    setNextState(State::CHOOSE_QUIZ);
}

void MainWindow::openMenuWindow()
{
    setNextState(MENU);
}

void MainWindow::setNextState(State newState)
{
    currentState = newState;
    updateWindowLayout();
}

void MainWindow::openEndWindow()
{
    setNextState(State::END);
}


void MainWindow::changeUserInfo(const QString& surName, const QString& name, const QString& secondName, const QDate& date)
{
    currentUser->setInfo(surName, name, secondName, date);
}

void MainWindow::updateWindowLayout()
{
    stackedWidget->setCurrentIndex((int)currentState);
}



