/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gLauout_graphicsView;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout;
    QPushButton *pbt_setZoomInState;
    QPushButton *pbt_zoomIn;
    QPushButton *pbt_zoomOut;
    QPushButton *pbt_reset;
    QPushButton *pbt_changeImage;
    QPushButton *pbt_setZoomOutState;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName(QString::fromUtf8("MainWidget"));
        MainWidget->resize(500, 312);
        verticalLayout = new QVBoxLayout(MainWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gLauout_graphicsView = new QGridLayout();
        gLauout_graphicsView->setSpacing(0);
        gLauout_graphicsView->setObjectName(QString::fromUtf8("gLauout_graphicsView"));
        gLauout_graphicsView->setSizeConstraint(QLayout::SetDefaultConstraint);

        verticalLayout->addLayout(gLauout_graphicsView);

        verticalSpacer = new QSpacerItem(20, 128, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout->addItem(verticalSpacer);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pbt_setZoomInState = new QPushButton(MainWidget);
        pbt_setZoomInState->setObjectName(QString::fromUtf8("pbt_setZoomInState"));

        gridLayout->addWidget(pbt_setZoomInState, 0, 2, 1, 1);

        pbt_zoomIn = new QPushButton(MainWidget);
        pbt_zoomIn->setObjectName(QString::fromUtf8("pbt_zoomIn"));

        gridLayout->addWidget(pbt_zoomIn, 0, 0, 1, 1);

        pbt_zoomOut = new QPushButton(MainWidget);
        pbt_zoomOut->setObjectName(QString::fromUtf8("pbt_zoomOut"));

        gridLayout->addWidget(pbt_zoomOut, 0, 1, 1, 1);

        pbt_reset = new QPushButton(MainWidget);
        pbt_reset->setObjectName(QString::fromUtf8("pbt_reset"));

        gridLayout->addWidget(pbt_reset, 0, 4, 1, 1);

        pbt_changeImage = new QPushButton(MainWidget);
        pbt_changeImage->setObjectName(QString::fromUtf8("pbt_changeImage"));

        gridLayout->addWidget(pbt_changeImage, 0, 5, 1, 1);

        pbt_setZoomOutState = new QPushButton(MainWidget);
        pbt_setZoomOutState->setObjectName(QString::fromUtf8("pbt_setZoomOutState"));

        gridLayout->addWidget(pbt_setZoomOutState, 0, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(MainWidget);

        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QApplication::translate("MainWidget", "Form", nullptr));
        pbt_setZoomInState->setText(QApplication::translate("MainWidget", "\346\224\276\345\244\247\347\212\266\346\200\201", nullptr));
        pbt_zoomIn->setText(QApplication::translate("MainWidget", "\346\224\276\345\244\247", nullptr));
        pbt_zoomOut->setText(QApplication::translate("MainWidget", "\347\274\251\345\260\217", nullptr));
        pbt_reset->setText(QApplication::translate("MainWidget", "\345\244\215\344\275\215", nullptr));
        pbt_changeImage->setText(QApplication::translate("MainWidget", "\346\233\264\346\215\242\345\233\276\347\211\207", nullptr));
        pbt_setZoomOutState->setText(QApplication::translate("MainWidget", "\347\274\251\345\260\217\347\212\266\346\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
