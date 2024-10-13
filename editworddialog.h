#ifndef EDITWORDDIALOG_H
#define EDITWORDDIALOG_H

#include <QDialog>

#include "mainwindow.h"

namespace Ui {
class EditWordDialog;
}

class EditWordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditWordDialog(QWidget *parent = nullptr);
    ~EditWordDialog();

    QString GetFieldType() const;

    QString GetFieldValue() const;

private:
    Ui::EditWordDialog *ui;
};

#endif // EDITWORDDIALOG_H
