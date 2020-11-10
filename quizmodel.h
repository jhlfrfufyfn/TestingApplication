#ifndef QUIZMODEL_H
#define QUIZMODEL_H

#include <QObject>

#include <vector>
#include <utility>
#include <set>

class QuizModel
{
public:
    QuizModel();

    void nextModel();

    bool hasModelEnded()const;

    int getCurrentModel()const;

    std::vector<std::pair<QString,QString> > getCurrentQuestions()const;

public slots:
    void setNotUsedQuizQuestions(int size, const std::vector<QString>& values);
private:
    int currentModel = 0;

    std::set<std::pair<int,int> > used;

    std::vector<std::pair<QString,QString> > currentQuestions;

public:
    const int MODEL_SIZE_LIMIT = 4;

};

#endif // QUIZMODEL_H
