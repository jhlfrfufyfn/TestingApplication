#ifndef USER_H
#define USER_H

#include <QString>

#include "quizresult.h"

#include <unordered_map>

class User:public QObject
{
    Q_OBJECT
public:
    User(const QString& name, QObject *parent = nullptr);

    void setName(const QString &name);

public slots:
    void saveToFile();

public:
    QuizResult *results;
private:
    QString name;
};

#endif // USER_H
