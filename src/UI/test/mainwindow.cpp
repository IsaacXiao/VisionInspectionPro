#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	EnableControls(FALSE);
    connect(ui->enum_device, SIGNAL(clicked()), this, SLOT(OnBnClickedEnumButton()));
	connect(ui->open_device, SIGNAL(clicked()), this, SLOT(OnBnClickedOpenButton()));
	connect(ui->close_device, SIGNAL(clicked()), this, SLOT(OnBnClickedCloseButton()));
	connect(ui->live_model, SIGNAL(toggled(bool)), this, SLOT(OnLiveModel(bool)));
	connect(ui->trigger_model, SIGNAL(toggled(bool)), this, SLOT(OnTriggerModel(bool)));
	connect(ui->get_setting, SIGNAL(clicked()), this, SLOT(OnBnClickedGetParameterButton()));
	connect(ui->grab_start, SIGNAL(clicked()), this, SLOT(OnStartGrab()));
	connect(ui->grab_stop, SIGNAL(clicked()), this, SLOT(OnStopGrab()));

	stDisplayInfo.hWnd = (HWND)ui->img_show->winId();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::EnableControls(bool bIsCameraReady)
{
	ui->open_device->setEnabled(m_bOpenDevice ? FALSE : (bIsCameraReady ? TRUE : FALSE));
	ui->close_device->setEnabled((m_bOpenDevice && bIsCameraReady) ? TRUE : FALSE);
	ui->grab_start->setEnabled((m_bStartGrabbing && bIsCameraReady) ? FALSE : (m_bOpenDevice ? TRUE : FALSE));
	ui->grab_stop->setEnabled(m_bStartGrabbing ? TRUE : FALSE);
	ui->is_soft_trigger->setEnabled(m_bOpenDevice ? TRUE : FALSE);
	ui->soft_trigger->setEnabled((m_bStartGrabbing && m_bSoftWareTriggerCheck && (ui->is_soft_trigger->checkState()== Qt::Checked) ? TRUE : FALSE));
	ui->save_bmp->setEnabled(m_bStartGrabbing ? TRUE : FALSE);
	ui->save_tiff->setEnabled(m_bStartGrabbing ? TRUE : FALSE);
	ui->save_png->setEnabled(m_bStartGrabbing ? TRUE : FALSE);
	ui->save_jpg->setEnabled(m_bStartGrabbing ? TRUE : FALSE);
	ui->exposure->setEnabled(m_bOpenDevice ? TRUE : FALSE);
	ui->gain->setEnabled(m_bOpenDevice ? TRUE : FALSE);
	ui->frame_rate->setEnabled(m_bOpenDevice ? TRUE : FALSE);
	ui->get_setting->setEnabled(m_bOpenDevice ? TRUE : FALSE);
	ui->save_setting->setEnabled(m_bOpenDevice ? TRUE : FALSE);
	ui->live_model->setEnabled(m_bOpenDevice ? TRUE : FALSE);
	ui->trigger_model->setEnabled(m_bOpenDevice ? TRUE : FALSE);
}

void MainWindow::OnBnClickedEnumButton()
{
	STRING strMsg;
	using std::to_string;

	ui->list_devices->clear();
	memset(&m_stDevList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));

	// ch:枚举子网内所有设备 | en:Enumerate all devices within subnet
	CMvCamera::EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &m_stDevList);

	for (USHORT i = 0; i < m_stDevList.nDeviceNum; i++)
	{
		MV_CC_DEVICE_INFO* pDeviceInfo = m_stDevList.pDeviceInfo[i];
		assert(pDeviceInfo->nTLayerType == MV_GIGE_DEVICE);

		int Ip1 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
		int Ip2 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
		int Ip3 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
		int Ip4 = (m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);

		char strUserName[256] = { 0 };
		sprintf_s(strUserName, "%s %s (%s)", pDeviceInfo->SpecialInfo.stGigEInfo.chManufacturerName,
			pDeviceInfo->SpecialInfo.stGigEInfo.chModelName,
			pDeviceInfo->SpecialInfo.stGigEInfo.chSerialNumber);
		STRING&& Ip = std::to_string(Ip1) + "." + to_string(Ip2) + "." + to_string(Ip3) + "." + to_string(Ip4);
		STRING&& id_serial = STRING(strUserName) + ":" + Ip;
		ui->list_devices->addItem(QString::fromStdString(id_serial));
	}

	if (0 == m_stDevList.nDeviceNum)
	{
		throw "No device";
	}
	ui->list_devices->setCurrentIndex(0);

	EnableControls(true);

	return;
}

void MainWindow::OnBnClickedOpenButton()
{
	if (TRUE == m_bOpenDevice) return;

	m_nDeviceCombo = ui->list_devices->currentIndex();
	m_pcMyCamera = new CMvCamera;

	m_pcMyCamera->Open(m_stDevList.pDeviceInfo[m_nDeviceCombo]);

	unsigned int nPacketSize = 0;
	m_pcMyCamera->GetOptimalPacketSize(&nPacketSize);
	m_pcMyCamera->SetIntValue("GevSCPSPacketSize", nPacketSize);

	m_bOpenDevice = TRUE;

	EnableControls(TRUE);
	OnBnClickedGetParameterButton();
}

void MainWindow::OnBnClickedGetParameterButton()
{
	GetTriggerSource();
	MVCC_FLOATVALUE stFloatValue = { 0 };
	m_pcMyCamera->GetFloatValue("ExposureTime", &stFloatValue);
	ui->exposure->setText(QString::number(stFloatValue.fCurValue, 'f', 1));
	m_pcMyCamera->GetFloatValue("Gain", &stFloatValue);
	ui->gain->setText(QString::number(stFloatValue.fCurValue, 'f', 1));
	m_pcMyCamera->GetFloatValue("ResultingFrameRate", &stFloatValue);
	ui->frame_rate->setText(QString::number(stFloatValue.fCurValue, 'f', 1));
}

