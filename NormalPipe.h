#pragma once

#include "Pipe.h"

class NormalPipe : public Pipe
{
public:
  NormalPipe(const std::string& dataAsset, Tile* parentTile);
  ~NormalPipe();

private:
  void UpdatePipeStatus() override;
};

