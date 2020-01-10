#include "Sprite.h"
#include "DirectXGeneralManager.h"
using namespace std;

Sprite& Sprite::operator=(const Sprite& other)
{
	*this->id = *other.id;
	*this->transform = *other.transform;
}