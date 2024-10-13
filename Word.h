#pragma once

#include <string>
#include <QString>

extern const std::wstring wordFieldNames[5];

// n
// ? ?
// a e i o u u

struct Word {
    QString spanish_word;       // слово на испанском языке
    QString russian_translation; // перевод на русский язык
    QString example_sentence;    // пример использования в предложении на испанском языке
    QString example_translation; // перевод примера использования на русский язык
    QString topic;               // тема слова
};

Word* InputWord();

bool EditWord(Word* word, const QString& fieldName,
    const QString& newValue);

void OutputWord(Word* word, const bool = true);
