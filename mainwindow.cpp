#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "quizwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , currentUser(User())
    , currentLayoutType(INPUT)
    , stackedWidget(new QStackedWidget(this))
{
    stackedWidget->addWidget(new QuizWindow());
    stackedWidget->setCurrentIndex(0);
    setCentralWidget(stackedWidget->currentWidget());
}

MainWindow::~MainWindow()
{
}

