
#include <QPainter>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QStandardPaths>
#include <QFileDialog>
#include <QDebug>

#include "CameraShot.h"


CameraShot::CameraShot(QWidget *parent)
	: QLabel(parent)
{
	this->initViewer();

	num = 0;

	m_commResult = " ";   //通讯结果
	m_result = " ";       //检测结果
	m_resultType = " ";   //瑕疵类型
	m_detectNum = " ";    //检测总数
	m_detectOkNum = " ";    //检测OK数
	m_detectNgNum = " ";  //检测NG数
	m_detectTbaNum = " "; //检测TBA数
}

CameraShot::~CameraShot()
{
}

void CameraShot::initViewer()
{
	m_bPainterPressed = false;
	m_bMovedPressed = false;
	m_bScalePressed = false;
	m_roiRect = QRect(0, 0, 0, 0);
	m_emCurDir = EmDirection::DIR_NONE;

	this->setMouseTracking(true);
	this->setFocusPolicy(Qt::StrongFocus);

	m_pOptMenu = new QMenu(this);
	m_pDelAction = new QAction(QStringLiteral("删除"), this);
	connect(m_pDelAction, &QAction::triggered, this, [&]() { m_roiRect = QRect(0, 0, 0, 0); });
	m_pSaveAction = new QAction(QStringLiteral("保存"), this);
    connect(m_pSaveAction, &QAction::triggered, this, &CameraShot::saveROIImage);

	m_pSoftTriggerAction = new QAction(QStringLiteral("触发"), this);
    connect(m_pSoftTriggerAction, &QAction::triggered, this, &CameraShot::softTrigger);

	m_pOpenImage = new QAction(QStringLiteral("打开图像"), this);
    connect(m_pOpenImage, &QAction::triggered, this, &CameraShot::openImage);

	m_pOptMenu->setStyleSheet("background:rgba(135,206,235,100);");
	m_pOptMenu->addAction(m_pDelAction);
	m_pOptMenu->addAction(m_pSaveAction);
	m_pOptMenu->addAction(m_pSoftTriggerAction);
	m_pOptMenu->addAction(m_pOpenImage);
}

void CameraShot::softTrigger()
{
	assert(false);
	emit sigSoftTrigger(num);
}

void CameraShot::openImage()
{
	emit sigOpenImage(num);
}


/**
 * @brief				保存roi图形
 *
 * @return				void
 */
void CameraShot::saveROIImage()
{
	//QString fileName = QFileDialog::getSaveFileName(this, "Save", QStandardPaths::writableLocation(QStandardPaths::PicturesLocation), "*.png");
	//if (fileName.isEmpty())
	//{
	//	return;
	//}

	//QImage saveImg = m_backImage.copy(m_roiRect);
	//saveImg.save(fileName);

	//QImage saveImg = m_backImage.copy();
	//saveImg.save("saveImage.jpg");

	emit sigSaveROI(num);
}

/**
 * @brief				获取绘制的矩形
 *
 * @return				绘制的矩形
 */
QRect CameraShot::getRoiRect() const
{
	return m_roiRect;
}

/**
 * @brief				设置背景图片
 * @param img        	QImage图片
 *
 * @return				void
 */
void CameraShot::setBackImage(const QImage & img)
{
	m_backImage = img;
	this->setMinimumSize(img.width(), img.height());
	update();
}

/**
 * @brief				绘制矩形
 * @param event         绘图事件
 *
 * @return				void
 */
