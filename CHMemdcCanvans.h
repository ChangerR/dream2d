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
	CHdcCanvans(HWND hwnd,s32 sWidth,s32 sHeight):ICanvans(COLOR_A8R8G8B8) {
		HDC hdc = GetDC(hwnd);
		m_hDc = CreateCompatibleDC(hdc);
		BITMAPINFOHEADER *pbmiDIB = ( BITMAPINFOHEADER * ) &dibheader;

		memset( &dibheader, 0, sizeof( dibheader ) );
		m_pitch = (sWidth*32 +31)>>5;
		m_Width = (u32)sWidth;
		m_Height = (u32)sHeight;
		pbmiDIB->bmiHeader.biSize          = sizeof(BITMAPINFOHEADER);
		pbmiDIB->bmiHeader.biWidth         = sWidth;
		pbmiDIB->bmiHeader.biHeight        = sHeight;
		pbmiDIB->bmiHeader.biPlanes        = 1;
		pbmiDIB->bmiHeader.biBitCount      = 32;
		pbmiDIB->bmiHeader.biCompression   = BI_RGB;
		pbmiDIB->bmiHeader.biSizeImage     = 0;
		pbmiDIB->bmiHeader.biXPelsPerMeter = 0;
		pbmiDIB->bmiHeader.biYPelsPerMeter = 0;
		pbmiDIB->bmiHeader.biClrUsed       = 256;
		pbmiDIB->bmiHeader.biClrImportant  = 256;

		void* pbuffer;
		m_hDIBSection = CreateDIBSection( hdc,
		                                  pbmiDIB,
		                                  DIB_RGB_COLORS,
		                                  (void**)&pbuffer,
		                                  NULL,
		                                  0 );
		if ( pbmiDIB->bmiHeader.biHeight > 0 ) {
			m_buffer	= pbuffer + ( sHeight - 1 ) * sWidth * 4;
			pitch		= -pitch;
		} else {
			m_buffer	= pbuffer;
		}
		memset(pbuffer, 0xff, sWidth *sHeight*4 );
		SeleteObject(m_hDc,m_hDIBSection);
		ReleaseDC(hwnd,hdc);
		SetBkMode(m_hDc,TRANSPARENT);
	}
	virtual ~CHdcCanvans() {
		if(m_hDc) {
			DeleteDc(m_hDc);
			m_hDc = NULL;
		}
		if(m_hDIBSection) {
			DeleteObject(m_hDIBSection);
			m_hDIBSection = NULL;
		}
	}
	u8* lock() {
		return m_buffer;
	}
	void unlock() {

	}
	HDC getMemDc() const {
		return m_hDc;
	}
	//friend class CWinGUIDriver;
private:
	HDC m_hDc;
	u8* m_buffer;
	HBITMAP m_hDIBSection;
};

#endif
#endif