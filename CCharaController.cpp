#include "CCharaController.h"
#include "CGameObject.h"

bool CCharaController::Init(int moveType) {

	if (this->isInit) {
		this->UnInit();
	}

	switch (moveType)
	{
	case MOVE_NONE:
		this->pMove = new CharaMove_None;
		this->isActive = false;
		this->moveSpeed = Float2zero;
		this->maxMoveSpeed = 0.0f;
		this->accelForce = 0.0f;
		this->stopForce = 0.0f;
		break;
	case MOVE_BG_SCROLL_TOPDOWN:
		this->pMove = new CharaMove_BackGround_TopDown;
		this->isActive = false;
		this->moveSpeed = { 0.0f, 0.0f };
		this->maxMoveSpeed = 0.0f;
		this->accelForce = 10.0f;
		this->stopForce = 0.0f;
		break;
	case MOVE_PLAYER:
		this->pMove = new CharaMove_Player;
		this->isActive = false;
		this->moveSpeed = { 0.0f, 0.0f };
		this->maxMoveSpeed = 10.0f;
		this->accelForce = 3.0f;
		this->stopForce = 1.0f;
		break;
	default:
		return false;
		break;
	}

	this->pMove->controller = this;

	this->isInit = true;

	return true;
}

void CCharaController::UnInit() {
	delete this->pMove;
	this->isInit = false;
}

void CCharaMove::Update() {

}

void CCharaMove::AddForce() {
	this->controller->pOwner->transform.position = this->controller->pOwner->transform.position + this->controller->moveSpeed;

	if (this->controller->moveSpeed.x > 0) {
		this->controller->moveSpeed.x -= this->controller->stopForce;
		if (this->controller->moveSpeed.x < 0) {
			this->controller->moveSpeed.x = 0;
		}
	}
	else if (this->controller->moveSpeed.x < 0) {
		this->controller->moveSpeed.x += this->controller->stopForce;
		if (this->controller->moveSpeed.x > 0) {
			this->controller->moveSpeed.x = 0;
		}
	}

	if (this->controller->moveSpeed.y > 0) {
		this->controller->moveSpeed.y -= this->controller->stopForce;
		if (this->controller->moveSpeed.y < 0) {
			this->controller->moveSpeed.y = 0;
		}
	}
	else if (this->controller->moveSpeed.y < 0) {
		this->controller->moveSpeed.y += this->controller->stopForce;
		if (this->controller->moveSpeed.y > 0) {
			this->controller->moveSpeed.y = 0;
		}
	}
}

void CCharaMove::AddForce(const Float2 *addForce) {
	this->controller->pOwner->transform.position = this->controller->pOwner->transform.position + *addForce;
}

void CharaMove_None::Update() {
	//“Á‚É‚È‚µ
}

void CharaMove_BackGround_TopDown::Update() {
	this->controller->pOwner->transform.position.y -= this->controller->accelForce;

	if (this->controller->pOwner->transform.position.y <= -this->controller->pOwner->transform.size.y) {
		this->controller->pOwner->transform.position.y += this->controller->pOwner->transform.size.y * 2;
	}
}

void CharaMove_Player::Update() {
	Float2 speed = Float2zero;
	CCharaController *con = this->controller;

	if (Input_GetKeyPress(VK_LEFT)) {
		speed.x = -this->controller->accelForce;
	}
	else if (Input_GetKeyPress(VK_RIGHT)) {
		speed.x = this->controller->accelForce;
	}
	if (Input_GetKeyPress(VK_DOWN)) {
		speed.y = -this->controller->accelForce;
	}
	else if (Input_GetKeyPress(VK_UP)) {
		speed.y = this->controller->accelForce;
	}

	if (speed.x != 0.0f, speed.y != 0.0f) {
		speed = speed * 0.75f;
	}

	con->moveSpeed = con->moveSpeed + speed;

	if (Input_GetKeyPress(VK_SHIFT)) {
		con->moveSpeed = con->moveSpeed / 2;
	}

	if (con->moveSpeed.x < -con->maxMoveSpeed) {
		con->moveSpeed.x = -con->maxMoveSpeed;
	}
	else if (con->moveSpeed.x > con->maxMoveSpeed) {
		con->moveSpeed.x = con->maxMoveSpeed;
	}

	if (con->moveSpeed.y < -con->maxMoveSpeed) {
		con->moveSpeed.y = -con->maxMoveSpeed;
	}
	else if (con->moveSpeed.y > con->maxMoveSpeed) {
		con->moveSpeed.y = con->maxMoveSpeed;
	}


}

