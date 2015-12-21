#include "pch.h"

#include "SinkPipe.h"
#include "NormalPipe.h"
#include "Tile.h"


//-----------------------------------------------------------------------------------------------------------------------------------
NormalPipe::NormalPipe(const std::string& dataAsset, Tile* parentTile) :
  Pipe(dataAsset, parentTile, PipeStatus::kEmpty)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
NormalPipe::~NormalPipe()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void NormalPipe::HandleInput(DX::StepTimer const& timer, const Vector2& mousePosition)
{
  Pipe::HandleInput(timer, mousePosition);

  if (AcceptsInput())
  {
    if (IsClicked(MouseButton::kLeftButton))
    {
      // If the pipe is left clicked on, we need to rotate it
      Rotate();
    }

    if (IsClicked(MouseButton::kRightButton))
    {
      // If the pipe is right clicked on, we are going to remove it from the tilemap so we should kill it and it will get cleaned up automatically
      Die();
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void NormalPipe::Rotate()
{
  SetLocalRotation(GetLocalRotation() + XM_PIDIV2);
  GetPipeInfo().Rotate90Clockwise();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void NormalPipe::UpdatePipeStatus()
{
  // Add validation code for empty/full here
  const Tile* tile = GetParentAs<Tile>();
  assert(tile);

  // Iterate through the neighbours and work out if this pipe is connect to a pipe with water in it
  for (int neighbour = Tile::kUp; neighbour != Tile::kNumNeighbours; neighbour++)
  {
    // Check to see if our pipe has an opening onto this particular neighbour direction - if not, continue
    if (!ConstGetPipeInfo().m_pipeInfoArray[neighbour])
    {
      continue;
    }


    // Check to see if the neighbour tile exists
    const Tile* neighbourTile = tile->GetNeighbour(static_cast<Tile::Neighbours>(neighbour));
    if (!neighbourTile)
    {
      continue;
    }
        
    // If the neighbour tile exists we need to get it's stored pipe
    // If it is a sink pipe then we continue searching
    Pipe* neighbourPipe = neighbourTile->GetStoredObjectAs<Pipe>();
    if (!neighbourPipe || dynamic_cast<SinkPipe*>(neighbourPipe) || !neighbourPipe->GetPipeStatus() == PipeStatus::kFull)
    {
      continue;
    }

    // If the neighbour tile has a pipe which is full we need to check whether the pipes match up
    if (neighbourPipe->ConstGetPipeInfo().CheckMatch(static_cast<PipeInfo::PipeDirection>(neighbour)))
    {
      // We are connect to a full pipe so we can automatically stop searching and set the status to full
      SetPipeStatus(PipeStatus::kFull);
      return;
    }
  }

  // None of the neighbours match and are full so the pipe is still empty
  SetPipeStatus(PipeStatus::kEmpty);
}