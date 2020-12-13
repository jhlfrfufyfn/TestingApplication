#include "itomodel.h"
#include "constants.h"
ItoModel::ItoModel():
    currentQuestion(0)
{
}

bool ItoModel::hasQuizEnded() const
{
    return currentQuestion == (int)ITO_QUESTIONS.size()-1;
}

void ItoModel::goToNextQuestion()
{
    currentQuestion++;
    if(currentQuestion == (int)ITO_QUESTIONS.size()){
        currentQuestion = 0;
    }
}

void ItoModel::resetModel()
{
    currentQuestion = 0;
}

int ItoModel::getCurrentQuestionIndex() const
{
    return currentQuestion;
}

QString ItoModel::getCurrentQuestion() const
{
    return ITO_QUESTIONS[currentQuestion];
}

