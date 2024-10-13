#include "newwordinputdialog.h"
#include "ui_newwordinputdialog.h"

NewWordInputDialog::NewWordInputDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewWordInputDialog)
{
    ui->setupUi(this);

    ui->spanishWordInput->setFocus();

    setTabOrder(ui->spanishWordInput, ui->translationInput);
    setTabOrder(ui->translationInput, ui->exampleInput);
    setTabOrder(ui->exampleInput, ui->exampleTranslationInput);
    setTabOrder(ui->exampleTranslationInput, ui->topicInput);

    setTabOrder(ui->topicInput, ui->buttonBox);
}

NewWordInputDialog::~NewWordInputDialog()
{
    delete ui;
}

QString NewWordInputDialog::getWord() const{
    return ui->spanishWordInput->text();
}

QString NewWordInputDialog::getTranslation() const{
    return ui->translationInput->text();
}

QString NewWordInputDialog::getExample() const{
    return ui->exampleInput->text();
}

QString NewWordInputDialog::getExampleTranslation() const {
    return ui->exampleTranslationInput->text();
}

QString NewWordInputDialog::getTopic() const {
    return ui->topicInput->text();
}

