#include <string>
#include <fstream>
#include <sstream>

#include <QString>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QKeyEvent>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "WordList.h"
#include "Word.h"
#include "tools.h"
#include "editworddialog.h"
#include "topicwordswindow.h"

//#include <QString>
//#include <QListWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    topicWordsWindow = new TopicWordsWindow(this);

    qApp->installEventFilter(this);

    QString lastFilePathFilePath = "D:\\nikit\\Documents\\Qt Creator\\Spanish_Dictionary\\build\\Desktop_Qt_6_7_3_MinGW_64_bit-Debug\\lastLoadFilePath.txt";
    QFile lastFilePathFile(lastFilePathFilePath);

    if (!lastFilePathFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for reading.";
    }
    else {
        QTextStream in(&lastFilePathFile);

        QString lastFilePath = in.readLine();
        list = ReadData(lastFilePath);
        UpdateListWidget();

        SetTitlePrefixByFilepath(lastFilePath);
    }

    HideCurrentWordLabels();
}

MainWindow::~MainWindow()
{
    EraseList(list);
    delete topicWordsWindow;
    delete ui;
}

void MainWindow::on_menuOptionLoadData_triggered() {
    const QString filename = QFileDialog::getOpenFileName(
        this, tr("Open text file"), "", tr("Text file (*.txt)"));

    if (!filename.isEmpty()) {
        list = ReadData(filename);

        UpdateListWidget();
        UpdateLastLoadFilePath(filename);
        SetTitlePrefixByFilepath(filename);

        this->topicWordsWindow->SetListByTopic(this->topicWordsWindow->topic);
    }
    HideCurrentWordLabels();
}

void MainWindow::on_menuOptionSaveData_triggered() {
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Text files (*.txt)"));
    dialog.setDefaultSuffix("txt");
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);

    QString filename;
    if (dialog.exec()) {
        filename = dialog.selectedFiles().first();
        UpdateLastLoadFilePath(filename);
        WriteData(list, filename);
    }
}

void MainWindow::UpdateListWidget() {
    auto* wordsListWidget = ui->WordsListWidget;

    HideCurrentWordLabels();
    wordsListWidget->clear();

    WordList* pCur = list;
    while (pCur) {
        QString qSpanishWord = pCur->word->spanish_word;
        wordsListWidget->addItem(qSpanishWord);
        pCur = pCur->pNext;
    }

    this->topicWordsWindow->SetListByTopic(this->topicWordsWindow->topic);
}

void MainWindow::on_WordsListWidget_itemClicked(QListWidgetItem *item)
{
    Word* currentWord = FindWord(list,item->text());
    SetCurrentWordLabels(currentWord);
}

void MainWindow::on_menuOptionAddWord_triggered() {
    NewWordInputDialog dialog;

    while (true) {

        const auto dialogExec = dialog.exec();

        if (dialogExec != QDialog::Accepted) break;

        const QString spanishWord = dialog.getWord();
        const QString translation = dialog.getTranslation();
        const QString example = dialog.getExample();
        const QString exampleTranslation = dialog.getExampleTranslation();
        const QString topic = dialog.getTopic();

        if (!spanishWord.isEmpty() &&
            !translation.isEmpty() &&
            !example.isEmpty() &&
            !exampleTranslation.isEmpty() &&
            !topic.isEmpty()
            ) {

            // qDebug() << correctWord("spanish", spanishWord);
            // qDebug() << correctWord("russian", translation);
            // qDebug() << correctSentence("spanish", example);
            // qDebug() << correctSentence("russian", exampleTranslation);
            // qDebug() << correctWord("russian", topic);
            // qDebug() << QString::fromStdString("\n");

            // проблема с русскими словами и предложениями - всегда выводит false

            if (correctWord("spanish", spanishWord) &&
                correctWord("russian", translation) &&
                correctSentence("spanish", example) &&
                correctSentence("russian", exampleTranslation) &&
                correctWord("russian", topic)) {
                bool added = AddWord(list, new Word {
                                               spanishWord,
                                               translation,
                                               example,
                                               exampleTranslation,
                                               topic
                                           });

                if (added) {
                    UpdateListWidget();
                    return;
                }
                else {
                    QString stringMessage = "";
                    stringMessage += "Слово \"" + spanishWord + "\" уже есть в словаре!";
                    QMessageBox::warning(this, "Ошибка",
                                         stringMessage, QMessageBox::Ok);
                    //(FindWord(list, spanishWord) == nullptr)
                }
            }
            else {
                QMessageBox::warning(this, "Ошибка",
                                     "Введенные значения некорректны!", QMessageBox::Ok);
            }
        }
        else {
            QMessageBox::warning(this, "Ошибка", "Все значения должны быть введены!", QMessageBox::Ok);
        }
    }
}

