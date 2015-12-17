#include "pch.h"
#include "Label.h"


//-----------------------------------------------------------------------------------------------------------------------------------
Label::Label(const std::wstring& text, BaseObject* parent, float lifeTime) :
	Label(Vector2::Zero, Vector2::Zero, text, parent, lifeTime)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Label::Label(const Vector2& localPosition, const std::wstring& text, BaseObject* parent, float lifeTime) :
	Label(Vector2::Zero, localPosition, text, parent, lifeTime)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Label::Label(const Vector2& size, const Vector2& localPosition, const std::wstring& text, BaseObject* parent, float lifeTime) :
	UIObject(size, localPosition, "", LoadType::kNoLoad, parent, lifeTime),
	m_text(text)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Label::~Label()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Label::Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont)
{
	// Catches the label size being zero
	if (GetSize() == Vector2::Zero)
	{
		SetSize(spriteFont->MeasureString(m_text.c_str()));
	}

	// Do not need to do any base drawing - will just be doing a custom draw using the spritefont
	spriteFont->DrawString(
		spriteBatch,
		m_text.c_str(),
		GetWorldPosition(),
		GetColour(),
		GetWorldRotation(),
		spriteFont->MeasureString(m_text.c_str()) * 0.5f,
		XMVectorDivide(GetSize(), spriteFont->MeasureString(m_text.c_str())));
}