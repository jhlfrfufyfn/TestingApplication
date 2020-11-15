#ifndef QUIZWINDOW_H
#define QUIZWINDOW_H

#include "quizmodel.h"

#include <vector>

#include <QObject>
#include <QWidget>

namespace Ui {
class QuizWindow;
}

class QuizWindow :public QWidget
{
    Q_OBJECT
public:
    QuizWindow(QWidget *parent = nullptr);
    std::vector<QString> getWindowResult()const;

signals:
    void goToNextMode();
    void sendWindowResults(int, std::vector<QString>);

public slots:
    void changeWindow();

private:
    Ui::QuizWindow *ui;
    QuizModel model;
};

#endif // QUIZWINDOW_H
