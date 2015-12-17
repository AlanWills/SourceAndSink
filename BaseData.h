#pragma once

#include "tinyxml2.h"

using namespace tinyxml2;

class BaseData
{
public:
	BaseData(const char* dataAsset);
	~BaseData();

	void LoadData();
	const char* GetDataAsset() const { return m_dataAsset; }

protected:
	const tinyxml2::XMLDocument* GetDocument() const { return m_document.get(); }

private:
	std::unique_ptr<tinyxml2::XMLDocument> m_document;
	const char* m_dataAsset;
};

