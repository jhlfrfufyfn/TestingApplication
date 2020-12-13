#pragma once
#include <QDialog>
#include "user.h"

namespace Ui {
class UserInfoWindow;
}

class UserInfoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit UserInfoWindow(QWidget *parent = nullptr);
    ~UserInfoWindow();

public slots:
    void checkLineEdits();
    void accept() override;
    void reject() override;
    void updateUserList();
    void userSelected(int index);
    void enableButtons();

signals:
    void sendUserInfo(const QString& surname, const QString& name,const QString& secondname, const QDate& date);
    void sendExistingUser(User*);

private:
    Ui::UserInfoWindow *ui;
    void setEnabledButtons(bool value);
};

