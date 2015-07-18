#This file is for window visual studio 10.0 
#you can use "nmake -f Makefile"
DREAM2D_OBJ=CDreamDeviceWin32.obj dream2d.obj CWinGUIDriver.obj ICanvans.obj CCanvansLoader.obj CCanvansTool.obj
TARGET_PATH=
CXXINCS =
CPPFLAGS = $(CXXINCS) /DBUILD_DLL /nologo /c /O2 /MT /D_WIN32 /DNDEBUG /D_WINDOWS /DDREAM2D_WIN32 /I./
LDFLAGS = /NOLOGO /DLL gdi32.lib User32.lib kernel32.lib Advapi32.lib
all:$(TARGET_PATH)dream2d.dll sample

$(TARGET_PATH)dream2d.dll:$(DREAM2D_OBJ)
	link $(LDFLAGS) /OUT:$@ $(DREAM2D_OBJ)

sample:$(TARGET_PATH)test1.exe

$(TARGET_PATH)test1.exe:sample/main.obj
	link /NOLOGO /SUBSYSTEM:WINDOWS gdi32.lib User32.lib kernel32.lib Advapi32.lib sample/main.obj /OUT:$@
	
.SUFFIX:.cpp .obj

.cpp.obj:
	cl $(CPPFLAGS) /Fo$@ $<
	
clean:
	del *.obj