#include "DalsaDll.h"

#ifdef WIN32
#include <Windows.h>
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	return TRUE;
}
#endif

#include <string.h>

////
////通过名称Id创建对象
////
extern "C" DALSA_CAMERA_API CameraGrabberPtr Create( const char* name_ptr, const char* config_path )
{
	if( 0 == strcmp( name_ptr, DalsaCamera::Name() ) )
	{
		return new DalsaCamera(config_path);
	}
	return nullptr;	
}

////
////获取所提供的名称Id数量
////
extern "C" DALSA_CAMERA_API short Number()
{
	return 1;
}

////
////获取名称Id列表
////
extern "C" DALSA_CAMERA_API void Names( char** names_ptr )
{
	strcpy( names_ptr[0], DalsaCamera::Name() );	
}

////
////保证谁创建谁释放的原理释放对象空间.
////
extern "C" DALSA_CAMERA_API void Remove( CameraGrabberPtr ptr )
{
	delete ptr;
}
