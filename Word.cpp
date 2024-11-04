#include <iostream>
#define NOMINMAX
#include <windows.h>

#include "Word.h"
#include "WordList.h"
#include "tools.h"

const std::wstring wordFieldNames[5]{
    L"Слово", L"Перевод", L"Пример", L"Перевод примера", L"Тема"
};

bool EditWord(Word* word, const QString& fieldName,
    const QString& newValue) {
    if (fieldName == QString("Слово")) {
        if (!correctWord("spanish", newValue)) {
            return false;
        }
		word->spanish_word = newValue;
	}
    else if (fieldName == QString("Перевод")) {
        if (!correctWord("russian", newValue)) {
            return false;
        }
		word->russian_translation = newValue;
	}
    else if (fieldName == QString("Пример")) {
        if (!correctSentence("spanish", newValue)) {
            return false;
        }
		word->example_sentence = newValue;
	}
    else if (fieldName == QString("Перевод примера")) {
        if (!correctSentence("russian", newValue)) {
            return false;
        }
		word->example_translation = newValue;
	}
    else if (fieldName == QString("Тема")) {
        if (!correctWord("russian", newValue
                         )) {
            return false;
        }
		word->topic = newValue;
	}
    return true;
}
