#pragma once

// �ėp���〈�Ă���̗ǂ������搶�T���v���Ɋ�{���B
// �Q�l�ɂ����N������̓V���v���ɂ��̂��Ƃɂ��Ċo���Ă����Ă��炢�����B

#include "Information.h"	// �e��萔�ƍ\���̗p(DX21�T���v�����ړ�)
#include "CGameObject.h"	// �`�悷��I�u�W�F�N�g�p(DX21�T���v����"GameObject.h"�����ρE�ǋL�A�������݊����Ȃ�)

// �`��p�N���X�B
// �ǂݍ��ރe�N�X�`���̕��������Ă��������B
class CDraw
{
public:
	// �@�\:������
	// ����1:�ǂݍ��ރe�N�X�`���̃p�X(��) "assets/TitleBack.png")
	// ����2:�X�v���C�g�̍ő吔(������MAX_SPRITE�ȉ�)
	// ��) CDraw *pBG_Draw = new CDraw("assets/TitleBack.png", 2);
	CDraw(const char*, int);
	// �@�\:�������
	// new���g���Ă���̂ŉ�����Ă����Ȃ���΂����Ȃ�
	~CDraw();
	// �@�\:isClear��false�ɂ���
	// �K���Q�[�����[�v���̕`�����ɌĂяo���Ȃ��Ƃ����Ȃ�
	static void Update();
	// �@�\:�I�u�W�F�N�g�̒��_���i�[
	// ����:�Q�[���I�u�W�F�N�g(DX21�T���v���ł�GameObject�̂���)
	void SetVertex(CGameObject*);
	// �@�\:���ۂɕ`��
	void DrawAct();

	// �^���J����
	static Float2 camera;

private:
	// ���_�o�b�t�@�p�̕ϐ�
	ID3D11Buffer* pVertexBuffer;
	// �e�N�X�`���p�ϐ�
	ID3D11ShaderResourceView* pTexture;
	// (�����قڂ܂�)
	// �|���S���̒��_���`
	// ���_������Ń|���S�����`������Ƃ��̖@��
	// �E���_�́A�z��̔ԍ��̎Ⴂ���ԂɎg�p�����
	// �E���_������Ń|���S�����`�����ꂽ�Ƃ��A���̌��я������v���ɂȂ�ꍇ�����|���S�����\�������
	VERTEX_POSTEX vx[MAX_SPRITE * VERTEX_PER_SPRITE];
	// �ő�X�v���C�g��
	int maxSprite;
	// �`�悷�鐔
	int drawCount;
	// ����ɏ��������ꂽ��
	bool successInit;
	// ��x������ʃN���A���邽�߂̃t���O
	static bool isClear;
};

