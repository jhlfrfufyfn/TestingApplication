#include "instructionwindow.h"

InstructionWindow::InstructionWindow(QWidget *parent) :
    QWidget(parent)
  , ui(new Ui::Instruction)
{
    ui->setupUi(this);
}

Ui::Instruction *InstructionWindow::getUi() const
{
    return ui;
}

void InstructionWindow::setInstructionLabel(const QString &text)
{
    ui->label_2->setText(text);
}
