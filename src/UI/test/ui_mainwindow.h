/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QComboBox *list_devices;
    QLabel *img_show;
    QGroupBox *groupBox;
    QPushButton *enum_device;
    QPushButton *open_device;
    QPushButton *close_device;
    QGroupBox *groupBox_2;
    QRadioButton *live_model;
    QRadioButton *trigger_model;
    QPushButton *grab_start;
    QPushButton *grab_stop;
    QCheckBox *is_soft_trigger;
    QPushButton *soft_trigger;
    QGroupBox *groupBox_3;
    QPushButton *save_bmp;
    QPushButton *save_jpg;
    QPushButton *save_tiff;
    QPushButton *save_png;
    QGroupBox *groupBox_4;
    QLabel *label_2;
    QLineEdit *exposure;
    QLineEdit *gain;
    QLabel *label_3;
    QLineEdit *frame_rate;
    QLabel *label_4;
    QPushButton *get_setting;
    QPushButton *save_setting;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(922, 579);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        list_devices = new QComboBox(centralwidget);
        list_devices->setObjectName(QString::fromUtf8("list_devices"));
        list_devices->setGeometry(QRect(10, 10, 591, 21));
        img_show = new QLabel(centralwidget);
        img_show->setObjectName(QString::fromUtf8("img_show"));
        img_show->setGeometry(QRect(20, 40, 571, 501));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(640, 10, 251, 91));
        enum_device = new QPushButton(groupBox);
        enum_device->setObjectName(QString::fromUtf8("enum_device"));
        enum_device->setGeometry(QRect(30, 20, 191, 23));
        open_device = new QPushButton(groupBox);
        open_device->setObjectName(QString::fromUtf8("open_device"));
        open_device->setGeometry(QRect(40, 50, 75, 23));
        close_device = new QPushButton(groupBox);
        close_device->setObjectName(QString::fromUtf8("close_device"));
        close_device->setGeometry(QRect(140, 50, 75, 23));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(640, 120, 251, 111));
        live_model = new QRadioButton(groupBox_2);
        live_model->setObjectName(QString::fromUtf8("live_model"));
        live_model->setGeometry(QRect(20, 20, 81, 16));
        trigger_model = new QRadioButton(groupBox_2);
        trigger_model->setObjectName(QString::fromUtf8("trigger_model"));
        trigger_model->setGeometry(QRect(120, 20, 89, 16));
        grab_start = new QPushButton(groupBox_2);
        grab_start->setObjectName(QString::fromUtf8("grab_start"));
        grab_start->setGeometry(QRect(30, 50, 75, 23));
        grab_stop = new QPushButton(groupBox_2);
        grab_stop->setObjectName(QString::fromUtf8("grab_stop"));
        grab_stop->setGeometry(QRect(150, 50, 75, 23));
        is_soft_trigger = new QCheckBox(groupBox_2);
        is_soft_trigger->setObjectName(QString::fromUtf8("is_soft_trigger"));
        is_soft_trigger->setGeometry(QRect(30, 80, 71, 16));
        soft_trigger = new QPushButton(groupBox_2);
        soft_trigger->setObjectName(QString::fromUtf8("soft_trigger"));
        soft_trigger->setGeometry(QRect(150, 80, 75, 23));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(640, 250, 241, 101));
        save_bmp = new QPushButton(groupBox_3);
        save_bmp->setObjectName(QString::fromUtf8("save_bmp"));
        save_bmp->setGeometry(QRect(20, 20, 75, 23));
        save_jpg = new QPushButton(groupBox_3);
        save_jpg->setObjectName(QString::fromUtf8("save_jpg"));
        save_jpg->setGeometry(QRect(140, 20, 75, 23));
        save_tiff = new QPushButton(groupBox_3);
        save_tiff->setObjectName(QString::fromUtf8("save_tiff"));
        save_tiff->setGeometry(QRect(20, 60, 75, 23));
        save_png = new QPushButton(groupBox_3);
        save_png->setObjectName(QString::fromUtf8("save_png"));
        save_png->setGeometry(QRect(140, 60, 75, 23));
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(640, 370, 241, 151));
        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(21, 31, 54, 16));
        exposure = new QLineEdit(groupBox_4);
        exposure->setObjectName(QString::fromUtf8("exposure"));
        exposure->setGeometry(QRect(81, 31, 133, 20));
        gain = new QLineEdit(groupBox_4);
        gain->setObjectName(QString::fromUtf8("gain"));
        gain->setGeometry(QRect(80, 60, 133, 20));
        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 60, 54, 20));
        frame_rate = new QLineEdit(groupBox_4);
        frame_rate->setObjectName(QString::fromUtf8("frame_rate"));
        frame_rate->setGeometry(QRect(80, 90, 133, 20));
        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 90, 54, 20));
        get_setting = new QPushButton(groupBox_4);
        get_setting->setObjectName(QString::fromUtf8("get_setting"));
        get_setting->setGeometry(QRect(20, 120, 75, 23));
        save_setting = new QPushButton(groupBox_4);
        save_setting->setObjectName(QString::fromUtf8("save_setting"));
        save_setting->setGeometry(QRect(130, 120, 75, 23));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 922, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        img_show->setText(QCoreApplication::translate("MainWindow", "Camera", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\345\210\235\345\247\213\345\214\226", nullptr));
        enum_device->setText(QCoreApplication::translate("MainWindow", "\346\237\245\346\211\276\350\256\276\345\244\207", nullptr));
        open_device->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\350\256\276\345\244\207", nullptr));
        close_device->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255\350\256\276\345\244\207", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\345\233\276\345\203\217\351\207\207\351\233\206", nullptr));
        live_model->setText(QCoreApplication::translate("MainWindow", "\350\277\236\347\273\255\346\250\241\345\274\217", nullptr));
        trigger_model->setText(QCoreApplication::translate("MainWindow", "\350\247\246\345\217\221\346\250\241\345\274\217", nullptr));
        grab_start->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\351\207\207\351\233\206", nullptr));
        grab_stop->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242\351\207\207\351\233\206", nullptr));
        is_soft_trigger->setText(QCoreApplication::translate("MainWindow", "\350\275\257\350\247\246\345\217\221", nullptr));
        soft_trigger->setText(QCoreApplication::translate("MainWindow", "\350\275\257\350\247\246\345\217\221\344\270\200\346\254\241", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\345\233\276\347\211\207\344\277\235\345\255\230", nullptr));
        save_bmp->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230BMP", nullptr));
        save_jpg->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230JPG", nullptr));
        save_tiff->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230tiff", nullptr));
        save_png->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230PNG", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\345\217\202\346\225\260", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\233\235\345\205\211", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\345\242\236\347\233\212", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\345\270\247\347\216\207", nullptr));
        get_setting->setText(QCoreApplication::translate("MainWindow", "\345\217\202\346\225\260\350\216\267\345\217\226", nullptr));
        save_setting->setText(QCoreApplication::translate("MainWindow", "\345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
