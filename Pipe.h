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

  const PipeStatus GetPipeStatus() const { return m_pipeStatus; }
  const PipeInfo& ConstGetPipeInfo() const { return m_pipeInfo; }
  PipeInfo& GetPipeInfo() { return m_pipeInfo; }

  /// \brief Reset pipe status to kEmpty and sets filled flag to false
  virtual void ResetPipeStatus();

  /// \brief Fill all matching neighbours with water if this pipe is full and the neighbours exist
  virtual void FillNeighbours() = 0;

  void SetPipeStatus(const PipeStatus& pipeStatus) { m_pipeStatus = pipeStatus; }
  bool DoneFilling() const { return m_doneFilling; }

protected:
  Texture2D* GetTexture() const override;

  void SetDoneFilling(const bool doneFilling) { m_doneFilling = doneFilling; }

private:
  PipeInfo m_pipeInfo;

  std::unique_ptr<PipeData> m_pipeData;

  /// \brief Current status of the pipe
  PipeStatus m_pipeStatus;

  /// \brief A flag to indicate whether this tile has already been through the fill neighbour iteration this update loop - get's reset in reset pipe status
  bool m_doneFilling;

  /// \brief Texture handlers to represent the full pipe texture
  std::unique_ptr<Texture2D> m_fullTexture;
};