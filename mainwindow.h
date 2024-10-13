#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>

#include "NewWordInputDialog.h"
#include "WordList.h"
#include "topicwordswindow.h"

class TopicWordsWindow;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    WordList* GetTopicWordslist;
    TopicWordsWindow* topicWordsWindow;
    WordList* list = nullptr;

    void SetCurrentWordLabels(Word* word);

private slots:
    void on_WordsListWidget_itemClicked(QListWidgetItem *item);

    void on_menuOptionLoadData_triggered();

    void on_menuOptionSaveData_triggered();

    void on_menuOptionAddWord_triggered();

    void on_menuOptionSortData_triggered();

    void on_menuOptionDeleteWord_triggered();

    void on_menuOptionEditWord_triggered();

    void on_menuOptionTopicSortData_triggered();

private:
    Ui::MainWindow *ui;

    void UpdateListWidget();

    void HideCurrentWordLabels();

    void SetTitlePrefixByFilepath(const QString& filepath);

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};
#endif // MAINWINDOW_H
