#include "pch.h"
#include "Tilemap.h"


//-----------------------------------------------------------------------------------------------------------------------------------
Tilemap::Tilemap(Microsoft::WRL::ComPtr<ID3D11Device> device, const char* tilemapDataAsset) :
	m_tiles(new BaseObjectManager<Tile>(device)),
	m_tilemapData(new TilemapData(tilemapDataAsset))
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Tilemap::~Tilemap()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Tilemap::LoadContent()
{
	// Load the tile data here and create the tiles
	m_tilemapData->LoadData();
	std::list<Tile*> tiles;
	m_tilemapData->GetTiles(tiles);

	// Push back the tiles to the BaseObjectManager using the elements in 'tiles'
	for (Tile* tile : tiles)
	{
		m_tiles->AddObject(tile);
	}

	m_tiles->LoadContent();

	// Free the memory
	m_tilemapData.release();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Tilemap::Initialize()
{
	m_tiles->Initialize();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Tilemap::Update(DX::StepTimer const& timer)
{
	m_tiles->Update(timer);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Tilemap::Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont)
{
	m_tiles->Draw(spriteBatch, spriteFont);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Tilemap::HandleInput(DX::StepTimer const& timer, const Vector2& mousePosition)
{
	m_tiles->HandleInput(timer, mousePosition);
}


//-----------------------------------------------------------------------------------------------------------------------------------
const bool Tilemap::IsClicked(const Vector2& mousePosition) const
{
  for (auto& tile : m_tiles->GetObjects())
  {
    if (tile->GetCollider()->CheckCollisionWith(mousePosition))
    {
      return true;
    }
  }

  return false;
}


//-----------------------------------------------------------------------------------------------------------------------------------
Tile* Tilemap::GetClickedTile(const Vector2& mousePosition) const
{
  assert(IsClicked(mousePosition));

  for (auto& tile : m_tiles->GetObjects())
  {
    if (tile->GetCollider()->CheckCollisionWith(mousePosition))
    {
      return tile.get();
    }
  }

  return nullptr;
}


//-----------------------------------------------------------------------------------------------------------------------------------
const Tile* Tilemap::ConstGetClickedTile(const Vector2& mousePosition) const
{
  assert(IsClicked(mousePosition));

  for (auto& tile : m_tiles->GetObjects())
  {
    if (tile->GetCollider()->CheckCollisionWith(mousePosition))
    {
      return tile.get();
    }
  }

  return nullptr;
}