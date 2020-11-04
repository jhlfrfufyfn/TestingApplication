#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "quizwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , currentUser(User())
    , currentLayoutType(QUIZ)
    , stackedWidget(new QStackedWidget(this))
{
    stackedWidget->addWidget(new QuizWindow(this));
    stackedWidget->setCurrentIndex(0);
    setCentralWidget(stackedWidget);
    setGeometry(100,100,1000,500);
}

MainWindow::~MainWindow()
{
}

