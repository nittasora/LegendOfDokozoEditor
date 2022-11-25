#pragma once

#include "CGameObject.h"

enum BACKGROUND_TYPE
{
	SCROLL_NONE,
	SCROLL_TOPDOWN,
	MAPCHIP,
	MAPCHIPMT,
	SCOREBOARD,
	CURSOR
};

namespace CObjGene
{
	// èâä˙âªä÷åW
	void CreateInvisibleObject(CGameObject*, float, float, float, float);
	void CreateBackGround(CGameObject*, int, int);
	void CreatePlayer(CGameObject*, float, float);
	void CreateNull(CGameObject*);
	void SetEnemyParameter(CGameObject*, int, float, float);
	void SetItemParameter(CGameObject*, int, float, float);

}

class CMapData
{
public:
	void Init(int);
	void Set(CGameObject*);

private:
	int mapChipID[MAP_SIZE_X][MAP_SIZE_Y];
	int mapChipHitID[MAP_SIZE_X][MAP_SIZE_Y];
};
