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
    ui->btnGetSetting->setDisabled(true);
    ui->btnSaveSetting01->setDisabled(true);

	connect(ui->actStart, SIGNAL(clicked(bool)), this, SLOT(OnStartBtnClick()));
	connect(ui->actStop, SIGNAL(clicked(bool)), this, SLOT(OnStopBtnClick()));

    ui->btnCloseDevice->setDisabled(true);
    ui->btnGrabImageCam01->setDisabled(true);

	//设置软触发按钮的调用函数
	for (USHORT camera_id = 0; camera_id < facade_->CameraNum(); camera_id++)
	{
		connect(soft_trigger_[camera_id], &QPushButton::clicked, this,
			[=]()
		{
            Camera(camera_id)->SoftTrigger();
		});
	}

    connect(ui->btnOpenDevice, &QPushButton::clicked, this,
        [=]()
    {
		//TODO: 最好在界面上画个按钮来重新加载配置文件
		facade_->ReloadCfg();

        facade_->OpenDevice(0);
        ui->btnOpenDevice->setDisabled(true);
        ui->btnCloseDevice->setEnabled(true);
        ui->actStart->setEnabled(true);
		ui->btnGetSetting->setEnabled(true);
		ui->btnSaveSetting01->setEnabled(true);
        ui->btnGrabImageCam01->setEnabled(true);
    });

	connect(ui->btnCloseDevice, &QPushButton::clicked, this,
		[=]()
	{
		facade_->CloseDevice(0);
        ui->btnCloseDevice->setDisabled(true);
        ui->actStart->setDisabled(true);
		ui->btnGetSetting->setDisabled(true);
		ui->btnSaveSetting01->setDisabled(true);
        ui->btnOpenDevice->setEnabled(true);
        ui->btnGrabImageCam01->setDisabled(true);
	});

	connect(ui->btnGetSetting, &QPushButton::clicked, this,
		[=]()
	{
        float exposure_time = facade_->GetFloatValue(0,"ExposureTime");
        float gain = facade_->GetFloatValue(0, "Gain");
        float frame_rate = facade_->GetFloatValue(0, "AcquisitionFrameRate");
        ui->exposure_time01->setText(QString::number(exposure_time, 'f',1));
        ui->gain01->setText(QString::number(gain, 'f'));
        ui->frame_rate01->setText(QString::number(frame_rate, 'f'));
	});

	connect(ui->btnSaveSetting01, &QPushButton::clicked, this,
		[=]()
	{
        QString exposure_time = ui->exposure_time01->text();
        facade_->SetFloatValue(0, "ExposureTime", exposure_time.toFloat());
		QString gain = ui->gain01->text();
        facade_->SetFloatValue(0, "Gain", gain.toFloat());
        QString frame_rate = ui->frame_rate01->text();
        facade_->SetFloatValue(0, "AcquisitionFrameRate", frame_rate.toFloat());
	});
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
    //ui->actStop->setDisabled(true);


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
	camra_shot_[0] = ui->labShowImgCam01;
	camra_shot_[1] = ui->labShowImgCam02;
	camra_shot_[2] = ui->labShowImgCam03;
	camra_shot_[3] = ui->labShowImgCam04;
	camra_shot_[4] = ui->labShowImgCam05;
	camra_shot_[5] = ui->labShowImgCam06;
	camra_shot_[6] = ui->labShowImgCam07;
	camra_shot_[7] = ui->labShowImgCam08;
	camra_shot_[8] = ui->labShowImgCam09;

	soft_trigger_[0] = ui->btnGrabImageCam01;
	soft_trigger_[1] = ui->btnGrabImageCam02;

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
}

void MainWnd::DisplayImage(unsigned short pos, ImgTypePtr img)
{
	QImage img_raw = cvMat2QImage(img->mat_, false, true);
	QImage image_scale = img_raw.scaled(camra_shot_[pos]->width(), camra_shot_[pos]->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	camra_shot_[pos]->setBackImage(image_scale);
    camra_shot_[pos]->frame_num_.setNum(img->num_);
	camra_shot_[pos]->update();
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
