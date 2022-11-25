#pragma once

#include "Information.h"
#include "input.h"

enum {
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP
};

enum MOVETYPE
{
	MOVE_NONE,
	MOVE_BG_SCROLL_TOPDOWN,
	MOVE_PLAYER
};

struct CGameObject;
class CCharaController;

class CCharaMove
{
public:
	virtual void Update();
	void AddForce();
	void AddForce(const Float2*);

	CCharaController *controller;

private:

};

class CharaMove_None : public CCharaMove
{
public:
	void Update();
};

class CharaMove_BackGround_TopDown : public CCharaMove
{
public:
	void Update();
};

class CharaMove_Player : public CCharaMove
{
public:
	void Update();
};

class CCharaController
{
public:
	bool Init(int);
	void UnInit();

	bool isActive;
	bool isInit = false;
	CGameObject *pOwner;
	CCharaMove *pMove;
	Float2 moveSpeed;
	float maxMoveSpeed;
	float accelForce;
	float stopForce;
};

