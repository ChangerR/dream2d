#include <Windows.h>
#include <dream2d.h>
#include <IDreamDevice.h>

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow ) {
	typedef IDreamDevice* (*CreateDeviceFunc)(DRIVER_TYPE driver_type,u32 uWidth,u32 uHeight);
	HMODULE hModule = LoadLibraryA("dream2d.dll");
	if (hModule ==  NULL)
	{
		MessageBoxA(NULL,"add dream2d failed","alert",MB_OK);
		return 0;
	}
	CreateDeviceFunc createDevice2 = (CreateDeviceFunc)GetProcAddress(hModule,"createDevice");
	if (createDevice2 == NULL)
	{
		MessageBoxA(NULL,"Get failed","alert",MB_OK);
		return 0;
	}
	IDreamDevice* pDevice  = createDevice2(DRIVER_GUIWIN32,640,480);
	IVideoDriver* videoDriver = pDevice->getVideoDriver();
	ICanvans* pCanvans = videoDriver->CreateCanvans(100,100,COLOR_A8R8G8B8,CANVANS_MEMORY);
	u8* buf = pCanvans->lock();
	memset(buf,0,pCanvans->m_Height*pCanvans->m_pitch);
	pCanvans->unlock();
	while (pDevice->run())
	{
		videoDriver->BeginScene(d_false);
			videoDriver->DrawTextW(L"HELLO WORLD!!!",100,100);
			videoDriver->DrawPic(0,0,50,50,pCanvans,0,0,COPY_NORMAL);
		videoDriver->EndScene();
		pDevice->yield();
	}
	pCanvans->drop();
	pDevice->drop();
	return 0;
}
