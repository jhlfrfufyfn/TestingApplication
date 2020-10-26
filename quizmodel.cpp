#include "quizmodel.h"

QuizModel::QuizModel()
{

}

std::vector<std::pair<QString, QString> > QuizModel::getQuizQuestions(const std::vector<QString> &values) const {
        std::vector<std::pair<QString,QString> > result;
        for(int i=0;i<(int)values.size();i++){
            for(int j = i+1;j<(int)values.size();j++){
                result.emplace_back(values[i],values[j]);
            }
        }
        return result;
}

