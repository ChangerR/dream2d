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
#ifndef __D_DREAM2D_VIDEODRIVER
#define __D_DREAM2D_VIDEODRIVER
#include "IReferenceCounted.h"
#include "IFont.h"
#include "ICanvans.h"
class IVideoDriver:public IReferenceCounted {
public:
	IVideoDriver() {

	}

	virtual ~IVideoDriver() {
		
	}
	virtual void BeginScene(d_bool clearScreen) = 0;
	virtual void EndScene() = 0;
	virtual u32 DrawPic(s32 x0,s32 y0,s32 sWidth,s32 sHeight,ICanvans* source,s32 sx0,s32 sy0,COPY_SELECTION sel) = 0;
	virtual u32 DrawTextW(wchar_t* text,int x0,int y0) = 0;
	virtual u32 DrawTextA(char* text,int x0,int y0) = 0;
	virtual ICanvans* CreateCanvans(s32 sWidth,s32 sHeight,COLOR_FORMAT f,CANVANS_TYPE t) = 0;
	virtual ICanvans* LoadCanvans(const char*) = 0;
	virtual u32 DrawRectAngle(s32 x0,s32 y0,s32 sWidth,s32 sHeight,u32 color) = 0;
protected:
};
#endif