#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QGraphicsView>    //视图类
#include <QGraphicsScene>   //场景类
#include <QGraphicsItem>    //图元类

#include "pixitem.h"
#include <math.h>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void on_pbt_zoomIn_clicked();            //放大图片

    void on_pbt_zoomOut_clicked();          //缩小图片

    void on_pbt_reset_clicked();                //重置图片

    void on_pbt_changeImage_clicked();          //更换图片

    void on_pbt_setZoomInState_clicked();

    void on_pbt_setZoomOutState_clicked();

private:
    Ui::MainWidget *ui;
    PixItem *pixItem;       //自定义的图元类
    QGraphicsScene *m_graphicsScene;  //场景
    QGraphicsView *m_graphicsView;
};

#endif // MAINWIDGET_H
