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
class ICanvans:public IReferenceCounter{
public:
	ICanvans() {
		m_Width = 0;
		u_Height = 0;
		m_pitch = 0;
	}
	virtual ~ICanvans() {
	
	}
	void* lock() = 0;
	void unlock() = 0;
public:
	u32 m_Width,u_Height;
	u32 m_pitch;
};
#endif