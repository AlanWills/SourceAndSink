#include "pch.h"
#include "GameplayScreenData.h"


//-----------------------------------------------------------------------------------------------------------------------------------
GameplayScreenData::GameplayScreenData(const std::string& dataAsset) :
  BaseScreenData(dataAsset)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
GameplayScreenData::~GameplayScreenData()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
const char* GameplayScreenData::GetTilemapAsset() const
{
  return GetDocument()->RootElement()->FirstChildElement("TilemapAsset")->GetText();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void GameplayScreenData::GetAvailablePipesForLevel(std::unordered_map<const char*, int>& pipeDataAssets) const
{
  // Push back the number and name of the tiles in this level
  const XMLElement* pipesElement = GetDocument()->RootElement()->FirstChildElement("Pipes");
  assert(pipesElement);

  // Loop through all the child elements of our pipes node - these are the available pipes
  for (const XMLElement* item = pipesElement->FirstChildElement(); item != nullptr; item = item->NextSiblingElement())
  {
    int numPipes = 0;
    item->QueryIntText(&numPipes);

    // If we do not have pipes then continue and do not push back any data
    if (numPipes == 0)
    {
      continue;
    }

    // Get the name of the pipe asset
    const char* pipeAsset = item->Name();

    // Push back the data
    pipeDataAssets.insert(std::pair<const char*, int>(pipeAsset, numPipes));
  }
}