void CameraShot::paintEvent(QPaintEvent * event)
{
#if 1
	QLabel::paintEvent(event);

	if (m_backImage.isNull())
		return;

	QPixmap rawImg = QPixmap::fromImage(m_backImage);
	QString strPoint = QString("X:%0, Y:%1").arg(m_roiRect.x()).arg(m_roiRect.y());           //位置信息
	QString strSize = QString("W:%0, H:%1").arg(m_roiRect.width()).arg(m_roiRect.height());   //大小信息

	QPen pen;
	pen.setColor(Qt::yellow);
	pen.setWidth(EDGE_WIDTH);
	
	QFont font;
	font.setPixelSize(10);

	QPainter painter;
	painter.begin(this);
	painter.setBrush(QBrush(QColor(0, 0, 200, 120)));
	painter.setPen(pen);
	painter.setFont(font);
	painter.drawPixmap(0, 0, rawImg);
	painter.drawText(m_roiRect.topLeft().x(), m_roiRect.topLeft().y() - 5, strSize);
	painter.drawText(m_roiRect.topLeft().x(), m_roiRect.topLeft().y() - 18, strPoint);
	painter.drawRect(m_roiRect);

	QPen dashPen2(Qt::magenta);
	dashPen2.setWidth(8);
	dashPen2.setWidth(MIDDLELINE_WIDTH);
	dashPen2.setStyle(Qt::SolidLine);
	painter.setBrush(Qt::transparent);
	painter.setPen(dashPen2);
    for (auto i = 0; i < m_regionRect.size(); i++)
	{
		painter.drawRect(m_regionRect[i].topLeft().x(), m_regionRect[i].topLeft().y(), m_regionRect[i].width(), m_regionRect[i].height());
	}

	if (m_roiRect.width() != 0 && m_roiRect.height() != 0)
	{
#ifdef DRAW_SUB_LINE
		//绘制中间十字架
		QPen dashPen(Qt::white);
		dashPen.setWidth(MIDDLELINE_WIDTH);
		dashPen.setStyle(Qt::DashDotLine);
		painter.setPen(dashPen);
		painter.drawLine(m_roiRect.topLeft().x() + m_roiRect.width() / 2, m_roiRect.topLeft().y() + EDGE_WIDTH, m_roiRect.bottomRight().x() - m_roiRect.width() / 2, m_roiRect.bottomRight().y());
		painter.drawLine(m_roiRect.topLeft().x() + EDGE_WIDTH, m_roiRect.topLeft().y() + m_roiRect.height() / 2, m_roiRect.bottomRight().x(), m_roiRect.bottomRight().y() - m_roiRect.height() / 2);
#endif

#ifdef DRAW_TEN_POINT
		//绘制边缘十个点
		painter.setBrush(Qt::green);
		pen.setWidth(0);
		painter.setPen(pen);

		painter.drawRect(m_roiRect.topLeft().x(), m_roiRect.topLeft().y(), POINT_WIDTH, POINT_HEIGHT); //左上角
		painter.drawRect(m_roiRect.topLeft().x(), m_roiRect.topLeft().y() + m_roiRect.height() / 2 - POINT_WIDTH / 2, POINT_WIDTH, POINT_HEIGHT); //左边中心点
		painter.drawRect(m_roiRect.bottomLeft().x(), m_roiRect.bottomLeft().y()- POINT_WIDTH, POINT_WIDTH, POINT_HEIGHT); //左下角
		painter.drawRect(m_roiRect.topLeft().x() + m_roiRect.width() / 2 - POINT_WIDTH / 2, m_roiRect.topLeft().y(), POINT_WIDTH, POINT_HEIGHT);  //顶部中心
		painter.drawRect(m_roiRect.topLeft().x() + m_roiRect.width() / 2 - POINT_WIDTH /2, m_roiRect.topLeft().y() + m_roiRect.height() / 2 - POINT_WIDTH / 2, POINT_WIDTH, POINT_HEIGHT);  //中心点
		painter.drawRect(m_roiRect.bottomLeft().x() + m_roiRect.width() / 2 - POINT_WIDTH / 2, m_roiRect.bottomLeft().y() - POINT_WIDTH, POINT_WIDTH, POINT_HEIGHT); //底部中心点
		painter.drawRect(m_roiRect.topRight().x() - POINT_WIDTH, m_roiRect.topRight().y(), POINT_WIDTH, POINT_HEIGHT); //右上角
		painter.drawRect(m_roiRect.topRight().x() - POINT_WIDTH / 2, m_roiRect.topRight().y() + m_roiRect.height() / 2 - POINT_WIDTH /2, POINT_WIDTH, POINT_HEIGHT); //右边中心点
		painter.drawRect(m_roiRect.bottomRight().x() - POINT_WIDTH, m_roiRect.bottomRight().y() - POINT_WIDTH, POINT_WIDTH, POINT_HEIGHT); //右下角点
#endif
	}
	
	QPen dashPen3(Qt::darkGreen);
	painter.setPen(dashPen3);
	painter.setBrush(Qt::transparent);
	
	for (int i = 0; i < m_showRoi.size(); i++)
	{
		painter.drawRect(m_showRoi[i].topLeft().x(), m_showRoi[i].topLeft().y(), m_showRoi[i].width(), m_showRoi[i].height());
	}
	
	QPen dashPen4(Qt::darkGreen);
	QFont font4;
	font4.setPixelSize(26);
	painter.setPen(dashPen4);
	painter.setFont(font4);
	//painter.drawText(10, 50, QStringLiteral("通讯状态: ") + m_commResult);
	//painter.drawText(10, 130, QStringLiteral("检测总数: ") + m_detectNum);
	if (m_result == "OK")
	{
		painter.drawText(10, 90, QStringLiteral("检测结果: ") + m_result);
	}
	else
	{
		QPen dashPen5(Qt::red);
		painter.setPen(dashPen5);
		painter.drawText(10, 90, frame_num_ + m_result);
	}
	

	//if (num < 3)
	//{
	//	font3.setPixelSize(16);
	//	painter.setFont(font3);
	//	painter.drawText(10, 280, QStringLiteral("通讯状态: ") + m_commResult);
	//	painter.drawText(10, 300, QStringLiteral("检测结果: ") + m_result);
	//	painter.drawText(10, 320, QStringLiteral("瑕疵类型: ") + m_resultType);
	//	painter.drawText(10, 340, QStringLiteral("检测总数: ") + m_detectNum);
	//	painter.drawText(200, 280, QStringLiteral("检测OK数: ") + m_detectOkNum);
	//	painter.drawText(200, 300, QStringLiteral("检测NG数: ") + m_detectNgNum);
	//	painter.drawText(200, 320, QStringLiteral("检测TBA数: ") + m_detectTbaNum);
	//}
	//else
	//{
	//	font3.setPixelSize(16);
	//	painter.setFont(font3);
	//	painter.drawText(10, 420, QStringLiteral("通讯状态: ") + m_commResult);
	//	painter.drawText(10, 440, QStringLiteral("检测结果: ") + m_result);
	//	painter.drawText(10, 460, QStringLiteral("瑕疵类型: ") + m_resultType);
	//	painter.drawText(10, 480, QStringLiteral("检测总数: ") + m_detectNum);
	//	painter.drawText(200, 420, QStringLiteral("检测OK数: ") + m_detectOkNum);
	//	painter.drawText(200, 440, QStringLiteral("检测NG数: ") + m_detectNgNum);
	//	painter.drawText(200, 460, QStringLiteral("检测TBA数: ") + m_detectTbaNum);
	//}

	painter.end();

	//qDebug() << m_roiRect;
#else
	QLabel::paintEvent(event);

	if (m_backImage.isNull())
		return;
	QPixmap rawImg = QPixmap::fromImage(m_backImage);
	QPainter painter(this);
	painter.begin(&rawImg);
	painter.setBrush(Qt::gray);
	painter.drawRect(30,30,100,100);
	painter.end();
	this->setPixmap(rawImg);
#endif
}

