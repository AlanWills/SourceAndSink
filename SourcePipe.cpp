#include "pch.h"

#include "SourcePipe.h"
#include "Tile.h"
#include "SinkPipe.h"


//-----------------------------------------------------------------------------------------------------------------------------------
SourcePipe::SourcePipe(const std::string& dataAsset, Tile* parentTile) :
  Pipe(dataAsset, parentTile, PipeStatus::kFull)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
SourcePipe::~SourcePipe()
{
}


void SourcePipe::ResetPipeStatus()
{
  Pipe::ResetPipeStatus();

  SetPipeStatus(PipeStatus::kFull);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void SourcePipe::FillNeighbours()
{
  SetDoneFilling(true);

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
    // If it is a sink pipe then we continue searching
    // If it has already had the fill iteration run on it the continue
    Pipe* neighbourPipe = neighbourTile->GetStoredObjectAs<Pipe>();
    if (!neighbourPipe || dynamic_cast<SinkPipe*>(neighbourPipe) || neighbourPipe->DoneFilling())
    {
      continue;
    }

    // Check that the pipes match up, if not, we can just continue
    if (!neighbourPipe->ConstGetPipeInfo().CheckMatch(static_cast<PipeInfo::PipeDirection>(neighbour)))
    {
      continue;
    }

    // The pipes match up so fill it
    neighbourPipe->SetPipeStatus(PipeStatus::kFull);
    neighbourPipe->FillNeighbours();
  }
}