/******************************************************************************************************
Dream2d is 2d game engine written by Changer. 
Copyright (C) Changer Stdio. 
This program is free software; 
you can redistribute it and/or modify it under the terms of the GNU General Public License as 
published by the Free Software Foundation; either version 2 of the License, or (at your option) 
any later version.  
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
General Public License for more details.  
You should have received a copy of the GNU General Public License along with this program; if not,
write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, US
******************************************************************************************************/
#ifndef __I_DREAM2D_DREAM2DH
#define __I_DREAM2D_DREAM2DH
#include "IDreamDevice.h"

#ifdef BUILD_DLL
extern "C" {
	__declspec(dllexport) IDreamDevice* createDevice(DRIVER_TYPE driver_type,u32 uWidth,u32 uHeight,COLOR_FORMAT f);
};
#else
extern "C" {
	__declspec(dllimport) IDreamDevice* createDevice(DRIVER_TYPE driver_type,u32 uWidth,u32 uHeight,COLOR_FORMAT f);
};
#endif

#endif