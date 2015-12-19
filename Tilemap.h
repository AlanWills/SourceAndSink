#pragma once

#include "BaseObjectManager.h"

#include "Tile.h"
#include "TilemapData.h"

class Tilemap
{
public:
	Tilemap(Microsoft::WRL::ComPtr<ID3D11Device> device, const char* tilemapDataAsset);
	~Tilemap();

	void LoadContent();
	void Initialize();
	void Update(DX::StepTimer const& timer);
	void Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont);
	void HandleInput(DX::StepTimer const& timer, const Vector2& mousePosition);

  /// \brief Work out whether we have clicked on the tilemap using an inputted mouseposition
  const bool IsClicked(const Vector2& mousePosition) const;
  Tile* GetClickedTile(const Vector2& mousePosition) const;
  const Tile* ConstGetClickedTile(const Vector2& mousePosition) const;

private:
	/// \brief Typedefs
	typedef std::unique_ptr<BaseObjectManager<Tile>> Tiles;
  typedef std::vector<std::vector<Tile*>> TilemapInfo;

	// Container for the tiles in the tilemap
	Tiles		m_tiles;

	// Will be used to obtain the information to create the Tiles
  std::unique_ptr<TilemapData>	m_tilemapData;

  /// \brief A data structure designed to be able to find neighbours of tiles and plot out the map in a data structure
  /// [row][column]
  TilemapInfo m_tilemap;
};