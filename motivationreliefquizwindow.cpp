#include <unordered_map>

#include <QKeyEvent>
#include <QObject>
#include <QPushButton>

#include "ui_MotivationReliefQuizWindow.h"
#include "motivationreliefquizwindow.h"
#include "constants.h"

MotivationReliefQuizWindow::MotivationReliefQuizWindow(QWidget *parent):
    QWidget(parent)
  , ui(new Ui::MotivationReliefQuizWindow)
  , model(MotivationReliefQuizModel())
{
    ui->setupUi(this);
    ///setWindowState(Qt::WindowFullScreen);

}

void MotivationReliefQuizWindow::changeWindow()
{
    bool modelEnded = model.hasModelEnded();
    bool allEnded = modelEnded && (model.getCurrentModel() == model.MODEL_SIZE_LIMIT - 1);

    if(modelEnded){
        model.nextModel();
    }

    model.setNotUsedQuizQuestions(1, QUIZ_VALUES_NAMES[model.getCurrentModel()]);
    changeLabels();

    if(allEnded) {
        emit goToNextState();
    }
}

void MotivationReliefQuizWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key::Key_Left){
        emit sendWindowResults(model.getCurrentModel(), {ui->leftChoiceLabel->text()});
        changeWindow();
    }
    else if(event->key() == Qt::Key::Key_Right){
        emit sendWindowResults(model.getCurrentModel(), {ui->rightChoiceLabel->text()});
        changeWindow();
    }
}

void MotivationReliefQuizWindow::changeLabels()
{
    ui->leftChoiceLabel->setText(model.getCurrentQuestions()[0].first);
    ui->rightChoiceLabel->setText(model.getCurrentQuestions()[0].second);
}
