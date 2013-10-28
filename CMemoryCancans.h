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
#ifndef __D_DREAM2D_CMEMORYCANVANS
#define __D_DREAM2D_CMEMORYCANVANS
#include "ICanvans.h"
class CMemoryCanvans :public ICanvans {
public:
	CMemoryCanvans(s32 uWidth,s32 uHeight,COLOR_FORMAT f):ICanvans(f) {
		int bitCount;
		switch(f) {
		case COLOR_A8R8G8B8:
			bitCount = 32;
			break;
		case COLOR_INDEX8:
			bitCount = 8;
			break;
		case COLOR_A1R5G5B5:
		case COLOR_R5G6B5:
			bitCount = 16;
			break;
		}
		m_pitch = (uWidth*bitCount +31)>>5;
		m_Width = uWidth;
		m_Height = uHeight;
		m_pallet = NULL;
		m_buffer = new u8[m_pitch*uHeight];
		if(bitCount == 8) {
			m_pallet = new u32[256];
		}
	}
	virtual ~CMemoryCanvans() {
		if(m_buffer) {
			delete[] m_buffer;
			m_buffer = NULL;
		}
		if(m_pallet) {
			delete[] m_pallet;
			m_pallet = NULL;
		} 		
	}
	u8* lock()  {
		return m_buffer;
	}
	void unlock() {
	
	}
private:
	u8* m_buffer;
	u32* m_pallet;
};
#endif