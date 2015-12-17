#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;

class Texture2D
{
public:
	Texture2D();
	~Texture2D();

	void Load(ID3D11Device* device, const wchar_t* filename);

	ID3D11ShaderResourceView* GetTexture() { return m_texture; }

	const Vector2& GetCentre() const { return m_centre; }
	const Vector2& GetDimensions() const { return m_dimensions; }

private:
	ID3D11ShaderResourceView* m_texture;

	Vector2 m_centre;
	Vector2 m_dimensions;
};

