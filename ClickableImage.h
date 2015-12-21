#pragma once

#include "UIObject.h"

class ClickableImage : public UIObject
{
public:
  ClickableImage(const Vector2& localPosition, const std::string& dataAsset, LoadType loadType = LoadType::kTexture, BaseObject* parent = nullptr, float lifeTime = FLT_MAX);
  ClickableImage(const Vector2& size, const Vector2& localPosition, const std::string& dataAsset, LoadType loadType = LoadType::kTexture, BaseObject* parent = nullptr, float lifeTime = FLT_MAX);
  virtual ~ClickableImage();

  void Update(DX::StepTimer const& timer) override;
  void HandleInput(DX::StepTimer const& timer, const Vector2& mousePosition) override;

  /// \brief Set the click function for this object
  void SetClickFunction(const std::function<void()>& clickFunction) { m_clickFunction = clickFunction; }

  enum ClickState
  {
    kIdle,
    kHighlighted,
    kPressed,
    kDisabled,
    kNumStates
  };

protected:
  const ClickState GetClickState() const { return m_clickState; }

private:
  ClickState m_clickState;

  float m_clickResetTimer;
  const float m_resetTime;

  /// \brief The function that will be execusted when the button is clicked
  std::function<void()> m_clickFunction;
};

