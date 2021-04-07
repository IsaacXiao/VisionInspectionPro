
#ifndef TYPE_DEFINE_HEAD_H
#define TYPE_DEFINE_HEAD_H

#include <string>
#include <vector>
#include <map>
#include <cstdint>
#include "opencv2/opencv.hpp"
#include <memory>

/// <summary>
/// ͳһ�淶ָ�붨��
/// Ĭ��ʹ��ԭ��ָ��
/// ������������ָ��
/// �;���������ָ��
/// ����Ҫ�ĵط�
/// ��ģ���ػ�����
/// </summary>
template<typename T>
struct PointType
{
	typedef T Org;
	typedef T* Ptr;
};

class EmptyClass
{
};

using ImgType = cv::Mat;

template<>
struct PointType<ImgType>
{
	using Org = ImgType;
	using Ptr = std::shared_ptr<ImgType>;
};

using ImgTypeOrg = PointType<ImgType>::Org;
using ImgTypePtr = PointType<ImgType>::Ptr;

///essential data type
enum BINARY { ZERO = 0, ONE };

typedef int			ERROR_CODE;
typedef unsigned short USHORT;
typedef unsigned int UINT;
typedef char					CHAR;
typedef char*					PCHAR;
typedef unsigned char			UCHAR;
typedef unsigned char*			PUCHAR;
//typedef long	long	LONG;

typedef std::string STRING;

template<typename T>
using VECTOR = std::vector<T>;

typedef bool		IS_SUCCESS;
#define SUCCESS ZERO;
#define FAILURE ONE;

enum class LOG_LEVEL : std::uint32_t { TRACK = 0, WARN, HIGH_WARN, ERR, DEAD };
enum FRAMWORK_PART { CAMERAGRABBER = 0, PLCAGENT, MEDIATOR, ALGPROCESSOR, EXPORT, FACADE, MAIN, LOGGER, DEFAULT };

#endif