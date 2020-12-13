#include "userinfowindow.h"
#include "ui_userinfowindow.h"
#include "user.h"
#include <QPushButton>
#include <QJsonDocument>
#include <QFile>

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
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::activated), this, &UserInfoWindow::userSelected);
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::activated), this, &UserInfoWindow::enableButtons);
}

UserInfoWindow::~UserInfoWindow()
{
    delete ui;
}

void UserInfoWindow::checkLineEdits()
{
    if(ui->lineEdit->text().isEmpty()){
        setEnabledButtons(false);
        return ;
    }
    if(ui->lineEdit_2->text().isEmpty()){
        setEnabledButtons(false);
        return ;
    }
    if(ui->lineEdit_3->text().isEmpty()){
        setEnabledButtons(false);
        return ;
    }
    setEnabledButtons(true);
}

void UserInfoWindow::accept()
{
    if(ui->comboBox->currentIndex() == -1){
        emit sendUserInfo(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text(),ui->dateEdit->date());
    }
    QDialog::accept();
}

void UserInfoWindow::reject()
{
    QDialog::reject();
}

void UserInfoWindow::updateUserList()
{
    ui->comboBox->addItems(User::getUserList());
    ui->comboBox->setCurrentIndex(-1);
}

void UserInfoWindow::userSelected(int index)
{
    if(index == -1){
        return;
    }
    QString selectedUser = ui->comboBox->itemText(index);

    QString dateStr = selectedUser.split(" \"").at(1);
    dateStr.remove(dateStr.size()-1, 1);
    QDate date = QDate::fromString(dateStr);
    QString fileName = "data/" + selectedUser.split(" ").at(0) + selectedUser.split(" ").at(1)+ selectedUser.split(" ").at(2)
            + QString::number(date.day()) + QString::number(date.month()) + QString::number(date.year())+".txt";

    User *user = User::loadFromFile(fileName);

    emit sendExistingUser(user);
}

void UserInfoWindow::enableButtons()
{
    setEnabledButtons(true);
}

void UserInfoWindow::setEnabledButtons(bool value)
{
    ui->buttonBox->setEnabled(value);
}
