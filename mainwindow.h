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

public slots:
    void changeWindowType();
    void changeUserName(const QString& name);

private:
    void updateWindowMode();

private:
    const int LAYOUT_TYPE_SIZE = 2;
    ///enum LayoutType{INPUT, CHOOSEQUIZ, RULES, QUIZ_MOTIVATION_RELIEF, ADMIN, SETTINGS};
    enum LayoutType{INPUT, QUIZ_MOTIVATION_RELIEF, END};

    LayoutType currentLayoutType;

    User* currentUser;
    QStackedWidget *stackedWidget;

};
#endif // MAINWINDOW_H
