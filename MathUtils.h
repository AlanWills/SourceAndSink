#pragma once

class BaseObject;

using namespace DirectX;
using namespace DirectX::SimpleMath;

class MathUtils
{
public:
	MathUtils();
	~MathUtils();

	static const float GetAngleBetweenObjectAndWorldSpaceVector(const BaseObject* object, const Vector2& v);
	static const float LerpDown(float currentValue, float targetValue, float amount);

	/// \brief Clamps an inputted type between two numbers inclusive
	/// e.g. clamping 5 between 0 and 5 would return 5
	template <typename T>
	static const T Clamp(const T numberToClamp, const T min, const T max);
};

template <typename T>
const T MathUtils::Clamp(const T numberToClamp, const T min, const T max)
{
	assert(min <= max);

	T clampedNumber = numberToClamp;

	if (numberToClamp > max)
	{
		clampedNumber = max;
	}
	else if (numberToClamp < min)
	{
		clampedNumber = min;
	}

	return clampedNumber;
}