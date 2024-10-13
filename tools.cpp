﻿#include <string>
#include <iostream>
#include <fstream>
//#include <locale>
#include <codecvt>
#include <sstream>
#include <cwctype>
#include <QDebug>
#include <QFile>

#include "tools.h"

//int getInt(const std::wstring& query, const std::wstring& incorrectMessage) {
//	std::wcout << query;
//	int res;
//	std::cin >> res;
//	while (!std::cin.good()) {
//		std::cin.clear();
//		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//		std::wcout << incorrectMessage << std::endl << std::endl;
//		std::wcout << query;
//		std::cin >> res;
//	}
//	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//	//std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
//	return res;
//}

extern const int SLEEP_TIME_BETWEEN_WORDS = 100;

extern const int SLEEP_TIME_BETWEEN_ACTIONS = 500;


int getInt(const QString& query, const QString& incorrectMessage) {
    int number;
    std::wstring input;

    while (true) {
        //std::wcout << query;
        std::getline(std::wcin, input);  //                     

        std::wstringstream wss(input);  //                                         
        if (wss >> number && wss.eof()) {
            //                                                       ,                      
            break;
        }
        //std::wcout << incorrectMessage << std::endl << std::endl;
    }
    return number;
}


int getIntFromTo(const int n1, const int n2, const QString& query, const QString& incorrectMessage) {
	int res;
	while (true) {
		res = getInt(query, incorrectMessage);
		if (res < n1 || res > n2) {
            //std::wcout << incorrectMessage << std::endl << std::endl;
		}
		else {
			break;
		}
	}
	return res;
}


bool correctWord(const QString& language, const QString& input) {
    QString word;

    QString tempInput = input;  // Create a non-const copy
    QTextStream stream(&tempInput);
      // Use QTextStream to handle QString input

    bool correct = true;

    // Read the word from the QTextStream and check if it is the only one
    stream >> word;
    if (!word.isEmpty() && stream.atEnd()) {
        for (const QChar& ch : word) {
            if ((language == "spanish" && !isQCharSpanish(ch)) ||
                (language == "russian" && !isQCharRussian(ch))) {
                correct = false;
                break;
            }
        }
    } else {
        correct = false;
    }

    return correct;
}


bool correctSentence(const QString& language, const QString& input) {
    QString tempInput = input;
    QTextStream stream(&tempInput);

    bool correct = true;

    return correct;

    // std::QChar ch;
    // while ((ch = stream.read) != WEOF) {

    //     if (ch == L' ' || ch == L'.' || ch == L',') {
    //         continue;
    //     }
    //     if (language == "spanish" && !isQCharSpanish(ch) ||
    //         language == "russian" && !isQCharRussian(ch)) {
    //         correct = false;
    //         break;
    //     }
    // }

    // return correct;
}

bool isQCharEnglish(const QChar ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}
// ñ
// ¿ ¡
// á é í ó ú ü

bool isQCharSpanish(const QChar ch) {
    QString spanishUniqueSymbols("ñÑ¿¡áéíóúü");
    for (const QChar sym : spanishUniqueSymbols) {
        if (sym == ch || isQCharEnglish(ch)) {
            return true;
        }
    }
    return isQCharEnglish(ch);// || ch == L'ñ' || ch == L'Ñ' || ch == L'¿';  //
}

bool isQCharRussian(const QChar ch) {
    return (ch >= QChar(0x0410) && ch <= QChar(0x042F)) || // Uppercase А-Я
           (ch >= QChar(0x0430) && ch <= QChar(0x044F)); // Lowercase а-я
}

void UpdateLastLoadFilePath(const QString& newFilePath) {
    QFile file("lastLoadFilePath.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for writing:" << file.errorString();
        return;
    }

    QTextStream out(&file);
    out << newFilePath;
    file.close();
}