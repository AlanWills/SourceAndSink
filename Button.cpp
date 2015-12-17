#include "pch.h"
#include "Button.h"


//-----------------------------------------------------------------------------------------------------------------------------------
Button::Button(Vector2 localPosition, const std::wstring& text, const char* dataAsset, LoadType loadType, BaseObject* parent, float lifeTime) :
	Button(Vector2::Zero, localPosition, text, dataAsset, loadType, parent, lifeTime)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Button::Button(Vector2 size, Vector2 localPosition, const std::wstring& text, const char* dataAsset, LoadType loadType, BaseObject* parent, float lifeTime) :
	UIObject(size, localPosition, dataAsset, loadType, parent, lifeTime),
	m_label(new Label(text, this)),
	m_buttonState(kIdle),
	m_clickResetTimer(m_resetTime)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Button::~Button()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Button::Initialize()
{
	UIObject::Initialize();

	m_label->Initialize();

	// Set up the colours here
	SetColour(m_defaultColour);
	m_label->SetColour(Color(0, 0, 0, 1));
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Button::Update(DX::StepTimer const& timer)
{
	UIObject::Update(timer);

	if (IsActive())
	{
		m_clickResetTimer += (float)timer.GetElapsedSeconds();
		if (m_clickResetTimer >= m_resetTime)
		{
			m_buttonState = ButtonState::kIdle;
		}

		// Lerp our current colour to the default one to create effect when mouse over button
		SetColour(Color::Lerp(GetColour(), m_defaultColour, (float)timer.GetElapsedSeconds() * 3));
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Button::Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont)
{
	UIObject::Draw(spriteBatch, spriteFont);

	if (IsVisible())
	{
		m_label->Draw(spriteBatch, spriteFont);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Button::HandleInput(DX::StepTimer const& timer, const Vector2& mousePosition)
{
	UIObject::HandleInput(timer, mousePosition);

	if (AcceptsInput())
	{
		if (IsMouseOver() && m_buttonState != ButtonState::kPressed)
		{
			m_buttonState = ButtonState::kHighlighted;
			SetColour(m_highlightedColour);
		}

		if (IsSelected())
		{
			if (m_buttonState != ButtonState::kPressed)
			{
				assert(m_clickFunction);

				m_clickFunction();
				m_buttonState = ButtonState::kPressed;
			}
		}
	}
}