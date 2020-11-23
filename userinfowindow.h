#ifndef USERINFOWINDOW_H
#define USERINFOWINDOW_H

#include <QDialog>
#include "ui_userinfowindow.h"

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

signals:
    void sendUserInfo(const QString& surname, const QString& name,const QString& secondname, const QDate& date);

private:
    Ui::UserInfoWindow *ui;
    void enableButtons(bool value);
};

#endif // USERINFOWINDOW_H
