#include "pch.h"
#include "Texture2D.h"
#include "WICTextureLoader.h"

using Microsoft::WRL::ComPtr;
using namespace DX;

//-----------------------------------------------------------------------------------------------------------------------------------
Texture2D::Texture2D() :
m_texture(nullptr),
m_centre(Vector2(0, 0)),
m_dimensions(Vector2(0, 0))
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Texture2D::~Texture2D()
{
	if (m_texture)
	{
		m_texture->Release();
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Texture2D::Load(ID3D11Device* device, const wchar_t* filename)
{
	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(CreateWICTextureFromFile(
		device,
		filename,
		resource.GetAddressOf(),
		&m_texture));

	ComPtr<ID3D11Texture2D> texture;
	DX::ThrowIfFailed(resource.As(&texture));

	CD3D11_TEXTURE2D_DESC desc;
	texture->GetDesc(&desc);

	m_centre = Vector2(desc.Width * 0.5f, desc.Height * 0.5f);
	m_dimensions = Vector2((float)desc.Width, (float)desc.Height);

	resource.Reset();
	texture.Reset();
}
