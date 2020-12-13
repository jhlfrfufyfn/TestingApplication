#pragma once

#include <QWidget>

#include "ui_Instruction.h"

class InstructionWindow : public QWidget
{
    Q_OBJECT
public:
    explicit InstructionWindow(QWidget *parent = nullptr);
    Ui::Instruction* getUi()const;

public slots:
    void setInstructionLabel(const QString& text);

private:
    Ui::Instruction* ui;

};

