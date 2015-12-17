#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;

// Get a circulate dependency otherwise with BaseObject.h - DO NOT REMOVE THIS
class BaseObject;

class Collider
{
public:
	Collider(BaseObject* m_parent);
	virtual ~Collider();

	virtual bool CheckCollisionWith(const Vector2& point) = 0;

protected:
	const BaseObject* GetParent() const { return m_parent; }

private:
	/// \brief Updates the collider to match up with the parent's size and position
	virtual void UpdateColliderBounds() = 0;

	// Can't use a unique_ptr because we need the header file to do so
	BaseObject* m_parent;
};

