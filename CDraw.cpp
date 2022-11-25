#include "CDraw.h"

// static�ϐ�������
bool CDraw::isClear = false;
Float2 CDraw::camera = Float2zero;

CDraw::CDraw(const char *textureName, int maxSprite) {
	// �Ƃ肠�������������s�ɂ��Ă���
	this->successInit = false;
	// �Ƃ肠�����`��Ȃ�
	this->drawCount = 0;

#pragma region // ���_�o�b�t�@�쐬 & �e�N�X�`���ǂݍ��� (�ق�DX21�܂�)

	HRESULT hr;

	this->maxSprite = maxSprite;

	if (this->maxSprite <= 0) {
		return;
	}
	else if (this->maxSprite > MAX_SPRITE) {
		this->maxSprite = MAX_SPRITE;
	}

	// ���_�o�b�t�@�쐬
	D3D11_BUFFER_DESC bufferDesc;
	// �����͕ύX
	// MAX_SPRITE����this->maxSprite�ɂȂ��Ă���
	// ���̃N���X�Ŏg�����������w�肷��悤�ɂ��Ă���
	bufferDesc.ByteWidth = this->maxSprite * sizeof(VERTEX_POSTEX) * VERTEX_PER_SPRITE;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	hr = Direct3D_GetDevice()->CreateBuffer(&bufferDesc, NULL, &this->pVertexBuffer);

	if (FAILED(hr)) {
		return;
	}
	// ���@���_�o�b�t�@�쐬�@�����܂�

	// �����Ŏg�p�������摜�t�@�C�����e�N�X�`���Ƃ��ēǂݍ���
	// �������F�摜�t�@�C�����B�����t�H���_�ɓ����Ă���Ȃ�t�H���_�����ꏏ�ɏ����B
	// �������F�ǂݍ��񂾃e�N�X�`��������ϐ����w��
	hr = Direct3D_LoadTexture(textureName, &this->pTexture);

	if (FAILED(hr)) {
		return;
	}

#pragma endregion

	// ����������
	this->successInit = true;
}

CDraw::~CDraw() {
	COM_SAFE_RELEASE(pTexture);  // �e�N�X�`����ǂݍ��񂾂�A�Y�ꂸ�����[�X���邱��
	COM_SAFE_RELEASE(pVertexBuffer); // ���_�o�b�t�@���쐬������A�Y�ꂸ�Ƀ����[�X���邱��
}

void CDraw::Update() {
	// ��ʃN���A���ł���悤��
	CDraw::isClear = false;
}

void CDraw::SetVertex(CGameObject *drawTarget) {

	// �������s�\���Ȃ炷��K�v���Ȃ�
	// �J�E���g���ő�l�ɒB���Ă���Ȃ炻��ȏ�i�[�ł��Ȃ�
	if (this->successInit && this->drawCount < this->maxSprite) {
		// �e���_�̍��W��UV���W�v�Z
		FRECT verPos = drawTarget->GameObject_GetXY();
		FRECT verUV = drawTarget->GameObject_GetUV();

		verPos.left -= this->camera.x / SCREEN_WIDTH;
		verPos.right -= this->camera.x / SCREEN_WIDTH;
		verPos.top -= this->camera.y / SCREEN_HEIGHT;
		verPos.bottom -= this->camera.y / SCREEN_HEIGHT;

		// �z��Ɋi�[
		this->vx[this->drawCount * VERTEX_PER_SPRITE + 0] = { verPos.left, verPos.top, 0.0f, verUV.left, verUV.top };
		this->vx[this->drawCount * VERTEX_PER_SPRITE + 1] = { verPos.right, verPos.top, 0.0f, verUV.right, verUV.top };
		this->vx[this->drawCount * VERTEX_PER_SPRITE + 2] = { verPos.right, verPos.bottom, 0.0f, verUV.right, verUV.bottom };
		this->vx[this->drawCount * VERTEX_PER_SPRITE + 3] = { verPos.right, verPos.bottom, 0.0f, verUV.right, verUV.bottom };
		this->vx[this->drawCount * VERTEX_PER_SPRITE + 4] = { verPos.left, verPos.bottom, 0.0f, verUV.left, verUV.bottom };
		this->vx[this->drawCount * VERTEX_PER_SPRITE + 5] = { verPos.left, verPos.top, 0.0f, verUV.left, verUV.top };

		// �`�搔�J�E���g�𑝂₷
		this->drawCount++;
	}
}

void CDraw::DrawAct() {

	// �������s�\���Ȃ�ʂ��Ă͂Ȃ�Ȃ��I
	// ��΂ɁI
	if (this->successInit) {
		// ���_�o�b�t�@�̃f�[�^��vx�z��̃f�[�^�ōX�V����
		Direct3D_GetContext()->UpdateSubresource(
			this->pVertexBuffer,		// �X�V�Ώۂ̃o�b�t�@
			0,				// �C���f�b�N�X(0)
			NULL,				// �X�V�͈�(nullptr)
			vx,		// ���f�f�[�^
			0,				// �f�[�^��1�s�̃T�C�Y(0)
			0);				// 1�[�x�X���C�X�̃T�C�Y(0)

		// ���@���O�̕`�揈���������ɏ��� *******

		// �N���A�ς݃t���O�������Ă��Ȃ��Ȃ��ʃN���A����
		if (!this->isClear) {
			// ��ʃN���A�i�w��F�œh��Ԃ��j
			// �h��Ԃ��F�̎w��i�����F0.0f�`1.0f�j
			float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha

			Direct3D_GetContext()->ClearRenderTargetView(Direct3D_GetRenderTargetView(), clearColor);

			// �N���A�ς݃t���O�𗧂Ă�
			this->isClear = true;
		}

		// �`��Ŏg�p����e�N�X�`�����w�肷��֐��Ăяo��
		// �����Ŏw�肳�ꂽ�e�N�X�`�����A�s�N�Z���V�F�[�_�[�̃O���[�o���ϐ��ɃZ�b�g�����
		Direct3D_GetContext()->PSSetShaderResources(0, 1, &this->pTexture);

		// �`��Ɏg�����_�o�b�t�@���w�肷��
		UINT strides = sizeof(VERTEX_POSTEX);
		UINT offsets = 0;
		Direct3D_GetContext()->IASetVertexBuffers(0, 1, &this->pVertexBuffer, &strides, &offsets);   // gpVertexBuffer�����_�o�b�t�@

		// ����܂ł̐ݒ�Ŏ��ۂɕ`�悷��
		// �`�搔��this->drawCount
		// ����ɂ��`�掞�̃o�O���y������
		Direct3D_GetContext()->Draw(this->drawCount *VERTEX_PER_SPRITE, 0);

		// �`����I�������̂ŕ`�搔��0�ɂ���
		this->drawCount = 0;

		// ���@���O�̕`�揈���������ɏ��� *******
	}
}

