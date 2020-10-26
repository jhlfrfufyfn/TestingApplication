#include "quizwindow.h"

QuizWindow::QuizWindow(QWidget *parent):
    QWidget(parent)
    , ui(new Ui::QuizWindow)
{
    ui->setupUi(this);
}
