#pragma once

#include "GameObject.h"

class PipeData;

class Pipe : public GameObject
{
public:
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

  Pipe(const char* dataAsset, BaseObject* parent);
  ~Pipe();

  void LoadContent(ID3D11Device* device) override;

private:
  PipeInfo m_pipeInfo;

  std::unique_ptr<PipeData> m_pipeData;
};