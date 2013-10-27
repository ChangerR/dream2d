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
#ifndef __I_DREAM2D_CONFIGH
#define __I_DREAM2D_CONFIGH
typedef unsigned char u8;
typedef char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef float f32;
typedef double f64;
typedef enum {
	d_false,d_true
} d_bool;
typedef enum {
	DRIVER_GUIWIN32,
	DRIVER_OPENGL,
	DRIVER_DIRECT9,
	DRIVER_DDRAW
} DRIVER_TYPE;
typedef enum {
	COLOR_A8R8G8B8,
	COLOR_INDEX8,
	COLOR_A1R5G5B5,
	COLOR_R5G6B5
}COLOR_FORMAT;
#endif