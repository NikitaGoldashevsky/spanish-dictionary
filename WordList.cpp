#include <iostream>
#include <fstream>
#include <string>
//#include <locale>
#include <codecvt>
#include <qstring.h>
#include <sstream>
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <QDebug>
#include <QFile>
#include <QMessageBox>

#include "mainwindow.h"
#include "Wordlist.h"
#include "tools.h"


bool AddWord(WordList*& wordList, Word* word) {
    if (!wordList) {
        wordList = new WordList;
        wordList->word = word;
    }
    else {
        if (FindWord(wordList, word->spanish_word) != nullptr) {
            return false;
        }

        WordList* pCur = wordList;
        while (pCur->pNext) {
            pCur = pCur->pNext;
        }
        pCur->pNext = new WordList;
        pCur->pNext->word = word;
    }
    return true;
}

bool DeleteWord(WordList*& wordList, const QString& spanishWord) {
    WordList* pCur = wordList;

    if (pCur->word->spanish_word == spanishWord) {
        wordList = wordList->pNext;
        delete pCur;
        return true;
    }
    else {
        while (pCur->pNext) {
            if (pCur->pNext->word->spanish_word == spanishWord) {
                WordList* pAfterDeleted = pCur->pNext->pNext;
                delete pCur->pNext;
                pCur->pNext = pAfterDeleted;
                return true;
            }
            pCur = pCur->pNext;
        }
        if (pCur->word->spanish_word == spanishWord) {
            delete pCur->pNext;
            pCur->pNext = nullptr;
        }
    }
}

Word* FindWord(WordList*& wordList, const QString& spanishWord) {
    if (wordList) {
        WordList* pCur = wordList;
        while (pCur) {
            if (pCur->word->spanish_word == spanishWord) {
                return pCur->word;
            }
            pCur = pCur->pNext;
        }
    }

    return nullptr;
}

WordList* GetTopicWords(WordList*& wordList, const QString& topic) {
    WordList* topicList = nullptr;
    WordList* pCur = wordList;
    while (pCur) {
        if (pCur->word->topic == topic) {
            AddWord(topicList, pCur->word);
        }
        pCur = pCur->pNext;
    }
    return topicList;
}

bool WriteData(WordList*& wordList, const QString& filename) {

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream stream(&file);
    WordList* pCur = wordList;
    while (pCur) {
        Word* word = pCur->word;

        stream << word->spanish_word << ";";
        stream << word->russian_translation << ";";
        stream << word->example_sentence << ";";
        stream << word->example_translation << ";";
        stream << word->topic << "\n";

        pCur = pCur->pNext;
    }

    file.close();
    return true;
}

WordList* ReadData(const QString& filename) {
    QFile file(filename);
    //bool hasUnexpectedFormatLines = false;

    WordList* list = nullptr;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);

        int stringNumber = 0;
        while (!stream.atEnd()) {
            stringNumber++;
            QString line = stream.readLine();
            QStringList parts = line.split(';');

            if (parts.size() == 5) {
                QString spanishWord = parts[0].trimmed();
                QString russianTranslation = parts[1].trimmed();
                QString exampleSentence = parts[2].trimmed();
                QString exampleTranslation = parts[3].trimmed();
                QString topic = parts[4].trimmed();

                if (true) {
                    qDebug() << "Spanish Word:" << spanishWord;
                    qDebug() << "Russian Translation:" << russianTranslation;
                    qDebug() << "Example Sentence:" << exampleSentence;
                    qDebug() << "Example Translation:" << exampleTranslation;
                    qDebug() << "Topic:" << topic;
                    qDebug() << "------------------------------------";
                }

                bool added = AddWord(list, new Word {spanishWord, russianTranslation, exampleSentence, exampleTranslation, topic});
                if (!added) {
                    QString stringMessage = "";
                    stringMessage = "Повторное объявление слова " + spanishWord + " в строке под номером " + QString::number(stringNumber) + ".";
                    QMessageBox::warning(nullptr, QStringLiteral("Ошибка"),
                                         stringMessage, QMessageBox::Ok);
                }
            } else {
                QString stringMessage = "";
                stringMessage = "Некорректный формат данных в строке под номером " + QString::number(stringNumber) + ".";
                QMessageBox::warning(nullptr, QStringLiteral("Ошибка"),
                                     stringMessage, QMessageBox::Ok);
                //qDebug() << "Unexpected format in line:" << line;
            }
        }

        file.close();
    } else {
        qWarning() << "Could not open file for reading:" << file.errorString();
    }
    return list;
}

// WordList* InsertSortedWordList(WordList*& wordList, WordList* pNew) {
//     if (wordList == nullptr || wordList->word->spanish_word > pNew->word->spanish_word) {
//         //
//         pNew->pNext = wordList;
//         return pNew;
//     }
//     else {
//         //
//         WordList* pCur = wordList;
//         while (pCur->pNext != nullptr && pCur->pNext->word->spanish_word < pNew->word->spanish_word) {
//             pCur = pCur->pNext;
//         }
//         pNew->pNext = pCur->pNext;
//         pCur->pNext = pNew;
//     }
//     return wordList;
// }

// WordList* SortedWordList(WordList*& wordList) {
//     WordList* pCur = wordList;
//     WordList* sorted = nullptr;

//     while (pCur) {
//         WordList* pNext = pCur->pNext;
//         sorted = InsertSortedWordList(sorted, pCur);
//         pCur = pNext;
//     }

//     return sorted;
// }

WordList* SortedMerge(WordList*& a, WordList*& b, const bool byTopic) {
    // base cases
    if (a == nullptr)
        return b;
    if (b == nullptr) {
        return a;
    }

    // final list
    WordList* result = nullptr;

    // elements comparasion and recursive merge
    if ((a->word->spanish_word <= b->word->spanish_word) && !byTopic ||
        a->word->topic <= b->word->topic && byTopic) {
        result = a;
        result->pNext = SortedMerge(a->pNext, b, byTopic);
    }
    else {
        result = b;
        result->pNext = SortedMerge(a, b->pNext, byTopic);
    }

    return result;

}

void SplitList(WordList*& source, WordList*& frontRef, WordList*& backRef, const bool byTopic) {
    WordList* slow = source;
    WordList* fast = source->pNext;

    // Fast, slow
    while (fast != nullptr) {
        fast = fast->pNext;
        if (fast != nullptr) {
            slow = slow->pNext;
            fast = fast->pNext;
        }
    }

    // Slow                        
    frontRef = source;
    backRef = slow->pNext;
    slow->pNext = nullptr;
}

void MergeSort(WordList*& wordList, const bool byTopic) {
    WordList* head = wordList;
    WordList *a = nullptr, *b = nullptr;

    if ((head == nullptr) || (head->pNext == nullptr)) {
        return;
    }

    SplitList(head, a, b, byTopic);

    MergeSort(a, byTopic);
    MergeSort(b, byTopic);

    wordList = SortedMerge(a, b, byTopic);
}

void EraseList(WordList*& wordList) {
    WordList* pCur = wordList, *pNext;
    while (pCur) {
        qDebug() << "deleted " << pCur->word->spanish_word;
        pNext = pCur->pNext;
        delete pCur;
        pCur = pNext;
    }
}
