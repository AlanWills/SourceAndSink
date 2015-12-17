#pragma once

#include "GameObject.h"

class Tile : public GameObject
{
public:
	Tile(const Vector2& localPosition, const char* dataAsset, LoadType loadType = LoadType::kTexture, BaseObject* baseObject = nullptr);
	~Tile();

  void SetOccupied(const bool occupied) { m_occupied = occupied; }
  const bool IsOccupied() const { return m_occupied; }

private:
  /// \brief Quite often with tiles you want to store something on them or indicate whether they can be moved through
  /// You can use this flag to provide that logic
  bool m_occupied;
};