#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "CommonInclude/TypeDefine.h"
#include "Logger/BroadCastLogger.hpp"

#include "CommonInclude/Memory.hpp"
#include "../../Mediator/Mediator.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), 
	ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	connect(ui->StartButton, SIGNAL(clicked(bool)), this, SLOT(on_StartButton_clicked()));
	connect(ui->EndButton, SIGNAL(clicked(bool)), this, SLOT(on_EndButton_clicked()));

	facade_ = std::make_unique<Facade>();
}

MainWindow::~MainWindow()
{
	DeletePtr(ui);
}

void MainWindow::on_StartButton_clicked()
{
	facade_->Run((HWND)ui->DisplayLabel->winId());
}

void MainWindow::on_EndButton_clicked()
{
	facade_->Stop();
}