/**
 * @brief				鼠标按下事件 用于拖动绘制缩放起始
 * @param ev	        鼠标事件
 *
 * @return				void
 */
void CameraShot::mousePressEvent(QMouseEvent * ev)
{
	if (ev->buttons() & Qt::LeftButton)
	{
		EmDirection dir = region(ev->pos());     //获取鼠标当前的位置

		if (dir == DIR_MIDDLE)
		{
			//鼠标在矩形中心位置
			this->setCursor(Qt::ClosedHandCursor);
			m_moveStartPoint.setX(ev->pos().x());
			m_moveStartPoint.setY(ev->pos().y());
			m_bMovedPressed = true;
		}
		else if (dir == DIR_NONE)
		{
			//鼠标在矩形外部
			this->setCursor(Qt::ArrowCursor);
			m_bPainterPressed = true;
			m_paintStartPoint.setX(ev->pos().x());
			m_paintStartPoint.setY(ev->pos().y());
		}
		else
		{
			//矩形在矩形边缘
			m_moveStartPoint.setX(ev->pos().x());
			m_moveStartPoint.setY(ev->pos().y());
			m_bScalePressed = true;
			m_emCurDir = dir;
		}
	}
}

/**
 * @brief				鼠标移动事件
 * @param ev         	鼠标事件
 *
 * @return				void
 */
void CameraShot::mouseMoveEvent(QMouseEvent * ev)
{
	if (ev->buttons() & Qt::LeftButton)
	{
		if (m_bPainterPressed)
		{
			//正在绘制状态
			paintRect(ev->pos());
			
		}
		else if (m_bMovedPressed)
		{
			//正在移动状态
			moveRect(ev->pos());
		}
		else if (m_bScalePressed)
		{
			//正在缩放大小状态
			scaleRect(ev->pos());
		}

		//更新界面
		update();
		return;
	}

	//根据鼠标的位置设置当前的鼠标形状
	EmDirection dir = region(ev->pos());

	if (dir == DIR_NONE)
	{
		setCursor(Qt::ArrowCursor);
	}
	else if (dir == DIR_MIDDLE)
	{
		setCursor(Qt::OpenHandCursor);
	}
}

