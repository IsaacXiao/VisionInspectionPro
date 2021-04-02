#include "mainwindow.h"
#include <QApplication>
#include <sqlite3.h>
#include <QDebug>
#include "qfile.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString qss;
    //QFile qssFile("C:/Users/admin/Documents/UI1/qss/red.css");
    QFile qssFile("D:/WorkSpace/Repository/VisionInspectionPro/src/UI/UI1/qss/red.css");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        qss = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(qss);
        qssFile.close();
    }

    MainWindow w;
    w.show();

    return a.exec();
}
