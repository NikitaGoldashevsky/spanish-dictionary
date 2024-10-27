#include "topicwordswindow.h"
#include "ui_topicwordswindow.h"
#include "WordList.h"

TopicWordsWindow::TopicWordsWindow(MainWindow* mainWindow, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TopicWordsWindow)
{
    ui->setupUi(this);
    this->mainWindow = mainWindow;
}

TopicWordsWindow::~TopicWordsWindow()
{
    delete ui;
}

void TopicWordsWindow::AddWord(const QString& word) {
    ui->topicWordsList->addItem(word);
}

void TopicWordsWindow::on_topicWordsList_itemClicked(QListWidgetItem *item) {
    Word* word = FindWord(this->mainWindow->list, item->text());
    qDebug() << word->spanish_word;
    this->mainWindow->SetCurrentWordLabels(word);
}

void TopicWordsWindow::SetTitle(const QString& title) {
    this->setWindowTitle(title);
}

void TopicWordsWindow::SetList(WordList*& wordList) {
    ui->topicWordsList->clear();
    WordList* pCur = wordList;
    while (pCur) {
        this->AddWord(pCur->word->spanish_word);
        pCur = pCur->pNext;
    }
}

void TopicWordsWindow::SetListByTopic(const QString& topic){
    WordList* topicWordsList = GetTopicWords(this->mainWindow->list, topic);
    SetList(topicWordsList);
}

void TopicWordsWindow::SetTopic(const QString& topic) {
    this->topic = topic;
}
