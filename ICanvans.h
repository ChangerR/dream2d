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
#ifndef __D_DREAM2D_CANVANS
#define __D_DREAM2D_CANVANS
#include "IReferenceCounted.h"
class CCanvansTool;
class ICanvans:public IReferenceCounted{
public:
	ICanvans(COLOR_FORMAT f) {
		m_Width = 0;
		m_Height = 0;
		m_pitch = 0;
		m_Format = f;
		m_colorkey = 0;
	}
	virtual ~ICanvans() {
	
	}
	virtual u32* getPallet() const = 0;
	virtual u8* lock() = 0;
	virtual void unlock() = 0;
	virtual u32 CopyCanvans(s32 x0,s32 y0,s32 sWidth,s32 sHeight,ICanvans* source,s32 sx0,s32 sy0,COPY_SELECTION sel);
	virtual CANVANS_TYPE getCanvansType() const = 0;
	virtual u32 LoadColorKey(s32 xPos,s32 yPos) = 0;
public:
	s32 m_Width,m_Height;
	s32 m_pitch;
	COLOR_FORMAT m_Format;
	u32 m_colorkey;
	friend class CCanvansTool;
};
#endif