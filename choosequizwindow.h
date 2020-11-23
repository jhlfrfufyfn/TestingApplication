#ifndef CHOOSEQUIZWINDOW_H
#define CHOOSEQUIZWINDOW_H

#include <QWidget>
#include "constants.h"

namespace Ui {
class ChooseQuizWindow;
}

class ChooseQuizWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseQuizWindow(QWidget *parent = nullptr);
    ~ChooseQuizWindow();

signals:
    void takeQuizButtonPressed();
    void backToMenuButtonPressed();
    void quizChosen(State currentState);


public slots:
    void processQuizSelecting();
    void processQuizChoosing();



private:
    Ui::ChooseQuizWindow *ui;
};

#endif // CHOOSEQUIZWINDOW_H
