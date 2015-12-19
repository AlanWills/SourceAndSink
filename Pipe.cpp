#include "pch.h"

#include "Pipe.h"
#include "Tile.h"

#include "PipeData.h"


//-----------------------------------------------------------------------------------------------------------------------------------
Pipe::Pipe(const char* dataAsset, Tile* parent) :
  GameObject(dataAsset, LoadType::kData, parent),
  m_pipeData(new PipeData(dataAsset)),
  m_pipeStatus(kEmpty)
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

  LoadTexture(device, m_pipeData->GetEmptyTextureAsset());

  m_pipeData->SetUpPipeInfo(m_pipeInfo);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Pipe::Update(DX::StepTimer const& timer)
{
  GameObject::Update(timer);

  if (IsActive())
  {
    // Add validation code for empty/full here
    const Tile* tile = GetParentAs<Tile>();
    assert(tile);

    // Iterate through the neighbours and work out if this pipe is connect to a pipe with water in it
    for (int neighbour = Tile::kUp; neighbour < Tile::kNumNeighbours; neighbour++)
    {

    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Pipe::HandleInput(DX::StepTimer const& timer, const Vector2& mousePosition)
{
  GameObject::HandleInput(timer, mousePosition);

  if (AcceptsInput() && IsClicked())
  {
    // If the pipe is clicked on, we need to rotate it
    SetLocalRotation(GetLocalRotation() + XM_PIDIV2);
  }
}