#include "itoquizwindow.h"
#include "ui_itoquizwindow.h"

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

ItoQuizWindow::ItoQuizWindow(QWidget *parent):
    QWidget(parent)
  , ui(new Ui::ItoQuizWindow)
  , model(ItoModel())
  , stackedWidget(new QStackedWidget(this))
  , timer(new QTimer(this))
  , timeOfLastKeyPressMsec(0)
{
    timer->setTimerType(Qt::VeryCoarseTimer);
    timer->start(TIMER_INTERVAL);
    setLayout(stackedWidget->layout());
    InstructionWindow* instWindow = new InstructionWindow(stackedWidget);
    instWindow->resize(this->size());
    stackedWidget->addWidget(instWindow);
    connect(this, &ItoQuizWindow::sendInstructionShown, instWindow, &InstructionWindow::setInstructionLabel);

    connect(instWindow->getUi()->pushButton, &QPushButton::pressed, this, &ItoQuizWindow::loadTestLayout);

    QWidget* testWidget = new QWidget(stackedWidget);
    ui->setupUi(testWidget);
    testWidget->resize(this->size());
    stackedWidget->addWidget(testWidget);

    updateUiQuestionLabel();

    ui->leftChoiceLabel->setText("Верно");
    ui->rightChoiceLabel->setText("Неверно");

    showInstruction();

}

void ItoQuizWindow::showInstruction()
{
    const QString& labelText = ITO_INSTRUCTION;
    emit sendInstructionShown(labelText);
    stackedWidget->setCurrentIndex(0);
}

void ItoQuizWindow::goToNextQuizQuestion()
{
    bool quizEnded = model.hasQuizEnded();

    model.goToNextQuestion();
    if(!quizEnded){
        updateUiQuestionLabel();
    }

    if(quizEnded){
        resetQuiz();
        emit sendQuizEnded();
        return ;
    }
}


void ItoQuizWindow::keyPressEvent(QKeyEvent *event)
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
            msgBox.exec();
        }
        timeOfLastKeyPressMsec = currentTime;
    }
    if(event->key() == Qt::Key::Key_Left){
        emit sendWindowResults(true);
        goToNextQuizQuestion();
    }
    else if(event->key() == Qt::Key::Key_Right){
        emit sendWindowResults(false);
        goToNextQuizQuestion();
    }
}


void ItoQuizWindow::loadTestLayout()
{
    stackedWidget->setCurrentIndex(1);
}


void ItoQuizWindow::updateUiQuestionLabel()
{
    ui->label->setText(model.getCurrentQuestion());
}

void ItoQuizWindow::resetQuiz()
{
    model.resetModel();
    updateUiQuestionLabel();
    showInstruction();
}

