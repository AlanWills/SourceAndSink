#pragma once

#include "UIObject.h"

class Bar : public UIObject
{
public:
	/// \brief Used for static bar value
	Bar(const float maxValue,
		const Vector2& localPosition,
		const char* backgroundDataAsset,
		LoadType loadType = LoadType::kTexture,
		BaseObject* parent = nullptr,
		float lifeTime = FLT_MAX);

	/// \brief Used for static bar value
	Bar(const float maxValue,
		const Vector2& size,
		const Vector2& localPosition,
		const char* backgroundDataAsset,
		LoadType loadType = LoadType::kTexture,
		BaseObject* parent = nullptr,
		float lifeTime = FLT_MAX);

	/// \brief Used for dynamic bar value
	Bar(const float* valueToWatch, 
		const float maxValue, 
		const Vector2& localPosition, 
		const char* backgroundDataAsset, 
		LoadType loadType = LoadType::kTexture, 
		BaseObject* parent = nullptr, 
		float lifeTime = FLT_MAX);

	/// \brief Used for dynamic bar value
	Bar(const float* valueToWatch, 
		const float maxValue, 
		const Vector2& size, 
		const Vector2& localPosition, 
		const char* backgroundDataAsset, 
		LoadType loadType = LoadType::kTexture, 
		BaseObject* parent = nullptr, 
		float lifeTime = FLT_MAX);

	~Bar();

	void LoadContent(ID3D11Device* device) override;
	void Update(DX::StepTimer const& timer) override;
	void Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont) override;

private:
	/// \brief This texture represents the front bar
	std::unique_ptr<Texture2D> m_frontTexture;

	float m_maxValue;

	/// \brief We want to point at a value which we will use to draw the front bar
	const float* m_valueToWatch;
	Vector2 m_frontBarPosition;
	Vector2 m_frontBarSize;
};

