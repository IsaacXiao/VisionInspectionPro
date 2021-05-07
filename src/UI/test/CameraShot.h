#pragma once

#include <QLabel>
#include <vector>
#include <string>

/* 缩放方向 */
enum EmDirection
{
	DIR_TOP = 0,
	DIR_BOTTOM,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_LEFTTOP,
	DIR_LEFTBOTTOM,
	DIR_RIGHTTOP,
	DIR_RIGHTBOTTOM,
	DIR_MIDDLE,
	DIR_NONE
};

#define EDGPADDING       3        //四周边缘可拉伸宽度
#define CORPADDING       4        //四角可拉伸宽度

#define MIN_WIDTH        3        //可拉伸的最小宽度
#define MIN_HEIGHT       3        //可拉伸的最小高度

#define POINT_WIDTH      4        //边缘9点的宽度
#define POINT_HEIGHT     4        //边缘9点的高度

#define EDGE_WIDTH       2        //边框的宽度
#define MIDDLELINE_WIDTH 1        //辅助线的宽度

#define DRAW_TEN_POINT            //绘制十个点
#define DRAW_SUB_LINE             //绘制辅助线

class QMenu;
class QAction;

class CameraShot : public QLabel
{
	Q_OBJECT

public:
    CameraShot(QWidget *parent = nullptr);
    ~CameraShot();
	QRect getRoiRect() const;               //获取已经圈选的框 外部调用
	void setBackImage(const QImage &img);   //设置背景图片  外部调用

	void putText(std::vector<QString>&  showText);
	void putRect(std::vector<QRect>&  showRect);
	void putRoi(std::vector<QRect>&  showRoi);

	int num;

	std::vector<QRect> m_regionRect;
	std::vector<QRect> m_showRoi;

	QString frame_num_{ "" };
	QString camera_id_{ "" };
protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *ev);
	void mouseMoveEvent(QMouseEvent *ev);
	void mouseReleaseEvent(QMouseEvent *ev);
	void keyPressEvent(QKeyEvent *ev);
	void contextMenuEvent(QContextMenuEvent *ev);

private:
	void initViewer();                         //初始化
	void saveROIImage();                       //把ROI区域的图片存储下来
	EmDirection region(const QPoint &point);   //根据鼠标位置设置鼠标形状
	void scaleRect(const QPoint &mousePoint);  //缩放矩形
	void paintRect(const QPoint &mousePoint);  //绘制矩形
	void moveRect(const QPoint &mousePoint);   //移动矩形

	void softTrigger();
	void openImage();

	

private:
	bool m_bPainterPressed;        //是否正在绘制
	bool m_bMovedPressed;          //是否正在拖动
	bool m_bScalePressed;          //是否正在缩放大小
	QPoint m_paintStartPoint;      //绘制的初始位置
	QPoint m_moveStartPoint;       //拖动的初始位置
	QRect m_roiRect;               //绘制的ROI
	EmDirection m_emCurDir;        //拖动的方向

	QImage m_backImage;            //背景图

	QMenu *m_pOptMenu;
	QAction *m_pDelAction;
	QAction *m_pSaveAction;
	QAction *m_pSoftTriggerAction;
	QAction *m_pOpenImage;

	//显示处理结果
	QString   m_commResult;   //通讯结果
	QString   m_result;       //检测结果
	QString   m_resultType;   //瑕疵类型
	QString   m_detectNum;    //检测总数
	QString   m_detectOkNum;   //检测OK数
	QString   m_detectNgNum;  //检测NG数
	QString   m_detectTbaNum; //检测TBA数

signals:
	void sigSoftTrigger(int num);
	void sigOpenImage(int num);
	void sigSaveROI(int num);
};
