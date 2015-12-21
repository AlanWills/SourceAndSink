#pragma once

#include "Pipe.h"

class SinkPipe : public Pipe
{
public:
  SinkPipe(const std::string& dataAsset, Tile* parentTile);
  ~SinkPipe();

private:
  void UpdatePipeStatus() override;
};