/**
 * @brief				鼠标松开事件
 * @param ev	        鼠标事件
 *
 * @return				void
 */
void CameraShot::mouseReleaseEvent(QMouseEvent * ev)
{
	//判断鼠标是否在矩形中
	if (m_roiRect.contains(ev->pos()))
	{
		//松开鼠标前是否正在拖放
		if (m_bMovedPressed)
		{
			this->setCursor(Qt::OpenHandCursor);
		}
		else
		{
			this->setCursor(Qt::ArrowCursor);
		}
	}

	m_paintStartPoint = QPoint();
	m_bMovedPressed = false;
	m_bPainterPressed = false;
	m_bScalePressed = false;
}

/**
 * @brief				键盘按下事件
 * @param ev	        键盘事件
 *
 * @return				void
 */
void CameraShot::keyPressEvent(QKeyEvent * ev)
{
	if (ev->key() == Qt::Key_Delete)
	{
		m_roiRect = QRect(0,0,0,0);
		update();
	}
}

/**
 * @brief				右键菜单
 * @param ev	        菜单事件
 *
 * @return				void
 */
void CameraShot::contextMenuEvent(QContextMenuEvent * ev)
{
	QPoint mousePos = ev->pos();

	if (m_roiRect.contains(mousePos))
	{
		m_pOptMenu->exec(QCursor::pos());
	}
	
	ev->accept();
}

/**
 * @brief				判断鼠标的位置
 * @param point         鼠标的位置	
 *
 * @return				EmDirection 方向
 */
EmDirection CameraShot::region(const QPoint & point)
{
	int mouseX = point.x();
	int mouseY = point.y();

	QPoint roiTopLeft = m_roiRect.topLeft();
	QPoint roiBottomRight = m_roiRect.bottomRight();

	EmDirection dir = DIR_NONE;

	if (mouseX <= roiTopLeft.x() + CORPADDING && mouseX >= roiTopLeft.x() && mouseY <= roiTopLeft.y() + CORPADDING && mouseY >= roiTopLeft.y())
	{
		//左上角
		this->setCursor(Qt::SizeFDiagCursor);
		dir = DIR_LEFTTOP;
	}
	else if (mouseX >= roiBottomRight.x() - CORPADDING && mouseX < roiBottomRight.x() && mouseY <= roiTopLeft.y() + CORPADDING && mouseY >= roiTopLeft.y())
	{
		//右上角
		this->setCursor(Qt::SizeBDiagCursor);
		dir = DIR_RIGHTTOP;
	}
	else if (mouseX <= roiTopLeft.x() + CORPADDING && mouseX >= roiTopLeft.x() && mouseY >= roiBottomRight.y() - CORPADDING && mouseY <= roiBottomRight.y())
	{
		//左下角
		this->setCursor(Qt::SizeBDiagCursor);
		dir = DIR_LEFTBOTTOM;
	}
	else if (mouseX >= roiBottomRight.x() - CORPADDING && mouseX < roiBottomRight.x() && mouseY >= roiBottomRight.y() - CORPADDING && mouseY <= roiBottomRight.y())
	{
		//右下角
		this->setCursor(Qt::SizeFDiagCursor);
		dir = DIR_RIGHTBOTTOM;
	}
	else if (mouseX >= roiBottomRight.x() - EDGPADDING && mouseX <= roiBottomRight.x() && mouseY >= roiTopLeft.y() && mouseY <= roiBottomRight.y())
	{
		//右边
		this->setCursor(Qt::SizeHorCursor);
		dir = DIR_RIGHT;
	}
	else if (mouseY <= roiTopLeft.y() + EDGPADDING && mouseY >= roiTopLeft.y() && mouseX >= roiTopLeft.x() && mouseX <= roiBottomRight.x())
	{
		//上边
		this->setCursor(Qt::SizeVerCursor);
		dir = DIR_TOP;
	}
	else if (mouseY >= roiBottomRight.y() - EDGPADDING && mouseY <= roiBottomRight.y() && mouseX >= roiTopLeft.x() && mouseX <= roiBottomRight.x())
	{
		//下边
		this->setCursor(Qt::SizeVerCursor);
		dir = DIR_BOTTOM;
	}
	else if (mouseX <= roiTopLeft.x() + EDGPADDING && mouseX >= roiTopLeft.x() && mouseY >= roiTopLeft.y() && mouseY <= roiBottomRight.y())
	{
		//左边
		this->setCursor(Qt::SizeHorCursor);
		dir = DIR_LEFT;
	}
	else if(m_roiRect.contains(point))
	{
		//中间
		dir = DIR_MIDDLE;
	}
	else
	{
		dir = DIR_NONE;
	}

	return dir;
}

