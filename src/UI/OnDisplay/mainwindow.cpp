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
    
	ui->setupUi(this);
    InitFrame();
    InitStatisticsTab();
    InitCamArea();
    InitStatusBar();

	connect(ui->actStart, SIGNAL(clicked(bool)), this, SLOT(OnStartBtnClick()));
	connect(ui->actStop, SIGNAL(clicked(bool)), this, SLOT(OnStopBtnClick()));

	//设置软触发按钮的调用函数
	for (USHORT camera_id = 0; camera_id < 2; camera_id++)
	{
		connect(soft_trigger_[camera_id], &QPushButton::clicked, this,
			[=]()
		{
			facade_->SoftTriggerGrab(camera_id);
		});
	}
	//qRegisterMetaType<ImgTypePtr>("ImgTypePtr");
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
    //setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);

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

void MainWnd::InitStatisticsTab()
{
    QStringList headers;
    headers << Gb2312ToUnicode("型号") << Gb2312ToUnicode("开始时间") << Gb2312ToUnicode("OK结果") << Gb2312ToUnicode("NG结果")<< Gb2312ToUnicode ("TBA") << Gb2312ToUnicode("结束时间");
    ui->DataTable->setColumnCount(6);
    ui->DataTable->setHorizontalHeaderLabels(headers);
    ui->DataTable->verticalHeader()->setVisible(false);//纵向表头可视化
    ui->DataTable->horizontalHeader()->setVisible(true);//横向表头可视化
    ui->DataTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置编辑方式：禁止编辑表格
    ui->DataTable->setSelectionBehavior(QAbstractItemView::SelectRows);//设置表格选择方式：设置表格为整行选中
    ui->DataTable->setSelectionMode(QAbstractItemView::SingleSelection);//选择目标方式
    ui->DataTable->setStyleSheet("selection-background-color:lightblue");//设置选中颜色：
    ui->DataTable->setAlternatingRowColors(true);
    ui->DataTable->setColumnWidth(0, 202);
    ui->DataTable->setColumnWidth(1, 205);
    ui->DataTable->setColumnWidth(2, 105);
    ui->DataTable->setColumnWidth(3, 105);
    ui->DataTable->setColumnWidth(4, 105);
    ui->DataTable->setColumnWidth(5, 205);
}

void MainWnd::InitCamArea()
{
	camra_shot_[0] = ui->labShowImgCam01;
	camra_shot_[0]->setStyleSheet("background-color:#B8B7B7");

	camra_shot_[1] = ui->labShowImgCam02;
	camra_shot_[1]->setStyleSheet("background-color:#B8B7B7");

	soft_trigger_[0] = ui->btnGrabImageCam01;
	soft_trigger_[1] = ui->btnGrabImageCam02;

	/*camra_shot_[0] = ui->labShowImgCam01;
	camra_shot_[1] = ui->labShowImgCam02;
	camra_shot_[2] = ui->labShowImgCam03;
	camra_shot_[3] = ui->labShowImgCam04;

	for (int i = 0; i < CAMERA_NUM; i++)
	{
	camra_shot_[i]->num = i;
	camra_shot_[i]->setStyleSheet("background-color:#B8B7B7");
	}

	camara_trigger[0] = ui->chkTriggerCam01;
	camara_trigger[1] = ui->chkTriggerCam02;
	camara_trigger[2] = ui->chkTriggerCam03;
	camara_trigger[3] = ui->chkTriggerCam04;
	for (int i = 0; i < CAMERA_NUM; i++)
	{
		camara_trigger[i]->setCheckState(Qt::Unchecked);
	}

	ui->camera0->setText(camera_counting[0]);
	ui->camera1->setText(camera_counting[1]);
	ui->camera2->setText(camera_counting[2]);
	ui->camera3->setText(camera_counting[3]);*/
}

