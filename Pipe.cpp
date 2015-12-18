#include "pch.h"

#include "Pipe.h"
#include "PipeData.h"


//-----------------------------------------------------------------------------------------------------------------------------------
Pipe::Pipe(const char* dataAsset, BaseObject* parent) :
  GameObject(dataAsset, LoadType::kData, parent),
  m_pipeData(new PipeData(dataAsset))
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
void Pipe::HandleInput(DX::StepTimer const& timer, const Vector2& mousePosition)
{
  GameObject::HandleInput(timer, mousePosition);

  if (AcceptsInput() && IsClicked())
  {
    // If the pipe is clicked on, we need to rotate it
    SetLocalRotation(GetLocalRotation() + XM_PIDIV2);
  }
}