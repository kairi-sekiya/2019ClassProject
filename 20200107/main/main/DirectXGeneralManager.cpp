#include "DirectXGeneralManager.h"

DirectXGeneralManager::DirectXGeneralManager()
{
	HRESULT hr;
	//  Direct2D Factory ‚Ì¶¬
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_pD2DFactory);
	GetClientRect(hWnd, &client);
	D2D1_SIZE_U size = D2D1::SizeU(
		client.right - client.left,
		client.bottom - client.top
	);

	//  Direct2D •`‰æƒ^[ƒQƒbƒg‚Ì¶¬
	hr = g_pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hWnd, size),
		&g_pRenderTarget
	);
}
