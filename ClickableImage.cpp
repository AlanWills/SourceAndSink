#include "pch.h"
#include "ClickableImage.h"


//-----------------------------------------------------------------------------------------------------------------------------------
ClickableImage::ClickableImage(const Vector2& localPosition, const char* dataAsset, LoadType loadType, BaseObject* parent, float lifeTime)
  : ClickableImage(Vector2::Zero, localPosition, dataAsset, loadType, parent, lifeTime)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
ClickableImage::ClickableImage(const Vector2& size, const Vector2& localPosition, const char* dataAsset, LoadType loadType, BaseObject* parent, float lifeTime)
  : UIObject(size, localPosition, dataAsset, loadType, parent, lifeTime),
  m_clickState(kIdle),
  m_resetTime(0.05f),
  m_clickResetTimer(0.05f)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
ClickableImage::~ClickableImage()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ClickableImage::Update(DX::StepTimer const& timer)
{
  UIObject::Update(timer);

  if (IsActive())
  {
    m_clickResetTimer += (float)timer.GetElapsedSeconds();
    if (m_clickResetTimer >= m_resetTime)
    {
      m_clickState = ClickState::kIdle;
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ClickableImage::HandleInput(DX::StepTimer const& timer, const Vector2& mousePosition)
{
  UIObject::HandleInput(timer, mousePosition);

  if (AcceptsInput())
  {
    if (IsMouseOver() && m_clickState != ClickState::kPressed)
    {
      m_clickState = ClickState::kHighlighted;
    }

    if (IsSelected())
    {
      if (m_clickState != ClickState::kPressed)
      {
        assert(m_clickFunction);

        m_clickFunction();
        m_clickState = ClickState::kPressed;
      }
    }
  }
}