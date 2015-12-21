#pragma once

#include "Pipe.h"

class NormalPipe : public Pipe
{
public:
  NormalPipe(const char* dataAsset, Tile* parentTile);
  ~NormalPipe();

private:
  void UpdatePipeStatus() override;
};

