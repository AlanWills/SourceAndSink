#include "pch.h"
#include "CircleCollider.h"
#include "BaseObject.h"


//-----------------------------------------------------------------------------------------------------------------------------------
CircleCollider::CircleCollider(BaseObject* parent) :
	Collider(parent)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
CircleCollider::~CircleCollider()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void CircleCollider::UpdateColliderBounds()
{
	Vector2 parentWorldPos = GetParent()->GetWorldPosition();
	float radius = std::max(GetParent()->GetSize().x * 0.5f, GetParent()->GetSize().y * 0.5f);

	m_boundingSphere.Center = Vector3(parentWorldPos.x, parentWorldPos.y, 0);
	m_boundingSphere.Radius = radius;
}


//-----------------------------------------------------------------------------------------------------------------------------------
bool CircleCollider::CheckCollisionWith(const Vector2& point)
{
	ContainmentType containmentType = m_boundingSphere.Contains(point);
	return containmentType != ContainmentType::DISJOINT;
}