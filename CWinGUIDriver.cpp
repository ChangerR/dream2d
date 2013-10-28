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
#include "CWinGUIDriver.h"
#ifdef DREAM2D_WIN32
void CWinGUIDriver::BeginScene(d_bool clearScreen) {
	if(clearScreen == d_false) 
		return;
	u8* buf = m_Canvans->lock();
	for(int i = 0;i < m_Canvans->m_Hieght;i++) {
		memset(buf,0xff,m_Canvans->m_pitch > 0?m_Canvans->m_pitch:-m_Canvans->m_pitch);
		buf+=m_Canvans->m_pitch;
	}
	m_Canvans->unlock();
}
void CWinGUIDriver::EndScene() {
	HDC hdc = GetDC(m_hWnd);
	BitBlt(hdc,0,0,m_Canvans->m_Width,m_Canvans->m_Height,m_Canvans->getMemDc(),0,0,SRCCOPY);
	ReleaseDC(m_hWnd,hdc);
}
u32 CWinGUIDriver::DrawPic(s32 x0,s32 y0,s32 sWidth,s32 sHeight,ICanvans* source,s32 sx0,s32 sy0,COPY_SELECTION sel) {	
	return m_Canvans->CopyCanvans(x0,y0,sWidth,sHeight,source,sx0,sy0,sel);
}
u32 DrawTextW(wchar_t* text,int x0,int y0) {
	return !TextOutW(m_Canvans->getMemDc(),x0,y0,text,wcslen(text);
}
u32 DrawTextA(char* text,int x0,int y0) {
	return !TextOutA(m_Canvans->getMemDc(),x0,y0,text,wcslen(text);
}

#endif