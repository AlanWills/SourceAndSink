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

    /// \brief Takes an input direction and checks whether this pipe info matches it
    /// i.e. input left -> checks right
    /// input up -> checks down
    bool CheckMatch(const PipeDirection direction) const
    {
      switch (direction)
      {
        case kTop:
          return m_pipeInfoArray[kBottom];

        case kRight:
          return m_pipeInfoArray[kLeft];

        case kBottom:
          return m_pipeInfoArray[kTop];

        case kLeft:
          return m_pipeInfoArray[kRight];

        default:
          return false;
      }
    }
  };

  Pipe(const std::string& dataAsset, Tile* parentTile, PipeStatus initialPipeStatus = kEmpty);
  ~Pipe();

  void LoadContent(ID3D11Device* device) override;
  void Update(DX::StepTimer const& timer) override;
  void HandleInput(DX::StepTimer const& timer, const Vector2& mousePosition) override;

  const PipeStatus GetPipeStatus() const { return m_pipeStatus; }
  const PipeInfo GetPipeInfo() const { return m_pipeInfo; }

protected:
  Texture2D* GetTexture() const override;

  void SetPipeStatus(const PipeStatus pipeStatus) { m_pipeStatus = pipeStatus; }

private:
  /// \brief Update pipe status using neighbours
  virtual void UpdatePipeStatus() = 0;

  /// \brief Changes pipe's rotation but also the info array
  void Rotate();

  PipeInfo m_pipeInfo;

  std::unique_ptr<PipeData> m_pipeData;

  /// \brief Current status of the pipe
  PipeStatus m_pipeStatus;

  /// \brief Texture handlers to represent the full pipe texture
  std::unique_ptr<Texture2D> m_fullTexture;
};