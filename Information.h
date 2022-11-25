#pragma once

#include <Windows.h>
#include "MYMath.h"
#include "direct3d.h"

#define PI 3.141592f       // 円周率

#define	SCREEN_WIDTH	(960)					// ウインドウの幅
#define	SCREEN_HEIGHT	(640)					// ウインドウの高さ

#define MAX_SPRITE  256
// ポリゴン２つで１つの四角形（スプライト）。ポリゴンは３頂点なので、１スプライトは６頂点。
#define VERTEX_PER_SPRITE  (3*2)
#define VERTEX_BUFFER_SIZE  (MAX_SPRITE*sizeof(VERTEX_POSTEX)*VERTEX_PER_SPRITE)

// ゲームモードの数
#define GAME_MODE_NUM 3

#define MAP_NUM 4

enum GAME_MODE
{
	GAME_MODE_TITLE,
	GAME_MODE_PLAY,
	GAME_MODE_RESULT
};

#define GAME_ORDER_NONE					0x00
#define GAME_ORDER_CONTINUE				0x01
#define GAME_ORDER_MODECHANGE_TITLE		0x02
#define GAME_ORDER_MODECHANGE_PLAY		0x04
#define GAME_ORDER_MODECHANGE_RESULT	0x08

#define MAP_SIZE 256
#define MAP_ONE_SIZE_X (15)
#define MAP_ONE_SIZE_Y (10)
#define MAP_SIZE_X (MAP_ONE_SIZE_X * 16)
#define MAP_SIZE_Y (MAP_ONE_SIZE_Y * 8)
#define MAP_CHIP_SIZE 128.0f
#define MAPCHIP_PIC_ALL_SIZE 1024.0f
#define MAPCHIP_PIC_ONE_SIZE 32.0f
#define MAPCHIP_UV_SIZE (MAPCHIP_PIC_ONE_SIZE / MAPCHIP_PIC_ALL_SIZE)
#define MAPCHIP_NUM ((int)MAPCHIP_PIC_ALL_SIZE / (int)MAPCHIP_PIC_ONE_SIZE)

#define ENEMY_STEP_MAX PLAYER_STEP_MAX

#define ENEMY_ANIM_STAND_SPEED 10
#define ENEMY_ANIM_WALK_SPEED 20
#define ENEMY_ANIM_RAN_SPEED 40

#define ENEMY_MAX 10
#define ENEMY_PIC_ALL_SIZE_X 1104.0f
#define ENEMY_PIC_ALL_SIZE_Y 720.0f
#define ENEMY_PIC_TYPE_1_SIZE_X 120.0f
#define ENEMY_PIC_TYPE_1_SIZE_Y 72.0f
#define ENEMY_PIC_TYPE_2_SIZE_X 120.0f
#define ENEMY_PIC_TYPE_2_SIZE_Y 112.0f
#define ENEMY_PIC_TYPE_3_SIZE_X 144.0f
#define ENEMY_PIC_TYPE_3_SIZE_Y 120.0f
#define ENEMY_PIC_TYPE_4_SIZE_X 132.0f
#define ENEMY_PIC_TYPE_4_SIZE_Y 104.0f
#define ENEMY_PIC_TYPE_5_SIZE_X 228.0f
#define ENEMY_PIC_TYPE_5_SIZE_Y 120.0f

#define ITEM_MAX 10
// 規格が違うので注意
#define ITEM_PIC_TYPE_1_SIZE_X 20.0f
#define ITEM_PIC_TYPE_1_SIZE_Y 28.0f
#define ITEM_PIC_TYPE_2_SIZE_X 32.0f
#define ITEM_PIC_TYPE_2_SIZE_Y 32.0f
#define ITEM_PIC_TYPE_3_SIZE_X 16.0f
#define ITEM_PIC_TYPE_3_SIZE_Y 18.0f
#define ITEM_PIC_TYPE_4_SIZE_X 48.0f
#define ITEM_PIC_TYPE_4_SIZE_Y 50.0f

// 頂点１つあたりを表す構造体
struct VERTEX_POSTEX {
	float x, y, z;  // 頂点の位置

	float u, v;  // テクスチャのUV座標
};


