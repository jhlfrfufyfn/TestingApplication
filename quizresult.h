#ifndef QUIZRESULT_H
#define QUIZRESULT_H

#include <QObject>

#include <unordered_map>

class QuizResult: public QObject
{
    Q_OBJECT
public:
    QuizResult(QObject *parent = nullptr);

    std::vector<std::unordered_map<QString, int> > results;

public slots:
    void integrateResults(int index,const QString& chosen);
};

#endif // QUIZRESULT_H
