#include "pch.h"

#include "GameplayScreen.h"

#include "ScreenManager.h"

#include "SourcePipe.h"
#include "NormalPipe.h"


//-----------------------------------------------------------------------------------------------------------------------------------
GameplayScreen::GameplayScreen(ScreenManager* screenManager, const char* dataAsset) :
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

  std::unordered_map<const char*, int> pipeData;
  m_gameplayScreenData->GetAvailablePipesForLevel(pipeData);

  m_hud = new HUD(this);
  AddScreenUIObject(m_hud, true, false);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void GameplayScreen::Initialize()
{
	BaseScreen::Initialize();

	m_backgroundTilemap->Initialize();

  AddPipe<SourcePipe>(GetScreenCentre(), m_hud->GetSelectedPipeAsset());
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
    if (gameMouse.IsClicked(GameMouse::MouseButton::kLeftButton) && m_backgroundTilemap->IsClicked(gameMouse.GetInGamePosition()))
    {
      AddPipe<NormalPipe>(gameMouse.GetInGamePosition(), m_hud->GetSelectedPipeAsset());
    }
	}
}