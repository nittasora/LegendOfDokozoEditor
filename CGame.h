#pragma once

#include "Information.h"
#include "input.h"
#include "GameTimer.h"
#include "CGameObject.h"
#include "CObjectGenerator.h"
#include "CDraw.h"

class CMode_Base
{
public:
	virtual bool Init();
	virtual int Update();
	virtual void UnInit();

	void SethWnd(const HWND*);

protected:
	HWND hWnd;
	int drawCount;

};

class CTitle : public CMode_Base
{
public:
	bool Init();
	int Update();
	void UnInit();

private:

};

class CPlay : public CMode_Base
{
public:
	bool Init();
	int Update();
	void UnInit();

private:
	// マップ関係
	CGameObject *mapChip[MAP_SIZE_X][MAP_SIZE_Y];
	CDraw *mapChip_Draw;

	CGameObject *mapChipHit[MAP_SIZE_X][MAP_SIZE_Y];
	CDraw *mapChipHit_Draw;

	Float2 *anchor[MAP_SIZE_X / MAP_ONE_SIZE_X][MAP_SIZE_Y / MAP_ONE_SIZE_Y];
	CGameObject *anchorObject;
	CDraw *anchor_Draw;

	// 敵関係
	CGameObject *enemy[MAP_SIZE_X / MAP_ONE_SIZE_X][MAP_SIZE_Y / MAP_ONE_SIZE_Y][ENEMY_MAX];
	CDraw *enemy_Draw;

	// アイテム関係
	CGameObject *item[MAP_SIZE_X / MAP_ONE_SIZE_X][MAP_SIZE_Y / MAP_ONE_SIZE_Y][ENEMY_MAX];
	CDraw *item_Draw;

	// カーソル関係
	CGameObject *cursor;
	CDraw *cursor_Draw;

	// マップチップ関係
	CGameObject *mapChipMT[MAPCHIP_NUM][MAPCHIP_NUM];
	CDraw *mapChipMT_Draw;

	// 敵素材関係
	CGameObject *enemyMT[ENEMYMTMAX];
	CDraw *enemyMT_Draw;

	// アイテム素材関係
	CGameObject *itemMT[ITEMMTMAX];
	CDraw *itemMT_Draw;

	int mode;
	int setMode;
	float animX;
	float animY;
	int enemyTag;
	int itemTag;

	int mapPointX;
	int mapPointY;
};

class CResult : public CMode_Base
{
public:
	bool Init();
	int Update();
	void UnInit();

private:

};

class CGame
{
public:
	CGame(const HWND*);
	~CGame();

	bool Update();

	CMode_Base *pGameMode[GAME_MODE_NUM];

private:
	bool isInit;
	int gameMode;
	int gameOrder;
};

