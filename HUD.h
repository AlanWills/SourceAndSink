#pragma once

#include "Menu.h"

class GameplayScreen;
class ClickableImage;

class HUD : public Menu
{
public:
  HUD(GameplayScreen* gameplayScreen);
  ~HUD();
  
  void Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont) override;

  /// \brief Get the .xml filename for the pipe data asset
  const std::string& GetSelectedPipeDataAsset() const;

  /// \brief Used to change the HUD UI for certain events like Add pipes etc.
  void RebuildHUD();

protected:
  void AddInitialUI() override;

private:
  /// \brief Pointer to the gameplay screen this HUD is attached too
  const GameplayScreen* m_gameplayScreen;

  /// \brief Current selected pipe the user wants to place
  UIObject* m_selectedPipeImage;
};

