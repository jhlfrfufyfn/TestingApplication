#include <QDir>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDebug>

#include "user.h"
#include "constants.h"

User::User(const QString& aName, QObject *parent):QObject(parent), results(new QuizResult(this))
{
    this->name = aName;
}

void User::setName(const QString &name)
{
    this->name = name;
}

void User::saveToFile()
{
    QDir dir;

    if(!dir.exists(FOLDER_NAME)){
        dir.mkpath(FOLDER_NAME);
    }
    dir.cd(FOLDER_NAME);

    //int count = 1;
    QString fileName = dir.path() + "/" + this->name + ".txt";
    //qDebug() << fileName <<"\n";

    QFile newFile(fileName);
    if(!newFile.open(QIODevice::WriteOnly | QIODevice::Text)){
    //    qDebug() << "file not opened\n";
        return ;
    }

    QTextStream textStream(&newFile);

    for(size_t quizIndex = 0; quizIndex<this->results->results.size(); quizIndex++){
        for(size_t i = 0;i < QUIZ_VALUES_NAMES[quizIndex].size(); i++) {
            textStream << this->results->results[quizIndex][QUIZ_VALUES_NAMES[quizIndex][i]] << SEPARATOR_SYMBOL;
      //      qDebug() << this->results->results[quizIndex][QUIZ_VALUES_NAMES[quizIndex][i]] << SEPARATOR_SYMBOL;
        }
        textStream << "\n";
    }
    results->results.clear();
    results->results.resize(QUIZ_VALUES_NAMES.size());
}
