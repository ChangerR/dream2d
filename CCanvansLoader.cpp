#include "CCanvansLoader.h"
#include "CMemoryCancans.h"
#ifdef DREAM2D_WIN32
#include <windows.h>
#define BITMAP_ID ((('M')<<8)+ ('B'))
ICanvans* CCanvansLoader::LoadBmpFile( const char* filename )
{
	FILE* f;
	int len;
	ICanvans* pCanvans = NULL;
	f = fopen(filename,"rb");
	if(f == NULL)
		return NULL;
	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER fileinfo;
	len = fread(&fileheader,sizeof(fileheader),1,f);
	if (fileheader.bfType != BITMAP_ID)
	{
		fclose(f);
		return NULL;
	}
	len = fread(&fileinfo,sizeof(BITMAPINFOHEADER),1,f);
	if (fileinfo.biCompression!=BI_RGB)
	{
		fclose(f);
		return NULL;
	}
	
	switch(fileinfo.biBitCount) {
	case 8:
		pCanvans = new CMemoryCanvans(fileinfo.biWidth,fileinfo.biHeight,COLOR_INDEX8);
		fread((void*)pCanvans->getPallet(),sizeof(u32),256,f);
		break;
	case 24:
		pCanvans = new CMemoryCanvans(fileinfo.biWidth,fileinfo.biHeight,COLOR_R8G8B8);
		break;
	case 32:
		pCanvans = new CMemoryCanvans(fileinfo.biWidth,fileinfo.biHeight,COLOR_A8R8G8B8);
		break;
	default:
		fclose(f);
		return NULL;
	}
	u8* buf = pCanvans->lock();
	fseek(f,fileheader.bfOffBits,SEEK_SET);
	len = fread(buf,pCanvans->m_pitch*pCanvans->m_Height,1,f);
	fclose(f);
	u8* tmp = new u8[pCanvans->m_pitch];
	int i = 0,j = pCanvans->m_Height -1;
	while(i < j) {
		memmove(tmp,buf+i*pCanvans->m_pitch,pCanvans->m_pitch);
		memmove(buf+i*pCanvans->m_pitch,buf+j*pCanvans->m_pitch,pCanvans->m_pitch);
		memmove(buf+j*pCanvans->m_pitch,tmp,pCanvans->m_pitch);
		i++;j--;
	}
	delete[] tmp;
	pCanvans->unlock();
	return pCanvans;
}
#endif