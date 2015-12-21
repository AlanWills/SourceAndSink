#include "pch.h"
#include "SourcePipe.h"


//-----------------------------------------------------------------------------------------------------------------------------------
SourcePipe::SourcePipe(const std::string& dataAsset, Tile* parentTile) :
  Pipe(dataAsset, parentTile, PipeStatus::kFull)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
SourcePipe::~SourcePipe()
{
}
