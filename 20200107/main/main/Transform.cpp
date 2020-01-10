#include "Transform.h"
#include <math.h>

Transform::Transform(const Vector2& position, const Vector2& rotation, const Vector2& scale)
	:position(position), rotation(), scale(scale)
{
	double rotationXIntPart, rotationYIntPart;
	double rotationXDecimalPart, rotationYDecimalPart;

	rotationXDecimalPart = modf(rotation.x, &rotationXIntPart);
	if (rotationXIntPart > 360) {
		rotationXIntPart = (int)rotationXIntPart % 360;
	}
	this->rotation.x = rotationXIntPart + rotationXDecimalPart;

	rotationYDecimalPart = modf(rotation.y, &rotationYIntPart);
	if (rotationYIntPart > 360) {
		rotationYIntPart = (int)rotationYIntPart % 360;
	}
	this->rotation.y = rotationYIntPart + rotationYDecimalPart;

}

Transform::~Transform()
{

}
