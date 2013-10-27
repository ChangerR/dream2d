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
#include "IReferenceCounter.h"
#include "IFont.h"
class IVideoDriver:public IReferenceCounter {
public:
	IVideoDriver() {
		m_font = NULL;
	}

	virtual ~IVideoDriver() {
		if(m_font != NULL) {
			m_font->drop();
			m_font = NULL;
		}
	}
	virtual void BeginScene() = 0;
	virtual void EndScene() = 0;
	virtual u32 DrawPic() = 0;
	virtual u32 DrawText() = 0;
	IFont* getFont() const {
		return m_font;
	}
	IFont* replaceFont(IFont* font) {
		IFont* tmp = m_font;
		m_font = font;
		return tmp;
	}
private:
	IFont* m_font;
};
#endif