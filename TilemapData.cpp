#include "pch.h"

#include "TilemapData.h"


//-----------------------------------------------------------------------------------------------------------------------------------
TilemapData::TilemapData(const char* dataAsset) :
	BaseData(dataAsset)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
TilemapData::~TilemapData()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void TilemapData::GetTiles(std::list<Tile*>& tileData)
{
	// Push back tiles here
	const XMLElement* tilesElement = GetDocument()->RootElement()->FirstChildElement("Tiles");
	assert(tilesElement);

  float startX = 0, startY = 0;
  tilesElement->QueryFloatAttribute("x", &startX);
  tilesElement->QueryFloatAttribute("y", &startY);

  int rowIndex = 0;

	// Loop through all the child elements of our tiles node - these are the row
	for (const XMLElement* item = tilesElement->FirstChildElement(); item != nullptr; item = item->NextSiblingElement())
	{
    int numTiles = 0;
    item->QueryIntAttribute("tiles", &numTiles);

    // Specifies an offset so that rows can be offset from one another
    int indent = 0;
    item->QueryIntAttribute("offset", &indent);

    for (int i = 0; i < numTiles; ++i)
    {
      // 64 is the width and height of our tile
      tileData.push_back(new Tile(Vector2(startX + (indent + i) * 64, startY + rowIndex * 64), "BackTile_Game.png"));
    }

    // Finished with this row's tiles - increment the row index
    rowIndex++;
	}

	assert(tileData.size() > 0);
}


//-----------------------------------------------------------------------------------------------------------------------------------
const std::wstring TilemapData::GetDisplayName() const
{
	return GenericUtils::CharToWChar(GetDocument()->RootElement()->FirstChildElement("DisplayName")->GetText());
}