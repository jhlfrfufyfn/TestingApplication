#include <QObject>
#include <QPushButton>

#include "quizwindow.h"
#include "constants.h"

QuizWindow::QuizWindow(QWidget *parent):
    QWidget(parent)
    , ui(new Ui::QuizWindow)
    , model(QuizModel())
{
    ui->setupUi(this);

    updateRadioButtonNames();

    QObject::connect(ui->pushButton,&QPushButton::clicked, this, &QuizWindow::changeWindow);
}

void QuizWindow::changeWindow()
{
    if(!allRadioGroupsChecked()){
        return ;
    }

    if(model.hasModelEnded()){
        model.nextModel();
    }

    ///TODO: get statistics to user's quiz results

    model.setNotUsedQuizQuestions(Constants::QUIZ_VALUES_SIZE, Constants::QUIZ_VALUES_NAMES[model.getCurrentModel()]);
    uncheckAllRadioGroups();

    updateRadioButtonNames();
}

void QuizWindow::updateRadioButtonNames()
{
    std::vector<std::pair<QString, QString> > questions = model.getCurrentQuestions();

    ui->LeftPoint1->setText(questions[0].first);
    ui->RightPoint1->setText(questions[0].second);

    ui->LeftPoint2->setText(questions[1].first);
    ui->RightPoint2->setText(questions[1].second);

    ui->LeftPoint3->setText(questions[2].first);
    ui->RightPoint3->setText(questions[2].second);

    ui->LeftPoint4->setText(questions[3].first);
    ui->RightPoint4->setText(questions[3].second);

    ui->LeftPoint5->setText(questions[4].first);
    ui->RightPoint5->setText(questions[4].second);

    ui->LeftPoint6->setText(questions[5].first);
    ui->RightPoint6->setText(questions[5].second);

    ui->LeftPoint7->setText(questions[6].first);
    ui->RightPoint7->setText(questions[6].second);
}

bool QuizWindow::allRadioGroupsChecked() const
{
    if(ui->buttonGroup_1->checkedButton()==nullptr){
        return false;
    }
    if(ui->buttonGroup_2->checkedButton()==nullptr){
        return false;
    }
    if(ui->buttonGroup_3->checkedButton()==nullptr){
        return false;
    }
    if(ui->buttonGroup_4->checkedButton()==nullptr){
        return false;
    }
    if(ui->buttonGroup_5->checkedButton()==nullptr){
        return false;
    }
    if(ui->buttonGroup_6->checkedButton()==nullptr){
        return false;
    }
    if(ui->buttonGroup_7->checkedButton()==nullptr){
        return false;
    }
    return true;
}

void QuizWindow::uncheckAllRadioGroups()
{
    QAbstractButton *button = ui->buttonGroup_1->checkedButton();
    ui->buttonGroup_1->setExclusive(false);
    button->setChecked(false);
    ui->buttonGroup_1->setExclusive(true);

    ui->buttonGroup_2->setExclusive(false);
    button = ui->buttonGroup_2->checkedButton();
    button->setChecked(false);
    ui->buttonGroup_2->setExclusive(true);

    ui->buttonGroup_3->setExclusive(false);
    button = ui->buttonGroup_3->checkedButton();
    button->setChecked(false);
    ui->buttonGroup_3->setExclusive(true);

    ui->buttonGroup_4->setExclusive(false);
    button = ui->buttonGroup_4->checkedButton();
    button->setChecked(false);
    ui->buttonGroup_4->setExclusive(true);

    ui->buttonGroup_5->setExclusive(false);
    button = ui->buttonGroup_5->checkedButton();
    button->setChecked(false);
    ui->buttonGroup_5->setExclusive(true);

    ui->buttonGroup_6->setExclusive(false);
    button = ui->buttonGroup_6->checkedButton();
    button->setChecked(false);
    ui->buttonGroup_6->setExclusive(true);

    ui->buttonGroup_7->setExclusive(false);
    button = ui->buttonGroup_7->checkedButton();
    button->setChecked(false);
    ui->buttonGroup_7->setExclusive(true);
}
