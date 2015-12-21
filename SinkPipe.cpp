#include "pch.h"
#include "SinkPipe.h"


//-----------------------------------------------------------------------------------------------------------------------------------
SinkPipe::SinkPipe(const char* dataAsset, Tile* parentTile)
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
}