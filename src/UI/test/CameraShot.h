#pragma once

#include <QLabel>
#include <vector>
#include <string>

/* ���ŷ��� */
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

#define EDGPADDING       3        //���ܱ�Ե��������
#define CORPADDING       4        //�Ľǿ�������

#define MIN_WIDTH        3        //���������С���
#define MIN_HEIGHT       3        //���������С�߶�

#define POINT_WIDTH      4        //��Ե9��Ŀ��
#define POINT_HEIGHT     4        //��Ե9��ĸ߶�

#define EDGE_WIDTH       2        //�߿�Ŀ��
#define MIDDLELINE_WIDTH 1        //�����ߵĿ��

#define DRAW_TEN_POINT            //����ʮ����
#define DRAW_SUB_LINE             //���Ƹ�����

class QMenu;
class QAction;

class CameraShot : public QLabel
{
	Q_OBJECT

public:
    CameraShot(QWidget *parent = nullptr);
    ~CameraShot();
	QRect getRoiRect() const;               //��ȡ�Ѿ�Ȧѡ�Ŀ� �ⲿ����
	void setBackImage(const QImage &img);   //���ñ���ͼƬ  �ⲿ����

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
	void initViewer();                         //��ʼ��
	void saveROIImage();                       //��ROI�����ͼƬ�洢����
	EmDirection region(const QPoint &point);   //�������λ�����������״
	void scaleRect(const QPoint &mousePoint);  //���ž���
	void paintRect(const QPoint &mousePoint);  //���ƾ���
	void moveRect(const QPoint &mousePoint);   //�ƶ�����

	void softTrigger();
	void openImage();

	

private:
	bool m_bPainterPressed;        //�Ƿ����ڻ���
	bool m_bMovedPressed;          //�Ƿ������϶�
	bool m_bScalePressed;          //�Ƿ��������Ŵ�С
	QPoint m_paintStartPoint;      //���Ƶĳ�ʼλ��
	QPoint m_moveStartPoint;       //�϶��ĳ�ʼλ��
	QRect m_roiRect;               //���Ƶ�ROI
	EmDirection m_emCurDir;        //�϶��ķ���

	QImage m_backImage;            //����ͼ

	QMenu *m_pOptMenu;
	QAction *m_pDelAction;
	QAction *m_pSaveAction;
	QAction *m_pSoftTriggerAction;
	QAction *m_pOpenImage;

	//��ʾ������
	QString   m_commResult;   //ͨѶ���
	QString   m_result;       //�����
	QString   m_resultType;   //覴�����
	QString   m_detectNum;    //�������
	QString   m_detectOkNum;   //���OK��
	QString   m_detectNgNum;  //���NG��
	QString   m_detectTbaNum; //���TBA��

signals:
	void sigSoftTrigger(int num);
	void sigOpenImage(int num);
	void sigSaveROI(int num);
};
