#pragma once

#include "BaseObject.h"
#include "RigidBody.h"

class GameObject : public BaseObject
{
public:
	GameObject(const std::string& dataAsset, LoadType loadType = LoadType::kData, BaseObject* parent = nullptr);
	GameObject(const Vector2& localPosition, const std::string& dataAsset, LoadType loadType = LoadType::kData, BaseObject* parent = nullptr);
	GameObject(const Vector2& size, const Vector2& localPosition, const std::string& dataAsset, LoadType loadType = LoadType::kData, BaseObject* parent = nullptr);

	void Initialize() override;
	void Update(DX::StepTimer const& timer) override;

	RigidBody* GetRigidBody() const { return m_rigidBody.get(); }

	virtual ~GameObject();

private:
	float m_health;
	std::unique_ptr<RigidBody> m_rigidBody;
};

