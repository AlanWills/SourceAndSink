#include "pch.h"
#include "RectangleCollider.h"
#include "BaseObject.h"


//-----------------------------------------------------------------------------------------------------------------------------------
RectangleCollider::RectangleCollider(BaseObject* parent) :
	Collider(parent)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
RectangleCollider::~RectangleCollider()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RectangleCollider::UpdateColliderBounds()
{
	Vector2 parentWorldPos = GetParent()->GetWorldPosition();
	float parentWorldRot = GetParent()->GetWorldRotation();

	m_boundingBox.Center = Vector3(parentWorldPos.x, parentWorldPos.y, 0); 
	m_boundingBox.Extents = Vector3(GetParent()->GetSize().x * 0.5f, GetParent()->GetSize().y * 0.5f, 0.001f);
	m_boundingBox.Orientation = Quaternion::CreateFromRotationMatrix(Matrix::CreateRotationZ(parentWorldRot));

	// May need to use this instead
	//m_boundingBox.Transform(m_boundingBox, 1, Vector3(parentWorldRot), Vector3(parentWorldPos.x, parentWorldPos.y, 0));
}


//-----------------------------------------------------------------------------------------------------------------------------------
bool RectangleCollider::CheckCollisionWith(const Vector2& point)
{
	UpdateColliderBounds();

	ContainmentType containmentType = m_boundingBox.Contains(point);
	return containmentType != ContainmentType::DISJOINT;
}