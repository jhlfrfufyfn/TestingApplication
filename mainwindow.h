#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "authorizationwindow.h"
#include "quizwindow.h"
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
    enum State{MENU, QUIZ_MOTIVATION_RELIEF, END};


    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setUser(User user);
    User* getUser()const;

    void createUserInfoWindow();

    State getNextState()const;
    void setNextState(State);

public slots:
    void changeWindowType();
    void changeUserInfo(const QString& surName, const QString& name, const QString& secondName, const QDate& date);

private:
    void updateWindowLayout();
    void createQuizWindowConnections(QuizWindow*);

private:
    State currentState;

    User* currentUser;
    QStackedWidget *stackedWidget;

};
#endif // MAINWINDOW_H
