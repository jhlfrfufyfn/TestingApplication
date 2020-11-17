#include "motivationreliefquizresult.h"
#include "constants.h"

MotivationReliefQuizResult::MotivationReliefQuizResult(QObject *parent):QObject(parent)
{
    results.resize(QUIZ_VALUES_NAMES.size());
}

void MotivationReliefQuizResult::integrateResults(int index, const std::vector<QString>& chosen)
{
    results[index][chosen[0]]++;
}
