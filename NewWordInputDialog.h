#ifndef NEWWORDINPUTDIALOG_H
#define NEWWORDINPUTDIALOG_H

#include <QDialog>

namespace Ui {
class NewWordInputDialog;
}

class NewWordInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewWordInputDialog(QWidget *parent = nullptr);
    ~NewWordInputDialog();

    QString getWord() const;

    QString getTranslation() const;

    QString getExample() const;

    QString getExampleTranslation() const;

    QString getTopic() const;

    void on_QDialogButtonBox_clicked() const;

private:
    Ui::NewWordInputDialog *ui;
};


#endif // NEWWORDINPUTDIALOG_H
