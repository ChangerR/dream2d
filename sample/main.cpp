#include <Windows.h>
#include <dream2d.h>
#include <IDreamDevice.h>

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow ) {
	typedef IDreamDevice* (*CreateDeviceFunc)(DRIVER_TYPE driver_type,u32 uWidth,u32 uHeight);
	HMODULE hModule = LoadLibrary("dream2d.dll");
	if (hModule ==  NULL)
	{
		MessageBox(NULL,"add dream2d failed","alert",MB_OK);
		return 0;
	}
	CreateDeviceFunc createDevice2 = (CreateDeviceFunc)GetProcAddress(hModule,"createDevice");
	if (createDevice2 == NULL)
	{
		MessageBox(NULL,"Get failed","alert",MB_OK);
		return 0;
	}
	IDreamDevice* pDevice  = createDevice2(DRIVER_GUIWIN32,640,480);
	while (pDevice->run())
	{
	}
	pDevice->drop();
}