/**
 * @brief				缩放矩形
 * @param mousePoint    鼠标的位置
 *
 * @return				void
 */
void CameraShot::scaleRect(const QPoint & mousePoint)
{
	QRect newRect(m_roiRect.topLeft(), m_roiRect.bottomRight());
    //auto width = mousePoint.x() - m_moveStartPoint.x();   //移动的宽度
    //auto height = mousePoint.y() - m_moveStartPoint.y();  //移动的高度

	//根据当前的缩放状态来改变矩形的位置大小信息
	switch (m_emCurDir)
	{
	case DIR_LEFT:
		newRect.setLeft(mousePoint.x());
		break;
	case DIR_RIGHT:
		newRect.setRight(mousePoint.x());
		break;
	case DIR_TOP:
		newRect.setTop(mousePoint.y());
		break;
	case DIR_BOTTOM:
		newRect.setBottom(mousePoint.y());
		break;
	case DIR_LEFTTOP:
		newRect.setTopLeft(mousePoint);
		break;
	case DIR_LEFTBOTTOM:
		newRect.setBottomLeft(mousePoint);
		break;
	case DIR_RIGHTTOP:
		newRect.setTopRight(mousePoint);
		break;
	case DIR_RIGHTBOTTOM:
		newRect.setBottomRight(mousePoint);
		break;
    default:
        break;
	}

	if (newRect.width() < MIN_WIDTH || newRect.height() < MIN_HEIGHT)
	{
		//缩放的大小限制
		return;
	}

	m_roiRect = newRect;
	m_moveStartPoint = mousePoint;  //更新鼠标的起始位置
}

/**
 * @brief				绘制矩形
 * @param mousePoint    鼠标的位置
 *
 * @return				void
 */
void CameraShot::paintRect(const QPoint & mousePoint)
{
	this->setCursor(Qt::ArrowCursor);                    //设置鼠标为指针形状

	int width = mousePoint.x() - m_paintStartPoint.x();  //移动的宽度
	int height = mousePoint.y() - m_paintStartPoint.y(); //移动的高度

	if (width < 0 && height < 0)
	{
		//鼠标向左上角移动
		m_roiRect.setX(mousePoint.x());
		m_roiRect.setY(mousePoint.y());
	}
	else if (width < 0)
	{
		//鼠标向负X位置移动
		m_roiRect.setX(mousePoint.x());
		m_roiRect.setY(m_paintStartPoint.y());
	}
	else if (height < 0)
	{
		//鼠标向负Y位置移动
		m_roiRect.setX(m_paintStartPoint.x());
		m_roiRect.setY(mousePoint.y());
	}
	else
	{
		//正常  向右下移动
		m_roiRect.setX(m_paintStartPoint.x());
		m_roiRect.setY(m_paintStartPoint.y());
	}

	//设置矩形大小 绝对值 避免反方向的产生的负值
	m_roiRect.setSize(QSize(abs(width), abs(height)));
}

/**
 * @brief				绘制矩形
 * @param mousePoint    鼠标的位置
 *
 * @return				void
 */
void CameraShot::moveRect(const QPoint & mousePoint)
{
	this->setCursor(Qt::ClosedHandCursor);

	int width = mousePoint.x() - m_moveStartPoint.x();
	int height = mousePoint.y() - m_moveStartPoint.y();

	QRect ret;
	ret.setX(m_roiRect.x() + width);
	ret.setY(m_roiRect.y() + height);
	ret.setSize(m_roiRect.size());
	m_roiRect = ret;
	m_moveStartPoint = mousePoint;
}


void CameraShot::putText(std::vector<QString>& showText)
{
	if (showText.size() >= 2)
	{
		m_commResult = showText[0];   //通讯结果
		m_result = showText[1];       //检测结果
		m_resultType = showText[2];   //瑕疵类型
		m_detectNum = showText[3];    //检测总数
		//m_detectOkNum = showText[4];  //检测OK数
		//m_detectNgNum = showText[5];  //检测NG数
		//m_detectTbaNum = showText[6]; //检测TBA数
	}
}

void CameraShot::putRect(std::vector<QRect>& showRect)
{
	m_regionRect.clear();
    for (auto i = 0; i < showRect.size(); i++)
	{
		m_regionRect.push_back(showRect[i]);
	}
}

void CameraShot::putRoi(std::vector<QRect>&  showRoi)
{
	m_showRoi.clear();
    for (auto i = 0; i < showRoi.size(); i++)
	{
		m_showRoi.push_back(showRoi[i]);
	}
}

