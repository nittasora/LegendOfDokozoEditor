#include "CAnimator.h"
#include "CGameObject.h"

bool CAnimator::Init(int animType) {

	if (this->isInit) {
		this->UnInit();
	}

	this->frameX = 0;
	this->frameY = 0;
	this->time = 0;

	switch (animType)
	{
	case ANIM_NONE:
		this->anim = new Anim_None;
		this->speed = 0;
		this->isActive = false;
		break;
	default:
		return false;
		break;
	}

	this->isInit = true;

	return true;
}

void CAnimator::UnInit() {
	delete this->anim;
	this->isInit = false;
}

void CAnim::Update() {

}

void Anim_None::Update() {
	// “Á‚É‚È‚µ
}