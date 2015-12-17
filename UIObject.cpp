#include "pch.h"
#include "UIObject.h"


//-----------------------------------------------------------------------------------------------------------------------------------
UIObject::UIObject(const char* dataAsset, LoadType loadType, BaseObject* parent, float lifeTime) :
	UIObject(Vector2::Zero, Vector2::Zero, dataAsset, loadType, parent, lifeTime)
{

}


//-----------------------------------------------------------------------------------------------------------------------------------
UIObject::UIObject(const Vector2& localPosition, const char* dataAsset, LoadType loadType, BaseObject* parent, float lifeTime) :
	UIObject(Vector2::Zero, localPosition, dataAsset, loadType, parent, lifeTime)
{

}


//-----------------------------------------------------------------------------------------------------------------------------------
UIObject::UIObject(const Vector2& size, const Vector2& localPosition, const char* dataAsset, LoadType loadType, BaseObject* parent, float lifeTime) :
	BaseObject(size, localPosition, dataAsset, loadType, parent),
	m_lifeTime(lifeTime),
	m_currentLifeTime(0)
{

}


//-----------------------------------------------------------------------------------------------------------------------------------
UIObject::~UIObject()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void UIObject::Update(DX::StepTimer const& timer)
{
	BaseObject::Update(timer);

	m_currentLifeTime += (float)timer.GetElapsedSeconds();
	if (m_currentLifeTime > m_lifeTime)
	{
		// This UIObject has been alive for longer than its lifetime so it dies
		// and will be cleared up by whatever manager is in charge of it
		Die();
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
void UIObject::Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont)
{
	BaseObject::Draw(spriteBatch, spriteFont);

	// draw text with spritefont here if visible
}