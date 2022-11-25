#include "CCollider.h"
#include "CGameObject.h"

bool CCollider::Init(int colliderType) {
	switch (colliderType)
	{
	case COLLIDER_NONE:
		this->isActive = false;
		this->offset = Float2zero;
		this->size = Float2zero;
		break;
	case COLLIDER_TRANSFORM:
		this->isActive = true;
		this->offset = Float2zero;
		this->size = this->pOwner->transform.size;
		break;
	case COLLIDER_PLAYER:
		this->isActive = true;
		this->offset = { 0.0f, -30.0f };
		this->size = { 60.0f, 96.0f };
		break;
	default:
		return false;
		break;
	}

	return true;
}

COLLIDER_RESULT Collider_Test(CCollider * pThis, CCollider * pOther)
{
	COLLIDER_RESULT res = { false };

	if (pThis->isActive == false || pOther->isActive == false) {
		return res;
	}

	// Colliderの親GameObjectの座標を足して中心点を計算
	float this_centerX = pThis->pOwner->transform.position.x + pThis->offset.x;
	float this_centerY = pThis->pOwner->transform.position.y + pThis->offset.y;
	float other_centerX = pOther->pOwner->transform.position.x + pOther->offset.x;
	float other_centerY = pOther->pOwner->transform.position.y + pOther->offset.y;

	// 中心点同士の距離を計算（絶対値）
	float distX = fabsf(other_centerX - this_centerX);
	float distY = fabsf(other_centerY - this_centerY);
	// ２つの四角形の縦横の長さを足して÷２した値を計算
	float halfTotalLenX = (pThis->size.x + pOther->size.x) / 2.0f;
	float halfTotalLenY = (pThis->size.y + pOther->size.y) / 2.0f;

	// 下の２つの条件が両方trueなら衝突している
	res.isHit = distX < halfTotalLenX && distY < halfTotalLenY;

	// 押し戻しの距離を計算する
#if 0
	// 元。なぜか下から上だけバグが出る。
	float dx1 = (other_centerX - pOther->size.x / 2) - (this_centerX + pThis->size.x / 2.0f);
	float dx2 = (other_centerX + pOther->size.x / 2) - (this_centerX - pThis->size.x / 2.0f);
	float dy1 = (this_centerY + pThis->size.y / 2) - (other_centerY - pOther->size.y / 2.0f);
	float dy2 = (other_centerY + pOther->size.y / 2) - (this_centerY - pThis->size.y / 2.0f);
#else
	// dy1のみ改変。なぜか下から上でもバグが出ない。
	float dx1 = (other_centerX - pOther->size.x / 2) - (this_centerX + pThis->size.x / 2.0f);
	float dx2 = (other_centerX + pOther->size.x / 2) - (this_centerX - pThis->size.x / 2.0f);
	float dy1 = (other_centerY - pOther->size.y / 2.0f) - (this_centerY + pThis->size.y / 2);
	float dy2 = (other_centerY + pOther->size.y / 2) - (this_centerY - pThis->size.y / 2.0f);
#endif

	float dx = fabsf(dx1) < fabsf(dx2) ? dx1 : dx2;
	float dy = fabsf(dy1) < fabsf(dy2) ? dy1 : dy2;

	if (fabsf(dx) < fabsf(dy)) {
		res.d.x = dx;
		res.d.y = 0.0f;
	}
	else {
		res.d.x = 0.0f;
		res.d.y = dy;
	}

	return res;
}

