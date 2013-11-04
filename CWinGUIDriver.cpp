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
#include "CMemoryCancans.h"
#include "CCanvansLoader.h"
#include "CCanvansTool.h"
#ifdef DREAM2D_WIN32
void CWinGUIDriver::BeginScene(d_bool clearScreen) {
	if(clearScreen == d_false) 
		return;
	u8* buf = m_Canvans->lock();
	for(int i = 0;i < m_Canvans->m_Height;i++) {
		memset(buf,0x0,m_Canvans->m_pitch > 0?m_Canvans->m_pitch:-m_Canvans->m_pitch);
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
u32 CWinGUIDriver::DrawTextW(wchar_t* text,int x0,int y0) {
	return !TextOutW(m_Canvans->getMemDc(),x0,y0,text,wcslen(text));
}
u32 CWinGUIDriver::DrawTextA(char* text,int x0,int y0) {
	return !TextOutA(m_Canvans->getMemDc(),x0,y0,text,strlen(text));
}

ICanvans* CWinGUIDriver::CreateCanvans( s32 sWidth,s32 sHeight,COLOR_FORMAT f,CANVANS_TYPE t )
{
	ICanvans* pCanvans = NULL;
	switch(t) {
	case CANVANS_WINGDI:
	case CANVANS_DEFAULT:
		pCanvans = new CHMemdcCanvans(m_hWnd,sWidth,sHeight);
		break;
	case CANVANS_MEMORY:
		pCanvans = new CMemoryCanvans(sWidth,sHeight,f);
		break;
	default:
		break;
	}
	return pCanvans;
}

ICanvans* CWinGUIDriver::LoadCanvans(const char* filename) {
	return CCanvansLoader::LoadBmpFile(filename);
}

u32 CWinGUIDriver::DrawRectAngle( s32 x0,s32 y0,s32 sWidth,s32 sHeight,u32 color )
{	
	x0 = x0 > 0 ? x0:(sWidth+=x0,0);
	y0 = y0 > 0 ? y0:(sHeight+=y0,0);	
	sWidth = (x0 + sWidth) > m_Canvans->m_Width ? (m_Canvans->m_Width - x0):sWidth;
	sHeight = (y0 + sHeight) >m_Canvans->m_Height ? (m_Canvans->m_Height - y0):sHeight;
	if(x0 >= m_Canvans->m_Width || y0 >= m_Canvans->m_Height||sWidth <= 0||sHeight <= 0)
		return 1;
	u8* buf = m_Canvans->lock();
	u32 alpha = (color >> 24) + 1;
	buf += m_Canvans->m_pitch*y0 + x0*4;
	for (int i = 0; i < sHeight;i++)
	{
		for(int j = 0;j < sWidth;j++) {
			*(buf + 4*j) = (*(buf + 4*j)*(256 - alpha) + (color&0x000000ff)* alpha) >>8;
			*(buf + 4*j + 1) = (*(buf + 4*j + 1)*(256 - alpha) + ((color&0x0000ff00)>>8)* alpha) >>8;
			*(buf + 4*j + 2) = (*(buf + 4*j + 2)*(256 - alpha) + ((color&0x00ff0000)>>16)* alpha) >>8;
		}
		buf += m_Canvans->m_pitch;
	}
	m_Canvans->unlock();
	return 0;
}

u32 CWinGUIDriver::DrawLine( s32 x0,s32 y0,s32 x1,s32 y1,u32 color )
{
	/*
	POINT pt;	
		::MoveToEx(this->m_Canvans->getMemDc(),x0,y0,&pt);
		::LineTo(this->m_Canvans->getMemDc(),x1,y1);
		::MoveToEx(this->m_Canvans->getMemDc(),pt.x,pt.y,&pt);*/
	
	return CCanvansTool::DrawLine2(m_Canvans,x0,y0,x1,y1,color);
}

#endif

