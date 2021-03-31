#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../../Facade/Facade.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	using FacadePtr = PointType<Facade>::Ptr;
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
	FacadePtr facade_;
private slots:
	void on_StartButton_clicked();
	void on_EndButton_clicked();
};
#endif // MAINWINDOW_H
