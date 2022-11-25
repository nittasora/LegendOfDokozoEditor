#include "CObjectGenerator.h"

void CObjGene::CreateInvisibleObject(CGameObject *obj, float posX, float posY, float sizeX, float sizeY) {
	FDATA_GAMEOBJECT data = {
		{
			{ posX, posY },
			{ sizeX, sizeY }
		},{
			{ 0.0f, 0.0f },
			{ 0.0f, 0.0f },
			FLIP_NONE
		},
		ANIM_NONE,
		MOVE_NONE,
		COLLIDER_TRANSFORM,
		ACTION_NONE,
		{ 0.0f, 0.0f },
		NULL,
		TAG_BACKGROUND
	};

	obj->Init(data);
}

void CObjGene::CreateBackGround(CGameObject *backGround, int scrollType, int index) {
	FDATA_GAMEOBJECT data = {
		{
			{ -(SCREEN_WIDTH / 3), 0.0f },
			{ SCREEN_WIDTH * (4.0f / 3.0f), SCREEN_HEIGHT * 2 }
		},{
			{ 0.0f, 0.0f },
			{ 1.0f, 1.0f },
			FLIP_NONE
		},
		ANIM_NONE,
		MOVE_NONE,
		COLLIDER_NONE,
		ACTION_NONE,
		{ 0.0f, 0.0f },
		NULL,
		TAG_BACKGROUND
	};

	switch (scrollType)
	{
	case SCROLL_TOPDOWN:
		data.transform.position.y += data.transform.size.y * index;
		data.moveType = MOVE_BG_SCROLL_TOPDOWN;
		break;
	case MAPCHIP:
		data.transform.position.x = (index % MAP_SIZE_X) * MAP_CHIP_SIZE + (MAP_CHIP_SIZE / 2);
		data.transform.position.y = (index / MAP_SIZE_X) * MAP_CHIP_SIZE + (MAP_CHIP_SIZE / 2);
		data.transform.size = { MAP_CHIP_SIZE, MAP_CHIP_SIZE };
		data.uv.size = { MAPCHIP_UV_SIZE, MAPCHIP_UV_SIZE };
		data.colliderType = COLLIDER_TRANSFORM;
		break;
	case MAPCHIPMT:
		data.transform.position.x = (index % MAPCHIP_NUM) * MAP_CHIP_SIZE + (MAP_CHIP_SIZE / 2);
		data.transform.position.y = (index / MAPCHIP_NUM) * MAP_CHIP_SIZE + (MAP_CHIP_SIZE / 2);
		data.transform.size = { MAP_CHIP_SIZE, MAP_CHIP_SIZE };
		data.uv.size = { MAPCHIP_UV_SIZE, MAPCHIP_UV_SIZE };
		data.colliderType = COLLIDER_TRANSFORM;
		break;
	case SCOREBOARD:
		data.transform.position.x = (SCREEN_WIDTH / 1.5f);
		data.transform.size.x = SCREEN_WIDTH * (2.0f / 3.0f);
		data.colliderType = COLLIDER_TRANSFORM;
		break;
	case CURSOR:
		data.transform.position = { (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT };
		data.transform.size = { MAP_CHIP_SIZE, MAP_CHIP_SIZE };
	case SCROLL_NONE:
	default:
		break;
	}

	backGround->Init(data);
}

void CObjGene::CreatePlayer(CGameObject *mapChip, float posX, float posY) {
	FDATA_GAMEOBJECT data = {
		{
			{ posX, posY },
			{ 120.0f, 168.0f }
		},{
			{ 0.0f, 0.0f },
			{ (120.0f / 6.0f) / 120.0f, (112.0f / 4.0f) / 112.0f },
			FLIP_NONE
		},
		ANIM_NONE,
		MOVE_PLAYER,
		COLLIDER_PLAYER,
		ACTION_NONE,
		{ 0.0f, 0.0f },
		NULL,
		TAG_PLAYER
	};

	mapChip->Init(data);
}

void CMapData::Init(int request) {
	switch (request)
	{
	case 0:
	default:
		break;
	}
}

void CMapData::Set(CGameObject*) {

}

void CObjGene::CreateNull(CGameObject *mapChip) {
	FDATA_GAMEOBJECT data = {
		{
			Float2zero,
			Float2zero
		},{
			Float2zero,
			Float2zero,
			FLIP_NONE
		},
		ANIM_NONE,
		MOVE_NONE,
		COLLIDER_NONE,
		ACTION_NONE,
		Float2zero,
		NULL,
		TAG_ENEMY_NULL
	};

	mapChip->Init(data);
}

void CObjGene::SetEnemyParameter(CGameObject *pThis, int kind, float posX, float posY) {
	const Float2 enemySize[5] = {
		{120.0f, 108.0f},
		{120.0f, 168.0f},
		{144.0f, 180.0f},
		{264.0f, 312.0f},
		{228.0f, 180.0f},
	};

	pThis->collider.isActive = true;
	pThis->tag = kind;

	switch (kind)
	{
	case TAG_ENEMY_DESTROY:
		pThis->transform.size = enemySize[1];
		pThis->collider.offset = MakeFloat2(0.0f, -6.0f);
		pThis->collider.size = MakeFloat2(60.0f, 72.0f);
		pThis->uv.offset = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X + (ENEMY_PIC_TYPE_2_SIZE_X * 2)) / ENEMY_PIC_ALL_SIZE_X, 0.0f);
		pThis->uv.size = MakeFloat2((ENEMY_PIC_TYPE_2_SIZE_X / 6) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y / 4) / ENEMY_PIC_ALL_SIZE_Y);
		break;
	case TAG_ENEMY_SKULL:
		pThis->transform.size = enemySize[1];
		pThis->collider.offset = MakeFloat2(0.0f, -6.0f);
		pThis->collider.size = MakeFloat2(60.0f, 72.0f);
		pThis->uv.offset = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X + (ENEMY_PIC_TYPE_2_SIZE_X * 2)) / ENEMY_PIC_ALL_SIZE_X, 0.0f);
		pThis->uv.size = MakeFloat2((ENEMY_PIC_TYPE_2_SIZE_X / 6) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y / 4) / ENEMY_PIC_ALL_SIZE_Y);
		break;
	case TAG_ENEMY_SPIRIT_1:
	case TAG_ENEMY_SPIRIT_2:
	case TAG_ENEMY_SPIRIT_3:
	case TAG_ENEMY_SPIRIT_4:
	case TAG_ENEMY_SPIRIT_5:
	case TAG_ENEMY_SPIRIT_6:
		pThis->transform.size = enemySize[1];
		pThis->collider.offset = MakeFloat2(0.0f, 12.0f);
		pThis->collider.size = MakeFloat2(60.0f, 96.0f);
		pThis->uv.offset = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X) / ENEMY_PIC_ALL_SIZE_X, 0.0f);
		pThis->uv.size = MakeFloat2((ENEMY_PIC_TYPE_2_SIZE_X / 6) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y / 4) / ENEMY_PIC_ALL_SIZE_Y);
		break;
	case TAG_ENEMY_ORC_1:
	case TAG_ENEMY_ORC_2:
		pThis->transform.size = enemySize[1];
		pThis->collider.offset = MakeFloat2(0.0f, -30.0f);
		pThis->collider.size = MakeFloat2(60.0f, 96.0f);
		if (kind == TAG_ENEMY_ORC_1) {
			pThis->uv.offset = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X + ENEMY_PIC_TYPE_2_SIZE_X) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y) / ENEMY_PIC_ALL_SIZE_Y);
			pThis->uv.size = MakeFloat2((ENEMY_PIC_TYPE_2_SIZE_X / 6) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y / 4) / ENEMY_PIC_ALL_SIZE_Y);
		}
		else {
			pThis->uv.offset = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X + ENEMY_PIC_TYPE_2_SIZE_X) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y * 2) / ENEMY_PIC_ALL_SIZE_Y);
			pThis->uv.size = MakeFloat2((ENEMY_PIC_TYPE_2_SIZE_X / 6) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y / 4) / ENEMY_PIC_ALL_SIZE_Y);
		}
		break;
	case TAG_ENEMY_PLANT_1:
	case TAG_ENEMY_PLANT_2:
	case TAG_ENEMY_PLANT_FLOWER:
		pThis->transform.size = enemySize[1];
		pThis->collider.offset = MakeFloat2(0.0f, -30.0f);
		pThis->collider.size = MakeFloat2(60.0f, 96.0f);
		if (kind == TAG_ENEMY_PLANT_1) {
			pThis->uv.offset = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y) / ENEMY_PIC_ALL_SIZE_Y);
			pThis->uv.size = MakeFloat2((ENEMY_PIC_TYPE_2_SIZE_X / 6) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y / 4) / ENEMY_PIC_ALL_SIZE_Y);
		}
		else if (kind == TAG_ENEMY_PLANT_2) {
			pThis->uv.offset = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y * 2) / ENEMY_PIC_ALL_SIZE_Y);
			pThis->uv.size = MakeFloat2((ENEMY_PIC_TYPE_2_SIZE_X / 6) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y / 4) / ENEMY_PIC_ALL_SIZE_Y);
		}
		else {
			pThis->uv.offset = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X + ENEMY_PIC_TYPE_2_SIZE_X) / ENEMY_PIC_ALL_SIZE_X, 0.0f);
			pThis->uv.size = MakeFloat2((ENEMY_PIC_TYPE_2_SIZE_X / 6) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y / 4) / ENEMY_PIC_ALL_SIZE_Y);
		}
		break;
	case TAG_ENEMY_MOMMY:
		pThis->transform.size = enemySize[1];
		pThis->collider.offset = MakeFloat2(0.0f, -30.0f);
		pThis->collider.size = MakeFloat2(60.0f, 96.0f);
		pThis->uv.offset = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y * 3) / ENEMY_PIC_ALL_SIZE_Y);
		pThis->uv.size = MakeFloat2((ENEMY_PIC_TYPE_2_SIZE_X / 6) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y / 4) / ENEMY_PIC_ALL_SIZE_Y);
		break;
	case TAG_ENEMY_SLIME:
		pThis->transform.size = enemySize[1];
		pThis->collider.offset = MakeFloat2(0.0f, -30.0f);
		pThis->collider.size = MakeFloat2(60.0f, 96.0f);
		pThis->uv.offset = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y * 4) / ENEMY_PIC_ALL_SIZE_Y);
		pThis->uv.size = MakeFloat2((ENEMY_PIC_TYPE_2_SIZE_X / 6) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y / 4) / ENEMY_PIC_ALL_SIZE_Y);
		break;
	case TAG_ENEMY_GHOST_1:
	case TAG_ENEMY_GHOST_2:
		pThis->transform.size = enemySize[1];
		pThis->collider.offset = MakeFloat2(0.0f, -30.0f);
		pThis->collider.size = MakeFloat2(60.0f, 96.0f);
		if (kind == TAG_ENEMY_GHOST_1) {
			pThis->uv.offset = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X + (ENEMY_PIC_TYPE_2_SIZE_X * 2)) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y) / ENEMY_PIC_ALL_SIZE_Y);
			pThis->uv.size = MakeFloat2((ENEMY_PIC_TYPE_2_SIZE_X / 6) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y / 4) / ENEMY_PIC_ALL_SIZE_Y);
		}
		else {
			pThis->uv.offset = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X + (ENEMY_PIC_TYPE_2_SIZE_X * 2)) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y * 2) / ENEMY_PIC_ALL_SIZE_Y);
			pThis->uv.size = MakeFloat2((ENEMY_PIC_TYPE_2_SIZE_X / 6) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y / 4) / ENEMY_PIC_ALL_SIZE_Y);
		}
		break;
	case TAG_ENEMY_EYE_1:
	case TAG_ENEMY_EYE_2:
		pThis->transform.size = enemySize[1];
		pThis->collider.offset = MakeFloat2(0.0f, 12.0f);
		pThis->collider.size = MakeFloat2(60.0f, 96.0f);
		if (kind == TAG_ENEMY_EYE_1) {
			pThis->uv.offset = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X + (ENEMY_PIC_TYPE_2_SIZE_X * 3)) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y) / ENEMY_PIC_ALL_SIZE_Y);
			pThis->uv.size = MakeFloat2((ENEMY_PIC_TYPE_2_SIZE_X / 6) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y / 4) / ENEMY_PIC_ALL_SIZE_Y);
		}
		else {
			pThis->uv.offset = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X + (ENEMY_PIC_TYPE_2_SIZE_X * 3)) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y * 2) / ENEMY_PIC_ALL_SIZE_Y);
			pThis->uv.size = MakeFloat2((ENEMY_PIC_TYPE_2_SIZE_X / 6) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y / 4) / ENEMY_PIC_ALL_SIZE_Y);
		}
		break;
	case TAG_ENEMY_SHADOW:
		pThis->transform.size = enemySize[1];
		pThis->collider.offset = MakeFloat2(0.0f, -30.0f);
		pThis->collider.size = MakeFloat2(60.0f, 96.0f);
		pThis->uv.offset = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X + (ENEMY_PIC_TYPE_2_SIZE_X * 4)) / ENEMY_PIC_ALL_SIZE_X, 0.0f);
		pThis->uv.size = MakeFloat2((ENEMY_PIC_TYPE_2_SIZE_X / 6) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y / 4) / ENEMY_PIC_ALL_SIZE_Y);
		break;
	case TAG_ENEMY_LIZARD_1:
	case TAG_ENEMY_LIZARD_2:
		pThis->transform.size = enemySize[0];
		pThis->collider.offset = MakeFloat2(0.0f, 0.0f);
		pThis->collider.size = MakeFloat2(72.0f, 108.0f);
		if (kind == TAG_ENEMY_LIZARD_1) {
			pThis->uv.offset = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X + (ENEMY_PIC_TYPE_2_SIZE_X * 4)) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y) / ENEMY_PIC_ALL_SIZE_Y);
			pThis->uv.size = MakeFloat2((ENEMY_PIC_TYPE_1_SIZE_X / 6) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_1_SIZE_Y / 4) / ENEMY_PIC_ALL_SIZE_Y);
		}
		else {
			pThis->uv.offset = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X + (ENEMY_PIC_TYPE_2_SIZE_X * 4)) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y + ENEMY_PIC_TYPE_1_SIZE_Y) / ENEMY_PIC_ALL_SIZE_Y);
			pThis->uv.size = MakeFloat2((ENEMY_PIC_TYPE_1_SIZE_X / 6) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_1_SIZE_Y / 4) / ENEMY_PIC_ALL_SIZE_Y);
		}
		break;
	case TAG_ENEMY_DEATH:
		pThis->transform.size = enemySize[2];
		pThis->collider.offset = MakeFloat2(0.0f, -24.0f);
		pThis->collider.size = MakeFloat2(60.0f, 108.0f);
		pThis->uv.offset = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X + (ENEMY_PIC_TYPE_2_SIZE_X * 5) + ENEMY_PIC_TYPE_4_SIZE_X) / ENEMY_PIC_ALL_SIZE_X, 0.0f);
		pThis->uv.size = MakeFloat2((ENEMY_PIC_TYPE_3_SIZE_X / 6) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_3_SIZE_Y / 4) / ENEMY_PIC_ALL_SIZE_Y);
		break;
	case TAG_ENEMY_GOLEM_1:
	case TAG_ENEMY_GOLEM_2:
		pThis->transform.size = enemySize[3];
		pThis->collider.offset = MakeFloat2(0.0f, 0.0f);
		pThis->collider.size = MakeFloat2(264.0f, 288.0f);
		if (kind == TAG_ENEMY_GOLEM_1) {
			pThis->uv.offset = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X + (ENEMY_PIC_TYPE_2_SIZE_X * 5)) / ENEMY_PIC_ALL_SIZE_X, 0.0f);
			pThis->uv.size = MakeFloat2((ENEMY_PIC_TYPE_4_SIZE_X / 6) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_4_SIZE_Y / 4) / ENEMY_PIC_ALL_SIZE_Y);
		}
		else {
			pThis->uv.offset = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X + (ENEMY_PIC_TYPE_2_SIZE_X * 5)) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_4_SIZE_Y) / ENEMY_PIC_ALL_SIZE_Y);
			pThis->uv.size = MakeFloat2((ENEMY_PIC_TYPE_4_SIZE_X / 6) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_4_SIZE_Y / 4) / ENEMY_PIC_ALL_SIZE_Y);
		}
		break;
	case TAG_ENEMY_DRAGON_1:
	case TAG_ENEMY_DRAGON_2:
	case TAG_ENEMY_DRAGON_3:
		pThis->transform.size = enemySize[4];
		pThis->collider.offset = MakeFloat2(0.0f, 0.0f);
		pThis->collider.size = MakeFloat2(108.0f, 132.0f);
		if (kind == TAG_ENEMY_DRAGON_1) {
			pThis->uv.offset = MakeFloat2(0.0f, 0.0f);
			pThis->uv.size = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X / 6) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_5_SIZE_Y / 4) / ENEMY_PIC_ALL_SIZE_Y);
		}
		else if (kind == TAG_ENEMY_DRAGON_2) {
			pThis->transform.size = pThis->transform.size * 1.5;
			pThis->collider.offset = pThis->collider.offset * 1.5;
			pThis->collider.size = pThis->collider.size * 1.5;
			pThis->uv.offset = MakeFloat2(0.0f, (ENEMY_PIC_TYPE_5_SIZE_Y) / ENEMY_PIC_ALL_SIZE_Y);
			pThis->uv.size = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X / 6) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_5_SIZE_Y / 4) / ENEMY_PIC_ALL_SIZE_Y);
		}
		else {
			pThis->transform.size = pThis->transform.size * 2;
			pThis->collider.offset = pThis->collider.offset * 2;
			pThis->collider.size = pThis->collider.size * 2;
			pThis->uv.offset = MakeFloat2(0.0f, (ENEMY_PIC_TYPE_5_SIZE_Y * 2) / ENEMY_PIC_ALL_SIZE_Y);
			pThis->uv.size = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X / 6) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_5_SIZE_Y / 4) / ENEMY_PIC_ALL_SIZE_Y);
		}
		break;
	case TAG_ENEMY_ME:
		pThis->transform.size = enemySize[1];
		pThis->collider.offset = MakeFloat2(0.0f, -30.0f);
		pThis->collider.size = MakeFloat2(60.0f, 96.0f);
		pThis->uv.offset = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X + (ENEMY_PIC_TYPE_2_SIZE_X * 3)) / ENEMY_PIC_ALL_SIZE_X, 0.0f);
		pThis->uv.size = MakeFloat2((ENEMY_PIC_TYPE_2_SIZE_X / 6) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y / 4) / ENEMY_PIC_ALL_SIZE_Y);
		break;
	case TAG_ENEMY_NULL:
	default:
		pThis->uv.offset = MakeFloat2(0.0f, 0.0f);
		pThis->uv.size = MakeFloat2(0.0f, 0.0f);
		pThis->collider.isActive = false;
		pThis->tag = TAG_ENEMY_NULL;
		break;
	}

	pThis->transform.position = MakeFloat2(posX, posY) - pThis->collider.offset;
}

