#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QChartView>
//#include <QChart>
//using namespace QtCharts;

#include <future>

#include "ui_OnDisplay.h"
#include "../Convert.h"

#include "../../Facade/Facade.h"
//#include "../IForDisplay.h"

class CameraShot;


class MainWnd : public QMainWindow, public IForDisplay
{
public:
    MainWnd(QWidget *parent = nullptr);
	~MainWnd();
private:
    Q_OBJECT

    enum { CAMERA_NUM = 9 };

	FacadePtr facade_;

    CameraGrabberPtr Camera(USHORT camera_id) { return facade_->Camera(camera_id); }

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


   
    CameraShot* camra_shot_[CAMERA_NUM];

    QPushButton* open_device_[CAMERA_NUM];
    QPushButton* close_device_[CAMERA_NUM];
    QPushButton* soft_trigger_[CAMERA_NUM];
    QLineEdit* exposure_time_[CAMERA_NUM];
    QLineEdit* gain_[CAMERA_NUM];
    QLineEdit* frame_rate_[CAMERA_NUM];
    QPushButton* get_setting_[CAMERA_NUM];
    QPushButton* save_setting_[CAMERA_NUM];
    QCheckBox* live_mode_[CAMERA_NUM];

    //std::future<void> grab_done_;

    void InitFrame(); 
    void InitCamArea();
    //void InitStatusBar();
public slots :
    void OnNavBtnClick();
	void OnStartBtnClick();
	void OnStopBtnClick();
	virtual void DisplayImage(unsigned short pos, ImgTypePtr img) override;
};
#endif // MAINWINDOW_H
