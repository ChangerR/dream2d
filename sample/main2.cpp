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
	ICanvans* pCanvans = videoDriver->LoadCanvans("a.bmp");
	if (pCanvans == NULL)
	{
		MessageBoxA(NULL,"¼ÓÔØÎÄ¼þÊ§°Ü","error",MB_OK);
		PostQuitMessage(0);
	}
	pCanvans->LoadColorKey(0,0);
	int x,y;
	pDevice->setWindowCaption(L"Demo1");
	while (pDevice->run())
	{
		videoDriver->BeginScene(d_true);
			videoDriver->DrawTextW(L"HELLO WORLD!!!",100,100);
			/*
			if (pCanvans)
			{
				videoDriver->DrawPic(0,0,pCanvans->m_Width,pCanvans->m_Height,pCanvans,0,0,COPY_USE_SOURCE_KEY);
			}
			
			*/
			videoDriver->DrawLine(100,200,400,400,0x00ff00ff);
			pDevice->getCursorControl()->getPosition(&x,&y);
			videoDriver->DrawRectAngle(x-50,y-50,100,100,0x1fffffff);
		videoDriver->EndScene();
		pDevice->yield();
	}
	pCanvans->drop();
	pDevice->drop();
	return 0;
}
