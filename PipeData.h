#pragma once

#include "BaseData.h"
#include "Pipe.h"

class PipeData : public BaseData
{
public:
  PipeData(const char* dataAsset);
  ~PipeData();

  const char* GetEmptyTextureAsset() const;
  const char* GetFullTextureAsset() const;
  void SetUpPipeInfo(Pipe::PipeInfo& pipeInfo) const;
};