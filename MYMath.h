#pragma once

#include <math.h>

struct Float2
{
	float x, y;
};

struct Float3
{
	float x, y, z;
};

struct Float4
{
	float x, y, z, w;
};

struct HitResult
{
	bool isHit;
	Float2 position;
};

//�\���̂ɕς���
Float2 MakeFloat2(float, float);
Float3 MakeFloat3(float, float, float);
Float3 MakeFloat3(Float2*, float);
Float4 MakeFloat4(float, float, float, float);
Float4 MakeFloat4(Float3*, float);
Float4 MakeFloat4(Float2*, Float2*);
Float2 operator+(Float2, Float2);
Float3 operator+(Float3, Float3);
Float2 operator-(Float2, Float2);
Float3 operator-(Float3, Float3);
Float2 operator*(Float2, Float2);
Float2 operator*(Float2, float);
Float3 operator*(Float3, Float3);
Float2 operator/(Float2, Float2);
Float2 operator/(Float2, float);
Float3 operator/(Float3, Float3);

//�~����
const float MYMATH_PI = acosf(-1);
//�������p
const Float2 Float2zero = { 0.0f, 0.0f };
const Float3 Float3zero = { 0.0f, 0.0f, 0.0f };
const Float4 Float4zero = { 0.0f, 0.0f, 0.0f, 0.0f };

#define MYMATH_DISTANCE_1(x, y) sqrtf(x * x + y * y)
#define MYMATH_DISTANCE_2(x1, y1, x2, y2) sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))
#define MYMATH_RADIAN(x1, y1, x2, y2) atan2f(y2 - y1, x2 - x1)
#define MYMATH_DEGREE(x1, y1, x2, y2) (atan2f(y2 - y1, x2 - x1) * (180.0f / MYMATH_PI))
#define MYMATH_CROSSVECTOR(x1, y1, x2, y2) ((x1 * y2) - (y1 * x2))

namespace MYMath {
	//�@�\	:2�_�Ԃ̋������o��
	//����1	:1�߂̍��W
	//����2	:2�߂̍��W
	//�߂�l:2�_�Ԃ̋���
	float CalcuDistance2D(const Float2*, const Float2*);
	float CalcuDistance2D(const Float3*, const Float3*);
	float CalcuDistance2D(const Float4*, const Float4*);
	//�@�\	:���W�A�����o��
	//����1	:1�߂̍��W
	//����2	:2�߂̍��W
	//�߂�l:���W�A��
	float CalcuRadian2D(const Float2*, const Float2*);
	float CalcuRadian2D(const Float3*, const Float3*);
	float CalcuRadian2D(const Float4*, const Float4*);
	//�@�\	:�x�����o��
	//����1	:1�߂̍��W
	//����2	:2�߂̍��W
	//�߂�l:�x��
	float CalcuDegree2D(const Float2*, const Float2*);
	float CalcuDegree2D(const Float3*, const Float3*);
	float CalcuDegree2D(const Float4*, const Float4*);
	//�@�\	:�p�x(���W�A��)�Ƌ���������W���o��
	//����1	:���a
	//����2	:�p�x
	//�߂�l:2�߂̍��W
	Float2 CalcuPosByRadian2D(const float, const float);
	Float3 CalcuPosByRadian2D(const float, const float, const float);
	Float4 CalcuPosByRadian2D(const float, const float, const Float2);
	//�@�\	:�p�x(�x��)�Ƌ���������W���o��
	//����1	:���a
	//����2	:�p�x
	//�߂�l:2�߂̍��W
	Float2 CalcuPosByDegree2D(const float, const float);
	Float3 CalcuPosByDegree2D(const float, const float, const float);
	Float4 CalcuPosByDegree2D(const float, const float, const Float2);
	//�@�\	:����̊p�x���������ŉ�]
	//����1	:1�߂̍��W
	//����2	:2�߂̍��W
	//����2	:�p�x
	//�߂�l:2�߂̍��W
	Float2 CalcuPosToAlpha2D(const Float2*, const Float2*, float);
	Float3 CalcuPosToAlpha2D(const Float3*, const Float3*, float);
	Float4 CalcuPosToAlpha2D(const Float4*, const Float4*, float);
	//�@�\	:�P�ʃx�N�g��(���x�ɒ�)
	//����1	:1�߂̍��W
	//����2	:2�߂̍��W
	//�߂�l:�P�ʃx�N�g��
	Float2 UnitVector2D(const Float2*, const Float2*);
	//�@�\	:�O��
	//����1	:1�߂̃x�N�g��
	//����2	:2�߂̃x�N�g��
	//�߂�l:�O��
	float CrossVector2D(const Float2*, const Float2*);
	//�@�\	:�l�p�`������(�Ȉ�)
	//����1	:1�߂̍�����W
	//����2	:1�߂̉E�����W
	//����3	:2�߂̍�����W
	//����4	:2�߂̉E�����W
	//�߂�l:����������
	bool HitBoxToBox2D(const Float3*, const Float3*, const Float3*, const Float3*);
	//�@�\	:�����Ɛ�������
	//����1	:1�߂̍��W
	//����2	:1�߂̕���
	//����3	:2�߂̍��W
	//����4	:2�߂̕���
	//����5	:��_
	//�߂�l:����������
	bool CrossLineToLine2D(const Float2*, const Float2*, const Float2*, const Float2*, Float2*);
}
