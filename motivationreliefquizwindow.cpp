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
  , isValue(true)
{
    setLayout(stackedWidget->layout());
    InstructionWindow* instWindow = new InstructionWindow(stackedWidget);
    instWindow->resize(this->size());
    stackedWidget->addWidget(instWindow);
    connect(this, &MotivationReliefQuizWindow::instructionShown, instWindow, &InstructionWindow::setInstructionLabel);

    connect(instWindow->getUi()->pushButton, &QPushButton::pressed, this, &MotivationReliefQuizWindow::loadTestLayout);

    QWidget* testWidget = new QWidget(stackedWidget);
    ui->setupUi(testWidget);
    testWidget->resize(this->size());
    stackedWidget->addWidget(testWidget);

    changeLabels();

    prepareToValue();

    connect(this, &MotivationReliefQuizWindow::changeToAccess, this, &MotivationReliefQuizWindow::prepareToAccess);
    connect(this, &MotivationReliefQuizWindow::changeToValue, this, &MotivationReliefQuizWindow::prepareToValue);
}

void MotivationReliefQuizWindow::showInstruction()
{
    const QString& labelText = (isValue)?MOTIVATIONAL_RELIEF_INSTRUCTION_VALUE:MOTIVATIONAL_RELIEF_INSTRUCTION_ACCESS;
    emit instructionShown(labelText);
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
        if(isValue){
            emit changeToAccess();
        }
        else {
            emit changeToValue();
            emit goToNextState();
        }
    }
}

void MotivationReliefQuizWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key::Key_Left){
        if(isValue){
            emit sendWindowResultsValue(model.getCurrentModel(), {ui->leftChoiceLabel->text()});
        }
        else{
            emit sendWindowResultsAccess(model.getCurrentModel(), {ui->leftChoiceLabel->text()});
        }
        changeWindow();
    }
    else if(event->key() == Qt::Key::Key_Right){
        if(isValue){
            emit sendWindowResultsValue(model.getCurrentModel(), {ui->rightChoiceLabel->text()});
        }
        else{
            emit sendWindowResultsAccess(model.getCurrentModel(), {ui->rightChoiceLabel->text()});
        }
        changeWindow();
    }
}


void MotivationReliefQuizWindow::loadTestLayout()
{
    stackedWidget->setCurrentIndex(1);
}

void MotivationReliefQuizWindow::prepareToAccess()
{
    isValue = false;
    ui->label->setText(MOTIVATIONAL_RELIEF_LABEL_ACCESS);
    showInstruction();
}

void MotivationReliefQuizWindow::prepareToValue()
{
    isValue = true;
    ui->label->setText(MOTIVATIONAL_RELIEF_LABEL_VALUE);
    showInstruction();
}

void MotivationReliefQuizWindow::changeLabels()
{
    ui->leftChoiceLabel->setText(model.getCurrentQuestions()[0].first);
    ui->rightChoiceLabel->setText(model.getCurrentQuestions()[0].second);
}
