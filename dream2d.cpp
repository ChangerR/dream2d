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
#include "dream2d.h"
#ifdef DREAM2D_WIN32
#include "CDreamDeviceWin32.h"
CDreamDeviceWin32* createDeviceWin32(DRIVER_TYPE driver_type,u32 uWidth,u32 uHeight,COLOR_FORMAT f) {
	CDreamDeviceWin32* pDevice = new CDreamDeviceWin32(driver_type,uWidth,uHeight);
	return pDevice;
}
#else
IDreamDevice* createDeviceWin32(DRIVER_TYPE driver_type,u32 uWidth,u32 uHeight,COLOR_FORMAT f) {
	return (IDreamDevice*)0;
}
#endif

IDreamDevice* createDevice(DRIVER_TYPE driver_type,u32 uWidth,u32 uHeight,COLOR_FORMAT f) {
	#ifdef DREAM2D_WIN32
		return createDeviceWin32(driver_type,uWidth,uHeight,f);
	#endif
	return NULL;
}
