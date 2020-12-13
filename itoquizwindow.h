#ifndef ITOQUIZWINDOW_H
#define ITOQUIZWINDOW_H

#include <QWidget>
#include <QStackedWidget>

#include "itomodel.h"
#include "itoresult.h"

namespace Ui {
class ItoQuizWindow;
}

class ItoQuizWindow : public QWidget
{
    Q_OBJECT
public:
    ItoQuizWindow(QWidget *parent = nullptr);
    void showInstruction();

signals:
    void sendQuizEnded();
    void sendWindowResults(bool isLeft);
    void sendInstructionShown(const QString& text);

protected slots:
    void keyPressEvent(QKeyEvent *event) override;

public slots:
    void goToNextQuizQuestion();
    void loadTestLayout();

private:
    void updateUiQuestionLabel();
    void resetQuiz();

private:
    Ui::ItoQuizWindow *ui;
    ItoModel model;
    QStackedWidget* stackedWidget;
    QTimer* timer;
    int timeOfLastKeyPressMsec;

};

#endif // ITOQUIZWINDOW_H
