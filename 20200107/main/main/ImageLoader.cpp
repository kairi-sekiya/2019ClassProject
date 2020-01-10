#include "ImageLoader.h"

ImageLoader::ImageLoader() 
{
	bitmapProperties.dpiX = 96.0f;
	bitmapProperties.dpiY = 96.0f;
	bitmapProperties.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
	bitmapProperties.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;

	HRESULT hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		nullptr,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&pFactory)
	);
	

}

ImageLoader* ImageLoader::Getinstance() 
{
	if (instance != NULL) 
	{
		return instance;
	}
	instance = new ImageLoader;
	return instance;
}

ID2D1Bitmap* ImageLoader::LoadImageFromFile(const char*& filename) 
{

}