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
#ifndef __D_DREAM2D_WINGUI_DRIVER
#define __D_DREAM2D_WINGUI_DRIVER
#include "IVideoDriver.h"
#include "CHMemdcCanvans.h"
#ifdef DREAM2D_WIN32
#include <Windows.h>
class CWinGUIDriver:public IVideoDriver {
public:
	CWinGUIDriver(HWND hwnd,s32 sWidth,s32 sHeight) {
		m_hWnd = hwnd;
		m_Canvans = new CHMemdcCanvans(hwnd,sWidth,sHeight);
	}
	
	virtual ~CWinGUIDriver() {
		m_Canvans->drop();
		m_Canvans = NULL;
	}
	void BeginScene(d_bool clearScreen);
	void EndScene();
	u32 DrawPic(s32 x0,s32 y0,s32 sWidth,s32 sHeight,ICanvans* source,s32 sx0,s32 sy0,COPY_SELECTION sel);
	u32 DrawTextW(wchar_t* text,int x0,int y0);
	u32 DrawTextA(char* text,int x0,int y0);
private:
	CHMemdcCancans* m_Canvans;
	HWND m_hWnd;
};
#endif
#endif