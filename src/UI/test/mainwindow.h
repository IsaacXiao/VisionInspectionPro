#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <windows.h>
#include <assert.h>
#include <future>
#include <memory>
#include <mutex>
#include "MvCamera.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using STRING = std::string;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    CMvCamera* m_pcMyCamera;
    MV_CC_DEVICE_INFO_LIST m_stDevList;

    BOOL m_bOpenDevice{ FALSE };
    BOOL m_bStartGrabbing{ FALSE };
    BOOL m_bSoftWareTriggerCheck{ FALSE };
    int m_nDeviceCombo;
    int m_nTriggerMode;
    BOOL m_bThreadState{FALSE};
    MV_FRAME_OUT_INFO_EX m_stImageInfo;
    std::future<void> grab_done_;
    std::mutex mut_;
    unsigned char* m_pGrabBuf{ nullptr };
    unsigned int m_nGrabBufSize{ 0 };
    MV_DISPLAY_FRAME_INFO stDisplayInfo{ 0 };

    void EnableControls(bool bIsCameraReady);
private slots:
    void OnBnClickedEnumButton();
    void OnBnClickedOpenButton();
    void OnBnClickedCloseButton();
    void OnBnClickedGetParameterButton();
    void OnBnClickedSetParameterButton();
    void GetTriggerSource();
    void OnLiveModel(bool checked);
    void OnTriggerModel(bool checked);
    void OnBnClickedSoftwareTriggerCheck();
    void OnStartGrab();
    void OnStopGrab();
};

#endif // MAINWINDOW_H