void MainWindow::on_menuOptionSortData_triggered() {
    MergeSort(list);
    UpdateListWidget();
}

void MainWindow::on_menuOptionTopicSortData_triggered() {
    MergeSort(list, true);
    UpdateListWidget();
}

void MainWindow::on_menuOptionDeleteWord_triggered() {
    if (ui->WordsListWidget->selectedItems().empty()) {
        QMessageBox::warning(this, "Ошибка", "Выберите слово, которое нужно удалить!", QMessageBox::Ok);
        return;
    }

    QString spanishWord = ui->WordsListWidget->currentItem()->text();
    DeleteWord(list, spanishWord);
    UpdateListWidget();
}

void MainWindow::SetCurrentWordLabels(Word* word) {

    ui->WordLabel->setText(word->spanish_word);
    ui->TranslationLabel->setText(word->russian_translation);
    ui->ExampleLabel->setText(word->example_sentence);
    ui->ExampleTranslationLabel->setText(word->example_translation);
    ui->TopicLabel->setText(word->topic);

    ui->WordLabel->show();
    ui->TranslationLabel->show();
    ui->ExampleLabel->show();
    ui->ExampleTranslationLabel->show();
    ui->TopicLabel->show();

    ui->line->show();
    ui->chooseWordLabel->hide();
}

void MainWindow::HideCurrentWordLabels() {

    ui->WordLabel->hide();
    ui->TranslationLabel->hide();
    ui->ExampleLabel->hide();
    ui->ExampleTranslationLabel->hide();
    ui->TopicLabel->hide();

    ui->line->hide();

    ui->chooseWordLabel->show();
}

void MainWindow::on_menuOptionEditWord_triggered() {
    if (ui->WordsListWidget->selectedItems().empty()) {
        QMessageBox::warning(this, "Ошибка", "Выберите слово, которое нужно редактировать!", QMessageBox::Ok);
        return;
    }

    while (true) {
        EditWordDialog dialog(this);

        const auto dialogExec = dialog.exec();
        if (dialogExec != QDialog::Accepted) {
            break;
        }

        const QString fieldType = dialog.GetFieldType();
        const QString fieldValue = dialog.GetFieldValue();

        QString spanishWord = ui->WordsListWidget->currentItem()->text();
        Word* word = FindWord(list, spanishWord);

        if (fieldValue.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Значение поля не может быть пустым!", QMessageBox::Ok);
        }
        else {
            if (fieldType == QString("Слово") && (FindWord(list, fieldValue) != nullptr)) {
                QMessageBox::warning(this, "Ошибка", "Это слово уже есть в словаре!", QMessageBox::Ok);
            }
            else {
                bool edited = EditWord(word, fieldType, fieldValue);
                if (edited) {
                    break;
                }
                else {
                    QMessageBox::warning(this, "Ошибка", "Введенное значение поля некорректно!", QMessageBox::Ok);
                }
            }
        }
    }

    UpdateListWidget();
}


void MainWindow::SetTitlePrefixByFilepath(const QString& filepath) {
    QStringList dirList = filepath.split("/");
    this->setWindowTitle(dirList[dirList.size()-1] + " - Испанско-русский словарь");
}


bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (obj == ui->SearchLineEdit && event->type() == QEvent::KeyPress) {
        QKeyEvent *key = static_cast<QKeyEvent *>(event);

        if (key->key() == 16777220) {
            QString input = ui->SearchLineEdit->text();

            Word* foundWord = FindWord(list, input);
            if (foundWord) {
                qDebug() << "found the word" << input << "in the list";
                ui->WordsListWidget->setCurrentItem(ui->WordsListWidget->findItems(input, Qt::MatchExactly)[0]);
                SetCurrentWordLabels(foundWord);
            }
            else {
                WordList* topicWordsList = GetTopicWords(list, input);

                if (!topicWordsList) {
                    return false;
                }

                this->topicWordsWindow->show();
                this->topicWordsWindow->SetTitle(input[0].toUpper() + input.right(input.size()-1));
                this->topicWordsWindow->SetListByTopic(input);
                this->topicWordsWindow->SetTopic(input);
            }
        }
    }

    return QObject::eventFilter(obj, event);
}
