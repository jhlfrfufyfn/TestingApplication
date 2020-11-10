#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "quizwindow.h"
#include "authorizationwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , currentLayoutType(INPUT)
    , currentUser(new User("",this))
    , stackedWidget(new QStackedWidget(this))
{
    setGeometry(100,100,1000,500);

    setCentralWidget(stackedWidget);
    AuthorizationWindow *authWindow = new AuthorizationWindow(this);
    QuizWindow *quizWindow = new QuizWindow(this);

    stackedWidget->addWidget(authWindow);
    stackedWidget->addWidget(quizWindow);

    stackedWidget->setCurrentIndex(0);


    ///connections between MainWindow's subwidgets
    connect(authWindow, &AuthorizationWindow::goToNextMode, this, &MainWindow::changeWindowType);
    connect(authWindow, &AuthorizationWindow::sendUserName, this, &MainWindow::changeUserName);
    connect(quizWindow, &QuizWindow::goToNextMode, currentUser, &User::saveToFile);
    connect(quizWindow, &QuizWindow::goToNextMode, this, &MainWindow::changeWindowType);
    connect(quizWindow, &QuizWindow::sendWindowResults, this->currentUser->results, &QuizResult::integrateResults);
}

MainWindow::~MainWindow()
{
}

void MainWindow::changeWindowType()
{
    currentLayoutType = static_cast<LayoutType>((int)currentLayoutType + 1);
    currentLayoutType = static_cast<LayoutType>((int)currentLayoutType % LAYOUT_TYPE_SIZE);
    updateWindowMode();
}

void MainWindow::changeUserName(const QString& name)
{
    currentUser->setName(name);
}

void MainWindow::updateWindowMode()
{
    stackedWidget->setCurrentIndex((int)currentLayoutType);
}

