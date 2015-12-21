#include "pch.h"
#include "SourcePipe.h"


//-----------------------------------------------------------------------------------------------------------------------------------
SourcePipe::SourcePipe(const char* dataAsset, Tile* parentTile) :
  Pipe(dataAsset, parentTile, PipeStatus::kFull)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
SourcePipe::~SourcePipe()
{
}
