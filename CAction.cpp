#include "CAction.h"
#include "CGameObject.h"

bool CAction::Init(int actionType) {

	if (this->isInit) {
		this->UnInit();
	}

	switch (actionType)
	{
	case ACTION_NONE:
		this->isActive = false;
		this->action = new CACTION_NONE;
		break;
	default:
		return false;
		break;
	}

	this->isInit = true;

	return true;
}

void CAction::UnInit() {
	delete this->action;
	this->isInit = false;
}

void CAction_Base::Update() {

}

void CAction_Base::StartAction(int actionIndex) {
	switch (actionIndex)
	{
	case ACTION_INDEX_1:
		this->frame[0] = 0;
		break;
	case ACTION_INDEX_2:
		this->frame[1] = 0;
		break;
	default:
		return;
		break;
	}

	this->actionID |= actionIndex;

}

void CACTION_NONE::Update() {

}
