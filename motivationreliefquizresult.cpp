#include "motivationreliefquizresult.h"
#include "constants.h"


MotivationReliefQuizResult::MotivationReliefQuizResult(QObject *parent):QObject(parent)
{
    resultsValue.resize(QUIZ_VALUES_NAMES.size());
    resultsAccess.resize(QUIZ_VALUES_NAMES.size());
}

void MotivationReliefQuizResult::clear()
{
    resultsAccess.clear();
    resultsValue.clear();
    resultsAccess.resize(QUIZ_VALUES_NAMES.size());
    resultsValue.resize(QUIZ_VALUES_NAMES.size());
}

void MotivationReliefQuizResult::readFromJson(const QJsonObject &json)
{
    if(json.contains("value")&&json["value"].isArray()){
        auto valueMap = json["value"].toArray();
        for(int index = 0;index < (int)QUIZ_VALUES_NAMES.size();index++) {
            const auto& vector = QUIZ_VALUES_NAMES[index];
            for(const auto& str: vector){
                if(valueMap.at(index).toObject().contains(str)){
                    resultsValue[index][str] = valueMap.at(index).toObject()[str].toInt();
                }
            }
        }
    }

    if(json.contains("access")&&json["access"].isArray()){
        auto valueMap = json["access"].toArray();

        for(int index = 0;index < (int)QUIZ_VALUES_NAMES.size();index++) {
            const auto& vector = QUIZ_VALUES_NAMES[index];
            for(const auto& str: vector){
                if(valueMap.at(index).toObject().contains(str)){
                    resultsAccess[index][str] = valueMap.at(index).toObject()[str].toInt();
                }
            }
        }
    }
}

void MotivationReliefQuizResult::integrateResultsValue(int index, const std::vector<QString>& chosen)
{
    for(const auto &it: chosen){
        resultsValue[index][it]++;
    }
}

void MotivationReliefQuizResult::integrateResultsAccess(int index, const std::vector<QString>& chosen)
{
    for(const auto &it: chosen){
        resultsAccess[index][it]++;
    }
}

QJsonObject MotivationReliefQuizResult::saveToJsonResult()
{
    QJsonObject resultObject;

    QJsonArray valueArray;
    for(const auto& resultMap:resultsValue){
        QJsonObject currentQuaterObject;
        for(const auto& pair:resultMap){
            currentQuaterObject[pair.first] = pair.second;
        }
        valueArray.append(currentQuaterObject);
    }

    QJsonArray accessArray;
    for(const auto& resultMap:resultsAccess){
        QJsonObject currentQuaterObject;
        for(const auto& pair:resultMap){
            currentQuaterObject[pair.first] = pair.second;
        }
        accessArray.append(currentQuaterObject);
    }

    resultObject["value"] = valueArray;
    resultObject["access"] = accessArray;

    return resultObject;
}

