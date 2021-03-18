#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "CommonInclude/TypeDefine.h"
#include "Logger/BroadCastLogger.hpp"

#include "CommonInclude/Memory.hpp"
#include "../../Mediator/Mediator.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), 
	ui(new Ui::MainWindow),
	facade_( new Facade )
{
    ui->setupUi(this);

	connect(ui->StartButton, SIGNAL(clicked(bool)), this, SLOT(on_StartButton_clicked()));
	connect(ui->EndButton, SIGNAL(clicked(bool)), this, SLOT(on_EndButton_clicked()));
}

MainWindow::~MainWindow()
{
	DeletePtr(facade_);
	DeletePtr(ui);
}

void MainWindow::on_StartButton_clicked()
{
	facade_->Run((HWND)ui->DisplayLabel->winId(), ui->DisplayLabel->width(), ui->DisplayLabel->height());
}

void MainWindow::on_EndButton_clicked()
{
	facade_->Stop();
}