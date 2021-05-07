#include "mainwindow.h"
#include <assert.h>
#include <QFile>
#include "../Mediator/ThreadMediator/ThreadMediator.h"

MainWnd::MainWnd(QWidget *parent)
    : QMainWindow(parent),ui(new Ui::OnDisplayUi)
{
	//facade_ = std::make_unique<Facade>();
	

	facade_ = new Facade;
	facade_->AttachUI(this);
    
	//TODO: 最好在界面上画个按钮来重新加载配置文件
	facade_->ReloadCfg();

	ui->setupUi(this);
    InitFrame();

    InitCamArea();

    ui->actStart->setDisabled(true);
    ui->actStop->setDisabled(true);


	connect(ui->actStart, SIGNAL(clicked(bool)), this, SLOT(OnStartBtnClick()));
	connect(ui->actStop, SIGNAL(clicked(bool)), this, SLOT(OnStopBtnClick()));


	//设置软触发按钮的调用函数
	for (USHORT camera_id = 0; camera_id < facade_->CameraNum(); camera_id++)
	{
		camra_shot_[camera_id]->camera_id_ = QString::fromStdString(Camera(camera_id)->Id_Serial(camera_id));

		get_setting_[camera_id]->setDisabled(true);
		save_setting_[camera_id]->setDisabled(true);
		close_device_[camera_id]->setDisabled(true);
		soft_trigger_[camera_id]->setDisabled(true);

		connect(open_device_[camera_id], &QPushButton::clicked, this,
			[this,camera_id]()
		{
			//TODO: 最好在界面上画个按钮来重新加载配置文件
			//facade_->ReloadCfg();

			Camera(camera_id)->OpenDevice();
			open_device_[camera_id]->setDisabled(true);
			close_device_[camera_id]->setEnabled(true);
			ui->actStart->setEnabled(true);
			get_setting_[camera_id]->setEnabled(true);
			save_setting_[camera_id]->setEnabled(true);
			soft_trigger_[camera_id]->setEnabled(true);
		});

		connect(close_device_[camera_id], &QPushButton::clicked, this,
			[this,camera_id]()
		{
			Camera(camera_id)->CloseDevice();
			close_device_[camera_id]->setDisabled(true);
			ui->actStart->setDisabled(true);
			ui->actStop->setDisabled(true);
			get_setting_[camera_id]->setDisabled(true);
			save_setting_[camera_id]->setDisabled(true);
			open_device_[camera_id]->setEnabled(true);
			soft_trigger_[camera_id]->setDisabled(true);
		});

		connect(get_setting_[camera_id], &QPushButton::clicked, this,
			[this,camera_id]()
		{
			float exposure_time = Camera(camera_id)->GetFloatValue("ExposureTime");
			float gain = Camera(camera_id)->GetFloatValue("Gain");
			float frame_rate = Camera(camera_id)->GetFloatValue("AcquisitionFrameRate");
			exposure_time_[camera_id]->setText(QString::number(exposure_time, 'f', 1));
			gain_[camera_id]->setText(QString::number(gain, 'f'));
			frame_rate_[camera_id]->setText(QString::number(frame_rate, 'f'));
		});

		connect(save_setting_[camera_id], &QPushButton::clicked, this,
			[this,camera_id]()
		{
			QString exposure_time = exposure_time_[camera_id]->text();
			Camera(camera_id)->SetFloatValue("ExposureTime", exposure_time.toFloat());
			QString gain = gain_[camera_id]->text();
			Camera(camera_id)->SetFloatValue("Gain", gain.toFloat());
			QString frame_rate = frame_rate_[camera_id]->text();
			Camera(camera_id)->SetFloatValue("AcquisitionFrameRate", frame_rate.toFloat());
		});

		connect(soft_trigger_[camera_id], &QPushButton::clicked, this,
			[this, camera_id]()
		{
			Camera(camera_id)->SoftTrigger();
		});

		connect(live_mode_[camera_id], &QCheckBox::stateChanged, this,
			[this,camera_id](int state)
		{
			if (live_mode_[camera_id]->checkState()== Qt::Checked)
			{
				Camera(camera_id)->SetMode(1);
			}
			else
			{
				Camera(camera_id)->SetMode(0);
			}
		});
	}
}