void MainWindow::OnBnClickedSetParameterButton()
{
	// ch:调节这两个曝光模式，才能让曝光时间生效
	m_pcMyCamera->SetEnumValue("ExposureMode", MV_EXPOSURE_MODE_TIMED);
	m_pcMyCamera->SetEnumValue("ExposureAuto", MV_EXPOSURE_AUTO_MODE_OFF);
	QString exposure_time = ui->exposure->text();
	m_pcMyCamera->SetFloatValue("ExposureTime", exposure_time.toFloat());

	// ch:设置增益前先把自动增益关闭
	m_pcMyCamera->SetEnumValue("GainAuto", 0);
	QString gain = ui->gain->text();
	m_pcMyCamera->SetFloatValue("Gain", gain.toFloat());

	m_pcMyCamera->SetBoolValue("AcquisitionFrameRateEnable", true);
	QString frame_rate = ui->frame_rate->text();
	m_pcMyCamera->SetFloatValue("AcquisitionFrameRate", frame_rate.toFloat());
}

void MainWindow::GetTriggerSource()
{
	MVCC_ENUMVALUE stEnumValue = { 0 };
	m_pcMyCamera->GetEnumValue("TriggerSource", &stEnumValue);
	if ((unsigned int)MV_TRIGGER_SOURCE_SOFTWARE == stEnumValue.nCurValue)
	{
		m_bSoftWareTriggerCheck = TRUE;
		OnTriggerModel(true);
	}
	else
	{
		m_bSoftWareTriggerCheck = FALSE;
		OnLiveModel(true);
	}
}

void MainWindow::OnBnClickedCloseButton()
{
	//TODO:线程join
	m_bThreadState = FALSE;

	if (m_pcMyCamera)
	{
		m_pcMyCamera->Close();
		delete m_pcMyCamera;
		m_pcMyCamera = NULL;
	}

	m_bStartGrabbing = FALSE;
	m_bOpenDevice = FALSE;

	EnableControls(TRUE);
}

void MainWindow::OnLiveModel(bool checked)
{
	if(checked)
	{
		m_nTriggerMode = MV_TRIGGER_MODE_OFF;
		m_pcMyCamera->SetEnumValue("TriggerMode", m_nTriggerMode);
		ui->trigger_model->setChecked(false);
		ui->live_model->setChecked(true);
		ui->soft_trigger->setEnabled(false);
	}
}

void MainWindow::OnTriggerModel(bool checked)
{
	if (checked)
	{
		m_nTriggerMode = MV_TRIGGER_MODE_ON;
		m_pcMyCamera->SetEnumValue("TriggerMode", m_nTriggerMode);
		ui->trigger_model->setChecked(true);
		ui->live_model->setChecked(false);
		ui->soft_trigger->setEnabled(true);
	}
}

void MainWindow::OnBnClickedSoftwareTriggerCheck()
{
	//响应触发勾选框
}

void MainWindow::OnStartGrab()
{
	m_bThreadState = TRUE;
	memset(&m_stImageInfo, 0, sizeof(MV_FRAME_OUT_INFO_EX));
	std::cout << "main thread: " << std::this_thread::get_id() << std::endl;
	grab_done_ = std::async(std::launch::async, 
	[this](){
		std::cout << "grab thread: " << std::this_thread::get_id() << std::endl;
		// ch:从相机中获取一帧图像大小 | en:Get size of one frame from camera
		MVCC_INTVALUE_EX stIntValue = { 0 };
		m_pcMyCamera->GetIntValue("PayloadSize", &stIntValue);
		unsigned int nDataSize = (unsigned int)stIntValue.nCurValue;

		if (NULL == m_pGrabBuf || nDataSize > m_nGrabBufSize)
		{
			if (m_pGrabBuf)
			{
				free(m_pGrabBuf);
				m_pGrabBuf = NULL;
			}
			m_pGrabBuf = (unsigned char*)malloc(sizeof(unsigned char) * nDataSize);
			m_nGrabBufSize = nDataSize;
		}

		MV_FRAME_OUT_INFO_EX stImageInfo = { 0 };
		
		while (m_bThreadState)
		{
			mut_.lock();
			int nRet = m_pcMyCamera->GetOneFrameTimeout(m_pGrabBuf, m_nGrabBufSize, &stImageInfo, 1000);
			memcpy(&m_stImageInfo, &stImageInfo, sizeof(MV_FRAME_OUT_INFO_EX));
			mut_.unlock();

			if (nRet == MV_OK)
			{
				stDisplayInfo.pData = m_pGrabBuf;
				stDisplayInfo.nDataLen = stImageInfo.nFrameLen;
				stDisplayInfo.nWidth = stImageInfo.nWidth;
				stDisplayInfo.nHeight = stImageInfo.nHeight;
				stDisplayInfo.enPixelType = stImageInfo.enPixelType;

				m_pcMyCamera->DisplayOneFrame(&stDisplayInfo);
			}
			else
			{
				if (MV_TRIGGER_MODE_ON == m_nTriggerMode)
				{
					Sleep(5);
				}
			}
		}
	});

	m_pcMyCamera->StartGrabbing();
	m_bStartGrabbing = TRUE;
	EnableControls(TRUE);
}

void MainWindow::OnStopGrab()
{
	m_bStartGrabbing = FALSE;
	m_bThreadState = FALSE;
	grab_done_.get();
	EnableControls(TRUE);
}
