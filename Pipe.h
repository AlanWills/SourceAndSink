#pragma once

#include "GameObject.h"

class PipeData;
class Tile;

class Pipe : public GameObject
{
public:
  enum PipeStatus
  {
    kEmpty,
    kFull,
  };

  // Holds information on which way the pipe lets water flow through
  struct PipeInfo
  {
  public:
    enum PipeDirection
    {
      kTop,
      kRight,
      kBottom,
      kLeft,
      kNumDirections,
    };

    PipeInfo()
    {
      m_pipeInfoArray[kTop] = false;
      m_pipeInfoArray[kRight] = false;
      m_pipeInfoArray[kBottom] = false;
      m_pipeInfoArray[kLeft] = false;
    }

    void Rotate90Clockwise()
    {
      bool top = m_pipeInfoArray[kLeft];
      bool right = m_pipeInfoArray[kTop];
      bool bottom = m_pipeInfoArray[kRight];
      bool left = m_pipeInfoArray[kBottom];

      m_pipeInfoArray[kTop] = top;
      m_pipeInfoArray[kRight] = right;
      m_pipeInfoArray[kBottom] = bottom;
      m_pipeInfoArray[kLeft] = left;
    }

    bool m_pipeInfoArray[4];
  };

  Pipe(const char* dataAsset, Tile* parentTile);
  ~Pipe();

  void LoadContent(ID3D11Device* device) override;
  void Update(DX::StepTimer const& timer) override;
  void HandleInput(DX::StepTimer const& timer, const Vector2& mousePosition) override;

  const PipeStatus GetPipeStatus() const { return m_pipeStatus; }

private:
  PipeInfo m_pipeInfo;

  std::unique_ptr<PipeData> m_pipeData;

  /// \brief Current status of the pipe
  PipeStatus m_pipeStatus;
};