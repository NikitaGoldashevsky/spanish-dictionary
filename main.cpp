#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    a.setStyle(QStyleFactory::create("windows11"));

    qDebug() << QStyleFactory::keys();

    w.show();
    return a.exec();
}
