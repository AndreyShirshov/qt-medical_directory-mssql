#include <QApplication>
#include <QDebug>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile styleFile(":/qss/style.css");
    if( styleFile.open(QFile::ReadOnly) )
        a.setStyleSheet(styleFile.readAll());
    else
        qDebug() << "Style can't be loaded.";

    MainWindow w;
    w.showMaximized() ;
    return a.exec();
}
