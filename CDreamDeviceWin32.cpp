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
#ifdef DREAM2D_WIN32
#include <Windows.h>
#include <tchar.h>
#include "CDreamDeviceWin32.h"
#define WINDOWS_CLASS_NAME _T("DREAM2D")
LRESULT CALLBACK WindowProc(
    HWND hwnd, UINT uMsg,WPARAM wParam,  LPARAM lParam ) {
	PAINTSTRUCT ps;
	HDC hdc;

	switch(uMsg) {
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd,&ps);

		EndPaint(hwnd,&ps);
		break;
	case WM_SIZE:
		break;
	case WM_CLOSE:		
		return DefWindowProc(hwnd,uMsg,wParam,lParam);
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd,uMsg,wParam,lParam);
	}
	return 0;
}

void CDreamDeviceWin32::InitWin32Device()
{
	WNDCLASSEX ws;
	int style = WS_CAPTION|WS_SYSMENU;
	ZeroMemory(&ws,sizeof(WNDCLASSEX));
	ws.cbSize = sizeof(WNDCLASSEX);
	ws.style = CS_VREDRAW|CS_HREDRAW;
	ws.lpfnWndProc = WindowProc;
	ws.cbClsExtra = 0;
	ws.cbWndExtra = 0;
	ws.hInstance = m_hInstance;
	ws.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	ws.hCursor = LoadCursor(NULL,IDC_ARROW);
	ws.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	ws.lpszClassName = WINDOWS_CLASS_NAME;

	RegisterClassEx(&ws);

	RECT rect = {0,0,0,0};
	rect.right = m_Width;
	rect.bottom = m_Height;

	AdjustWindowRect(&rect,style,false);

	m_hWnd = CreateWindow(WINDOWS_CLASS_NAME,_T("Hello"),style,100,100,rect.right-rect.left,rect.bottom-rect.top,NULL,NULL,m_hInstance,NULL);

	ShowWindow(m_hWnd,SW_NORMAL);
	UpdateWindow(m_hWnd);
}

s32 CDreamDeviceWin32::run() {
	MSG msg = {0};
	while(PeekMessage(&msg,NULL,0,0,PM_REMOVE)) {
		if(msg.message == WM_QUIT)
			return 0;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 1;
}
#endif