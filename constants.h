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

const std::vector<QString> TEST_LIST = {"Мотивационный рельеф", "Тест Люшера"};


const QString MOTIVATIONAL_RELIEF_LABEL_VALUE = "Сравните каждую пару понятий-ценностей и выберите наиболее ЗНАЧИМУЮ из каждой пары:";
const QString MOTIVATIONAL_RELIEF_LABEL_ACCESS = "Сравните каждую пару понятий-ценностей и выберите наиболее ДОСТУПНУЮ из каждой пары:";

const QString MOTIVATIONAL_RELIEF_INSTRUCTION_VALUE = "Вам будут предложены пары понятий-ценностей, сравните их по ЦЕННОСТИ и выберите из пары наиболее значимую для вас.\n\nПример: \nСамоактуализация (совершенствование) и Безопасность (защита)\n\nЕсли понятие слева более ЗНАЧИМО для вас, нажмите на клавиатуре левую стрелочку, если же понятие справа более значимо - правую стрелочку.";
const QString MOTIVATIONAL_RELIEF_INSTRUCTION_ACCESS = "Вам будут предложены пары понятий-ценностей, сравните их по ДОСТУПНОСТИ и выберите из пары наиболее значимую для вас.\n\nПример: \nСамоактуализация (совершенствование) и Безопасность (защита)\n\nЕсли понятие слева более ДОСТУПНО для вас, нажмите на клавиатуре левую стрелочку, если же понятие справа более значимо - правую стрелочку.";


const QString FOLDER_NAME = "data/";

const QString SEPARATOR_SYMBOL = ";";

enum State{MENU, CHOOSE_QUIZ, QUIZ_MOTIVATION_RELIEF, /*LUSHER_QUIZ,*/STATISTICS, END};

const int TIMER_INTERVAL = INT_MAX;

const int TIME_LIMIT_BETWEEN_PRESSES = 500;

const int DAY_HASHER = 31;

const int MONTH_HASHER = 5;

const int YEAR_HASHER = 3;

enum SaveFormat {JSON, BINARY};

const std::vector<QString> CATEGORY_NAMES = {"статусные"
                                             ,"гностические"
                                             ,"организующие"
                                             ,"гедонистические"
                                             ,"консолидирующие"
                                             ,"коммуникативные"
                                             ,"морально-этические"
                                            };
