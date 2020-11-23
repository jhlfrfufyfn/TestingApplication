#include "motivationreliefquizmodel.h"
#include <random>
#include <chrono>

#include "constants.h"

MotivationReliefQuizModel::MotivationReliefQuizModel()
{
    setNotUsedQuizQuestions(1, QUIZ_VALUES_NAMES[currentModel]);
}

///returns vector of not used questions with fixed size
void MotivationReliefQuizModel::setNotUsedQuizQuestions(int size, const std::vector<QString> &values) {

    std::vector<std::pair<QString,QString> > notUsedPairs;
    std::vector<std::pair<int,int> > notUsedPairsIndex;
    for(int i=0;i<(int)values.size();i++){
        for(int j = i+1;j<(int)values.size();j++){
            if(used.find({i,j}) == used.end()){
                notUsedPairs.emplace_back(values[i],values[j]);
                notUsedPairsIndex.emplace_back(i,j);
            }
        }
    }

    int limit = notUsedPairs.size();

    std::mt19937 generator(std::chrono::steady_clock::now().time_since_epoch().count());
    std::vector<int> randomIndexes;
    for(int i=0;i<size;i++){
        int newRandom = generator()%limit;
        while(find(randomIndexes.begin(),randomIndexes.end(),newRandom)!=randomIndexes.end()){
            newRandom = generator()%limit;
        }
        randomIndexes.push_back(newRandom);
    }

    std::vector<std::pair<QString,QString> > result;
    for(const auto& it:randomIndexes){
        int randomOrder = generator()%2;
        if(randomOrder){
            result.push_back(notUsedPairs[it]);
            used.insert({notUsedPairsIndex[it].first, notUsedPairsIndex[it].second});
        }
        else{
            result.push_back({notUsedPairs[it].second, notUsedPairs[it].first});
            used.insert({notUsedPairsIndex[it].first, notUsedPairsIndex[it].second});
        }
    }

    currentQuestions = result;
}

void MotivationReliefQuizModel::nextModel()
{
    used.clear();
    currentModel++;
    if(currentModel >= MODEL_SIZE_LIMIT){
        currentModel = 0;
    }
}

bool MotivationReliefQuizModel::hasModelEnded() const
{
    if((int)used.size() == (QUIZ_VALUES_SIZE*(QUIZ_VALUES_SIZE-1))/2){
        return true;
    }
    return false;
}

int MotivationReliefQuizModel::getCurrentModel() const
{
    return currentModel;
}

std::vector<std::pair<QString, QString> > MotivationReliefQuizModel::getCurrentQuestions() const
{
    return currentQuestions;
}

