#pragma once

#include "Information.h"

enum COLLIDERTYPE
{
	COLLIDER_NONE,
	COLLIDER_TRANSFORM,
	COLLIDER_PLAYER
};

struct COLLIDER_RESULT {

	bool isHit;
	Float2 d;

};

struct CGameObject;

class CCollider
{
public:
	bool Init(int);

	bool isActive;
	CGameObject *pOwner;
	Float2 offset;
	Float2 size;
};

// ２つのコライダーが衝突しているか判定結果を返す関数
COLLIDER_RESULT Collider_Test(CCollider* pThis, CCollider* pOther);
