#pragma once
#include <QString>
#include <vector>


const std::vector<QString> QUIZ_VALUES_NAMES_1 = {"Статус (положение)","Исследование (Поиск)","Безопасность (защита)","Удовольствие (довольство)",
                                "Принадлежность (причастность)","Заметность (внимание)","Самоактуализация (совершенствование)"};
const std::vector<QString> QUIZ_VALUES_NAMES_2 = {"Признание (честь)","Познание (изучение)","Порядок (организованность)",
                                "Комфорт(удобство)","Принятие (приязнь)","Общение (контакты)","Самоактуализация"};
const std::vector<QString> QUIZ_VALUES_NAMES_3 = {"Доверие (уверенность)","Понимание (осознание)","Уважение (значимость)","Свобода (независимость)",
                                "Идентичность (соответствие себе)","Привязанность (близость)","Самоактуализация"};
const std::vector<QString> QUIZ_VALUES_NAMES_4 = {"Смысл (схватывание сути)","Власть (возможности)","Любовь","Помощь (поддержка)",
                                "Истина (правда)","Счастье (благо)","Самоактуализация"};

const std::vector<std::vector<QString> > QUIZ_VALUES_NAMES = {QUIZ_VALUES_NAMES_1,QUIZ_VALUES_NAMES_2,QUIZ_VALUES_NAMES_3,QUIZ_VALUES_NAMES_4};

const int QUIZ_VALUES_SIZE = QUIZ_VALUES_NAMES_1.size();

const QString FOLDER_NAME = "data/";

const QString SEPARATOR_SYMBOL = ";";

enum State{MENU, CHOOSE_QUIZ, QUIZ_MOTIVATION_RELIEF, /*LUSHER_QUIZ,*/ END};
