#ifndef QUIZWINDOW_H
#define QUIZWINDOW_H

#include <QObject>
#include <QWidget>
#include <ui_quizwindow.h>

class QuizWindow :public QWidget
{
    Q_OBJECT
public:
    QuizWindow(QWidget *parent = nullptr);

public slots:
    void changeWindow();

private:
    Ui::QuizWindow *ui;
};

#endif // QUIZWINDOW_H
