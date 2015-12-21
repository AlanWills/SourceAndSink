#include "pch.h"

#include "TilemapData.h"


//-----------------------------------------------------------------------------------------------------------------------------------
TilemapData::TilemapData(const std::string& dataAsset) :
	BaseData(dataAsset)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
TilemapData::~TilemapData()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void TilemapData::GetTiles(std::list<Tile*>& tileData, TilemapInfo& tilemap)
{
	// Push back tiles here
	const XMLElement* tilesElement = GetDocument()->RootElement()->FirstChildElement("Tiles");
	assert(tilesElement);

  float startX = 0, startY = 0;
  tilesElement->QueryFloatAttribute("x", &startX);
  tilesElement->QueryFloatAttribute("y", &startY);

  int numRows = 0, numColumns = 0;

  // Work out the number of rows and push back containers to the tilemap structure
  for (const XMLElement* item = tilesElement->FirstChildElement(); item != nullptr; item = item->NextSiblingElement())
  {
    numRows++;
    tilemap.push_back(std::vector<Tile*>());
  }

  int rowIndex = 0;

	// Loop through all the child elements of our tiles node - these are the row
	for (const XMLElement* item = tilesElement->FirstChildElement(); item != nullptr; item = item->NextSiblingElement())
	{
    int numTiles = 0;
    item->QueryIntAttribute("tiles", &numTiles);

    // Specifies an offset so that rows can be offset from one another
    int indent = 0;
    item->QueryIntAttribute("offset", &indent);

    numColumns = indent + numTiles;

    for (int i = 0; i < indent; ++i)
    {
      // For anything in the indent we push back a nullptr so that really our tilemap data structure is square
      tilemap[rowIndex].push_back(nullptr);
    }

    for (int i = 0; i < numTiles; ++i)
    {
      // 64 is the width and height of our tile
      Tile* tile = new Tile(Vector2(startX + (indent + i) * 64, startY + rowIndex * 64), std::pair<int, int>(rowIndex, i + indent), "BackTile_Game.png");
      tilemap[rowIndex].push_back(tile);
      tileData.push_back(tile);
    }

    // Finished with this row's tiles - increment the row index
    rowIndex++;
	}

  // Set up tile neighbours here
  for (size_t y = 0; y < tilemap.size(); y++)
  {
    for (size_t x = 0; x < tilemap[y].size(); x++)
    {
      // If we have nullptr here, we do not have a tile so we can continue
      if (!tilemap[y][x])
      {
        continue;
      }

      // If tile is on the far left, it's left neighbour is null
      if (x == 0)
      {
        tilemap[y][x]->SetNeighbour(nullptr, Tile::Neighbours::kLeft);
      }
      // Else we just set it to the tile to the left
      else
      {
        tilemap[y][x]->SetNeighbour(tilemap[y][x - 1], Tile::Neighbours::kLeft);
      }

      // If tile is on the far right, it's right neighbour is null
      if (x == numColumns - 1)
      {
        tilemap[y][x]->SetNeighbour(nullptr, Tile::Neighbours::kRight);
      }
      // Else we just set it to the tile on the right
      else
      {
        tilemap[y][x]->SetNeighbour(tilemap[y][x + 1], Tile::Neighbours::kRight);
      }

      // If the tile is on the top of the tilemap it's up neighbour is null
      if (y == 0)
      {
        tilemap[y][x]->SetNeighbour(nullptr, Tile::Neighbours::kUp);
      }
      // Else we just set it to the tile above us
      else
      {
        tilemap[y][x]->SetNeighbour(tilemap[y - 1][x], Tile::Neighbours::kUp);
      }

      // If the tile is on the bottom of the tilemap it's down neighbour is null
      if (y == numRows - 1)
      {
        tilemap[y][x]->SetNeighbour(nullptr, Tile::Neighbours::kDown);
      }
      // Else we just set it to the tile below us
      else
      {
        tilemap[y][x]->SetNeighbour(tilemap[y + 1][x], Tile::Neighbours::kDown);
      }
    }
  }


	assert(tileData.size() > 0);
}


//-----------------------------------------------------------------------------------------------------------------------------------
const std::wstring TilemapData::GetDisplayName() const
{
	return GenericUtils::CharToWChar(GetDocument()->RootElement()->FirstChildElement("DisplayName")->GetText());
}