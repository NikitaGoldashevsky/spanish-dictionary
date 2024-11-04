#pragma once

#include <string>
#include <qstring>
#include <iostream>
#include <fstream>
#include <string>
//#include <codecvt>


extern const int SLEEP_TIME_BETWEEN_WORDS;

extern const int SLEEP_TIME_BETWEEN_ACTIONS;



int getInt(const QString& = "", const QString& = "");

int getIntFromTo(const int, const int, const QString& = "", const QString& = "");

bool correctWord(const QString& language, const QString& input);

bool correctSentence(const QString& language, const QString& input);

QString inputSentence(const QString& language, const QString& query);

bool isQCharEnglish(const QChar ch);

bool isQCharSpanish(const QChar ch);

bool isQCharRussian(const QChar ch);

void updateLastLoadFilePath(const QString& newFilePath);
