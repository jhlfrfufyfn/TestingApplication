#include "quizresult.h"
#include "constants.h"

QuizResult::QuizResult(QObject *parent):QObject(parent)
{
    results.resize(QUIZ_VALUES_NAMES.size());
}

void QuizResult::integrateResults(int index, const QString& chosen)
{
    results[index][chosen]++;
}
