#include "mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>

#include <SDKDDKVer.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	//TODO: 写try-catch块
    MainWnd w;
    w.show();
    w.move((QApplication::desktop()->width() - w.width()) / 2, (QApplication::desktop()->height() - w.height()) / 2); //居中显示
    return a.exec();
}
