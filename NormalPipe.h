#pragma once

#include "Pipe.h"

class NormalPipe : public Pipe
{
public:
  NormalPipe(const std::string& dataAsset, Tile* parentTile);
  ~NormalPipe();

  void HandleInput(DX::StepTimer const& timer, const Vector2& mousePosition) override;

  void FillNeighbours() override;

private:
  /// \brief Changes pipe's rotation but also the info array
  void Rotate();
};

