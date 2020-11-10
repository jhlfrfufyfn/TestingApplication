#include <unordered_map>

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

std::vector<QString> QuizWindow::getWindowResult() const
{
    std::vector<QString> result;
    std::vector<std::pair<QString, QString> > curQuestions = this->model.getCurrentQuestions();
    if(ui->LeftPoint1->isChecked()){
        result.push_back(curQuestions[0].first);
    }
    else{
        result.push_back(curQuestions[0].second);
    }
    if(ui->LeftPoint2->isChecked()){
        result.push_back(curQuestions[1].first);
    }
    else{
        result.push_back(curQuestions[1].second);
    }
    if(ui->LeftPoint3->isChecked()){
        result.push_back(curQuestions[2].first);
    }
    else{
        result.push_back(curQuestions[2].second);
    }
    if(ui->LeftPoint4->isChecked()){
        result.push_back(curQuestions[3].first);
    }
    else{
        result.push_back(curQuestions[3].second);
    }
    if(ui->LeftPoint5->isChecked()){
        result.push_back(curQuestions[4].first);
    }
    else{
        result.push_back(curQuestions[4].second);
    }
    if(ui->LeftPoint6->isChecked()){
        result.push_back(curQuestions[5].first);
    }
    else{
        result.push_back(curQuestions[5].second);
    }
    if(ui->LeftPoint7->isChecked()){
        result.push_back(curQuestions[6].first);
    }
    else{
        result.push_back(curQuestions[6].second);
    }
    return result;
}

void QuizWindow::changeWindow()
{
    if(!allRadioGroupsChecked()){
        return ;
    }

    bool modelEnded = model.hasModelEnded();
    bool allEnded = modelEnded && (model.getCurrentModel() == model.MODEL_SIZE_LIMIT - 1);

    emit sendWindowResults(model.getCurrentModel(), getWindowResult());
    uncheckAllRadioGroups();

    if(modelEnded){
        model.nextModel();
    }

    model.setNotUsedQuizQuestions(QUIZ_VALUES_SIZE, QUIZ_VALUES_NAMES[model.getCurrentModel()]);
    updateRadioButtonNames();

    if(allEnded) {
        emit goToNextMode();
    }
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
