#pragma once

#include "BaseObject.h"

class UIObject : public BaseObject
{
public:
	UIObject(const char* dataAsset, LoadType loadType = LoadType::kTexture, BaseObject* parent = nullptr, float lifeTime = FLT_MAX);
	UIObject(const Vector2& localPosition, const char* dataAsset, LoadType loadType = LoadType::kTexture, BaseObject* parent = nullptr, float lifeTime = FLT_MAX);
	UIObject(const Vector2& size, const Vector2& localPosition, const char* dataAsset, LoadType loadType = LoadType::kTexture, BaseObject* parent = nullptr, float lifeTime = FLT_MAX);
  ~UIObject();

	void Update(DX::StepTimer const& timer) override;
	void Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont) override;

  void SetStoredObject(void* storedObject) { m_storedObject = storedObject; }

  template <typename T>
  T GetStoredObjectAs() const { return static_cast<T>(m_storedObject); }

private:
	float m_lifeTime;
	float m_currentLifeTime;

  void* m_storedObject;
};

