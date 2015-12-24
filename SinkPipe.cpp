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
void SinkPipe::FillNeighbours()
{
  SetDoneFilling(true);
}


//-----------------------------------------------------------------------------------------------------------------------------------
bool SinkPipe::CheckFullyConnected()
{
  // Add validation code for empty/full here
  const Tile* tile = GetParentAs<Tile>();
  assert(tile);

  // Iterate through the neighbours
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
    Pipe* neighbourPipe = neighbourTile->GetStoredObjectAs<Pipe>();

    // Our Level should not be set up so we have two neighbouring sinks
    assert(!dynamic_cast<SinkPipe*>(neighbourPipe));

    // Neighbour pipe does not exist or is not full
    if (!neighbourPipe || neighbourPipe->GetPipeStatus() == PipeStatus::kEmpty)
    {
      return false;
    }

    // Check that the pipes match up, if not, we return false
    if (!neighbourPipe->ConstGetPipeInfo().CheckMatch(static_cast<PipeInfo::PipeDirection>(neighbour)))
    {
      return false;
    }
  }

  // All the open sections of this sink match up so fill it
  SetPipeStatus(PipeStatus::kFull);
  return true;
}