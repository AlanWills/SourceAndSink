#include "pch.h"
#include "BaseScreenData.h"


//-----------------------------------------------------------------------------------------------------------------------------------
BaseScreenData::BaseScreenData(const std::string& dataAsset) :
	BaseData(dataAsset)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
BaseScreenData::~BaseScreenData()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
const std::wstring BaseScreenData::GetDisplayName() const
{
  const char* displayName = GetDocument()->RootElement()->FirstChildElement("DisplayName")->GetText();
  if (!displayName)
  {
    return L"";
  }

	return GenericUtils::CharToWChar(displayName);
}


//-----------------------------------------------------------------------------------------------------------------------------------
const char* BaseScreenData::GetBackgroundAsset() const
{
	return GetDocument()->RootElement()->FirstChildElement("BackgroundTextureAsset")->GetText();
}