#include "pch.h"

#include "SinkPipe.h"
#include "Tile.h"


//-----------------------------------------------------------------------------------------------------------------------------------
SinkPipe::SinkPipe(const std::string& dataAsset, Tile* parentTile)
  : Pipe(dataAsset, parentTile, PipeStatus::kEmpty)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
SinkPipe::~SinkPipe()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void SinkPipe::UpdatePipeStatus()
{
  // It is only full when all entrances are connect to a full pipe
  const Tile* tile = GetParentAs<Tile>();
  assert(tile);

  // Iterate through the neighbours and work out if this pipe is connect to a pipe with water in it
  for (int neighbour = Tile::kUp; neighbour != Tile::kNumNeighbours; neighbour++)
  {
    // Check to see if our pipe has an opening onto this particular neighbour direction if not we continue
    if (!ConstGetPipeInfo().m_pipeInfoArray[neighbour])
    {
      continue;
    }


    // Check to see if the neighbour tile exists, if it does not then our sink is still empty so we return
    const Tile* neighbourTile = tile->GetNeighbour(static_cast<Tile::Neighbours>(neighbour));
    if (!neighbourTile)
    {
      SetPipeStatus(PipeStatus::kEmpty);
      return;
    }

    // If the neighbour tile exists we need to get it's stored pipe - if it does not exist or if it is not full, we return
    const Pipe* neighbourPipe = neighbourTile->GetStoredObjectAs<Pipe>();
    if (!neighbourPipe || neighbourPipe->GetPipeStatus() != PipeStatus::kFull)
    {
      SetPipeStatus(PipeStatus::kEmpty);
      return;
    }

    // If the neighbour tile has a pipe which is full we need to check whether the pipes match up.  If not, we return
    if (!neighbourPipe->ConstGetPipeInfo().CheckMatch(static_cast<PipeInfo::PipeDirection>(neighbour)))
    {
      // We are not connected to a full pipe so we return
      SetPipeStatus(PipeStatus::kEmpty);
      return;
    }
  }

  // All of the neighbours match and are full so the pipe is now full
  SetPipeStatus(PipeStatus::kFull);
}