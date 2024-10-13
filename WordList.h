#pragma once

#include <string>

#include "Word.h"


struct WordList {
    Word* word;
    WordList* pNext = nullptr;
};


bool AddWord(WordList*& wordList, Word* word);

bool DeleteWord(WordList*& wordList, const QString& spanishWord);

Word* FindWord(WordList*& wordList, const QString& spanishWord);

WordList* GetTopicWords(WordList*& wordList, const QString& topic);

void OutputWordList(WordList*& wordList, const bool = true);

bool WriteData(WordList*& wordList, const QString& filename);

WordList* ReadData(const QString& filename);

WordList* InsertSortedWordList(WordList*& wordList, WordList* pNew);

WordList* SortedWordList(WordList*& wordList);

WordList* SortedMerge(WordList*& a, WordList*& b, const bool byTopic);

void SplitList(WordList*& source, WordList*& frontRef, WordList*& backRef, const bool myTopic);

void MergeSort(WordList*& wordList, const bool byTopic = false);

void EraseList(WordList*& wordList);
