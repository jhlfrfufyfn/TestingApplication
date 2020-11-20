#include <unordered_map>

#include <QKeyEvent>
#include <QObject>
#include <QPushButton>
#include <QDebug>

#include "ui_MotivationReliefQuizWindow.h"
#include "motivationreliefquizwindow.h"
#include "ui_Instruction.h"
#include "constants.h"

MotivationReliefQuizWindow::MotivationReliefQuizWindow(QWidget *parent):
    QWidget(parent)
  , ui(new Ui::MotivationReliefQuizWindow)
  , model(MotivationReliefQuizModel())
  , stackedWidget(new QStackedWidget(this))
{
    setLayout(stackedWidget->layout());
    Ui::Instruction* inst = new Ui::Instruction();
    QWidget* instWidget = new QWidget(stackedWidget);
    inst->setupUi(instWidget);
    instWidget->resize(this->size());
    connect(inst->pushButton, &QPushButton::pressed, this, &MotivationReliefQuizWindow::loadTestLayout);
    stackedWidget->addWidget(instWidget);

    QWidget* testWidget = new QWidget(stackedWidget);
    ui->setupUi(testWidget);
    testWidget->resize(this->size());
    stackedWidget->addWidget(testWidget);
    changeLabels();

    stackedWidget->setCurrentIndex(0);
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
    qDebug()<<event->key();
    if(event->key() == Qt::Key::Key_Left){
        emit sendWindowResults(model.getCurrentModel(), {ui->leftChoiceLabel->text()});
        changeWindow();
    }
    else if(event->key() == Qt::Key::Key_Right){
        emit sendWindowResults(model.getCurrentModel(), {ui->rightChoiceLabel->text()});
        changeWindow();
    }
}


void MotivationReliefQuizWindow::loadTestLayout()
{
    stackedWidget->setCurrentIndex(1);
}

void MotivationReliefQuizWindow::changeLabels()
{
    ui->leftChoiceLabel->setText(model.getCurrentQuestions()[0].first);
    ui->rightChoiceLabel->setText(model.getCurrentQuestions()[0].second);
}
