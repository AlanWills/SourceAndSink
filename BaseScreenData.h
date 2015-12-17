#pragma once

#include "BaseData.h"

class BaseScreenData : public BaseData
{
public:
	BaseScreenData(const char* dataAsset);
	~BaseScreenData();

	const std::wstring GetDisplayName() const;
	const char* GetBackgroundAsset() const;
};

