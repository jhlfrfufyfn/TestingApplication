#ifndef QUIZWINDOW_H
#define QUIZWINDOW_H

#include "quizmodel.h"

#include <QObject>
#include <QWidget>
#include <ui_quizwindow.h>

class QuizWindow :public QWidget
{
    Q_OBJECT
public:
    QuizWindow(QWidget *parent = nullptr);

signals:
    void quizResultReady(std::vector<std::pair<QString, int> > );

public slots:
    void changeWindow();

private:
    Ui::QuizWindow *ui;
    QuizModel model;

    void updateRadioButtonNames();
    bool allRadioGroupsChecked()const;
    void uncheckAllRadioGroups();
    void sendQuizResultReady();

};

#endif // QUIZWINDOW_H
