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
d_bool FixBound(ICanvans* dest,s32& x0,s32& y0,s32& sWidth,s32& sHeight,ICanvans* source,s32& sx0,s32& sy0) {
	x0 = x0 > 0 ? x0:(sWidth+=x0,0);
	y0 = y0 > 0 ? y0:(sHeight+=y0,0);
	sWidth = (x0 + sWidth) > dest->m_Width ? (dest->m_Width - x0):sWidth;
	sHeight = (y0 + sHeight) >dest->m_Height ? (dest->m_Height - y0):sHeight;
	sWidth = (sx0 + sWidth) > source->m_Width ? (source->m_Width - sx0):sWidth;
	sHeight = (sy0 + sHeight) >source->m_Height ? (source->m_Height - y0):sHeight;
	sx0 = sx0 > 0 ? sx0:0;
	sy0 = sy0 > 0 ? sy0:0;
	if(x0 >= dest->m_Width || y0 >= dest->m_Height||sx0 >= source->m_Width||sy0 >= source->m_Height
	        ||sWidth <= 0||sHeight <= 0)
		return d_false;
	return d_true;
}

//Ok,I admit that this code is a bit ugly
inline void Alpha_Mix(u32* a,u32* b) {
	u32 alpha1 = *((u8*)b + 3) + 1,alpha2 = 256 - alpha1;
	*((u8*)a) = u8(((u32)(*((u8*)a)) * alpha2 + (u32)(*((u8*)b)) * alpha1)>>8);
	*((u8*)a+1) = u8(((u32)(*((u8*)a+1)) * alpha2 + (u32)(*((u8*)b+1)) * alpha1)>>8);
	*((u8*)a+2) = u8(((u32)(*((u8*)a+2)) * alpha2 + (u32)(*((u8*)b+2)) * alpha1)>>8);
}
u32 CopyCanvansNormal(ICanvans* dest,s32 x0,s32 y0,s32 sWidth,s32 sHeight,ICanvans* source,s32 sx0,s32 sy0) {
	if(FixBound(dest,x0,y0,sWidth,sHeight,source,sx0,sy0) == d_false)
		return 1;
	u8* s_buf = source->lock();
	u8* d_buf = dest->lock();
	int nRet = 0;
	if(dest->m_Format == COLOR_A8R8G8B8) {
		d_buf += y0*dest->m_pitch + (x0<<2);
		if(source->m_Format == COLOR_A8R8G8B8) {
			s_buf += sy0*source->m_pitch + (sx0<<2);
			for(int i = 0; i < sHeight; i++) {
				memcpy(d_buf,s_buf,sWidth<<2);
				d_buf+=dest->m_pitch;
				s_buf+=source->m_pitch;
			}
		} else if(source->m_Format == COLOR_R8G8B8) {
			s_buf += sy0*source->m_pitch + sx0*3;
			for(int i = 0; i < sHeight; i++) {
				for(int j = 0; j <sWidth; j++) {
					d_buf[j*4] = s_buf[j*3];
					d_buf[j*4+1] = s_buf[j*3+1];
					d_buf[j*4+2] = s_buf[j*3+2];
					d_buf[j*4+3] = 0xff;
				}
				d_buf+=dest->m_pitch;
				s_buf+=source->m_pitch;
			}
		} else if(source->m_Format == COLOR_INDEX8){
			s_buf += sy0*source->m_pitch + sx0;
			for(int i = 0;i<sWidth;i++) {
				for(int j = 0;j <sHeight;j++) {
					*((int*)d_buf + j) = *(source->getPallet() + *(s_buf+j));
				}
				d_buf+=dest->m_pitch;
				s_buf+=source->m_pitch;
			}
		}
	} else {

	}
	source->unlock();
	dest->unlock();
	return nRet;
}

