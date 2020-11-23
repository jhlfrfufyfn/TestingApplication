#ifndef QUIZWINDOW_H
#define QUIZWINDOW_H

#include <vector>

#include <QObject>
#include <QStackedWidget>
#include <QWidget>
#include <QTimer>

#include "motivationreliefquizmodel.h"
#include "instructionwindow.h"
#include "constants.h"

namespace Ui {
class MotivationReliefQuizWindow;
}

class MotivationReliefQuizWindow :public QWidget
{
    Q_OBJECT
public:
    MotivationReliefQuizWindow(QWidget *parent = nullptr);
    std::vector<QString> getWindowResult()const;
    void showInstruction();

signals:
    void changeToValue();
    void changeToAccess();
    void goToNextState();
    void sendWindowResultsValue(int, const std::vector<QString>&);
    void sendWindowResultsAccess(int, const std::vector<QString>&);
    void instructionShown(const QString& text);

public slots:
    void changeWindow();
    void keyPressEvent(QKeyEvent *event) override;
    void loadTestLayout();
    void prepareToAccess();
    void prepareToValue();

private:
    void changeLabels();

private:
    Ui::MotivationReliefQuizWindow *ui;
    MotivationReliefQuizModel model;
    QStackedWidget* stackedWidget;
    bool isValue;
    QTimer* timer;
    int timeOfLastKeyPressMsec;

};

#endif // QUIZWINDOW_H
