#include "choosequizwindow.h"
#include "ui_choosequizwindow.h"

ChooseQuizWindow::ChooseQuizWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseQuizWindow)
{
    ui->setupUi(this);
}

ChooseQuizWindow::~ChooseQuizWindow()
{
    delete ui;
}
