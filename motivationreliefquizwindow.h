#pragma once

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
    void showInstruction();

signals:
    void sendQuizEnded();
    void sendWindowResultsValue(int, const std::vector<QString>&);
    void sendWindowResultsAccess(int, const std::vector<QString>&);
    void sendInstructionShown(const QString& text);

protected slots:
    void keyPressEvent(QKeyEvent *event) override;

public slots:
    void goToNextQuizQuestion();
    void loadTestLayout();
    void switchToAccessMode();
    void switchToValueMode();

private:
    void updateUiChoiceLabels();
    void resetQuiz();

private:
    Ui::MotivationReliefQuizWindow *ui;
    MotivationReliefQuizModel model;
    QStackedWidget* stackedWidget;
    bool isValueMode;
    QTimer* timer;
    int timeOfLastKeyPressMsec;

};
