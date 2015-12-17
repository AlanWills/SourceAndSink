#include "pch.h"

#include "MathUtils.h"
#include "BaseObject.h"


//-----------------------------------------------------------------------------------------------------------------------------------
MathUtils::MathUtils()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
MathUtils::~MathUtils()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
const float MathUtils::GetAngleBetweenObjectAndWorldSpaceVector(const BaseObject* object, const Vector2& v)
{
	Vector2 diffVector2 = v - object->GetWorldPosition();
	float rotation = atan2(diffVector2.x, -diffVector2.y);
	XMScalarModAngle(rotation);

	return rotation;
}


//-----------------------------------------------------------------------------------------------------------------------------------
const float MathUtils::LerpDown(float currentValue, float targetValue, float amount)
{
	return Clamp<float>(currentValue - amount, targetValue, currentValue);
}