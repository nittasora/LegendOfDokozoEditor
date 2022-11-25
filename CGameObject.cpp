#include "CGameObject.h"

void CGameObject::Init(FDATA_GAMEOBJECT initData) {
	this->transform = initData.transform;
	this->uv = initData.uv;
	this->animator.pOwner = this;
	this->controller.pOwner = this;
	this->collider.pOwner = this;
	this->action.pOwner = this;
	if (!this->animator.Init(initData.animType)) {
		this->animator.isActive = false;
	}
	if (!this->controller.Init(initData.moveType)) {
		this->controller.isActive = false;
	}
	if (!this->collider.Init(initData.colliderType)) {
		this->collider.isActive = false;
	}
	if (!this->action.Init(initData.actionType)) {
		this->action.isActive = false;
	}
	this->localPosition = initData.localPosition;
	this->pOwner = initData.pOwner;
	this->tag = initData.tag;
}

FRECT CGameObject::GameObject_GetXY() {
	float leftX = this->transform.position.x - this->transform.size.x / 2;
	float topY = this->transform.position.y + this->transform.size.y / 2;
	float rightX = leftX + this->transform.size.x;
	float bottomY = topY - this->transform.size.y;

	FRECT rect = { leftX / (SCREEN_WIDTH), rightX / (SCREEN_WIDTH), topY / (SCREEN_HEIGHT), bottomY / (SCREEN_HEIGHT) };

	return rect;
}

FRECT CGameObject::GameObject_GetUV() {
	float leftU = this->uv.offset.x + (float)this->animator.frameX * this->uv.size.x;
	float rightU = leftU + this->uv.size.x;
	float topV = this->uv.offset.y + this->animator.frameY * this->uv.size.y;
	float bottomV = this->uv.offset.y + (this->animator.frameY + 1) * this->uv.size.y;

	FRECT rect;

	switch (this->uv.flip) {
	case FLIP_NONE: // ”½“]‚È‚µ
		rect = { leftU, rightU, topV, bottomV };
		break;
	case FLIP_VERTICAL: // ‚’¼”½“]
		rect = { leftU, rightU, bottomV, topV };
		break;
	case FLIP_HORIZONTAL: // …•½”½“]
		rect = { rightU, leftU, topV, bottomV };
		break;
	}

	return rect;
}

void CGameObject::SetUV(FUVINFO *info) {
	this->uv = *info;
}
