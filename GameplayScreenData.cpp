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
void GameplayScreenData::GetAvailablePipesForLevel(std::unordered_map<std::string, int>& pipeDataAssets) const
{
  // Push back the number and name of the tiles in this level
  const XMLElement* pipesElement = GetDocument()->RootElement()->FirstChildElement("AvailablePipes");
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

    // Push back the data
    pipeDataAssets.insert(std::pair<std::string, int>(item->Name(), numPipes));
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void GameplayScreenData::GetSourcesForLevel(std::unordered_map<std::string, std::pair<int, int>>& m_sources) const
{
  // Push back the number and name of the tiles in this level
  const XMLElement* sourcesElement = GetDocument()->RootElement()->FirstChildElement("Sources");
  assert(sourcesElement);

  // Loop through all the child elements of our pipes node - these are the available pipes
  for (const XMLElement* item = sourcesElement->FirstChildElement(); item != nullptr; item = item->NextSiblingElement())
  {
    std::string dataAsset = item->GetText();
    assert(!dataAsset.empty());

    int x = -1, y = -1;
    item->QueryIntAttribute("x", &x);
    item->QueryIntAttribute("y", &y);

    assert(x >= 0);
    assert(y >= 0);
    
    // Push back the data
    m_sources.insert(std::pair<std::string, std::pair<int, int>>(dataAsset, std::pair<int, int>(x - 1, y - 1)));
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void GameplayScreenData::GetSinksForLevel(std::unordered_map<std::string, std::pair<int, int>>& m_sinks) const
{
  // Push back the number and name of the tiles in this level
  const XMLElement* sinksElement = GetDocument()->RootElement()->FirstChildElement("Sinks");
  assert(sinksElement);

  // Loop through all the child elements of our pipes node - these are the available pipes
  for (const XMLElement* item = sinksElement->FirstChildElement(); item != nullptr; item = item->NextSiblingElement())
  {
    std::string dataAsset = item->GetText();
    assert(!dataAsset.empty());

    int x = -1, y = -1;
    item->QueryIntAttribute("x", &x);
    item->QueryIntAttribute("y", &y);

    assert(x >= 0);
    assert(y >= 0);

    // Push back the data
    m_sinks.insert(std::pair<std::string, std::pair<int, int>>(dataAsset, std::pair<int, int>(x - 1, y - 1)));
  }
}