u32 CopyCanvansAlpha(ICanvans* dest,s32 x0,s32 y0,s32 sWidth,s32 sHeight,ICanvans* source,s32 sx0,s32 sy0) {
	int nRet = 0;
	if (dest->m_Format == COLOR_A8R8G8B8&& source->m_Format == COLOR_A8R8G8B8)
	{
		if(FixBound(dest,x0,y0,sWidth,sHeight,source,sx0,sy0) == d_false)
			return 1;
		u8* s_buf = source->lock();
		u8* d_buf = dest->lock();
		d_buf += y0*dest->m_pitch + (x0<<2);
		s_buf += sy0*source->m_pitch + (sx0<<2);

		for(int i = 0;i < sHeight;i++) {
			for(int j=0;j < sWidth;j++) {
				Alpha_Mix((u32*)d_buf + j,(u32*)s_buf + j);
			}
			d_buf+=dest->m_pitch;
			s_buf+=source->m_pitch;
		}
		source->unlock();
		dest->unlock();
	}else {
		return CopyCanvansNormal(dest,x0,y0,sWidth,sHeight,source,sx0,sy0);
	}
	return nRet;
}
u32 CopyCanvansUsekey(ICanvans* dest,s32 x0,s32 y0,s32 sWidth,s32 sHeight,ICanvans* source,s32 sx0,s32 sy0,u32 key) {
	if(FixBound(dest,x0,y0,sWidth,sHeight,source,sx0,sy0) == d_false)
		return 1;
	u8* s_buf = source->lock();
	u8* d_buf = dest->lock();
	int nRet = 0;
	if(dest->m_Format == COLOR_A8R8G8B8) {
		d_buf += y0*dest->m_pitch + (x0<<2);
		if(source->m_Format == COLOR_A8R8G8B8) {
			s_buf += sy0*source->m_pitch + (sx0<<2);
			for(int i = 0; i < sHeight; i++) {
				for (int j = 0;j < sWidth;j++)
				{
					if(*((u32*)s_buf + j) != key) {
						*((u32*)d_buf + j) = *((u32*)s_buf + j);
					}
				}
				d_buf += dest->m_pitch;
				s_buf += source->m_pitch;
			}
		} else if(source->m_Format == COLOR_R8G8B8) {
			s_buf += sy0*source->m_pitch + sx0*3;
			for(int i = 0; i < sHeight; i++) {
				for(int j = 0; j <sWidth; j++) {
					if(s_buf[j*3] != (key&0x000000ff) ||
						s_buf[j*3 +1] != (key&0x0000ff00)>>8 ||
						s_buf[j*3 +2] != (key&0x00ff0000)>>16) {
					d_buf[j*4] = s_buf[j*3];
					d_buf[j*4+1] = s_buf[j*3+1];
					d_buf[j*4+2] = s_buf[j*3+2];
					d_buf[j*4+3] = 0xff;
					}
				}
				d_buf+=dest->m_pitch;
				s_buf+=source->m_pitch;
			}
		} else if(source->m_Format == COLOR_INDEX8){
			s_buf += sy0*source->m_pitch + sx0;
			for(int i = 0;i<sWidth;i++) {
				for(int j = 0;j <sHeight;j++) {
					if (*(source->getPallet() + *(s_buf+j)) != key)
					{
						*((int*)d_buf + j) = *(source->getPallet() + *(s_buf+j));
					}			
				}
				d_buf+=dest->m_pitch;
				s_buf+=source->m_pitch;
			}
		}
	} else {

	}
	source->unlock();
	dest->unlock();
	return nRet;
	return 1;
}
u32 CopyCanvansAlphaWithKey(ICanvans* dest,s32 x0,s32 y0,s32 sWidth,s32 sHeight,ICanvans* source,s32 sx0,s32 sy0,u32 key) {

	return 1;
}
u32 ICanvans::CopyCanvans(s32 x0,s32 y0,s32 sWidth,s32 sHeight,ICanvans* source,s32 sx0,s32 sy0,COPY_SELECTION sel) {
	switch(sel) {
	case COPY_USE_SOURCE_KEY:
		return CopyCanvansUsekey(this,x0,y0,sWidth,sHeight,source,sx0,sy0,source->m_colorkey);
	case COPY_USE_DEST_KEY:
		return CopyCanvansUsekey(this,x0,y0,sWidth,sHeight,source,sx0,sy0,this->m_colorkey);
	case COPY_USE_ALPHA_NORMAL:
		return CopyCanvansAlpha(this,x0,y0,sWidth,sHeight,source,sx0,sy0);
	case COPY_USE_ALPHA_SOURCEKEY:
		return CopyCanvansAlphaWithKey(this,x0,y0,sWidth,sHeight,source,sx0,sy0,source->m_colorkey);
	case COPY_USE_ALPHA_DESKKEY:
		return CopyCanvansAlphaWithKey(this,x0,y0,sWidth,sHeight,source,sx0,sy0,this->m_colorkey);
	case COPY_NORMAL:
		return CopyCanvansNormal(this,x0,y0,sWidth,sHeight,source,sx0,sy0);
	default:
		return 1;
	}
}