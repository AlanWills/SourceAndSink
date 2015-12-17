#include "pch.h"

#include "GameplayScreen.h"

#include "ScreenManager.h"


//-----------------------------------------------------------------------------------------------------------------------------------
GameplayScreen::GameplayScreen(ScreenManager* screenManager, const char* dataAsset) :
  BaseScreen(screenManager, dataAsset),
  m_gameplayScreenData(new GameplayScreenData(dataAsset)),
  m_backgroundTilemap(nullptr)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
GameplayScreen::~GameplayScreen()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void GameplayScreen::LoadContent()
{
  BaseScreen::LoadContent();

  m_gameplayScreenData->LoadData();
  assert(m_gameplayScreenData.get());

  m_backgroundTilemap.reset(new Tilemap(GetDevice(), m_gameplayScreenData->GetTilemapAsset()));
  m_backgroundTilemap->LoadContent();

  std::unordered_map<const char*, int> pipeData;
  m_gameplayScreenData->GetAvailablePipesForLevel(pipeData);

  // Used for positioning the UI for the pipes on the screen
  int pipeIndex = 0;
  for (std::pair<const char*, int> pair : pipeData)
  {
    // Store the string for this pipe
    std::unique_ptr<PipeData> pipeData(new PipeData(pair.first));
    pipeData->LoadData();

    for (int i = 0; i < pair.second; ++i)
    {
      AddScreenUIObject(new UIObject(Vector2(GetScreenCentre().x * 2 - 200 + 200 * (float)i, (float)300 + pipeIndex * 100), pipeData->GetEmptyTextureAsset()), true);
    }

    m_pipesDataAssets.push_back(pair.first);
    pipeIndex++;
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void GameplayScreen::Initialize()
{
	BaseScreen::Initialize();

	m_backgroundTilemap->Initialize();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void GameplayScreen::Update(DX::StepTimer const& timer)
{
	BaseScreen::Update(timer);

	if (IsActive())
	{
		m_backgroundTilemap->Update(timer);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
void GameplayScreen::DrawInGameObjects(SpriteBatch* spriteBatch, SpriteFont* spriteFont)
{
  if (IsVisible())
  {
    m_backgroundTilemap->Draw(spriteBatch, spriteFont);
  }

	BaseScreen::DrawInGameObjects(spriteBatch, spriteFont);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void GameplayScreen::HandleInput(DX::StepTimer const& timer)
{
	BaseScreen::Update(timer);

	if (AcceptsInput())
	{
    GameMouse& gameMouse = GetScreenManager()->GetGameMouse();

		m_backgroundTilemap->HandleInput(timer, gameMouse.GetInGamePosition());

    // Check that we have clicked the mouse and clicked on the tilemap
    if (gameMouse.IsClicked(GameMouse::MouseButton::kLeftButton) && m_backgroundTilemap->IsClicked(gameMouse.GetInGamePosition()))
    {
      AddPipe(gameMouse.GetInGamePosition());
    }
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
void GameplayScreen::AddPipe(const Vector2& location)
{
  // Get the tile we have clicked on
  Tile* clickedTile = m_backgroundTilemap->GetClickedTile(location);

  // Check that it is not already occupied
  if (!clickedTile->IsOccupied())
  {
    // If not, parent a pipe under it and set occupied to true for the tile
    AddGameObject(new Pipe(m_pipesDataAssets.front(), clickedTile), true, true);
    clickedTile->SetOccupied(true);
  }
}