#include <unordered_map>

#include <QObject>
#include <QPushButton>

#include "ui_quizwindow.h"
#include "quizwindow.h"
#include "constants.h"

QuizWindow::QuizWindow(QWidget *parent):
    QWidget(parent)
  , ui(new Ui::QuizWindow)
  , model(QuizModel())
{
    ui->setupUi(this);
    setWindowState(Qt::WindowFullScreen);

    QObject::connect(ui->pushButton,&QPushButton::clicked, this, &QuizWindow::changeWindow);
}

void QuizWindow::changeWindow()
{
    bool modelEnded = model.hasModelEnded();
    bool allEnded = modelEnded && (model.getCurrentModel() == model.MODEL_SIZE_LIMIT - 1);

    if(modelEnded){
        model.nextModel();
    }

    model.setNotUsedQuizQuestions(QUIZ_VALUES_SIZE, QUIZ_VALUES_NAMES[model.getCurrentModel()]);

    if(allEnded) {
        emit goToNextMode();
    }
}
