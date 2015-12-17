#include "pch.h"
#include "GameObject.h"
#include "ScreenManager.h"
#include "RigidBody.h"


//-----------------------------------------------------------------------------------------------------------------------------------
GameObject::GameObject(const char* dataAsset, LoadType loadType, BaseObject* parent) :
	GameObject(Vector2::Zero, Vector2::Zero, dataAsset, loadType, parent)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
GameObject::GameObject(const Vector2& localPosition, const char* dataAsset, LoadType loadType, BaseObject* parent) :
	GameObject(Vector2::Zero, localPosition, dataAsset, loadType, parent)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
GameObject::GameObject(const Vector2& size, const Vector2& localPosition, const char* dataAsset, LoadType loadType, BaseObject* parent) :
	BaseObject(size, localPosition, dataAsset, loadType, parent),
	m_rigidBody(nullptr),
	m_health(1)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
GameObject::~GameObject()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void GameObject::Initialize()
{
	BaseObject::Initialize();

	m_rigidBody.reset(new RigidBody(this));
}


//-----------------------------------------------------------------------------------------------------------------------------------
void GameObject::Update(DX::StepTimer const& timer)
{
	BaseObject::Update(timer);

	if (IsActive())
	{
		if (m_health <= 0)
		{
			Die();
		}

		assert(m_rigidBody);
		m_rigidBody->Update(timer);
	}
}