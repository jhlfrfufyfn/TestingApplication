#include <QDir>
#include <QJsonDocument>
#include <typeinfo>

#include "testapplication.h"

TestApplication::TestApplication(QWidget *parent)
    : QMainWindow(parent)
    , currentState(MENU)
    , currentUser()
    , stackedWidget(new QStackedWidget(this))
{
     User::createAllUsersDataTable();
    this->setWindowTitle("Тестирование");
    this->setWindowState(Qt::WindowMaximized);

    setCentralWidget(stackedWidget);

    MenuWindow *menuWindow = new MenuWindow(this);
    ChooseQuizWindow* chQuizWindow = new ChooseQuizWindow(this);
    MotivationReliefQuizWindow* mrQuizWindow = new MotivationReliefQuizWindow(this);
    ItoQuizWindow* itoQuizWindow = new ItoQuizWindow(this);
    StatisticsWindow* stWindow = new StatisticsWindow(this);
    EndQuizWindow* endQuizWindow = new EndQuizWindow(this);

    stackedWidget->addWidget(menuWindow);
    stackedWidget->addWidget(chQuizWindow);
    stackedWidget->addWidget(mrQuizWindow);
    stackedWidget->addWidget(itoQuizWindow);
    stackedWidget->addWidget(stWindow);
    stackedWidget->addWidget(endQuizWindow);

    setNextState(State::MENU);

    createMenuWindowConnections(menuWindow,stWindow);
    createChooseQuizWindowConnections(chQuizWindow);
    createMotivationalReliefQuizWindowConnections(mrQuizWindow);
    createItoQuizWindowConnections(itoQuizWindow);
    createStatisticsWindowConnections(stWindow);
    createEndQuizWindowConnections(endQuizWindow);

    openUserInfoWindow();
}

void TestApplication::createMenuWindowConnections(MenuWindow* menuWindow, StatisticsWindow* stWindow) {
    connect(menuWindow, &MenuWindow::statButtonPressed, stWindow, &StatisticsWindow::prepareStatisticsWindow);
    connect(menuWindow, &MenuWindow::statButtonPressed, this, &TestApplication::openStatisticsWindow);
    connect(menuWindow, &MenuWindow::changeUserButtonPressed, this, &TestApplication::openUserInfoWindow);
    connect(menuWindow, &MenuWindow::quitButtonPressed, this, &QApplication::quit);
    connect(menuWindow, &MenuWindow::testButtonPressed, this, &TestApplication::openChooseTestWindow);
}

void TestApplication::createChooseQuizWindowConnections(ChooseQuizWindow* chQuizWindow){
    connect(chQuizWindow, &ChooseQuizWindow::backToMenuButtonPressed, this, &TestApplication::openMenuWindow);
    connect(chQuizWindow, &ChooseQuizWindow::quizChosen, this, &TestApplication::setNextState);

}

void TestApplication::createStatisticsWindowConnections(StatisticsWindow *stWindow)
{
    connect(stWindow, &StatisticsWindow::returnToMenuButtonPressed, this,&TestApplication::openMenuWindow);
}

void TestApplication::createMotivationalReliefQuizWindowConnections(MotivationReliefQuizWindow* mrQuizWindow){
    connect(mrQuizWindow, &MotivationReliefQuizWindow::sendQuizEnded, &currentUser, &User::saveToFile);
    connect(mrQuizWindow, &MotivationReliefQuizWindow::sendQuizEnded, this, &TestApplication::openEndWindow);
    connect(mrQuizWindow, &MotivationReliefQuizWindow::sendQuizEnded, &User::createAllUsersDataTable);
    connect(mrQuizWindow, &MotivationReliefQuizWindow::sendWindowResultsValue, currentUser.mrResults, &MotivationReliefQuizResult::integrateResultsValue);
    connect(mrQuizWindow, &MotivationReliefQuizWindow::sendWindowResultsAccess, currentUser.mrResults, &MotivationReliefQuizResult::integrateResultsAccess);
}

void TestApplication::createEndQuizWindowConnections(EndQuizWindow* eqWindow){
    connect(eqWindow, &EndQuizWindow::returnToMenuButtonPressed, this, &TestApplication::openMenuWindow);
}

void TestApplication::createItoQuizWindowConnections(ItoQuizWindow *window)
{
    connect(window, &ItoQuizWindow::sendQuizEnded, &currentUser, &User::saveToFile);
    connect(window, &ItoQuizWindow::sendQuizEnded, this, &TestApplication::openEndWindow);
    connect(window, &ItoQuizWindow::sendQuizEnded, &User::createAllUsersDataTable);
    connect(window, &ItoQuizWindow::sendWindowResults, currentUser.itoResults, &ItoResult::integrateResults);
}

TestApplication::~TestApplication()
{
}


void TestApplication::openUserInfoWindow()
{
    UserInfoWindow* userWindow = new UserInfoWindow(this);
    connect(userWindow, &UserInfoWindow::sendUserInfo, this, &TestApplication::createNewUser);
    connect(userWindow, &UserInfoWindow::sendExistingUser,this,&TestApplication::createExistingUser);
    userWindow->updateUserList();
    userWindow->open();
}

void TestApplication::openChooseTestWindow()
{
    setNextState(State::CHOOSE_QUIZ);
}

void TestApplication::openStatisticsWindow(){

    setNextState(State::STATISTICS);
}

void TestApplication::openMenuWindow()
{
    setNextState(MENU);
}

void TestApplication::setNextState(State newState)
{
    currentState = newState;
    updateWindowLayout();
}

void TestApplication::openEndWindow()
{
    setNextState(State::END);
}


void TestApplication::createNewUser(const QString& surName, const QString& name, const QString& secondName, const QDate& date)
{
    //currentUser = new User(surName, name, secondName, date);
    currentUser.resetInfo(surName, name, secondName, date);
    currentUser.clearTestResults();

}

void TestApplication::createExistingUser(User *user)
{
    currentUser.copy(user);
    setNextState(State::MENU);
}

void TestApplication::updateWindowLayout()
{
    stackedWidget->setCurrentIndex((int)currentState);
}



