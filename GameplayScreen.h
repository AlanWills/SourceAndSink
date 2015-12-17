#pragma once

#include "BaseScreen.h"

#include "GameplayScreenData.h"
#include "PipeData.h"

#include "Tilemap.h"

class GameplayScreen : public BaseScreen
{
public:
	GameplayScreen(ScreenManager* screenManager, const char* dataAsset);
	~GameplayScreen();

	void LoadContent() override;
	void Initialize() override;
	void Update(DX::StepTimer const& timer) override;
	void DrawInGameObjects(SpriteBatch* spriteBatch, SpriteFont* spriteFont) override;
	void HandleInput(DX::StepTimer const& timer) override;

private:
	std::unique_ptr<Tilemap> m_backgroundTilemap;
  std::unique_ptr<GameplayScreenData> m_gameplayScreenData;

  typedef std::vector<const char*> PipesDataAssets;
  PipesDataAssets m_pipesDataAssets;

  /// A list of references for our pipes ONLY - they are looked after by the BaseObjectManager for the screen
  /// This will be for the purposes of validation etc.
  std::list<Pipe*> m_pipes;
};