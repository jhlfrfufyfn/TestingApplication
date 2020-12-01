#ifndef USER_H
#define USER_H

#include <QString>
#include <QDate>

#include <unordered_map>

#include "constants.h"
#include "motivationreliefquizresult.h"

class User:public QObject
{
    Q_OBJECT
public:
    User(const QString& surName, const QString& name, const QString& secondName,const QDate& date, QObject *parent = nullptr);

    void resetInfo(const QString& surName, const QString& name, const QString& secondName, const QDate& date);
    QString getSurname()const;
    QString getName()const;
    QString getSecondName()const;

    static QStringList getUserList();

    void clearTestResults();

public slots:
    void saveToFile();
    void loadFromFile(const QString&, SaveFormat);
    static void createAllUsersDataTable();

private:
    void userPersonalInfoToJson(QJsonObject& obj);
    void readUserInfoFromJson(const QJsonObject& obj);

public:
    MotivationReliefQuizResult *mrResults;
private:
    QString surName;
    QString name;
    QString secondName;
    QDate birthDate;
};

#endif // USER_H
