#include "pch.h"
#include "BaseData.h"


//-----------------------------------------------------------------------------------------------------------------------------------
BaseData::BaseData(const std::string& dataAsset) :
	m_document(nullptr),
	m_dataAsset(dataAsset)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
BaseData::~BaseData()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseData::LoadData()
{
	m_document.reset(new tinyxml2::XMLDocument());
	m_document->LoadFile(m_dataAsset.c_str());

	assert(m_document.get());
}