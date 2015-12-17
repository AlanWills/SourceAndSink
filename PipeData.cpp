#include "pch.h"

#include "PipeData.h"


//-----------------------------------------------------------------------------------------------------------------------------------
PipeData::PipeData(const char* dataAsset) :
  BaseData(dataAsset)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
PipeData::~PipeData()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
const char* PipeData::GetEmptyTextureAsset() const
{
  return GetDocument()->RootElement()->FirstChildElement("EmptyTextureAsset")->GetText();
}


//-----------------------------------------------------------------------------------------------------------------------------------
const char* PipeData::GetFullTextureAsset() const
{
  return GetDocument()->RootElement()->FirstChildElement("FullTextureAsset")->GetText();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void PipeData::SetUpPipeInfo(Pipe::PipeInfo& pipeInfo) const
{
  bool top = false, right = false, down = false, left = false;

  const XMLElement* info = GetDocument()->RootElement()->FirstChildElement("PipeInfo");
  assert(info);

  info->QueryBoolAttribute("top", &top);
  info->QueryBoolAttribute("right", &right);
  info->QueryBoolAttribute("bottom", &down);
  info->QueryBoolAttribute("left", &left);

  pipeInfo.m_pipeInfoArray[Pipe::PipeInfo::kTop] = top;
  pipeInfo.m_pipeInfoArray[Pipe::PipeInfo::kRight] = right;
  pipeInfo.m_pipeInfoArray[Pipe::PipeInfo::kBottom] = down;
  pipeInfo.m_pipeInfoArray[Pipe::PipeInfo::kLeft] = left;
}