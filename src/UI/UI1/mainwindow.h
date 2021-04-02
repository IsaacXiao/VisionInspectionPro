#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QListWidget>
#include <qimage.h>
#include <qdebug.h>
#include <sqlite3.h>
#include <QDialog>


#pragma execution_character_set("utf-8")


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void change();

private slots:
   int OnPage1();
   int OnPage2();
   int OnPage3();
   int OnPage4();
   int OnPage5();
   int OnPage6();

private:
    Ui::MainWindow *ui;

    int skin;

};

#endif // MAINWINDOW_H
