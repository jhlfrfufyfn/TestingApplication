#include <QDir>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QJsonDocument>
#include <QCborValue>
#include <QCborMap>
#include <QDate>

#include "user.h"
#include "constants.h"


User::User():
    surName("")
  , name("")
  , secondName("")
  , birthDate()
  , mrResults(new MotivationReliefQuizResult(this))
  , itoResults(new ItoResult(this))
{

}

User::User(const QString &psurName, const QString &pname, const QString &psecondName, const QDate &pdate, QObject *parent):
    QObject(parent)
  , mrResults(new MotivationReliefQuizResult(this))
  , itoResults(new ItoResult(this))
  , surName(psurName)
  , name(pname)
  , secondName(psecondName)
  , birthDate(pdate)
{

}

void User::copy(User *user)
{
    resetInfo(user->surName, user->name, user->secondName,user->birthDate);
    mrResults->resultsValue = user->mrResults->resultsValue;
    mrResults->resultsAccess = user->mrResults->resultsAccess;
    itoResults->keyMap = user->itoResults->keyMap;
}

void User::resetInfo(const QString &surName, const QString &name, const QString &secondName, const QDate &date)
{
    this -> surName = surName;
    this -> name = name;
    this -> secondName = secondName;
    this -> birthDate = date;
}

QString User::getSurname() const
{
    return surName;
}

QString User::getName() const
{
    return name;
}

QString User::getSecondName() const
{
    return secondName;
}

void User::createAllUsersDataTable()
{
    QDir directory("data");
    QStringList users = directory.entryList(QStringList() << "*.txt", QDir::Files);
    QFile usersDt("data/users.txt");
    usersDt.open(QIODevice::WriteOnly|QIODevice::Truncate);
    QJsonArray usersJson;
    foreach(QString filename, users) {
        filename = "data/"+filename;
        QFile file(filename);
        file.open(QIODevice::ReadOnly);
        QByteArray saveData = file.readAll();

        QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
        QJsonObject json = loadDoc.object();

        if(json.contains("name")&&json.contains("surName")&&json.contains("secondName")&&json.contains("birthDate")) {
            QJsonObject userObject;
            userObject["name"] = json["name"];
            userObject["surName"] = json["surName"];
            userObject["secondName"] = json["secondName"];
            userObject["birthDate"] = json["birthDate"];
            usersJson.push_back(userObject);
        }
    }
    usersDt.write(QJsonDocument(usersJson).toJson(QJsonDocument::Indented));
}

QStringList User::getUserList()
{
    QFile usersDt("data/users.txt");
    usersDt.open(QIODevice::ReadOnly);
    QByteArray saveData = usersDt.readAll();
    QJsonArray usersJson = QJsonDocument::fromJson(saveData).array();

    QStringList ans;
    for(auto it:usersJson){
        QJsonObject obj = it.toObject();
        ans.push_back(obj["surName"].toString()+" "+obj["name"].toString()+" "+obj["secondName"].toString()+" \""+obj["birthDate"].toString() + "\"");
    }
    return ans;
}

void User::clearTestResults()
{
    mrResults->clear();
}

void User::saveToFile()
{
    QJsonObject userJson;
    userPersonalInfoToJson(userJson);

    QJsonObject mqResult = mrResults->saveToJsonResult();
    userJson["mqResult"] = mqResult;

    QJsonObject itoResult = itoResults->saveToJsonResult();
    userJson["itoResult"] = itoResult;

    QDir dir;
    if(!dir.exists(FOLDER_NAME)){
        dir.mkpath(FOLDER_NAME);
    }
    dir.cd(FOLDER_NAME);

    QString fileName = dir.path() + "/" + this->surName + this->name + this->secondName
                     + QString::number(this->birthDate.day()) + QString::number(this->birthDate.month()) + QString::number(this->birthDate.year());

    QString extension = ".txt";

    fileName = fileName + extension;

    QFile newFile(fileName);
    if(!newFile.open(QIODevice::WriteOnly | QIODevice::Text|QIODevice::Truncate)){
        return ;
    }

    newFile.write(QJsonDocument(userJson).toJson(QJsonDocument::Indented));
}

User* User::loadFromFile(const QString& fileName)
{
    User *ans = new User("","","",QDate());
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);

    QByteArray savedData = file.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(savedData));

    ans->readUserInfoFromJson(loadDoc.object());

    QJsonObject mqResult = loadDoc.object()["mqResult"].toObject();
    QJsonObject itoResult = loadDoc.object()["itoObject"].toObject();

    ans->mrResults->readFromJson(mqResult);
    ans->itoResults->readFromJson(itoResult);

    return ans;
}

void User::readUserInfoFromJson(const QJsonObject& json){
    if(json.contains("name")){
        name = json["name"].toString();
    }
    if(json.contains("surName")){
        surName = json["surName"].toString();
    }
    if(json.contains("secondName")){
        secondName = json["secondName"].toString();
    }
    if(json.contains("birthDate")){
        birthDate = QDate::fromString(json["birthDate"].toString(),Qt::DateFormat::TextDate);
    }
    if(json.contains("mqResult") && json["mqResult"].isObject()){
        mrResults->clear();
        mrResults->readFromJson(json["mqResult"].toObject());
    }
    if(json.contains("itoResult")){
        itoResults->clear();
        itoResults->readFromJson(json["itoResult"].toObject());
    }
}

void User::userPersonalInfoToJson(QJsonObject &obj)
{
    obj["name"] = name;
    obj["surName"] = surName;
    obj["secondName"] = secondName;
    obj["birthDate"] = birthDate.toString(Qt::DateFormat::TextDate);
}








