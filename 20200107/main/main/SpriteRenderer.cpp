#include "SpriteRenderer.h"
#include "DirectXGeneralManager.h"
#include "Common.h"

SpriteRenderer* SpriteRenderer::GetInstance()
{
	return nullptr;
}

SpriteRenderer::SpriteRenderer()
{
	m_pRenderTarget = DirectXGeneralManager::GetInstance()->GetRenderTarget();
}

void SpriteRenderer::Release()
{
}

void SpriteRenderer::Draw()
{
}

int SpriteRenderer::AddSprite(Sprite sprite)
{
	spriteArray.resize(spriteArray.size+sizeof(Sprite));
	memcpy_s(&spriteArray[spriteCount], sizeof(Sprite), &sprite, sizeof(sprite));
	spriteCount++;
}

void SpriteRenderer::DeleteSprite(int index)
{
	if (spriteCount < index || index < 0) {
		// TODO: ”ÍˆÍŠO‚ÌŽž‚ÌƒGƒ‰[ˆ—
	}
	spriteArray.erase(spriteArray.begin()+index);
}