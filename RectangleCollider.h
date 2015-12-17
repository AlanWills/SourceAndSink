#pragma once

#include "Collider.h"

class RectangleCollider : public Collider
{
public:
	RectangleCollider(BaseObject* parent);
	~RectangleCollider();

	bool CheckCollisionWith(const Vector2& point) override;

private:
	void UpdateColliderBounds() override;

	BoundingOrientedBox m_boundingBox;
};

