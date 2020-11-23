#include "endquizwindow.h"
#include "ui_endquizwindow.h"

EndQuizWindow::EndQuizWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EndQuizWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::pressed, this, &EndQuizWindow::returnToMenuButtonPressed);
}

EndQuizWindow::~EndQuizWindow()
{
    delete ui;
}