MainWnd::~MainWnd()
{
	DeletePtr(facade_);
	DeletePtr(ui);
}

void MainWnd::InitFrame()
{
    //Init按钮
    ui->actStart->setEnabled(true);
    ui->actExit->setEnabled(true);
    ui->actSetting->setEnabled(true);

    //禁用最大化
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);

    //背景全黑
    QFile style(":psblack.css");
    assert(style.exists());
    style.open(QFile::ReadOnly);
    QString qss = QByteArray(style.readAll());
    QString paletteColor = qss.mid(20, 7);
    qApp->setPalette(QPalette(QColor(paletteColor)));
    //qApp->setPalette(QPalette(QColor("#444444")));
    qApp->setStyleSheet(qss);
    style.close();

    //设置顶部导航
    ui->widgetTitle->setProperty("form", "title");
    ui->widgetTop->setProperty("nav", "top");

    QSize icoSize(32, 32);
    int icoWidth = 85;

    //设置顶部导航按钮
    QList<QToolButton *> tbtns = ui->widgetTop->findChildren<QToolButton *>();
    foreach(QToolButton * btn, tbtns)
    {
        btn->setIconSize(icoSize);
        btn->setMinimumWidth(icoWidth);
        btn->setCheckable(true);
        connect(btn, SIGNAL(clicked()), this, SLOT(OnNavBtnClick()));
    }
    ui->btn_Main->click();
}

void MainWnd::InitCamArea()
{
	camra_shot_[0] = ui->labShowImgCam00;
	camra_shot_[1] = ui->labShowImgCam01;
	camra_shot_[2] = ui->labShowImgCam02;
	camra_shot_[3] = ui->labShowImgCam03;
	camra_shot_[4] = ui->labShowImgCam04;
	camra_shot_[5] = ui->labShowImgCam05;
	camra_shot_[6] = ui->labShowImgCam06;
	camra_shot_[7] = ui->labShowImgCam07;
	camra_shot_[8] = ui->labShowImgCam08;

    open_device_[0] = ui->btnOpenDevice00;
    open_device_[1] = ui->btnOpenDevice01;
    open_device_[2] = ui->btnOpenDevice02;
	open_device_[3] = ui->btnOpenDevice03;
	open_device_[4] = ui->btnOpenDevice04;
	open_device_[5] = ui->btnOpenDevice05;
	open_device_[6] = ui->btnOpenDevice06;
	open_device_[7] = ui->btnOpenDevice07;
	open_device_[8] = ui->btnOpenDevice08;

	close_device_[0] = ui->btnCloseDevice00;
    close_device_[1] = ui->btnCloseDevice01;
    close_device_[2] = ui->btnCloseDevice02;
	close_device_[3] = ui->btnCloseDevice03;
	close_device_[4] = ui->btnCloseDevice04;
	close_device_[5] = ui->btnCloseDevice05;
	close_device_[6] = ui->btnCloseDevice06;
	close_device_[7] = ui->btnCloseDevice07;
	close_device_[8] = ui->btnCloseDevice08;

    exposure_time_[0] = ui->exposure_time00;
    exposure_time_[1] = ui->exposure_time01;
    exposure_time_[2] = ui->exposure_time02;
	exposure_time_[3] = ui->exposure_time03;
	exposure_time_[4] = ui->exposure_time04;
	exposure_time_[5] = ui->exposure_time05;
	exposure_time_[6] = ui->exposure_time06;
	exposure_time_[7] = ui->exposure_time07;
	exposure_time_[8] = ui->exposure_time08;

    gain_[0] = ui->gain00;
    gain_[1] = ui->gain01;
    gain_[2] = ui->gain02;
	gain_[3] = ui->gain03;
	gain_[4] = ui->gain04;
	gain_[5] = ui->gain05;
	gain_[6] = ui->gain06;
	gain_[7] = ui->gain07;
	gain_[8] = ui->gain08;

    frame_rate_[0] = ui->frame_rate00;
    frame_rate_[1] = ui->frame_rate01;
    frame_rate_[2] = ui->frame_rate02;
	frame_rate_[3] = ui->frame_rate03;
	frame_rate_[4] = ui->frame_rate04;
	frame_rate_[5] = ui->frame_rate05;
	frame_rate_[6] = ui->frame_rate06;
	frame_rate_[7] = ui->frame_rate07;
	frame_rate_[8] = ui->frame_rate08;

    get_setting_[0] = ui->btnGetSetting00;
    get_setting_[1] = ui->btnGetSetting01;
    get_setting_[2] = ui->btnGetSetting02;
	get_setting_[3] = ui->btnGetSetting03;
	get_setting_[4] = ui->btnGetSetting04;
	get_setting_[5] = ui->btnGetSetting05;
	get_setting_[6] = ui->btnGetSetting06;
	get_setting_[7] = ui->btnGetSetting07;
	get_setting_[8] = ui->btnGetSetting08;

    save_setting_[0] = ui->btnSaveSetting00;
    save_setting_[1] = ui->btnSaveSetting01;
    save_setting_[2] = ui->btnSaveSetting02;
	save_setting_[3] = ui->btnSaveSetting03;
	save_setting_[4] = ui->btnSaveSetting04;
	save_setting_[5] = ui->btnSaveSetting05;
	save_setting_[6] = ui->btnSaveSetting06;
	save_setting_[7] = ui->btnSaveSetting07;
	save_setting_[8] = ui->btnSaveSetting08;

	soft_trigger_[0] = ui->btnGrabImageCam00;
	soft_trigger_[1] = ui->btnGrabImageCam01;
	soft_trigger_[2] = ui->btnGrabImageCam02;
	soft_trigger_[3] = ui->btnGrabImageCam03;
	soft_trigger_[4] = ui->btnGrabImageCam04;
	soft_trigger_[5] = ui->btnGrabImageCam05;
	soft_trigger_[6] = ui->btnGrabImageCam06;
	soft_trigger_[7] = ui->btnGrabImageCam07;
	soft_trigger_[8] = ui->btnGrabImageCam08;

	live_mode_[0] = ui->live00;
	live_mode_[1] = ui->live01;
	live_mode_[2] = ui->live02;
	live_mode_[3] = ui->live03;
	live_mode_[4] = ui->live04;
	live_mode_[5] = ui->live05;
	live_mode_[6] = ui->live06;
	live_mode_[7] = ui->live07;
	live_mode_[8] = ui->live08;
}

