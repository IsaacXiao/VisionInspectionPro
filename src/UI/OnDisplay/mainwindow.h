#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QChartView>
//#include <QChart>
//using namespace QtCharts;

#include "ui_OnDisplay.h"
#include "../Convert.h"

#include "../../Facade/Facade.h"
//#include "../IForDisplay.h"

class CameraShot;

#include <array>

class MainWnd : public QMainWindow, public IForDisplay
{
public:
    MainWnd(QWidget *parent = nullptr);
	~MainWnd();
private:
    Q_OBJECT

    enum { CAMERA_NUM = 4 };

	FacadePtr facade_;

    Ui::OnDisplayUi *ui;

    QLabel *labCurState;  //状态栏，显示相机的一些初始化状态
    QLabel *logoImage; //工具栏LOGO
    QLabel *sezilog;
    QLabel *QualificationRate;//状态栏，统计合格率
    QLabel *QCurrentime;//状态栏，时间显示

    bool mousePressed;
    QPoint mousePoint;
    QPoint last;

    QLabel *tredtRunningState;
    QLabel *tredOkNum;
    QLabel *tredNgNum;
    QLabel *tredtTbaNum;
    QLabel *tredpercent;

    //运行状态，OK数，NG数，待检数，合格率
    QLineEdit *edtRunningState;
    QLineEdit *edtOkNum;
    QLineEdit *edtNgNum;
    QLineEdit *edtTbaNum;
    QLineEdit *edPercent;

    //显示图像的Label对象
    CameraShot* camra_shot_[CAMERA_NUM];
	QPushButton * soft_trigger_[CAMERA_NUM];
    // 相机触发选择框
    QCheckBox* camara_trigger[CAMERA_NUM];
    std::array<QString, CAMERA_NUM> camera_counting{"-999","-999","-999","-999"};

    void InitFrame(); 
    void InitStatisticsTab();
    void InitCamArea();
    void InitStatusBar();
public slots :
    void OnNavBtnClick();
	void OnStartBtnClick();
	void OnStopBtnClick();
	virtual void DisplayImage(unsigned short pos, ImgTypePtr img) override;
};
#endif // MAINWINDOW_H
