#include "pch.h"

#include "GameplayScreen.h"

#include "HUD.h"
#include "ClickableImage.h"
#include "Label.h"


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

  // Used for positioning the UI clickable images for the pipes on the screen
  int pipeIndex = 0;
  // Absolutely need to pass these by reference - otherwise our pointers to the int don't work and we call the copy constructor for the string
  for (const std::pair<const std::string&, const int&>& pair : m_gameplayScreen->GetAvailablePipes())
  {
    // Store the string for this pipe
    std::unique_ptr<PipeData> pipeData(new PipeData(pair.first));
    pipeData->LoadData();

    ClickableImage* image = new ClickableImage(Vector2(m_gameplayScreen->GetScreenDimensions().x * 0.5f - 200, (float)-150 + pipeIndex * 100), pipeData->GetEmptyTextureAsset(), BaseObject::LoadType::kTexture, this);
    image->SetClickFunction([this, image]()
    {
      m_selectedPipeImage = new UIObject(Vector2(0, m_gameplayScreen->GetScreenDimensions().y * 0.5f - 100), image->GetDataAsset(), LoadType::kTexture, this);
      m_selectedPipeImage->LoadContent(m_gameplayScreen->GetDevice());
      m_selectedPipeImage->Initialize();
      m_selectedPipeImage->SetName(image->GetName());
    });
    image->SetName(pipeData->GetDataAsset());

    AddUIObject(image);

    // Add labels to indicate how many pipes there are
    Label* numberLabel = new Label(Vector2(-100, 0), std::to_wstring(pair.second), image);
    numberLabel->SetName(pair.first + " Number Label");
    numberLabel->SetStoredObject((void*)&pair.second);
    AddUIObject(numberLabel);

    // Initialize the starting selected pipe
    m_selectedPipeImage = new UIObject(Vector2(0, m_gameplayScreen->GetScreenDimensions().y * 0.5f - 100), pipeData->GetEmptyTextureAsset(), LoadType::kTexture, this);
    m_selectedPipeImage->SetName(pipeData->GetDataAsset());

    pipeIndex++;
  }

  m_selectedPipeImage->LoadContent(m_gameplayScreen->GetDevice());
  m_selectedPipeImage->Initialize();

  AddUIObject(new Label(Vector2(0, -m_selectedPipeImage->GetSize().y), L"Current Selected Pipe:", m_selectedPipeImage));
}


//-----------------------------------------------------------------------------------------------------------------------------------
void HUD::Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont)
{
  Menu::Draw(spriteBatch, spriteFont);

  if (IsVisible())
  {
    assert(m_selectedPipeImage);
    m_selectedPipeImage->Draw(spriteBatch, spriteFont);
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
const std::string& HUD::GetSelectedPipeDataAsset() const
{
  assert(m_selectedPipeImage);
  const std::string& dataAsset = m_selectedPipeImage->GetName();
  assert(!dataAsset.empty());

  return dataAsset;
}


//-----------------------------------------------------------------------------------------------------------------------------------
void HUD::RebuildHUD()
{
  for (const std::pair<const std::string&, int>& pair : m_gameplayScreen->GetAvailablePipes())
  {
    Label* label = FindObjectAs<Label>(pair.first + " Number Label");
    assert(label);

    label->SetText(std::to_wstring(*label->GetStoredObjectAs<int*>()));
  }
}