void MainWnd::InitStatusBar()
{
    QCurrentime = new QLabel;
    labCurState = new QLabel;
    QualificationRate = new QLabel;

    QFont trfont("Microsoft YaHei", 10, 0);
    QCurrentime->setFont(trfont);
    QualificationRate->setFont(trfont);
    labCurState->setFont(trfont);
    QualificationRate->setText(Gb2312ToUnicode("相机初始化成功"));
    labCurState->setText(Gb2312ToUnicode("版权所有：长沙麦睛科技有限公司"));

    ui->statusBar->addWidget(QualificationRate, 1);
    ui->statusBar->addWidget(labCurState, 1);

    //运行状态显示：
    QFont font("Microsoft YaHei", 12, 0);//设置QLabel 字体大小

    tredtRunningState = new QLabel;
    //plcsetupComm->PLCStates(statstate);
    tredtRunningState->setFont(font);
    tredtRunningState->setText(Gb2312ToUnicode("运行状态:"));
    ui->tbrRunningState->addWidget(tredtRunningState);
    edtRunningState = new QLineEdit;
    edtRunningState->setFixedWidth(90);
    edtRunningState->setAlignment(Qt::AlignCenter);
    edtRunningState->setStyleSheet("text-align:center; font-size:18px; font-weight:bold; font-style:Microsoft YaHei; color:yellow; background-color:rgba(0,0,0)");
    //edtRunningState->setText(statstate.sFunction);//状态
    edtRunningState->setFocusPolicy(Qt::NoFocus);
    ui->tbrRunningState->addWidget(edtRunningState);

    tredOkNum = new QLabel;
    tredOkNum->setFont(font);
    tredOkNum->setText(Gb2312ToUnicode("OK数:"));
    ui->tbrRunningState->addWidget(tredOkNum);
    edtOkNum = new QLineEdit;
    edtOkNum->setFixedWidth(80);
    edtOkNum->setAlignment(Qt::AlignCenter);
    edtOkNum->setStyleSheet("text-align:center; font-size:18px; font-weight:bold; font-style:Courier; color:yellow; background-color:rgba(0,0,0)");
    edtOkNum->setText("0");
    edtOkNum->setFocusPolicy(Qt::NoFocus);
    ui->tbrRunningState->addWidget(edtOkNum);

    tredNgNum = new QLabel;
    tredNgNum->setFont(font);
    tredNgNum->setText(Gb2312ToUnicode("NG数:"));
    ui->tbrRunningState->addWidget(tredNgNum);
    edtNgNum = new QLineEdit;
    edtNgNum->setFixedWidth(80);
    edtNgNum->setAlignment(Qt::AlignCenter);
    edtNgNum->setStyleSheet("text-align:center; font-size:18px; font-weight:bold; font-style:Courier; color:yellow; background-color:rgba(0,0,0)");
    edtNgNum->setText("0");
    edtNgNum->setFocusPolicy(Qt::NoFocus);
    ui->tbrRunningState->addWidget(edtNgNum);

    tredtTbaNum = new QLabel;
    tredtTbaNum->setFont(font);
    tredtTbaNum->setText(Gb2312ToUnicode("待检数:"));
    ui->tbrRunningState->addWidget(tredtTbaNum);
    edtTbaNum = new QLineEdit;
    edtTbaNum->setFixedWidth(80);
    edtTbaNum->setAlignment(Qt::AlignCenter);
    edtTbaNum->setStyleSheet("text-align:center; font-size:18px; font-weight:bold; font-style:Courier; color:yellow; background-color:rgba(0,0,0)");
    edtTbaNum->setText("0");
    edtTbaNum->setFocusPolicy(Qt::NoFocus);
    ui->tbrRunningState->addWidget(edtTbaNum);

    tredpercent = new QLabel;
    tredpercent->setFont(font);
    tredpercent->setText(Gb2312ToUnicode("合格率:"));
    ui->tbrRunningState->addWidget(tredpercent);
    edPercent = new QLineEdit;
    edPercent->setFixedWidth(80);
    edPercent->setAlignment(Qt::AlignCenter);
    edPercent->setStyleSheet("text-align:center; font-size:18px; font-weight:bold; font-style:Courier; color:yellow; background-color:rgba(0,0,0)");//设置文本框样式
    edPercent->setText("0");
    edPercent->setFocusPolicy(Qt::NoFocus);
    ui->tbrRunningState->addWidget(edPercent);
}

void MainWnd::OnStartBtnClick()
{
	//TODO: 最好在界面上画个按钮来重新加载配置文件
	facade_->ReloadCfg();

	facade_->Run();
}

void MainWnd::OnStopBtnClick()
{
	facade_->Stop();
}

void MainWnd::DisplayImage(unsigned short pos, ImgTypePtr img)
{
	QImage img_raw = cvMat2QImage(*(img), true, true);
	QImage image_scale = img_raw.scaled(camra_shot_[pos]->width(), camra_shot_[pos]->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	camra_shot_[pos]->setBackImage(image_scale);
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
