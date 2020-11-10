#include "authorizationwindow.h"
#include "ui_authorizationwindow.h"
#include "mainwindow.h"

AuthorizationWindow::AuthorizationWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AuthorizationWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &AuthorizationWindow::checkToNextMode);
}

AuthorizationWindow::~AuthorizationWindow()
{
    delete ui;
}

void AuthorizationWindow::checkToNextMode()
{
    QString name = ui->lineEdit->text();
    if(!name.isEmpty()) {
        emit sendUserName(name);
        emit goToNextMode();
        ui->lineEdit->setText("");
    }
}
