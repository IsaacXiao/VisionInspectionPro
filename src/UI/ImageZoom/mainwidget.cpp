#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QPolygon>
#include <QMouseEvent>
#include <QMessageBox>

MainWidget::MainWidget(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    setMinimumSize(740, 520);
    m_graphicsView = new QGraphicsView();
    ui->gLauout_graphicsView->addWidget(m_graphicsView);     //将自定义的组件添加到布局中
    m_graphicsScene = new QGraphicsScene;  //new 一个新的场景对象
    m_graphicsScene->setSceneRect(-370, -250, 740, 500);     //限定场景对象的显示区域
    m_graphicsView->setScene(m_graphicsScene);          //将视图对象于场景相连

    pixItem = new PixItem(new QPixmap(":/Image/p4.jpg"));
    //将该图元对象添加到场景中，并设置此图元在场景中的位置为中心（0，0）
    m_graphicsScene->addItem(pixItem);
    pixItem->setPos(0,0);
}

MainWidget::~MainWidget()
{
    delete ui;
}

//放大图片
void MainWidget::on_pbt_zoomIn_clicked()
{
    pixItem->setScaleValue(pixItem->getScaleValue() + 1);
    pixItem->setZoomState(NO_STATE);
}

//缩小图片
void MainWidget::on_pbt_zoomOut_clicked()
{
    pixItem->setScaleValue(pixItem->getScaleValue() - 1);
    pixItem->setZoomState(NO_STATE);
}

//复位图片
void MainWidget::on_pbt_reset_clicked()
{
    pixItem->setScaleValue(0);
    pixItem->setZoomState(RESET);
    pixItem->setPos(0, 0);
    m_graphicsView->resetMatrix(); //重置图片
}

//切换图片
void MainWidget::on_pbt_changeImage_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                this, tr("open image file"),
                "./", tr("Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)"));
    if(fileName.isEmpty())
    {
//        QMessageBox::warning(this, tr("警告"), tr("打开图片失败，请重新选择图片！"),
//                             NULL, QMessageBox::Yes);
        return;
    }

    m_graphicsScene->removeItem(pixItem);   //将上一个图元从场景中移除,重新添加新的图元
    QPixmap *pixmap = new QPixmap(fileName);
    pixItem = new PixItem(pixmap);          //实例化自定义类的一个对象,传入一个图片用于显示
    m_graphicsScene->addItem(pixItem);      //将该图元对象添加到场景中，并设置此图元在场景中的位置为中心(0,0)
    pixItem->setPos(0, 0);
    on_pbt_reset_clicked();
}

//点击处于【放大状态】后，点击图片才有放大的效果
void MainWidget::on_pbt_setZoomInState_clicked()
{
    pixItem->setZoomState(ZOOM_IN);
}

//点击处于【缩小状态】后，点击图片才有所缩小的效果
void MainWidget::on_pbt_setZoomOutState_clicked()
{
    pixItem->setZoomState(ZOOM_OUT);
}
