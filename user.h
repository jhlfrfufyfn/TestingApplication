#ifndef USER_H
#define USER_H

#include <QString>

#include "motivationreliefquizresult.h"

#include <QDate>
#include <unordered_map>

class User:public QObject
{
    Q_OBJECT
public:
    User(const QString& surName, const QString& name, const QString& secondName,const QDate& date, QObject *parent = nullptr);

    void setInfo(const QString& surName, const QString& name, const QString& secondName, const QDate& date);
    QString getSurname()const;
    QString getName()const;
    QString getSecondName()const;

public slots:
    void saveToFile();

public:
    MotivationReliefQuizResult *results;
private:
    QString surName;
    QString name;
    QString secondName;
    QDate birthDate;
};

#endif // USER_H
