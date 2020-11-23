#include "motivationreliefquizresult.h"
#include "constants.h"

MotivationReliefQuizResult::MotivationReliefQuizResult(QObject *parent):QObject(parent)
{
    resultsValue.resize(QUIZ_VALUES_NAMES.size());
    resultsAccess.resize(QUIZ_VALUES_NAMES.size());
}

void MotivationReliefQuizResult::integrateResultsValue(int index, const std::vector<QString>& chosen)
{
    resultsValue[index][chosen[0]]++;
}

void MotivationReliefQuizResult::integrateResultsAccess(int index, const std::vector<QString>& chosen)
{
    resultsAccess[index][chosen[0]]++;
}

