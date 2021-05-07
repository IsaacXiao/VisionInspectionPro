#ifndef ZH_CONVERT_H
#define ZH_CONVERT_H

#include "opencv2/opencv.hpp"
#include <QDebug>

namespace
{
	///参数说明
	///clone是否拷贝一个副本
	///rb_swap颜色通道是否转换
	QImage cvMat2QImage(const cv::Mat& mat, bool clone, bool rb_swap)
	{
		const uchar *pSrc = (const uchar*)mat.data;
		// 8-bits unsigned, NO. OF CHANNELS = 1
		if (mat.type() == CV_8UC1)
		{
			//QImage image(mat.cols, mat.rows, QImage::Format_Grayscale8);
			QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
			if (clone) return image.copy();
			return image;
		}
		// 8-bits unsigned, NO. OF CHANNELS = 3
		else if (mat.type() == CV_8UC3)
		{
			// Create QImage with same dimensions as input Mat
			QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
			if (clone)
			{
				if (rb_swap) return image.rgbSwapped();
				return image.copy();
			}
			else
			{
				if (rb_swap)
				{
					cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
				}
				return image;
			}
	
		}
		else if (mat.type() == CV_8UC4)
		{
			qDebug() << "CV_8UC4";
			QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
			if (clone) return image.copy();
			return image;
		}
		else
		{
			qDebug() << "ERROR: Mat could not be converted to QImage.";
			return QImage();
		}
	}
}

#ifdef _WIN64

#include <QString>
#include <QTextCodec>

inline QString Gb2312ToUnicode(const char *gb2312)
{
    //因为这个指针会在很多地方都要用到
    //所以使用static关键字延长它的生命周期
    //直到程序运行结束以后才释放
    static QTextCodec *codec = QTextCodec::codecForName("GB2312");

    return codec->toUnicode( gb2312 );
}

inline QString Utf8ToUnicode(const char *utf8)
{
    static QTextCodec *codec = QTextCodec::codecForName("utf-8");
    return codec->toUnicode( utf8 );
}

#else

//Linux无需转码

#define Gb2312ToUnicode
#define Utf8ToUnicode

#endif

#endif // ZH_CONVERT_H
