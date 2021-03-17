
#ifndef TYPE_DEFINE_HEAD_H
#define TYPE_DEFINE_HEAD_H

#include <string>
#include <vector>
#include <map>
#include <cstdint>
#include <functional>

template<typename T>
struct PointType
{
	typedef T* Ptr;
};

class EmptyClass
{
};


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
enum FRAMWORK_PART { MAIN = 0, LOGGER, CAMERAGRABBER, PLCAGENT, ALGPROCESSOR, EXPORT, FACADE, DEFAULT };

#endif