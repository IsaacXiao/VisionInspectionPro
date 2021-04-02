#ifndef IFORDISPLAY_HEADER
#define IFORDISPLAY_HEADER

#include "../include/CommonInclude/TypeDefine.h"

class IForDisplay
{
public:
	IForDisplay(){}
	virtual ~IForDisplay(){}
	virtual void DisplayImage(USHORT camera_id, ImgTypePtr img) = 0;
private:

};


#endif // !IFORDISPLAY_HEADER
