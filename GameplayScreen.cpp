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

  m_gameplayScreenData->GetAvailablePipesForLevel(m_availablePipes);

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

  for (std::pair<const std::string&, const std::pair<int, int>&> sourceInfo : m_sources)
  {
    Vector2 position = m_backgroundTilemap->GetWorldSpacePositionFromCoords(sourceInfo.second.first, sourceInfo.second.second);
    m_availablePipes.at(sourceInfo.first) += 1;
    AddPipe<SourcePipe>(position, sourceInfo.first);
  }

  // Clear our map so that we can reuse it for the sinks
  m_sources.clear();
  m_gameplayScreenData->GetSinksForLevel(m_sources);

  for (const std::pair<const std::string&, const std::pair<int, int>&>& sinkInfo : m_sources)
  {
    Vector2 position = m_backgroundTilemap->GetWorldSpacePositionFromCoords(sinkInfo.second.first, sinkInfo.second.second);
    m_availablePipes.at(sinkInfo.first) += 1;
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

    // Reset all the pipe statuses before iterating through and filling them
    std::list<Pipe*> pipes;
    FindPipes<Pipe>(pipes);

    for (Pipe* pipe : pipes)
    {
      pipe->ResetPipeStatus();
    }

    // We have to start from the source pipes otherwise we will have non-deterministic filling behaviour
    std::list<SourcePipe*> sourcePipes;
    FindPipes<SourcePipe>(sourcePipes);

    for (SourcePipe* sourcePipe : sourcePipes)
    {
      sourcePipe->FillNeighbours();
    }

    // Check all the sinks are full - if so, we are done
    bool allSinksFullyConnected = true;

    std::list<SinkPipe*> sinkPipes;
    FindPipes<SinkPipe>(sinkPipes);

    for (SinkPipe* sinkPipe : sinkPipes)
    {
      if (!sinkPipe->CheckFullyConnected())
      {
        // We have found a sink which is not fully connected and so we finish
        allSinksFullyConnected = false;
      }
    }
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
      // See if we have any more pipes of the selected one available
      if (m_availablePipes.at(m_hud->GetSelectedPipeDataAsset()) > 0)
      {
        AddPipe<NormalPipe>(gameMouse.GetInGamePosition(), m_hud->GetSelectedPipeDataAsset());
      }
    }
	}
}