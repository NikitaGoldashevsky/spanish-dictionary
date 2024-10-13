#include "editworddialog.h"
#include "ui_editworddialog.h"
#include "mainwindow.h"

EditWordDialog::EditWordDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditWordDialog)
{
    ui->setupUi(this);

}

EditWordDialog::~EditWordDialog()
{
    delete ui;
}

QString EditWordDialog::GetFieldType() const {
    return ui->fieldTypeComboBox->currentText();
}

QString EditWordDialog::GetFieldValue() const {
    return ui->fieldValueLineEdit->text();
}
