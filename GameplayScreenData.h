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
  void GetAvailablePipesForLevel(std::unordered_map<const char*, int>& pipeDataAssets) const;
};

