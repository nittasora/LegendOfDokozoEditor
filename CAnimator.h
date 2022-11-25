#pragma once

#include "Information.h"
#include "GameTimer.h"

enum ANIMTYPE
{
	ANIM_NONE
};

struct CGameObject;

// �A�j���[�V�����̃X�[�p�[�N���X
class CAnim
{
public:
	virtual void Update();

private:

};

class Anim_None : public CAnim
{
public:
	void Update();

};

class CAnimator
{
public:
	bool Init(int);
	void UnInit();

	int frameX;
	int frameY;
	bool isActive;
	bool isInit = false;
	CAnim *anim;
	CGameObject *pOwner;

protected:
	float time;
	float speed;
};