void MainWnd::OnStartBtnClick()
{
    //facade_->ReloadCfg();
	facade_->Run();

    ui->actStart->setDisabled(true);
    ui->actStop->setEnabled(true);
}

void MainWnd::OnStopBtnClick()
{
	facade_->Stop();
    ui->actStart->setEnabled(true);
    ui->actStop->setDisabled(true);
	//grab_done_.get();
}

void MainWnd::DisplayImage(unsigned short pos, ImgTypePtr img)
{
	QImage img_raw = cvMat2QImage(img->mat_, false, true);
	QImage image_scale = img_raw.scaled(camra_shot_[pos]->width(), camra_shot_[pos]->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	camra_shot_[pos]->setBackImage(image_scale);
    camra_shot_[pos]->frame_num_.setNum(img->num_);
	update();
	//grab_done_ = std::async(std::launch::async,
	//[this]() {
	//	update();
	//});
}

void MainWnd::OnNavBtnClick()
{
    QToolButton *b = static_cast<QToolButton*>(sender());
    QString name = b->text();

    QList<QToolButton *> tbtns = ui->widgetTop->findChildren<QToolButton *>();
    foreach(QToolButton *btn, tbtns)
    {
        if (btn == b)
        {
            btn->setChecked(true);
        }
        else
        {
            btn->setChecked(false);
        }
    }

    if (name == Gb2312ToUnicode("监控"))
    {
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if (name == Gb2312ToUnicode("设置"))
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if (name == Gb2312ToUnicode("统计"))
    {
        ui->stackedWidget->setCurrentIndex(2);
    }
}
