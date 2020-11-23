#ifndef QUIZRESULT_H
#define QUIZRESULT_H

#include <QObject>

#include <unordered_map>
#include <vector>

class MotivationReliefQuizResult: public QObject
{
    Q_OBJECT
public:
    MotivationReliefQuizResult(QObject *parent = nullptr);

    std::vector<std::unordered_map<QString, int> > resultsValue;
    std::vector<std::unordered_map<QString, int> > resultsAccess;

public slots:
    void integrateResultsValue(int index,const std::vector<QString>& chosen);
    void integrateResultsAccess(int index,const std::vector<QString>& chosen);
};

#endif // QUIZRESULT_H
