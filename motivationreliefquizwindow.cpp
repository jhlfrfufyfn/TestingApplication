#include <unordered_map>

#include <QKeyEvent>
#include <QObject>
#include <QPushButton>
#include <QMessageBox>
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
  , isValueMode(true)
  , timer(new QTimer(this))
  , timeOfLastKeyPressMsec(0)
{
    timer->setTimerType(Qt::VeryCoarseTimer);

    setLayout(stackedWidget->layout());
    InstructionWindow* instWindow = new InstructionWindow(stackedWidget);
    instWindow->resize(this->size());
    stackedWidget->addWidget(instWindow);
    connect(this, &MotivationReliefQuizWindow::sendInstructionShown, instWindow, &InstructionWindow::setInstructionLabel);

    connect(instWindow->getUi()->pushButton, &QPushButton::pressed, this, &MotivationReliefQuizWindow::loadTestLayout);

    QWidget* testWidget = new QWidget(stackedWidget);
    ui->setupUi(testWidget);
    testWidget->resize(this->size());
    stackedWidget->addWidget(testWidget);

    updateUiChoiceLabels();

    switchToValueMode();

    connect(this,&MotivationReliefQuizWindow::sendQuizEnded, this->timer, &QTimer::stop);
}

void MotivationReliefQuizWindow::showInstruction()
{
    const QString& labelText = (isValueMode)?MOTIVATIONAL_RELIEF_INSTRUCTION_VALUE:MOTIVATIONAL_RELIEF_INSTRUCTION_ACCESS;
    emit sendInstructionShown(labelText);
    stackedWidget->setCurrentIndex(0);
}

void MotivationReliefQuizWindow::goToNextQuizQuestion()
{
    bool modelEnded = model.hasModelEnded();
    bool allEnded = modelEnded && (model.getCurrentModel() == model.MODEL_SIZE_LIMIT - 1);

    if(modelEnded){
        model.nextModel();
    }

    model.setNotUsedQuizQuestions(1, QUIZ_VALUES_NAMES[model.getCurrentModel()]);
    updateUiChoiceLabels();

    if(allEnded) {
        if(isValueMode){
            switchToAccessMode();
        }
        else {
            resetQuiz();
            emit sendQuizEnded();
        }
    }
}


void MotivationReliefQuizWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key::Key_Left || event->key() == Qt::Key::Key_Right){
        auto timeFromTimerStart = [this](){
            return timer->interval() - timer->remainingTime();
        };
        int currentTime = timeFromTimerStart();
        if(currentTime - timeOfLastKeyPressMsec < TIME_LIMIT_BETWEEN_PRESSES){
            QMessageBox msgBox;
            msgBox.setWindowTitle("ПРЕДУПРЕЖДЕНИЕ");
            msgBox.setText("Пожалуйста, проходите тест более продуманно!");
            ///msgBox.exec();
        }
        timeOfLastKeyPressMsec = currentTime;
    }
    if(event->key() == Qt::Key::Key_Left){
        if(isValueMode){
            emit sendWindowResultsValue(model.getCurrentModel(), {ui->leftChoiceLabel->text()});
        }
        else{
            emit sendWindowResultsAccess(model.getCurrentModel(), {ui->leftChoiceLabel->text()});
        }
        goToNextQuizQuestion();
    }
    else if(event->key() == Qt::Key::Key_Right){
        if(isValueMode){
            emit sendWindowResultsValue(model.getCurrentModel(), {ui->rightChoiceLabel->text()});
        }
        else{
            emit sendWindowResultsAccess(model.getCurrentModel(), {ui->rightChoiceLabel->text()});
        }
        goToNextQuizQuestion();
    }
}


void MotivationReliefQuizWindow::loadTestLayout()
{
    stackedWidget->setCurrentIndex(1);
}

void MotivationReliefQuizWindow::switchToAccessMode()
{
    isValueMode = false;
    ui->label->setText(MOTIVATIONAL_RELIEF_LABEL_ACCESS);
    showInstruction();
}

void MotivationReliefQuizWindow::switchToValueMode()
{
    timer->start(TIMER_INTERVAL);
    isValueMode = true;
    ui->label->setText(MOTIVATIONAL_RELIEF_LABEL_VALUE);
    showInstruction();
}

void MotivationReliefQuizWindow::updateUiChoiceLabels()
{
    ui->leftChoiceLabel->setText(model.getCurrentQuestions()[0].first);
    ui->rightChoiceLabel->setText(model.getCurrentQuestions()[0].second);
}

void MotivationReliefQuizWindow::resetQuiz()
{
    switchToValueMode();
}
