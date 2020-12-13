#ifndef ITORESULT_H
#define ITORESULT_H

#include <vector>

#include <QJsonObject>
#include <QObject>

#include "constants.h"

class ItoResult : public QObject
{
    Q_OBJECT
public:
    ItoResult(QObject *parent = nullptr);
    void clear();
    void readFromJson(const QJsonObject& object);
    std::map<QString, int> keyMap;

public slots:
    void integrateResults(bool isLeft);
    QJsonObject saveToJsonResult();
private:
    void setKeyMap();
private:
    std::vector<bool> answers;

};

#endif // ITORESULT_H
