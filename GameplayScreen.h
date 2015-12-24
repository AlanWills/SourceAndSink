#pragma once

#include "BaseScreen.h"

#include "GameplayScreenData.h"
#include "PipeData.h"

#include "Tilemap.h"

#include "HUD.h"

class GameplayScreen : public BaseScreen
{
public:
	GameplayScreen(ScreenManager* screenManager, const std::string& dataAsset);
	~GameplayScreen();

	void LoadContent() override;
	void Initialize() override;
	void Update(DX::StepTimer const& timer) override;
	void DrawInGameObjects(SpriteBatch* spriteBatch, SpriteFont* spriteFont) override;
	void HandleInput(DX::StepTimer const& timer) override;

  const GameplayScreenData* GetGameplayScreenData() const { return m_gameplayScreenData.get(); }
  const std::unordered_map<std::string, int>& GetAvailablePipes() const { return m_availablePipes; }

private:
  template <typename T>
  void AddPipe(const Vector2& location, const std::string& dataAsset);

  template <typename T>
  void FindPipes(std::list<T*>& pipes) const;

	std::unique_ptr<Tilemap> m_backgroundTilemap;
  std::unique_ptr<GameplayScreenData> m_gameplayScreenData;

  /// A list of references for our pipes ONLY - they are looked after by the BaseObjectManager for the screen
  /// This will be for the purposes of validation etc.
  std::list<Pipe*> m_pipes;

  std::unordered_map<std::string, int> m_availablePipes;

  /// \brief Pointer to our HUD
  HUD* m_hud;
};

template <typename T>
void GameplayScreen::AddPipe(const Vector2& location, const std::string& dataAsset)
{
  // Get the tile we have clicked on
  Tile* clickedTile = m_backgroundTilemap->GetClickedTile(location);

  // Check that it is not already occupied
  if (!clickedTile->IsOccupied())
  {
    // If not, parent a pipe under it and set occupied to true for the tile
    T* addedPipe = new T(dataAsset, clickedTile);
    addedPipe->SetOnDeathFunction([this, addedPipe]()
    {
      addedPipe->GetParentAs<Tile>()->SetStoredObject(nullptr);
      m_availablePipes.at(addedPipe->GetDataAsset()) += 1;
      m_hud->RebuildHUD();
    });

    AddGameObject(addedPipe, true, true);
    clickedTile->SetStoredObject(addedPipe);

    // Subtract one from the current count of available pipes
    m_availablePipes.at(dataAsset) -= 1;

    // Rebuild the HUD
    m_hud->RebuildHUD();
  }
}

template <typename T>
void GameplayScreen::FindPipes(std::list<T*>& pipes) const
{
  pipes.clear();

  for (GameObject* gameObject : GetGameObjects())
  {
    if (dynamic_cast<T*>(gameObject))
    {
      pipes.push_back(dynamic_cast<T*>(gameObject));
    }
  }
}