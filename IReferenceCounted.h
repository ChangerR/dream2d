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
#ifndef __I_DREAM2D_REFERENCECOUNTED
#define __I_DREAM2D_REFERENCECOUNTED
//IReferenceCounted may be all class's father
#include "dream2dconf.h"
class IReferenceCounted {
public:
	IReferenceCounted()
		:m_ReferenceCounter(1) {
	}
	virtual ~IReferenceCounted() {
	}
	void AddRef() const {
		++m_ReferenceCounter;
	}
	d_bool drop() const {
		--m_ReferenceCounter;
		if (!m_ReferenceCounter) {
			delete this;
			return d_true;
		}
		return d_false;
	}
	s32 getReferenceCount() const {
		return m_ReferenceCounter;
	}
private:
	mutable int m_ReferenceCounter;
};

#endif