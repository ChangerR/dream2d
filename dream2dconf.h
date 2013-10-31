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
	COLOR_R5G6B5,
	COLOR_R8G8B8
}COLOR_FORMAT;
typedef struct _color{
	union _color_t{
		struct _color_argb{
			u8 a,r,g,b;
		};
		u32 argb;
		u32 M[4];
	};
}color32;
typedef enum {
	COPY_USE_SOURCE_KEY,
	COPY_USE_DEST_KEY,
	COPY_USE_ALPHA_NORMAL,
	COPY_USE_ALPHA_SOURCEKEY,
	COPY_USE_ALPHA_DESKKEY,
	COPY_NORMAL
}COPY_SELECTION;
typedef enum {
	CANVANS_WINGDI,
	CANVANS_MEMORY,
	CANVANS_D9SURFACE,
	CANVANS_DDRAWSURFACE,
	CANVANS_UNKNOWN,
	CANVANS_DEFAULT
	//FIXME:you can add your own canvans type
}CANVANS_TYPE;

template <typename T>
struct point2d {
	T x,y;
};

template <typename T>
struct rect {
	T top,left,right,bottom;
};
#include <stdlib.h>
#include <tchar.h>
#include <string.h>
#include <stdio.h>
#endif