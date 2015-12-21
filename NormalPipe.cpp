#include "pch.h"

#include "NormalPipe.h"
#include "Tile.h"


//-----------------------------------------------------------------------------------------------------------------------------------
NormalPipe::NormalPipe(const char* dataAsset, Tile* parentTile) :
  Pipe(dataAsset, parentTile, PipeStatus::kEmpty)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
NormalPipe::~NormalPipe()
{
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
    // Check to see if the neighbour tile exists
    const Tile* neighbourTile = tile->GetNeighbour(static_cast<Tile::Neighbours>(neighbour));
    if (neighbourTile)
    {
      // If the neighbour tile exists we need to get it's stored pipe
      const Pipe* neighbourPipe = neighbourTile->GetStoredObjectAs<Pipe>();
      if (neighbourPipe && neighbourPipe->GetPipeStatus() == PipeStatus::kFull)
      {
        // If the neighbour tile has a pipe which is full we need to check whether the pipes match up
        if (GetPipeInfo().m_pipeInfoArray[neighbour] == true && neighbourPipe->GetPipeInfo().CheckMatch(static_cast<PipeInfo::PipeDirection>(neighbour)))
        {
          // We are connect to a full pipe so we can automatically stop searching and set the status to full
          SetPipeStatus(PipeStatus::kFull);
          return;
        }
      }
    }
  }

  // None of the neighbours match and are full so the pipe is still empty
  SetPipeStatus(PipeStatus::kEmpty);
}