void CObjGene::SetItemParameter(CGameObject *pThis, int kind, float posX, float posY) {
	const Float2 enemySize[4] = {
		{120.0f, 168.0f},
		{MAP_CHIP_SIZE, MAP_CHIP_SIZE},
		{128.0f, 144.0f},
		{288.0f, 300.0f},
	};

	pThis->collider.isActive = true;
	pThis->tag = kind;

	switch (kind)
	{
	case TAG_ITEM_HEART:
	case TAG_ITEM_COIN_1:
	case TAG_ITEM_COIN_2:
	case TAG_ITEM_KEY:
	case TAG_ITEM_STATES_UP:
	case TAG_ITEM_NECKLACE:
	case TAG_ITEM_HEART_SHOP:
	case TAG_ITEM_KEY_SHOP:
	case TAG_ITEM_STATES_UP_SHOP:
		pThis->transform.size = enemySize[0];
		pThis->collider.offset = MakeFloat2(0.0f, 12.0f);
		pThis->collider.size = MakeFloat2(60.0f, 96.0f);
		pThis->uv.offset = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X + (ENEMY_PIC_TYPE_2_SIZE_X * 5)) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_4_SIZE_Y * 2) / ENEMY_PIC_ALL_SIZE_Y);
		pThis->uv.size = MakeFloat2((ITEM_PIC_TYPE_1_SIZE_X) / ENEMY_PIC_ALL_SIZE_X, (ITEM_PIC_TYPE_1_SIZE_Y) / ENEMY_PIC_ALL_SIZE_Y);
		if (kind == TAG_ITEM_COIN_1) {
			pThis->uv.offset.y += pThis->uv.size.y;
		}
		else if (kind == TAG_ITEM_COIN_2) {
			pThis->uv.offset.y += (pThis->uv.size.y * 2);
		}
		else if (kind == TAG_ITEM_KEY) {
			pThis->uv.offset.y += (pThis->uv.size.y * 3);
		}
		else if (kind == TAG_ITEM_STATES_UP) {
			pThis->uv.offset.x += (pThis->uv.size.x * 3);
		}
		else if (kind == TAG_ITEM_HEART_SHOP) {
			pThis->uv.offset.y += (pThis->uv.size.y * 4);
		}
		else if (kind == TAG_ITEM_KEY_SHOP) {
			pThis->uv.offset.y += (pThis->uv.size.y * 5);
		}
		else if (kind == TAG_ITEM_STATES_UP_SHOP) {
			pThis->uv.offset.y += (pThis->uv.size.y * 6);
		}
		else if (kind == TAG_ITEM_STATES_UP) {
			pThis->uv.offset.x += (pThis->uv.size.x * 3);
		}
		else if (kind == TAG_ITEM_NECKLACE) {
			pThis->uv.offset.x += (pThis->uv.size.x * 3);
			pThis->uv.offset.y += pThis->uv.size.y;
		}
		break;
	case TAG_ITEM_DOOR_KEY:
	case TAG_ITEM_DOOR_LOCK:
	case TAG_ITEM_FLOOR_KEY:
	case TAG_ITEM_FLOOR_STATES_UP:
	case TAG_ITEM_DOOR_CRYSTAL_1:
	case TAG_ITEM_DOOR_CRYSTAL_2:
	case TAG_ITEM_DOOR_CRYSTAL_3:
	case TAG_ITEM_DOOR_CRYSTAL_4:
	case TAG_ITEM_DOOR_CRYSTAL_5:
	case TAG_ITEM_DOOR_CRYSTAL_6:
	case TAG_ITEM_DOOR_CRYSTAL_7:
	case TAG_ITEM_DOOR_CRYSTAL_8:
	case TAG_ITEM_MOVE_BLOCK_1:
	case TAG_ITEM_MOVE_BLOCK_2:
	case TAG_ITEM_FLOOR_UP:
	case TAG_ITEM_FLOOR_DOWN:
	case TAG_ITEM_LASTANCHOR:
	case TAG_ITEM_MUSICBOX_1:
		pThis->transform.size = enemySize[1];
		pThis->collider.offset = MakeFloat2(0.0f, 0.0f);
		pThis->collider.size = enemySize[1];
		pThis->uv.offset = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X + (ENEMY_PIC_TYPE_2_SIZE_X * 5) + ENEMY_PIC_TYPE_4_SIZE_X) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_3_SIZE_Y) / ENEMY_PIC_ALL_SIZE_Y);
		pThis->uv.size = MakeFloat2((ITEM_PIC_TYPE_2_SIZE_X) / ENEMY_PIC_ALL_SIZE_X, (ITEM_PIC_TYPE_2_SIZE_Y) / ENEMY_PIC_ALL_SIZE_Y);
		if (kind == TAG_ITEM_DOOR_LOCK) {
			pThis->uv.offset.y += pThis->uv.size.y;
		}
		else if (kind == TAG_ITEM_FLOOR_KEY) {
			pThis->uv.offset.y += (pThis->uv.size.y * 2);
		}
		else if (kind == TAG_ITEM_FLOOR_STATES_UP) {
			pThis->uv.offset.y += (pThis->uv.size.y * 3);
		}
		else if (kind == TAG_ITEM_DOOR_CRYSTAL_1) {
			pThis->uv.offset.y += (pThis->uv.size.y * 4);
		}
		else if (kind == TAG_ITEM_DOOR_CRYSTAL_2) {
			pThis->uv.offset.y += (pThis->uv.size.y * 5);
		}
		else if (kind == TAG_ITEM_DOOR_CRYSTAL_3) {
			pThis->uv.offset.y += (pThis->uv.size.y * 6);
		}
		else if (kind == TAG_ITEM_DOOR_CRYSTAL_4) {
			pThis->uv.offset.y += (pThis->uv.size.y * 7);
		}
		else if (kind == TAG_ITEM_DOOR_CRYSTAL_5) {
			pThis->uv.offset.y += (pThis->uv.size.y * 8);
		}
		else if (kind == TAG_ITEM_DOOR_CRYSTAL_6) {
			pThis->uv.offset.y += (pThis->uv.size.y * 9);
		}
		else if (kind == TAG_ITEM_DOOR_CRYSTAL_7) {
			pThis->uv.offset.y += (pThis->uv.size.y * 10);
		}
		else if (kind == TAG_ITEM_DOOR_CRYSTAL_8) {
			pThis->uv.offset.y += (pThis->uv.size.y * 11);
		}
		else if (kind == TAG_ITEM_MOVE_BLOCK_1) {
			pThis->uv.offset.y += (pThis->uv.size.y * 12);
		}
		else if (kind == TAG_ITEM_MOVE_BLOCK_2) {
			pThis->uv.offset.y += (pThis->uv.size.y * 12);
			pThis->uv.offset.x += (pThis->uv.size.x * 1);
		}
		else if (kind == TAG_ITEM_MUSICBOX_1) {
			pThis->uv.offset.y += (pThis->uv.size.y * 13);
		}
		else if (kind == TAG_ITEM_LASTANCHOR) {
			pThis->uv.offset.y += (pThis->uv.size.y * 13);
			pThis->uv.offset.x += (pThis->uv.size.x * 1);
		}
		else if (kind == TAG_ITEM_FLOOR_UP) {
			pThis->uv.offset.y += (pThis->uv.size.y * 12);
			pThis->uv.offset.x += (pThis->uv.size.x * 2);
		}
		else if (kind == TAG_ITEM_FLOOR_DOWN) {
			pThis->uv.offset.y += (pThis->uv.size.y * 13);
			pThis->uv.offset.x += (pThis->uv.size.x * 2);
		}
		break;
	case TAG_ITEM_CRYSTAL_1:
	case TAG_ITEM_CRYSTAL_2:
	case TAG_ITEM_CRYSTAL_3:
	case TAG_ITEM_CRYSTAL_4:
	case TAG_ITEM_CRYSTAL_5:
	case TAG_ITEM_CRYSTAL_6:
	case TAG_ITEM_CRYSTAL_7:
	case TAG_ITEM_CRYSTAL_8:
		pThis->transform.size = enemySize[2];
		pThis->collider.offset = MakeFloat2(0.0f, 0.0f);
		pThis->collider.size = enemySize[2];
		pThis->uv.offset = MakeFloat2((ENEMY_PIC_TYPE_5_SIZE_X + (ENEMY_PIC_TYPE_2_SIZE_X * 4)) / ENEMY_PIC_ALL_SIZE_X, (ENEMY_PIC_TYPE_2_SIZE_Y + (ENEMY_PIC_TYPE_1_SIZE_Y * 2)) / ENEMY_PIC_ALL_SIZE_Y);
		pThis->uv.size = MakeFloat2((ITEM_PIC_TYPE_3_SIZE_X) / ENEMY_PIC_ALL_SIZE_X, (ITEM_PIC_TYPE_3_SIZE_Y) / ENEMY_PIC_ALL_SIZE_Y);
		if (kind == TAG_ITEM_CRYSTAL_2) {
			pThis->uv.offset.y += pThis->uv.size.y;
		}
		else if (kind == TAG_ITEM_CRYSTAL_3) {
			pThis->uv.offset.y += (pThis->uv.size.y * 2);
		}
		else if (kind == TAG_ITEM_CRYSTAL_4) {
			pThis->uv.offset.y += (pThis->uv.size.y * 3);
		}
		else if (kind == TAG_ITEM_CRYSTAL_5) {
			pThis->uv.offset.x += (pThis->uv.size.x * 3);
		}
		else if (kind == TAG_ITEM_CRYSTAL_6) {
			pThis->uv.offset.x += (pThis->uv.size.x * 3);
			pThis->uv.offset.y += pThis->uv.size.y;
		}
		else if (kind == TAG_ITEM_CRYSTAL_7) {
			pThis->uv.offset.x += (pThis->uv.size.x * 3);
			pThis->uv.offset.y += (pThis->uv.size.y * 2);
		}
		else if (kind == TAG_ITEM_CRYSTAL_8) {
			pThis->uv.offset.x += (pThis->uv.size.x * 3);
			pThis->uv.offset.y += (pThis->uv.size.y * 3);
		}
		break;
	case TAG_ITEM_CRYSTAL_BIG:
		pThis->transform.size = enemySize[3];
		pThis->collider.offset = MakeFloat2(0.0f, 0.0f);
		pThis->collider.size = enemySize[3];
		pThis->uv.offset = MakeFloat2(0.0f, ((ENEMY_PIC_TYPE_5_SIZE_Y * 3)) / ENEMY_PIC_ALL_SIZE_Y);
		pThis->uv.size = MakeFloat2((ITEM_PIC_TYPE_4_SIZE_X) / ENEMY_PIC_ALL_SIZE_X, (ITEM_PIC_TYPE_4_SIZE_Y) / ENEMY_PIC_ALL_SIZE_Y);
		break;
	case TAG_ITEM_NULL:
	default:
		pThis->transform.size = enemySize[1];
		pThis->uv.offset = MakeFloat2(0.0f, 0.0f);
		pThis->uv.size = MakeFloat2(0.0f, 0.0f);
		pThis->collider.isActive = false;
		pThis->tag = TAG_ITEM_NULL;
		break;
	}

	pThis->transform.position = MakeFloat2(posX, posY) - pThis->collider.offset;
}
