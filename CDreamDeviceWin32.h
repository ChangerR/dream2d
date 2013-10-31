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
#ifdef DREAM2D_WIN32
#include <Windows.h>
#include <WindowsX.h>
#include "IDreamDevice.h"
#include "ICursorControl.h"
class CDreamDeviceWin32 :public IDreamDevice {
public:
	CDreamDeviceWin32(DRIVER_TYPE driver,s32 uWidth = 640,s32 uHeight = 480):IDreamDevice(DEVICE_WIN32) {
		m_Width = uWidth;
		m_Height = uHeight;
		m_hInstance = GetModuleHandle(0);
		InitWin32Device();
		initDriver(m_Width,m_Height,driver,COLOR_A8R8G8B8);
		m_CursorControl = new CCursorContorl(m_hWnd,false);
	}
	virtual ~CDreamDeviceWin32() {
		if (m_CursorControl)
		{
			m_CursorControl->drop();
			m_CursorControl = NULL;
		}	
	}
	virtual void showVersion() const  {

	}
	virtual char* getVersionString() const {
		return "Dream2d Win32 0.1";
	}
	void initDriver(s32 sWidth,s32 sHeight,DRIVER_TYPE driver,COLOR_FORMAT f);
	void InitWin32Device();
	virtual s32 run();
	void yield() {
		Sleep(1);
	}
	ICursorControl* getCursorControl() const {
		return m_CursorControl;
	}
	virtual void sleep(u32 t) {
		Sleep(t);
	}
	virtual void setWindowCaption(const wchar_t* text) {
		DWORD_PTR dwResult;
		SendMessageTimeoutW(m_hWnd, WM_SETTEXT, 0,
			reinterpret_cast<LPARAM>(text),
			SMTO_ABORTIFHUNG, 2000, &dwResult);
	}
	virtual bool isWindowActive() const {
		return (GetActiveWindow() == m_hWnd);
	}
	virtual bool isWindowFocused() const{
		bool ret = (GetFocus() == m_hWnd);
		return ret;
	}
	virtual bool isFullscreen() const {
		return false;
	}
public:
	class CCursorContorl : public ICursorControl {
	public:
		CCursorContorl(HWND hWnd,bool fullScreen) {
			HWnd = hWnd;
			updateBorderSize(fullScreen,false);
		}
		~CCursorContorl() {

		};
		virtual void setVisible(d_bool visible) {
			CURSORINFO info;
			info.cbSize = sizeof(CURSORINFO);
			BOOL gotCursorInfo = GetCursorInfo(&info);
			while ( gotCursorInfo ) {
				if ( (visible == d_true && info.flags == CURSOR_SHOWING) 	// visible
				        || (visible == d_false && info.flags == 0 ) ) {		// hidden
					break;
				}
				int showResult = ShowCursor(visible == d_true?true:false);   // this only increases an internal display counter in windows, so it might have to be called some more
				if ( showResult < 0 ) {
					break;
				}
				info.cbSize = sizeof(CURSORINFO);	// yes, it really must be set each time
				gotCursorInfo = GetCursorInfo(&info);
			}
			IsVisible = visible;
		}

		virtual d_bool isVisible() const {
			return IsVisible;
		}

		virtual void setPosition(s32 x, s32 y) {
			RECT rect;
			if (GetWindowRect(HWnd, &rect))
				SetCursorPos(x + rect.left + BorderX, y + rect.top + BorderY);
			CursorPos.x = x;
			CursorPos.y = y;
		}

		virtual void getPosition(s32* x,s32* y) {
			updateInternalCursorPosition();
			*x = CursorPos.x;
			*y = CursorPos.y;
		}

		void updateBorderSize(bool fullscreen, bool resizable) {
			if (!fullscreen) {
				if (resizable) {
					BorderX = GetSystemMetrics(SM_CXSIZEFRAME);
					BorderY = GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYSIZEFRAME);
				} else {
					BorderX = GetSystemMetrics(SM_CXDLGFRAME);
					BorderY = GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYDLGFRAME);
				}
			} else {
				BorderX = BorderY = 0;
			}
		}
		void updateInternalCursorPosition() {
			POINT p;
			if (!GetCursorPos(&p)) {
				u32 xy = GetMessagePos();
				p.x = GET_X_LPARAM(xy);
				p.y = GET_Y_LPARAM(xy);
			}

			
			RECT rect;
			if (GetWindowRect(HWnd, &rect)) {
				CursorPos.x = p.x-rect.left-BorderX;
				CursorPos.y = p.y-rect.top-BorderY;
			} else {
				// window seems not to be existent, so set cursor to
				// a negative value
				CursorPos.x = -1;
				CursorPos.x = -1;
			}
			
		}
	private:
		point2d<s32> CursorPos;
		HWND HWnd;
		s32 BorderX, BorderY;
		d_bool IsVisible;
	};
private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	s32 m_Width,m_Height;
	CCursorContorl* m_CursorControl;
};
#endif

#endif