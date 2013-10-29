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
#ifndef __D_CDREAMDEVICE_H
#define __D_CDREAMDEVICE_H
#include "IReferenceCounted.h"
#include "IVideoDriver.h"
class IDreamDevice:public IReferenceCounted {
public:
	typedef enum {
		DEVICE_WIN32,DEVICE_LINUX
	} DEVICE_TYPE;
public:
	IDreamDevice(DEVICE_TYPE type) {
		m_DeviceType = type;
		m_videoDriver = NULL;
	}
	virtual ~IDreamDevice() {
		if(m_videoDriver != NULL ) {
			m_videoDriver->drop();
			m_videoDriver = NULL;
		}
	}
	DEVICE_TYPE getDeviceType() const {
		return m_DeviceType;
	}
	virtual void showVersion() const = 0;
	virtual char* getVersionString() const = 0;
	virtual s32 run() = 0;
	virtual void yield() = 0;
	IVideoDriver* getVideoDriver() const {
		return m_videoDriver;
	}
protected:
	DEVICE_TYPE m_DeviceType;
	IVideoDriver* m_videoDriver;
};

#endif