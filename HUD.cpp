#include "pch.h"

#include "GameplayScreen.h"

#include "HUD.h"
#include "ClickableImage.h"


//-----------------------------------------------------------------------------------------------------------------------------------
HUD::HUD(GameplayScreen* gameplayScreen) :
  Menu(gameplayScreen->GetDevice(), gameplayScreen->GetScreenDimensions(), gameplayScreen->GetScreenCentre(), "", LoadType::kNoLoad),
  m_gameplayScreen(gameplayScreen),
  m_selectedPipeImage(nullptr)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
HUD::~HUD()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void HUD::AddInitialUI()
{
  assert(m_gameplayScreen);
  std::unordered_map<const char*, int> pipeData;
  m_gameplayScreen->GetGameplayScreenData()->GetAvailablePipesForLevel(pipeData);

  // Used for positioning the UI clickable images for the pipes on the screen
  int pipeIndex = 0;
  for (std::pair<const char*, int> pair : pipeData)
  {
    // Store the string for this pipe
    std::unique_ptr<PipeData> pipeData(new PipeData(pair.first));
    pipeData->LoadData();

    // Don't iterate for now - just having button for each type of pipe - need to add label for quantity later
    /*for (int i = 0; i < pair.second; ++i)
    {
      
    }*/

    ClickableImage* image = new ClickableImage(Vector2(m_gameplayScreen->GetScreenDimensions().x - 200, (float)300 + pipeIndex * 100), pipeData->GetEmptyTextureAsset(), BaseObject::LoadType::kTexture, this);
    image->SetClickFunction([this, image]()
    {
      m_selectedPipeImage = image;
      RemoveUIObject(L"Selected Pipe Image");

      UIObject* selectedPipeImage = new UIObject(Vector2(200, 200), GetSelectedPipeAsset(), LoadType::kTexture, this);
      selectedPipeImage->SetName(L"Selected Pipe Image");
      AddUIObject(selectedPipeImage, true, true);
    });

    AddUIObject(image);

    // Initialize the selected pipe asset
    m_selectedPipeImage = image;

    pipeIndex++;
  }

  UIObject* selectedPipeImage = new UIObject(Vector2(200, 200), GetSelectedPipeAsset(), LoadType::kTexture, this);
  selectedPipeImage->SetName(L"Selected Pipe Image");
  AddUIObject(selectedPipeImage);
}


//-----------------------------------------------------------------------------------------------------------------------------------
const char* HUD::GetSelectedPipeAsset() const
{
  assert(m_selectedPipeImage);
  return m_selectedPipeImage->GetStoredObjectAs<std::string>().c_str();
}