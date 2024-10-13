#pragma once

#include <string>
#include <QString>

extern const std::wstring wordFieldNames[5];

// n
// ? ?
// a e i o u u

struct Word {
    QString spanish_word;       // ����� �� ��������� �����
    QString russian_translation; // ������� �� ������� ����
    QString example_sentence;    // ������ ������������� � ����������� �� ��������� �����
    QString example_translation; // ������� ������� ������������� �� ������� ����
    QString topic;               // ���� �����
};

Word* InputWord();

bool EditWord(Word* word, const QString& fieldName,
    const QString& newValue);

void OutputWord(Word* word, const bool = true);
