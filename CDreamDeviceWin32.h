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
#ifndef __D_DREAM2DDEVICE_WIN32
#define __D_DREAM2DDEVICE_WIN32
#include <Windows.h>
#include "IDreamDevice.h"
#ifdef DREAM2D_WIN32
class CDreamDeviceWin32 :public IDreamDevice {
public:
	CDreamDeviceWin32(DRIVER_TYPE driver,u32 uWidth = 640,u32 uHeight = 480):IDreamDevice(DEVICE_WIN32) {
		m_Width = uWidth;
		m_Height = uHeight;
		m_hInstance = GetModuleHandle(0);
		InitWin32Device();
		initDriver(driver);
	}
	virtual ~CDreamDeviceWin32() {

	}
	virtual void showVersion() const  {

	}
	virtual char* getVersionString() const {
		return "Dream2d Win32 0.1";
	}
	void initDriver(DRIVER_TYPE driver,COLOR_FORMAT f);
	void InitWin32Device();
	virtual s32 run();
private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	u32 m_Width,m_Height;
};
#endif

#endif