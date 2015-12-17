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