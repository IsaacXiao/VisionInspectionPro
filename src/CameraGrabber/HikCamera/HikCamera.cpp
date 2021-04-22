// HikCamera.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "HikCamera.h"

HikCamera::HikCamera(const STRING& cfg) :
	ICameraGrabber(cfg)
{
}

HikCamera::~HikCamera()
{
}
