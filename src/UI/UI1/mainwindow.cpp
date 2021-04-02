#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<qstackedwidget.h>
#include<QFile>
#include<Qimage>
#include<QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //实例化 QStackedWidget对象
    connect(ui->btnPage1,SIGNAL(clicked()),this,SLOT(OnPage1()));
    connect(ui->btnPage2,SIGNAL(clicked()),this,SLOT(OnPage2()));
    connect(ui->btnPage3,SIGNAL(clicked()),this,SLOT(OnPage3()));
    connect(ui->btnPage4,SIGNAL(clicked()),this,SLOT(OnPage4()));
    connect(ui->btnPage5,SIGNAL(clicked()),this,SLOT(OnPage5()));
    connect(ui->btnPage6,SIGNAL(clicked()),this,SLOT(OnPage6()));

    connect(ui->btn,SIGNAL(clicked()),this,SLOT(change()));
    skin = 0;

    //ui->CurproductionpageMainShow->setPixmap(QPixmap("C:/Users/admin/Desktop/1.jpg"));

 }

int MainWindow::OnPage1()
{
    ui->stackedWidget->setCurrentIndex(0);
    return 0;

}

int MainWindow::OnPage2()
{
    ui->stackedWidget->setCurrentIndex(1);
    return 0;
}

int MainWindow::OnPage3()
{
    ui->stackedWidget->setCurrentIndex(2);
    return 0;
}

int MainWindow::OnPage4()
{
    ui->stackedWidget->setCurrentIndex(3);
    return 0;
}

int MainWindow::OnPage5()
{
    ui->stackedWidget->setCurrentIndex(4);
    return 0;
}

int MainWindow::OnPage6()
{
    ui->stackedWidget->setCurrentIndex(5);
    return 0;
}

void MainWindow::change()
{

    QString qss;
    if(skin == 0){
        skin = 1;
        qss = ":/qss/red";
    }
    else{
        skin =0 ;
         qss = ":/qss/green";
    }
    QFile file(qss);

    file.open(QFile::ReadOnly);

    if(file.isOpen())
    {
        QString btnstylesheet = QObject::tr(file.readAll());
        qApp->setStyleSheet(btnstylesheet);
        file.close();
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

