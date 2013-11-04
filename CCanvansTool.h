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
#ifndef __D_DREAM2D_CANVANSTOOLS
#define __D_DREAM2D_CANVANSTOOLS
#include "ICanvans.h"
class CCanvansTool
{
public:
	static u32 ClipLine(s32& x0,s32& y0,s32& x1,s32& y1);
	static u32 DrawLine(ICanvans *dest,s32 x0,s32 y0,s32 x1,s32 y1,u32 color);
	/****************************
	DrawLine2 will draw line without cliped,if you sure that this line needn't clip ,you
	can use this function.
	***************************/
	static u32 DrawLine2(ICanvans* dest,s32 x0,s32 y0,s32 x1,s32 y1,u32 color);
	static u32 DrawTriangle(ICanvans *dest,s32 x0,s32 y0,s32 x1,s32 y1,s32 x2,s32 y2,u32 color);
	static u32 CopyCanvansNormal(ICanvans* dest,s32 x0,s32 y0,s32 sWidth,s32 sHeight,ICanvans* source,s32 sx0,s32 sy0);
	static u32 CopyCanvansAlpha(ICanvans* dest,s32 x0,s32 y0,s32 sWidth,s32 sHeight,ICanvans* source,s32 sx0,s32 sy0);
	static u32 CopyCanvansUsekey(ICanvans* dest,s32 x0,s32 y0,s32 sWidth,s32 sHeight,ICanvans* source,s32 sx0,s32 sy0,u32 key);
	static u32 CopyCanvansAlphaWithKey(ICanvans* dest,s32 x0,s32 y0,s32 sWidth,s32 sHeight,ICanvans* source,s32 sx0,s32 sy0,u32 key);
	static u32 CopyScaleCanvans(ICanvans* dest,s32 x0,s32 y0,s32 Width,s32 Height,ICanvans* source,s32 sx0,s32 sy0,s32 sWidth,s32 sHeight);
	static u32 CopyRotateCanvans(ICanvans* dest,s32 x0,s32 y0,s32 Width,s32 Height,ICanvans* source,s32 sx0,s32 sy0,s32 angle);
	static u32 DrawRoundRect(ICanvans* dest,s32 x0,s32 y0,s32 sWidth,s32 sHeight,s32 angle,u32 color);
	static u32 DrawRect(ICanvans* dest,s32 x0,s32 y0,s32 sWidth,s32 sHeight,u32 color);
};

#endif