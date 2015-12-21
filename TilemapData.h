#pragma once

#include "BaseData.h"
#include "Tile.h"

#include <list>

class TilemapData : public BaseData
{

public:
  typedef std::vector<std::vector<Tile*>> TilemapInfo;

	TilemapData(const std::string& dataAsset);
	~TilemapData();

	/// \brief Populates the inputted list with tiles created from data in the xml (better than dealing with having to return it
	void GetTiles(std::list<Tile*>& tiles, TilemapInfo& tilemap);

	/// \brief Gets the display name of the tilemap
	const std::wstring GetDisplayName() const;
};