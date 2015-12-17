#include "pch.h"

#include "Tile.h"


//-----------------------------------------------------------------------------------------------------------------------------------
Tile::Tile(const Vector2& localPosition, const char* dataAsset, LoadType loadType, BaseObject* parent) :
	GameObject(localPosition, dataAsset, loadType, parent)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Tile::~Tile()
{
}
