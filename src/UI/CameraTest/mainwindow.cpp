#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "CommonInclude/TypeDefine.h"
#include "Logger/BroadCastLogger.hpp"
#include "../../Facade/Facade.h"

#include "../../Mediator/Mediator.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	connect(ui->StartButton, SIGNAL(clicked(bool)), this, SLOT(on_StartButton_clicked()));
	connect(ui->EndButton, SIGNAL(clicked(bool)), this, SLOT(on_EndButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_StartButton_clicked()
{
	Facade facade;
	facade.Run((HWND)ui->DisplayLabel->winId(), ui->DisplayLabel->width(), ui->DisplayLabel->height());
}

void MainWindow::on_EndButton_clicked()
{
	//facede.Stop
}