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
#include "ICanvans.h"
#include "CCanvansTool.h"
u32 ICanvans::CopyCanvans(s32 x0,s32 y0,s32 sWidth,s32 sHeight,ICanvans* source,s32 sx0,s32 sy0,COPY_SELECTION sel) {
	switch(sel) {
	case COPY_USE_SOURCE_KEY:
		return CCanvansTool::CopyCanvansUsekey(this,x0,y0,sWidth,sHeight,source,sx0,sy0,source->m_colorkey);
	case COPY_USE_DEST_KEY:
		return CCanvansTool::CopyCanvansUsekey(this,x0,y0,sWidth,sHeight,source,sx0,sy0,this->m_colorkey);
	case COPY_USE_ALPHA_NORMAL:
		return CCanvansTool::CopyCanvansAlpha(this,x0,y0,sWidth,sHeight,source,sx0,sy0);
	case COPY_USE_ALPHA_SOURCEKEY:
		return CCanvansTool::CopyCanvansAlphaWithKey(this,x0,y0,sWidth,sHeight,source,sx0,sy0,source->m_colorkey);
	case COPY_USE_ALPHA_DESKKEY:
		return CCanvansTool::CopyCanvansAlphaWithKey(this,x0,y0,sWidth,sHeight,source,sx0,sy0,this->m_colorkey);
	case COPY_NORMAL:
		return CCanvansTool::CopyCanvansNormal(this,x0,y0,sWidth,sHeight,source,sx0,sy0);
	default:
		return 1;
	}
}