#pragma once

#include "ClickableImage.h"
#include "Label.h"

class Button : public ClickableImage
{
public:
	Button(const Vector2& localPosition, const std::wstring& text, const char* dataAsset = "Button.png", LoadType loadType = LoadType::kTexture, BaseObject* parent = nullptr, float lifeTime = FLT_MAX);
	Button(const Vector2& size, const Vector2& localPosition, const std::wstring& text, const char* dataAsset = "Button.png", LoadType loadType = LoadType::kTexture, BaseObject* parent = nullptr, float lifeTime = FLT_MAX);
	~Button();

	void Initialize() override;

	void Update(DX::StepTimer const& timer) override;
	void Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont) override;
	void HandleInput(DX::StepTimer const& timer, const Vector2& mousePosition) override;

private:
	// Button text label
	std::unique_ptr<Label> m_label;

	// Colours used to create an effect when mouse is hovered over
	const Color m_defaultColour = Color(0.0f, 0.7f, 0.0f, 1.0f);
	const Color m_highlightedColour = Color(0.0f, 1.0f, 0.0f, 1.0f);
};

