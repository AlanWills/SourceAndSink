#pragma once

#include "GameObject.h"

class Tile : public GameObject
{
public:
	Tile(const Vector2& localPosition, const char* dataAsset, LoadType loadType = LoadType::kTexture, BaseObject* baseObject = nullptr);
	~Tile();
};