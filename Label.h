#pragma once

#include "UIObject.h"

class Label : public UIObject
{
public:
	Label(const std::wstring& text, BaseObject* parent = nullptr, float lifeTime = FLT_MAX);
	Label(const Vector2& localPosition, const std::wstring& text, BaseObject* parent = nullptr, float lifeTime = FLT_MAX);
	Label(const Vector2& size, const Vector2& localPosition, const std::wstring& text, BaseObject* parent = nullptr, float lifeTime = FLT_MAX);
	~Label();

	/// \brief Don't want to add a collider for labels
	void AddCollider() override { }

	void Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont) override;
	
	/// \brief This function is empty because labels should not be handling any input
	void HandleInput(DX::StepTimer const& timer, const Vector2& mousePosition) override { }

private:
	// Text this label will represent
	std::wstring m_text;
};