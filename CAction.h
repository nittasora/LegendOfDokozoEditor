#pragma once

#include "Information.h"

#define ACTION_INDEX_NUM 2

#define ACTION_INDEX_NONE 0x00
#define ACTION_INDEX_1 0x01
#define ACTION_INDEX_2 0x02

enum ACTIONTYPE
{
	ACTION_NONE
};

struct CGameObject;

class CAction_Base
{
public:
	virtual void Update();
	void StartAction(int);

protected:
	int actionID;
	int frame[ACTION_INDEX_NUM];
};

class CACTION_NONE : public CAction_Base
{
public:
	void Update();
};

class CAction
{
public:
	bool Init(int);
	void UnInit();

	bool isActive;
	bool isInit = false;
	CGameObject *pOwner;
	CAction_Base *action;
};

