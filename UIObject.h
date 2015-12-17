#pragma once

#include "BaseObject.h"

class UIObject : public BaseObject
{
public:
	UIObject(const char* dataAsset, LoadType loadType = LoadType::kTexture, BaseObject* parent = nullptr, float lifeTime = FLT_MAX);
	UIObject(const Vector2& localPosition, const char* dataAsset, LoadType loadType = LoadType::kTexture, BaseObject* parent = nullptr, float lifeTime = FLT_MAX);
	UIObject(const Vector2& size, const Vector2& localPosition, const char* dataAsset, LoadType loadType = LoadType::kTexture, BaseObject* parent = nullptr, float lifeTime = FLT_MAX);

	void Update(DX::StepTimer const& timer) override;
	void Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont) override;
	
	~UIObject();

private:
	float m_lifeTime;
	float m_currentLifeTime;
};

