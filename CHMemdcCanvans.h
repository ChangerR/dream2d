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
#ifndef __D_DREAM2D_CHMEMDCCANVANS
#define __D_DREAM2D_CHMEMDCCANVANS
#include "ICanvans.h"
#ifdef DREAM2D_WIN32
#include <windows.h>
class CWinGUIDriver;
class CHMemdcCanvans :public ICanvans {
public:
	CHMemdcCanvans(HWND hwnd,s32 sWidth,s32 sHeight):ICanvans(COLOR_A8R8G8B8) {
		HDC hdc = GetDC(hwnd);
		m_hDc = CreateCompatibleDC(hdc);
		BITMAPINFOHEADER dibheader;
		BITMAPINFOHEADER *pbmiDIB = ( BITMAPINFOHEADER * ) &dibheader;

		memset( &dibheader, 0, sizeof( dibheader ) );
		m_pitch = ((sWidth*32 +31)>>5)<<2;
		m_Width = (u32)sWidth;
		m_Height = (u32)sHeight;
		pbmiDIB->biSize          = sizeof(BITMAPINFOHEADER);
		pbmiDIB->biWidth         = sWidth;
		pbmiDIB->biHeight        = sHeight;
		pbmiDIB->biPlanes        = 1;
		pbmiDIB->biBitCount      = 32;
		pbmiDIB->biCompression   = BI_RGB;
		pbmiDIB->biSizeImage     = 0;
		pbmiDIB->biXPelsPerMeter = 0;
		pbmiDIB->biYPelsPerMeter = 0;
		pbmiDIB->biClrUsed       = 256;
		pbmiDIB->biClrImportant  = 256;

		u8* pbuffer;
		m_hDIBSection = CreateDIBSection( hdc,
		                                  (BITMAPINFO*)pbmiDIB,
		                                  DIB_RGB_COLORS,
		                                  (void**)&pbuffer,
		                                  NULL,
		                                  0 );
		if ( pbmiDIB->biHeight > 0 ) {
			m_buffer	= pbuffer + ( sHeight - 1 ) * sWidth * 4;
			m_pitch		= -m_pitch;
		} else {
			m_buffer	= pbuffer;
		}
		memset(pbuffer, 0xff, sWidth *sHeight*4 );
		SelectObject(m_hDc,m_hDIBSection);
		ReleaseDC(hwnd,hdc);
		SetBkMode(m_hDc,TRANSPARENT);
	}
	virtual ~CHMemdcCanvans() {
		if(m_hDc) {
			DeleteDC(m_hDc);
			m_hDc = NULL;
		}
		if(m_hDIBSection) {
			DeleteObject(m_hDIBSection);
			m_hDIBSection = NULL;
		}
	}
	u32* getPallet() const {
		return NULL;
	}
	u8* lock() {
		return m_buffer;
	}
	void unlock() {

	}
	HDC getMemDc() const {
		return m_hDc;
	}
	CANVANS_TYPE getCanvansType() const {
		return CANVANS_WINGDI;
	}
	u32 CopyCanvans(s32 x0,s32 y0,s32 sWidth,s32 sHeight,ICanvans* source,s32 sx0,s32 sy0,COPY_SELECTION sel) {
		if (source->getCanvansType() == CANVANS_WINGDI&&sel == COPY_NORMAL)
		{
			BitBlt(m_hDc,x0,y0,sWidth,sHeight,((CHMemdcCanvans*)source)->getMemDc(),sx0,sy0,SRCCOPY);
		}else {
			return ICanvans::CopyCanvans(x0,y0,sWidth,sHeight,source,sx0,sy0,sel);
		}
		return 0;
	}
	//friend class CWinGUIDriver;
private:
	HDC m_hDc;
	u8* m_buffer;
	HBITMAP m_hDIBSection;
};

#endif
#endif