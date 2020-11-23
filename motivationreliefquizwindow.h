#ifndef QUIZWINDOW_H
#define QUIZWINDOW_H

#include <QObject>
#include <QStackedWidget>
#include <QWidget>

#include <vector>

#include "motivationreliefquizmodel.h"

namespace Ui {
class MotivationReliefQuizWindow;
}

class MotivationReliefQuizWindow :public QWidget
{
    Q_OBJECT
public:
    MotivationReliefQuizWindow(QWidget *parent = nullptr);
    std::vector<QString> getWindowResult()const;

signals:
    void goToNextState();
    void sendWindowResults(int, const std::vector<QString>&);

public slots:
    void changeWindow();
    void keyPressEvent(QKeyEvent *event) override;
    void loadTestLayout();

private:
    Ui::MotivationReliefQuizWindow *ui;
    MotivationReliefQuizModel model;
    QStackedWidget* stackedWidget;

private:
    void changeLabels();
};

#endif // QUIZWINDOW_H
