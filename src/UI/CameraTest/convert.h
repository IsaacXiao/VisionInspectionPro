#pragma once

#include <QString>
#include <QTextCodec>

inline QString Gb2312ToUnicode(const char *gb2312)
{
	//��Ϊ���ָ����ںܶ�ط���Ҫ�õ�
	//����ʹ��static�ؼ����ӳ�������������
	//ֱ���������н����Ժ���ͷ�
	static QTextCodec *codec = QTextCodec::codecForName("GB2312");

	return codec->toUnicode(gb2312);
}

inline QString Utf8ToUnicode(const char *utf8)
{
	static QTextCodec *codec = QTextCodec::codecForName("utf-8");
	return codec->toUnicode(utf8);
}
