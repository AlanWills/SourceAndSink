#include "pch.h"

#include "GameplayScreen.h"

#include "ScreenManager.h"

#include "SinkPipe.h"
#include "SourcePipe.h"
#include "NormalPipe.h"


//-----------------------------------------------------------------------------------------------------------------------------------
GameplayScreen::GameplayScreen(ScreenManager* screenManager, const std::string& dataAsset) :
  BaseScreen(screenManager, dataAsset),
  m_gameplayScreenData(new GameplayScreenData(dataAsset)),
  m_backgroundTilemap(nullptr),
  m_hud(nullptr)
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

  m_hud = new HUD(this);
  AddScreenUIObject(m_hud, true, false);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void GameplayScreen::Initialize()
{
	BaseScreen::Initialize();

	m_backgroundTilemap->Initialize();

  std::unordered_map<std::string, std::pair<int, int>> m_sources;
  m_gameplayScreenData->GetSourcesForLevel(m_sources);

  for (std::pair<std::string, std::pair<int, int>> sourceInfo : m_sources)
  {
    Vector2 position = m_backgroundTilemap->GetWorldSpacePositionFromCoords(sourceInfo.second.first, sourceInfo.second.second);
    AddPipe<SourcePipe>(position, sourceInfo.first);
  }

  // Clear our map so that we can reuse it for the sinks
  m_sources.clear();
  m_gameplayScreenData->GetSinksForLevel(m_sources);

  for (std::pair<std::string, std::pair<int, int>> sinkInfo : m_sources)
  {
    Vector2 position = m_backgroundTilemap->GetWorldSpacePositionFromCoords(sinkInfo.second.first, sinkInfo.second.second);
    AddPipe<SinkPipe>(position, sinkInfo.first);
  }
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
	BaseScreen::HandleInput(timer);

	if (AcceptsInput())
	{
    GameMouse& gameMouse = GetScreenManager()->GetGameMouse();

		m_backgroundTilemap->HandleInput(timer, gameMouse.GetInGamePosition());

    // Check that we have clicked the mouse and clicked on the tilemap
    if (gameMouse.IsClicked(MouseButton::kLeftButton) && m_backgroundTilemap->IsClicked(gameMouse.GetInGamePosition()))
    {
      AddPipe<NormalPipe>(gameMouse.GetInGamePosition(), m_hud->GetSelectedPipeDataAsset());
    }
	}
}