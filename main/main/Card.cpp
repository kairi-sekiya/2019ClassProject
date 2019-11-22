#include "Card.h"
#include "Common.h"

Card::Card()
{
}

Card::~Card()
{

}

void Card::Draw(ID2D1HwndRenderTarget* g_pRenderTarget) 
{
	ID2D1Bitmap* drawPicture;		// •`‰æ‚·‚é‰æ‘œ
	D2D1_SIZE_U drawPictureSize;	// ‰æ‘œƒf[ƒ^‚Ìc‰¡‚Ì‘å‚«‚³

	if (isFront) 
	{
		drawPicture = frontPicture;
		drawPictureSize = frontPictureSize;
	}
	else 
	{
		drawPicture = backPicture;
		drawPictureSize = backPictureSize;
	}

	D2D1_RECT_F drc, src;
	drc.left = 0;
	drc.top = 0;
	drc.right = drc.left + drawPictureSize.width * scale;
	drc.bottom = drc.top + drawPictureSize.height * scale;
	src.left = 0;
	src.top = 0;
	src.right = drawPictureSize.width * scale;
	src.bottom = drawPictureSize.height * scale;
	g_pRenderTarget->DrawBitmap(drawPicture, drc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);

}

void Card::SetTargetPoint(POINT targetPoint) 
{
	this->targetPoint = targetPoint;
}

void Card::Translate(float size) 
{
	
}

void Card::TurnOver() 
{
	isFront = !isFront;
}

