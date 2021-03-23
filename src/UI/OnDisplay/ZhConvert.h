#ifndef ZH_CONVERT_H
#define ZH_CONVERT_H

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
