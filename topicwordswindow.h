#ifndef TOPICWORDSWINDOW_H
#define TOPICWORDSWINDOW_H

#include <QWidget>
#include <QListWidgetItem>

#include "mainwindow.h"

class MainWindow;  // Forward declaration

namespace Ui {
class TopicWordsWindow;
}

class TopicWordsWindow : public QWidget
{
    Q_OBJECT

public:
    QString topic;

    explicit TopicWordsWindow(MainWindow* mainWindow, QWidget *parent = nullptr);
    ~TopicWordsWindow();

    void AddWord(const QString& word);

    void SetTitle(const QString& title);

    void SetList(WordList*& wordList);

    void SetListByTopic(const QString& topic);

    void SetTopic(const QString& topic);

private slots:
    void on_topicWordsList_itemClicked(QListWidgetItem *item);

private:
    Ui::TopicWordsWindow *ui;
    MainWindow* mainWindow;
};

#endif // TOPICWORDSWINDOW_H
