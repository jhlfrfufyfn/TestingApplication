#include "itoresult.h"
#include <QJsonArray>
ItoResult::ItoResult(QObject *parent) : QObject(parent)
{

}

void ItoResult::clear()
{
    answers.clear();
    keyMap.clear();
}

void ItoResult::readFromJson(const QJsonObject &object)
{
    for(int i = 0;i<(int)ITO_CATEGORIES.size();i++){
        if(object.contains(ITO_CATEGORIES[i])){
            keyMap[ITO_CATEGORIES[i]] = object[ITO_CATEGORIES[i]].toInt();
        }
    }
}

void ItoResult::integrateResults(bool isLeft)
{
    answers.push_back(isLeft);
}

QJsonObject ItoResult::saveToJsonResult()
{
    QJsonObject resultObject;

    if(!answers.empty()){
        setKeyMap();
    }
    for(const auto& resultPair:keyMap){
        resultObject[resultPair.first] = resultPair.second;
    }

    return resultObject;
}

void ItoResult::setKeyMap()
{
    keyMap.clear();
    for(int i = 0;i<(int)ITO_CATEGORIES.size();i++){
        keyMap[ITO_CATEGORIES[i]] = 0;
    }
    for(int i = 0;i<(int)ITO_CATEGORIES.size();i++){
        for(int j = 0;j<(int)ITO_KEY_CATEGORY_INDEXES_TRUE[i].size();j++){
            if(answers[ITO_KEY_CATEGORY_INDEXES_TRUE[i][j]-1] == true){
                keyMap[ITO_CATEGORIES[i]]++;
            }
        }for(int j = 0;j<(int)ITO_KEY_CATEGORY_INDEXES_FALSE[i].size();j++){
            if(answers[ITO_KEY_CATEGORY_INDEXES_FALSE[i][j]-1] == false){
                keyMap[ITO_CATEGORIES[i]]++;
            }
        }
    }
}
