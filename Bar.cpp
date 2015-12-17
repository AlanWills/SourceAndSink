#include "pch.h"

#include "Bar.h"


//-----------------------------------------------------------------------------------------------------------------------------------
Bar::Bar(
	const float maxValue,
	const Vector2& localPosition,
	const char* backgroundDataAsset,
	LoadType loadType,
	BaseObject* parent,
	float lifeTime) :
	Bar(maxValue, Vector2::Zero, localPosition, backgroundDataAsset, loadType, parent, lifeTime)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Bar::Bar(
	const float maxValue,
	const Vector2& size,
	const Vector2& localPosition,
	const char* backgroundDataAsset,
	LoadType loadType,
	BaseObject* parent,
	float lifeTime) :
	UIObject(size, localPosition, backgroundDataAsset, loadType, parent, lifeTime),
	m_maxValue(maxValue),
	m_valueToWatch(&m_maxValue),
	m_frontTexture(new Texture2D())
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Bar::Bar(
	const float* valueToWatch,
	const float maxValue,
	const Vector2& localPosition,
	const char* dataAsset,
	LoadType loadType,
	BaseObject* parent,
	float lifeTime) :
	Bar(valueToWatch, maxValue, Vector2::Zero, localPosition, dataAsset, loadType, parent, lifeTime)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Bar::Bar(
	const float* valueToWatch, 
	const float maxValue, 
	const Vector2& size, 
	const Vector2& localPosition, 
	const char* dataAsset,
	LoadType loadType,
	BaseObject* parent,
	float lifeTime) :
	UIObject(size, localPosition, dataAsset, loadType, parent, lifeTime),
	m_valueToWatch(valueToWatch),
	m_maxValue(maxValue),
	m_frontTexture(new Texture2D())
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Bar::~Bar()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Bar::LoadContent(ID3D11Device* device)
{
	UIObject::LoadContent(device);

	m_frontTexture->Load(device, GenericUtils::CharToWChar(GetDataAsset()));
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Bar::Update(DX::StepTimer const& timer)
{
	UIObject::Update(timer);

	if (IsActive())
	{
		float ratio = *m_valueToWatch / m_maxValue;
		m_frontBarPosition = GetLocalPosition() - GetSize() * ratio * 0.5f;
		m_frontBarSize = Vector2(GetSize().x * ratio, GetSize().y);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Bar::Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont)
{
	UIObject::Draw(spriteBatch, spriteFont);

	if (IsVisible())
	{
		assert(m_frontTexture->GetTexture());
		spriteBatch->Draw(
			m_frontTexture->GetTexture(),
			GetWorldPosition(m_frontBarPosition),
			nullptr,
			GetColour() * GetOpacity(),
			GetWorldRotation(),
			m_frontTexture->GetCentre(),
			XMVectorDivide(m_frontBarSize, m_frontTexture->GetDimensions()));
	}
}