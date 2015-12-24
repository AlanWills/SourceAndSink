#pragma once

#include "Pipe.h"

class SourcePipe : public Pipe
{
public:
  SourcePipe(const std::string& dataAsset, Tile* parentTile);
  ~SourcePipe();

  /// \brief The source will always be full
  void ResetPipeStatus() override;

  void FillNeighbours() override;
};

