#pragma once

#include "Pipe.h"

class SinkPipe : public Pipe
{
public:
  SinkPipe(const std::string& dataAsset, Tile* parentTile);
  ~SinkPipe();

  void FillNeighbours() override;

  /// \brief Checks to see whether all the neighbours are full and updates the texture if so
  bool CheckFullyConnected();
};

