#pragma once

#include "Menu.h"

class GameplayScreen;
class ClickableImage;

class HUD : public Menu
{
public:
  HUD(GameplayScreen* gameplayScreen);
  ~HUD();

  const char* GetSelectedPipeAsset() const;

protected:
  void AddInitialUI() override;

private:
  /// \brief Pointer to the gameplay screen this HUD is attached too
  const GameplayScreen* m_gameplayScreen;

  /// \brief Current selected pipe the user wants to place
  const ClickableImage* m_selectedPipeImage;
};

