#ifndef ITOMODEL_H
#define ITOMODEL_H

#include <QString>

class ItoModel
{
public:
    ItoModel();

    bool hasQuizEnded()const;
    void goToNextQuestion();

    void resetModel();

    int getCurrentQuestionIndex()const;
    QString getCurrentQuestion()const;

private:
    int currentQuestion = 0;

};

#endif // ITOMODEL_H
