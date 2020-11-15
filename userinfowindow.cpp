#include <QPushButton>

#include "userinfowindow.h"

UserInfoWindow::UserInfoWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserInfoWindow)
{
    ui->setupUi(this);
    ui->buttonBox->setEnabled(false);

    connect(ui->lineEdit, &QLineEdit::textChanged, this, &UserInfoWindow::checkLineEdits);
    connect(ui->lineEdit_2, &QLineEdit::textChanged, this, &UserInfoWindow::checkLineEdits);
    connect(ui->lineEdit_3, &QLineEdit::textChanged, this, &UserInfoWindow::checkLineEdits);
    connect(ui->buttonBox->button(ui->buttonBox->Ok),&QAbstractButton::pressed, this, &UserInfoWindow::accept);
    connect(ui->buttonBox->button(ui->buttonBox->Cancel),&QAbstractButton::pressed, this, &UserInfoWindow::reject);


}

UserInfoWindow::~UserInfoWindow()
{
    delete ui;
}

void UserInfoWindow::checkLineEdits()
{
    if(ui->lineEdit->text().isEmpty()){
        enableButtons(false);
        return ;
    }
    if(ui->lineEdit_2->text().isEmpty()){
        enableButtons(false);
        return ;
    }
    if(ui->lineEdit_3->text().isEmpty()){
        enableButtons(false);
        return ;
    }
    enableButtons(true);
}

void UserInfoWindow::accept()
{
    emit sendUserInfo(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text(),ui->dateEdit->date());
    QDialog::accept();
}

void UserInfoWindow::reject()
{
    QDialog::reject();
}

void UserInfoWindow::enableButtons(bool value)
{
    ui->buttonBox->setEnabled(value);
}
