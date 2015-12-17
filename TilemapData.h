#pragma once

#include "BaseData.h"
#include "Tile.h"

#include <list>

class TilemapData : public BaseData
{

public:
	TilemapData(const char* dataAsset);
	~TilemapData();

	/// \brief Populates the inputted list with tiles created from data in the xml (better than dealing with having to return it
	void GetTiles(std::list<Tile*>& tiles);

	/// \brief Gets the display name of the tilemap
	const std::wstring GetDisplayName() const;
};