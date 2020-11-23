#ifndef QUIZWINDOW_H
#define QUIZWINDOW_H

#include <QObject>
#include <QStackedWidget>
#include <QWidget>

#include <vector>

#include "motivationreliefquizmodel.h"
#include "instructionwindow.h"

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
    Ui::MotivationReliefQuizWindow *ui;
    MotivationReliefQuizModel model;
    QStackedWidget* stackedWidget;

private:
    void changeLabels();
    bool isValue;
};

#endif // QUIZWINDOW_H
