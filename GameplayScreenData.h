#pragma once

#include "BaseScreenData.h"
#include "Pipe.h"

#include <unordered_map>

class GameplayScreenData : public BaseScreenData
{
public:
  GameplayScreenData(const std::string& dataAsset);
  ~GameplayScreenData();

  const char* GetTilemapAsset() const;

  /// \brief Populates the inputted map with dataAssets and quantities of the number of pipes available for this level
  void GetAvailablePipesForLevel(std::unordered_map<std::string, int>& pipeDataAssets) const;

  /// \brief Populates the inputted map with dataAssets and tilemap grid positions of sources for this level - in the xml the grid positions are one indexed
  void GetSourcesForLevel(std::unordered_map<std::string, std::pair<int, int>>& sourceDataAssets) const;

  /// \brief Populates the inputted map with dataAssets and tilemap grid positions of sinks for this level - in the xml the grid positions are one indexed
  void GetSinksForLevel(std::unordered_map<std::string, std::pair<int, int>>& sinkDataAssets) const;
};

