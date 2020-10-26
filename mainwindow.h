#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "user.h"

#include <QMainWindow>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setUser(User user);
    void getUser()const;

private:
    enum LayoutType{INPUT, CHOOSEQUIZ, RULES, QUIZ, ADMIN, SETTINGS};
    User currentUser;

    LayoutType currentLayoutType;
    QStackedWidget *stackedWidget;
};
#endif // MAINWINDOW_H
