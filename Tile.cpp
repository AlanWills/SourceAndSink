#include "pch.h"

#include "Tile.h"


//-----------------------------------------------------------------------------------------------------------------------------------
Tile::Tile(const Vector2& localPosition, const std::pair<int, int> tilemapCoords, const std::string& dataAsset, LoadType loadType, BaseObject* parent) :
	GameObject(localPosition, dataAsset, loadType, parent),
  m_storedObject(nullptr),
  m_tilemapCoords(tilemapCoords),
  m_neighbours(4)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Tile::~Tile()
{
}