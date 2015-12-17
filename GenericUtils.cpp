#include "pch.h"
#include "GenericUtils.h"


//-----------------------------------------------------------------------------------------------------------------------------------
GenericUtils::GenericUtils()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
GenericUtils::~GenericUtils()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
const wchar_t* GenericUtils::CharToWChar(const char* string)
{
	assert(!std::string(string).empty());

	const wchar_t* pwcsName = L"";
	// required size
	int nChars = MultiByteToWideChar(CP_ACP, 0, string, -1, NULL, 0);
	// allocate it
	pwcsName = new wchar_t[nChars];
	MultiByteToWideChar(CP_ACP, 0, string, -1, (LPWSTR)pwcsName, nChars);

	assert(!std::wstring(pwcsName).empty());

	return pwcsName;
}