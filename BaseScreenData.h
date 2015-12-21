#pragma once

#include "BaseData.h"

class BaseScreenData : public BaseData
{
public:
	BaseScreenData(const std::string& dataAsset);
	~BaseScreenData();

	const std::wstring GetDisplayName() const;
	const char* GetBackgroundAsset() const;
};

