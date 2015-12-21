#include "pch.h"

#include "Pipe.h"
#include "Tile.h"

#include "PipeData.h"


//-----------------------------------------------------------------------------------------------------------------------------------
Pipe::Pipe(const std::string& dataAsset, Tile* parent, PipeStatus initialPipeStatus) :
  GameObject(dataAsset, LoadType::kData, parent),
  m_pipeData(new PipeData(dataAsset)),
  m_pipeStatus(initialPipeStatus),
  m_fullTexture(new Texture2D())
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Pipe::~Pipe()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Pipe::LoadContent(ID3D11Device* device)
{
  GameObject::LoadContent(device);

  m_pipeData->LoadData();
  assert(m_pipeData.get());

  // Load default empty texture 
  LoadTexture(device, m_pipeData->GetEmptyTextureAsset());

  // Load full texture
  const wchar_t* wTextureAsset = GenericUtils::CharToWChar(m_pipeData->GetFullTextureAsset());
  m_fullTexture->Load(device, wTextureAsset);

  assert(m_fullTexture->GetTexture());

  delete[] wTextureAsset;

  m_pipeData->SetUpPipeInfo(m_pipeInfo);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Pipe::Update(DX::StepTimer const& timer)
{
  GameObject::Update(timer);

  if (IsActive())
  {
    // Update pipe status
    UpdatePipeStatus();
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Pipe::HandleInput(DX::StepTimer const& timer, const Vector2& mousePosition)
{
  GameObject::HandleInput(timer, mousePosition);

  if (AcceptsInput())
  {
    if (IsClicked(MouseButton::kLeftButton))
    {
      // If the pipe is left clicked on, we need to rotate it
      Rotate();
    }

    if (IsClicked(MouseButton::kRightButton))
    {
      // If the pipe is right clicked on, we are going to remove it from the tilemap so we should kill it and it will get cleaned up automatically
      Die();
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Pipe::Rotate()
{
  SetLocalRotation(GetLocalRotation() + XM_PIDIV2);
  m_pipeInfo.Rotate90Clockwise();
}


//-----------------------------------------------------------------------------------------------------------------------------------
Texture2D* Pipe::GetTexture() const
{
  // Return the full or empty texture based on the status of the pipe
  if (m_pipeStatus == kEmpty)
  {
    // Return empty texture
    return GameObject::GetTexture();
  }
  else
  {
    // Return full texture
    return m_fullTexture.get();
  }

  return nullptr;
}