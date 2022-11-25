#include "CGame.h"
#include <iostream>

unsigned int filePath = 0;

char mapFilePath[MAP_NUM][255] = {
"assets/map/map1.csv",
"assets/map/map2.csv",
"assets/map/map3.csv",
"assets/map/map4.csv"
};
char anchorFilePath[MAP_NUM][255] = {
	"assets/map/anchor1.csv",
	"assets/map/anchor2.csv",
	"assets/map/anchor3.csv",
	"assets/map/anchor4.csv"
};
char enemyFilePath[MAP_NUM][255] = {
	"assets/enemy/enemy1.csv",
	"assets/enemy/enemy2.csv",
	"assets/enemy/enemy3.csv",
	"assets/enemy/enemy4.csv"
};
char itemFilePath[MAP_NUM][255] = {
	"assets/item/item1.csv",
	"assets/item/item2.csv",
	"assets/item/item3.csv",
	"assets/item/item4.csv"
};

int eneTag[ENEMYMTMAX] = {
	TAG_ENEMY_DESTROY,
	TAG_ENEMY_SPIRIT_1,
	TAG_ENEMY_SPIRIT_2,
	TAG_ENEMY_SPIRIT_3,
	TAG_ENEMY_SPIRIT_4,
	TAG_ENEMY_SPIRIT_5,
	TAG_ENEMY_SPIRIT_6,
	TAG_ENEMY_ORC_1,
	TAG_ENEMY_ORC_2,
	TAG_ENEMY_PLANT_1,
	TAG_ENEMY_PLANT_2,
	TAG_ENEMY_PLANT_FLOWER,
	TAG_ENEMY_SKULL,
	TAG_ENEMY_GHOST_1,
	TAG_ENEMY_GHOST_2,
	TAG_ENEMY_EYE_1,
	TAG_ENEMY_EYE_2,
	TAG_ENEMY_SHADOW,
	TAG_ENEMY_LIZARD_1,
	TAG_ENEMY_LIZARD_2,
	TAG_ENEMY_DEATH,
	TAG_ENEMY_GOLEM_1,
	TAG_ENEMY_GOLEM_2,
	TAG_ENEMY_DRAGON_1,
	TAG_ENEMY_DRAGON_2,
	TAG_ENEMY_DRAGON_3,
	TAG_ENEMY_ME,
	TAG_ENEMY_MOMMY,
	TAG_ENEMY_SLIME,
};

int iteTag[ITEMMTMAX] = {
	TAG_ITEM_NULL,
	TAG_ITEM_HEART,
	TAG_ITEM_COIN_1,
	TAG_ITEM_COIN_2,
	TAG_ITEM_KEY,
	TAG_ITEM_STATES_UP,
	TAG_ITEM_DOOR_KEY,
	TAG_ITEM_DOOR_LOCK,
	TAG_ITEM_FLOOR_KEY,
	TAG_ITEM_FLOOR_STATES_UP,
	TAG_ITEM_DOOR_CRYSTAL_1,
	TAG_ITEM_DOOR_CRYSTAL_2,
	TAG_ITEM_DOOR_CRYSTAL_3,
	TAG_ITEM_DOOR_CRYSTAL_4,
	TAG_ITEM_DOOR_CRYSTAL_5,
	TAG_ITEM_DOOR_CRYSTAL_6,
	TAG_ITEM_DOOR_CRYSTAL_7,
	TAG_ITEM_DOOR_CRYSTAL_8,
	TAG_ITEM_CRYSTAL_1,
	TAG_ITEM_CRYSTAL_2,
	TAG_ITEM_CRYSTAL_3,
	TAG_ITEM_CRYSTAL_4,
	TAG_ITEM_CRYSTAL_5,
	TAG_ITEM_CRYSTAL_6,
	TAG_ITEM_CRYSTAL_7,
	TAG_ITEM_CRYSTAL_8,
	TAG_ITEM_CRYSTAL_BIG,
	TAG_ITEM_HEART_SHOP,
	TAG_ITEM_KEY_SHOP,
	TAG_ITEM_STATES_UP_SHOP,
	TAG_ITEM_NECKLACE,
	TAG_ITEM_MOVE_BLOCK_1,
	TAG_ITEM_MOVE_BLOCK_2,
	TAG_ITEM_FLOOR_DOWN,
	TAG_ITEM_FLOOR_UP,
	TAG_ITEM_LASTANCHOR,
	TAG_ITEM_MUSICBOX_1,
};

#pragma region // ゲームの基本形

bool CMode_Base::Init() {
	return false;
}

int CMode_Base::Update() {
	return 0;
}

void CMode_Base::UnInit() {

}

void CMode_Base::SethWnd(const HWND *other) {
	this->hWnd = *other;
}

#pragma endregion

#pragma region // ゲームのタイトル

bool CTitle::Init() {
	bool isSuccess;

	return true;
}

int CTitle::Update() {
	int gameOrder = GAME_ORDER_CONTINUE;

	Input_Update();  // このゲームで使うキーの押下状態を調べて保存

	return gameOrder;
}

void CTitle::UnInit() {
}

#pragma endregion

#pragma region // ゲームの遊び画面

bool CPlay::Init() {
	bool isSuccess;

	{
		FILE* ifp;
		FILE* ofp;
		AllocConsole();
		freopen_s(&ifp, "CONIN$", "r", stdin);
		freopen_s(&ofp, "CONOUT$", "w", stdout);

		std::cout << "番号を入力してください。" << std::endl;
		std::cin >> filePath;
		if (filePath > 3)
			filePath = 3;

		fclose(ifp);
		fclose(ofp);
		FreeConsole();
	}

	this->mapChip_Draw = new CDraw("assets/Image/back.png", MAX_SPRITE);
	for (int x = 0; x < MAP_SIZE_X; x++) {
		for (int y = 0; y < MAP_SIZE_Y; y++) {
			this->mapChip[x][y] = new CGameObject;
			CObjGene::CreateBackGround(this->mapChip[x][y], MAPCHIP, x + (y * MAP_SIZE_X));
		}
	}

	this->mapChipHit_Draw = new CDraw("assets/Image/hitbox2.png", MAX_SPRITE);
	for (int x = 0; x < MAP_SIZE_X; x++) {
		for (int y = 0; y < MAP_SIZE_Y; y++) {
			this->mapChipHit[x][y] = new CGameObject;
			CObjGene::CreateBackGround(this->mapChipHit[x][y], MAPCHIP, x + (y * MAP_SIZE_X));
			this->mapChipHit[x][y]->uv.size = { 1.0f / 6.0f, 0.5f };
		}
	}

	FILE *fp;

	fopen_s(&fp, mapFilePath[filePath], "r");

	if (fp != NULL) {
		// 一文字分の変数
		int c;
		// マップチップの種類
		int chipID;
		// 当たり判定があるかどうか
		int hitID;
		// 文字列格納用
		char buf[10];

		// 文字列初期化
		memset(buf, 0, sizeof(buf));

		for (int y = 0; y < MAP_SIZE_Y; y++) {
			for (int x = 0; x < MAP_SIZE_X; x++) {
				while (true) {
					c = fgetc(fp);

					// マップチップ用区切り
					if (c == ',') {
						chipID = atoi(buf);
						memset(buf, 0, sizeof(buf));
					}
					// 当たり判定用区切り又は開業 -> 次のチップへ
					else if (c == ';' || c == '\n') {
						hitID = atoi(buf);
						memset(buf, 0, sizeof(buf));
						break;
					}
					// 文字列連結
					else {
						strcat_s(buf, (const char*)&c);
					}
				}

				this->mapChip[x][y]->animator.frameX = chipID % MAPCHIP_NUM;
				this->mapChip[x][y]->animator.frameY = chipID / MAPCHIP_NUM;
				this->mapChipHit[x][y]->animator.frameX = hitID % 6;
				this->mapChipHit[x][y]->animator.frameY = hitID / 6;
			}
		}

		fclose(fp);
	}
	else {
		for (int y = 0; y < MAP_SIZE_Y; y++) {
			for (int x = 0; x < MAP_SIZE_X; x++) {
				this->mapChip[x][y]->animator.frameX = 0;
				this->mapChip[x][y]->animator.frameY = 0;
				this->mapChipHit[x][y]->animator.frameX = 0;
			}
		}
	}

	this->mapChipMT_Draw = new CDraw("assets/Image/back.png", MAX_SPRITE);
	for (int x = 0; x < MAPCHIP_NUM; x++) {
		for (int y = 0; y < MAPCHIP_NUM; y++) {
			this->mapChipMT[x][y] = new CGameObject;
			CObjGene::CreateBackGround(this->mapChipMT[x][y], MAPCHIPMT, x + (y * MAPCHIP_NUM));
			this->mapChipMT[x][y]->animator.frameX = x;
			this->mapChipMT[x][y]->animator.frameY = MAPCHIP_NUM - y - 1;
		}
	}

	this->cursor_Draw = new CDraw("assets/Image/cursor.png", MAX_SPRITE);
	this->cursor = new CGameObject;
	CObjGene::CreateBackGround(this->cursor, CURSOR, 0);

	this->anchor_Draw = new CDraw("assets/Image/hitbox.png", MAX_SPRITE);
	this->anchorObject = new CGameObject;
	CObjGene::CreateBackGround(this->anchorObject, CURSOR, 0);
	this->anchorObject->uv.offset = { 0.5f, 0.0f };
	this->anchorObject->uv.size = { 0.5f, 1.0f };

	for (int x = 0; x < MAP_SIZE_X / MAP_ONE_SIZE_X; x++) {
		for (int y = 0; y < MAP_SIZE_Y / MAP_ONE_SIZE_Y; y++) {
			for (int index = 0; index < ENEMY_MAX; index++) {
				this->enemy[x][y][index] = new CGameObject;
				CObjGene::CreateNull(this->enemy[x][y][index]);
			}
		}
	}
	this->enemy_Draw = new CDraw("assets/Image/enemy.png", ENEMY_MAX);

	for (int index = 0; index < ENEMYMTMAX; index++) {
		this->enemyMT[index] = new CGameObject;
		CObjGene::CreateNull(this->enemyMT[index]);
		if (index != 0) {
			CObjGene::SetEnemyParameter(this->enemyMT[index], eneTag[index], 0.0f, 128.0f * 3);
			this->enemyMT[index]->transform.position.x = this->enemyMT[index - 1]->transform.position.x + ((this->enemyMT[index - 1]->transform.size.x + this->enemyMT[index]->transform.size.x) / 2);
		}
		else {
			CObjGene::SetEnemyParameter(this->enemyMT[index], eneTag[index], 128.0f, 128.0f * 3);
		}
	}
	this->enemyMT_Draw = new CDraw("assets/Image/enemy.png", ENEMYMTMAX);

	for (int x = 0; x < MAP_SIZE_X / MAP_ONE_SIZE_X; x++) {
		for (int y = 0; y < MAP_SIZE_Y / MAP_ONE_SIZE_Y; y++) {
			for (int index = 0; index < ITEM_MAX; index++) {
				this->item[x][y][index] = new CGameObject;
				CObjGene::CreateNull(this->item[x][y][index]);
				this->item[x][y][index]->tag = TAG_ITEM_NULL;
			}
		}
	}
	this->item_Draw = new CDraw("assets/Image/enemy.png", ITEM_MAX);

	for (int index = 0; index < ITEMMTMAX; index++) {
		this->itemMT[index] = new CGameObject;
		CObjGene::CreateNull(this->itemMT[index]);
		if (index != 0) {
			CObjGene::SetItemParameter(this->itemMT[index], iteTag[index], 0.0f, 128.0f * 3);
			this->itemMT[index]->transform.position.x = this->itemMT[index - 1]->transform.position.x + ((this->itemMT[index - 1]->transform.size.x + this->itemMT[index]->transform.size.x) / 2);
		}
		else {
			CObjGene::SetItemParameter(this->itemMT[index], iteTag[index], 128.0f, 128.0f * 3);
		}
	}
	this->itemMT_Draw = new CDraw("assets/Image/enemy.png", ITEMMTMAX);

	fopen_s(&fp, anchorFilePath[filePath], "r");

	for (int y = 0; y < MAP_SIZE_Y / MAP_ONE_SIZE_Y; y++) {
		for (int x = 0; x < MAP_SIZE_X / MAP_ONE_SIZE_X; x++) {
			this->anchor[x][y] = new Float2;
			if (fp != NULL) {
				// 一文字分の変数
				int c;
				// 文字列格納用
				char buf[10];

				int posX;
				int posY;

				// 文字列初期化
				memset(buf, 0, sizeof(buf));

				while (true) {
					c = fgetc(fp);

					// マップチップ用区切り
					if (c == ',') {
						posX = atoi(buf);
						memset(buf, 0, sizeof(buf));
					}
					// 当たり判定用区切り又は開業 -> 次のチップへ
					else if (c == ';' || c == '\n') {
						posY = atoi(buf);
						memset(buf, 0, sizeof(buf));
						break;
					}
					// 文字列連結
					else {
						strcat_s(buf, (const char*)&c);
					}
				}

				*this->anchor[x][y] = MakeFloat2(posX, posY);
			}
			else {
				*this->anchor[x][y] = this->mapChip[x * MAP_ONE_SIZE_X][y * MAP_ONE_SIZE_Y]->transform.position;
			}
		}
	}

	if (fp != NULL) {
		fclose(fp);
	}

	fopen_s(&fp, enemyFilePath[filePath], "r");

	for (int y = 0; y < MAP_SIZE_Y / MAP_ONE_SIZE_Y; y++) {
		for (int x = 0; x < MAP_SIZE_X / MAP_ONE_SIZE_X; x++) {
			for (int index = 0; index < ENEMY_MAX; index++) {
				if (fp != NULL) {
					// 一文字分の変数
					int c;
					// 文字列格納用
					char buf[10];

					int posX;
					int posY;

					// 文字列初期化
					memset(buf, 0, sizeof(buf));

					while (true) {
						c = fgetc(fp);

						if (c == ',' || c == '\n') {
							this->enemy[x][y][index]->tag = atoi(buf);
							memset(buf, 0, sizeof(buf));
							break;
						}
						// 文字列連結
						else {
							strcat_s(buf, (const char*)&c);
						}
					}

					CObjGene::SetEnemyParameter(this->enemy[x][y][index], this->enemy[x][y][index]->tag, 0.0f, 0.0f);

					while (true) {
						c = fgetc(fp);

						if (c == ',' || c == '\n') {
							this->enemy[x][y][index]->transform.position.x = atoi(buf);
							memset(buf, 0, sizeof(buf));
							break;
						}
						// 文字列連結
						else {
							strcat_s(buf, (const char*)&c);
						}
					}

					while (true) {
						c = fgetc(fp);

						if (c == ',' || c == '\n') {
							this->enemy[x][y][index]->transform.position.y = atoi(buf);
							memset(buf, 0, sizeof(buf));
							break;
						}
						// 文字列連結
						else {
							strcat_s(buf, (const char*)&c);
						}
					}

				}
				else {

				}
			}
		}
	}

	if (fp != NULL) {
		fclose(fp);
	}

	fopen_s(&fp, itemFilePath[filePath], "r");

	for (int y = 0; y < MAP_SIZE_Y / MAP_ONE_SIZE_Y; y++) {
		for (int x = 0; x < MAP_SIZE_X / MAP_ONE_SIZE_X; x++) {
			for (int index = 0; index < ITEM_MAX; index++) {
				if (fp != NULL) {
					// 一文字分の変数
					int c;
					// 文字列格納用
					char buf[10];

					int posX;
					int posY;

					// 文字列初期化
					memset(buf, 0, sizeof(buf));

					while (true) {
						c = fgetc(fp);

						if (c == ',' || c == '\n') {
							this->item[x][y][index]->tag = atoi(buf);
							memset(buf, 0, sizeof(buf));
							break;
						}
						// 文字列連結
						else {
							strcat_s(buf, (const char*)&c);
						}
					}

					CObjGene::SetItemParameter(this->item[x][y][index], this->item[x][y][index]->tag, 0.0f, 0.0f);

					while (true) {
						c = fgetc(fp);

						if (c == ',' || c == '\n') {
							this->item[x][y][index]->transform.position.x = atoi(buf);
							memset(buf, 0, sizeof(buf));
							break;
						}
						// 文字列連結
						else {
							strcat_s(buf, (const char*)&c);
						}
					}

					while (true) {
						c = fgetc(fp);

						if (c == ',' || c == '\n') {
							this->item[x][y][index]->transform.position.y = atoi(buf);
							memset(buf, 0, sizeof(buf));
							break;
						}
						// 文字列連結
						else {
							strcat_s(buf, (const char*)&c);
						}
					}

				}
				else {

				}
			}
		}
	}

	if (fp != NULL) {
		fclose(fp);
	}

	CDraw::camera = { (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT };

	this->mode = 0;
	this->setMode = 0;

	this->mapPointX = 0;
	this->mapPointY = 0;

	this->enemyTag = TAG_ENEMY_SPIRIT_1;
	this->itemTag = TAG_ITEM_HEART;

	return true;
}

int CPlay::Update() {
	int gameOrder = GAME_ORDER_CONTINUE;

	Input_Update();  // このゲームで使うキーの押下状態を調べて保存

	CDraw::Update();

	Float2 cameraSpeed = Float2zero;
	if (this->mode == 0) {
		if (Input_GetKeyTrigger(VK_LEFT)) {
			if (this->mapPointX > 0) {
				this->mapPointX--;
				cameraSpeed.x -= SCREEN_WIDTH * 2;
			}
		}
		if (Input_GetKeyTrigger(VK_RIGHT)) {
			if (this->mapPointX < (MAP_SIZE_X / MAP_ONE_SIZE_X) - 1) {
				this->mapPointX++;
				cameraSpeed.x += SCREEN_WIDTH * 2;
			}
		}
		if (Input_GetKeyTrigger(VK_DOWN)) {
			if (this->mapPointY > 0) {
				this->mapPointY--;
				cameraSpeed.y -= SCREEN_HEIGHT * 2;
			}
		}
		if (Input_GetKeyTrigger(VK_UP)) {
			if (this->mapPointY < (MAP_SIZE_Y / MAP_ONE_SIZE_Y) - 1) {
				this->mapPointY++;
				cameraSpeed.y += SCREEN_HEIGHT * 2;
			}
		}
		CDraw::camera = MakeFloat2((float)SCREEN_WIDTH + (this->mapPointX * (SCREEN_WIDTH * 2)), (float)SCREEN_HEIGHT + (this->mapPointY * (SCREEN_HEIGHT * 2)));
	}
	else {
		if (Input_GetKeyPress(VK_LEFT)) {
			cameraSpeed.x -= 10.0f;
		}
		if (Input_GetKeyPress(VK_RIGHT)) {
			cameraSpeed.x += 10.0f;
		}
		if (Input_GetKeyPress(VK_DOWN)) {
			cameraSpeed.y -= 10.0f;
		}
		if (Input_GetKeyPress(VK_UP)) {
			cameraSpeed.y += 10.0f;
		}
		if (Input_GetKeyPress(VK_SHIFT)) {
			cameraSpeed = cameraSpeed * 2;
		}
		CDraw::camera = CDraw::camera + cameraSpeed;
	}

	this->cursor->transform.position = this->cursor->transform.position + cameraSpeed;

	Float2 cursorSpeed = Float2zero;
	if (Input_GetKeyPress('E')) {
		this->setMode = 0;
	}
	if (Input_GetKeyPress('I')) {
		this->setMode = 1;
	}
	if (Input_GetKeyPress('A')) {
		cursorSpeed.x -= 10.0f;
	}
	if (Input_GetKeyPress('D')) {
		cursorSpeed.x += 10.0f;
	}
	if (Input_GetKeyPress('S')) {
		cursorSpeed.y -= 10.0f;
	}
	if (Input_GetKeyPress('W')) {
		cursorSpeed.y += 10.0f;
	}
	if (Input_GetKeyPress(VK_SHIFT)) {
		cursorSpeed = cursorSpeed * 2;
	}
	if (Input_GetKeyTrigger('M')) {
		this->mode = (this->mode + 1) % 4;
		if (this->mode == 0) {
			CDraw::camera = this->cursor->transform.position = MakeFloat2((float)SCREEN_WIDTH + (this->mapPointX * (SCREEN_WIDTH * 2)), (float)SCREEN_HEIGHT + (this->mapPointY * (SCREEN_HEIGHT * 2)));
		}
		else {
			CDraw::camera = this->cursor->transform.position = { (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT };
		}
	}

	this->cursor->transform.position = this->cursor->transform.position + cursorSpeed;

	if (this->cursor->transform.position.y > CDraw::camera.y + SCREEN_HEIGHT) {
		this->cursor->transform.position.y = CDraw::camera.y + SCREEN_HEIGHT;
	}
	if (this->cursor->transform.position.y < CDraw::camera.y - SCREEN_HEIGHT) {
		this->cursor->transform.position.y = CDraw::camera.y - SCREEN_HEIGHT;
	}
	if (this->cursor->transform.position.x > CDraw::camera.x + SCREEN_WIDTH) {
		this->cursor->transform.position.x = CDraw::camera.x + SCREEN_WIDTH;
	}
	if (this->cursor->transform.position.x < CDraw::camera.x - SCREEN_WIDTH) {
		this->cursor->transform.position.x = CDraw::camera.x - SCREEN_WIDTH;
	}

	if (this->mode == 0) {
		Float2 float2 = CDraw::camera;
		int chipPosX = float2.x / MAP_CHIP_SIZE;
		int chipPosY = float2.y / MAP_CHIP_SIZE;
		int startX = MAP_ONE_SIZE_X * this->mapPointX;
		int startY = MAP_ONE_SIZE_Y * this->mapPointY;
		int endX = startX + MAP_ONE_SIZE_X;
		int endY = startY + MAP_ONE_SIZE_Y;

		if (startX < 0) {
			startX = 0;
		}
		if (startY < 0) {
			startY = 0;
		}
		if (endX > MAP_SIZE_X) {
			endX = MAP_SIZE_X;
		}
		if (endY > MAP_SIZE_Y) {
			endY = MAP_SIZE_Y;
		}

		if (Input_GetKeyPress('H')) {
			bool endFlg = false;
			for (int x = startX; x < endX; x++) {
				for (int y = startY; y < endY; y++) {
					float leftX = this->mapChip[x][y]->transform.position.x - this->mapChip[x][y]->transform.size.x / 2;
					float topY = this->mapChip[x][y]->transform.position.y + this->mapChip[x][y]->transform.size.y / 2;
					float rightX = leftX + this->mapChip[x][y]->transform.size.x;
					float bottomY = topY - this->mapChip[x][y]->transform.size.y;

					if (this->cursor->transform.position.x > leftX && this->cursor->transform.position.x < rightX) {
						if (this->cursor->transform.position.y > bottomY && this->cursor->transform.position.y < topY) {
							this->mapChipHit[x][y]->animator.frameX = 1;
							this->mapChipHit[x][y]->animator.frameY = 0;
							endFlg = true;
						}
					}

				}
				if (endFlg) {
					break;
				}
			}
		}
		if (Input_GetKeyPress('V')) {
			bool endFlg = false;
			for (int x = startX; x < endX; x++) {
				for (int y = startY; y < endY; y++) {
					float leftX = this->mapChip[x][y]->transform.position.x - this->mapChip[x][y]->transform.size.x / 2;
					float topY = this->mapChip[x][y]->transform.position.y + this->mapChip[x][y]->transform.size.y / 2;
					float rightX = leftX + this->mapChip[x][y]->transform.size.x;
					float bottomY = topY - this->mapChip[x][y]->transform.size.y;

					if (this->cursor->transform.position.x > leftX && this->cursor->transform.position.x < rightX) {
						if (this->cursor->transform.position.y > bottomY && this->cursor->transform.position.y < topY) {
							this->mapChipHit[x][y]->animator.frameX = 1;
							this->mapChipHit[x][y]->animator.frameY = 1;
							endFlg = true;
						}
					}

				}
				if (endFlg) {
					break;
				}
			}
		}
		if (Input_GetKeyPress('O')) {
			bool endFlg = false;
			for (int x = startX; x < endX; x++) {
				for (int y = startY; y < endY; y++) {
					float leftX = this->mapChip[x][y]->transform.position.x - this->mapChip[x][y]->transform.size.x / 2;
					float topY = this->mapChip[x][y]->transform.position.y + this->mapChip[x][y]->transform.size.y / 2;
					float rightX = leftX + this->mapChip[x][y]->transform.size.x;
					float bottomY = topY - this->mapChip[x][y]->transform.size.y;

					if (this->cursor->transform.position.x > leftX && this->cursor->transform.position.x < rightX) {
						if (this->cursor->transform.position.y > bottomY && this->cursor->transform.position.y < topY) {
							this->mapChipHit[x][y]->animator.frameX = 4;
							this->mapChipHit[x][y]->animator.frameY = 0;
							endFlg = true;
						}
					}

				}
				if (endFlg) {
					break;
				}
			}
		}
		if (Input_GetKeyPress('P')) {
			bool endFlg = false;
			for (int x = startX; x < endX; x++) {
				for (int y = startY; y < endY; y++) {
					float leftX = this->mapChip[x][y]->transform.position.x - this->mapChip[x][y]->transform.size.x / 2;
					float topY = this->mapChip[x][y]->transform.position.y + this->mapChip[x][y]->transform.size.y / 2;
					float rightX = leftX + this->mapChip[x][y]->transform.size.x;
					float bottomY = topY - this->mapChip[x][y]->transform.size.y;

					if (this->cursor->transform.position.x > leftX && this->cursor->transform.position.x < rightX) {
						if (this->cursor->transform.position.y > bottomY && this->cursor->transform.position.y < topY) {
							this->mapChipHit[x][y]->animator.frameX = 4;
							this->mapChipHit[x][y]->animator.frameY = 1;
							endFlg = true;
						}
					}

				}
				if (endFlg) {
					break;
				}
			}
		}
		if (Input_GetKeyPress('L')) {
			bool endFlg = false;
			for (int x = startX; x < endX; x++) {
				for (int y = startY; y < endY; y++) {
					float leftX = this->mapChip[x][y]->transform.position.x - this->mapChip[x][y]->transform.size.x / 2;
					float topY = this->mapChip[x][y]->transform.position.y + this->mapChip[x][y]->transform.size.y / 2;
					float rightX = leftX + this->mapChip[x][y]->transform.size.x;
					float bottomY = topY - this->mapChip[x][y]->transform.size.y;

					if (this->cursor->transform.position.x > leftX && this->cursor->transform.position.x < rightX) {
						if (this->cursor->transform.position.y > bottomY && this->cursor->transform.position.y < topY) {
							this->mapChipHit[x][y]->animator.frameX = 5;
							this->mapChipHit[x][y]->animator.frameY = 0;
							endFlg = true;
						}
					}

				}
				if (endFlg) {
					break;
				}
			}
		}
		if (Input_GetKeyTrigger('Q')) {
			bool endFlg = false;
			for (int x = startX; x < endX; x++) {
				for (int y = startY; y < endY; y++) {
					float leftX = this->mapChip[x][y]->transform.position.x - this->mapChip[x][y]->transform.size.x / 2;
					float topY = this->mapChip[x][y]->transform.position.y + this->mapChip[x][y]->transform.size.y / 2;
					float rightX = leftX + this->mapChip[x][y]->transform.size.x;
					float bottomY = topY - this->mapChip[x][y]->transform.size.y;

					if (this->cursor->transform.position.x > leftX && this->cursor->transform.position.x < rightX) {
						if (this->cursor->transform.position.y > bottomY && this->cursor->transform.position.y < topY) {
							if (this->mapChipHit[x][y]->animator.frameX == 2 && this->mapChipHit[x][y]->animator.frameY == 0) {
								this->mapChipHit[x][y]->animator.frameX = 3;
								this->mapChipHit[x][y]->animator.frameY = 0;
							}
							else if (this->mapChipHit[x][y]->animator.frameX == 3 && this->mapChipHit[x][y]->animator.frameY == 0) {
								this->mapChipHit[x][y]->animator.frameX = 5;
								this->mapChipHit[x][y]->animator.frameY = 1;
							}
							else if (this->mapChipHit[x][y]->animator.frameX == 5 && this->mapChipHit[x][y]->animator.frameY == 1) {
								this->mapChipHit[x][y]->animator.frameX = 2;
								this->mapChipHit[x][y]->animator.frameY = 1;
							}
							else if (this->mapChipHit[x][y]->animator.frameX == 2 && this->mapChipHit[x][y]->animator.frameY == 1) {
								this->mapChipHit[x][y]->animator.frameX = 3;
								this->mapChipHit[x][y]->animator.frameY = 1;
							}
							else if (this->mapChipHit[x][y]->animator.frameX == 3 && this->mapChipHit[x][y]->animator.frameY == 1) {
								this->mapChipHit[x][y]->animator.frameX = 0;
								this->mapChipHit[x][y]->animator.frameY = 1;
							}
							else {
								this->mapChipHit[x][y]->animator.frameX = 2;
								this->mapChipHit[x][y]->animator.frameY = 0;
							}
							endFlg = true;
						}
					}

				}
				if (endFlg) {
					break;
				}
			}
		}
		if (Input_GetKeyPress('J')) {
			bool endFlg = false;
			for (int x = startX; x < endX; x++) {
				for (int y = startY; y < endY; y++) {
					float leftX = this->mapChip[x][y]->transform.position.x - this->mapChip[x][y]->transform.size.x / 2;
					float topY = this->mapChip[x][y]->transform.position.y + this->mapChip[x][y]->transform.size.y / 2;
					float rightX = leftX + this->mapChip[x][y]->transform.size.x;
					float bottomY = topY - this->mapChip[x][y]->transform.size.y;

					if (this->cursor->transform.position.x > leftX && this->cursor->transform.position.x < rightX) {
						if (this->cursor->transform.position.y > bottomY && this->cursor->transform.position.y < topY) {
							this->mapChipHit[x][y]->animator.frameX = 0;
							this->mapChipHit[x][y]->animator.frameY = 0;
							endFlg = true;
						}
					}

				}
				if (endFlg) {
					break;
				}
			}
		}
		if (Input_GetKeyPress('G')) {
			bool endFlg = false;
			for (int x = startX; x < endX; x++) {
				for (int y = startY; y < endY; y++) {
					float leftX = this->mapChip[x][y]->transform.position.x - this->mapChip[x][y]->transform.size.x / 2;
					float topY = this->mapChip[x][y]->transform.position.y + this->mapChip[x][y]->transform.size.y / 2;
					float rightX = leftX + this->mapChip[x][y]->transform.size.x;
					float bottomY = topY - this->mapChip[x][y]->transform.size.y;

					if (this->cursor->transform.position.x > leftX && this->cursor->transform.position.x < rightX) {
						if (this->cursor->transform.position.y > bottomY && this->cursor->transform.position.y < topY) {
							this->mapChip[x][y]->animator.frameX = this->animX;
							this->mapChip[x][y]->animator.frameY = this->animY;
							endFlg = true;
						}
					}

				}
				if (endFlg) {
					break;
				}
			}
		}

		if (Input_GetKeyPress('T')) {
			bool endFlg = false;
			for (int x = startX; x < endX; x++) {
				for (int y = startY; y < endY; y++) {
					float leftX = this->mapChip[x][y]->transform.position.x - this->mapChip[x][y]->transform.size.x / 2;
					float topY = this->mapChip[x][y]->transform.position.y + this->mapChip[x][y]->transform.size.y / 2;
					float rightX = leftX + this->mapChip[x][y]->transform.size.x;
					float bottomY = topY - this->mapChip[x][y]->transform.size.y;

					if (this->cursor->transform.position.x > leftX && this->cursor->transform.position.x < rightX) {
						if (this->cursor->transform.position.y > bottomY && this->cursor->transform.position.y < topY) {
							*this->anchor[this->mapPointX][this->mapPointY] = this->mapChip[x][y]->transform.position;
							this->anchorObject->transform.position = *this->anchor[this->mapPointX][this->mapPointY];
							endFlg = true;
						}
					}

				}
				if (endFlg) {
					break;
				}
			}
		}
		if (Input_GetKeyPress('0')) {
			if (this->setMode == 0) {
				CObjGene::SetEnemyParameter(this->enemy[this->mapPointX][this->mapPointY][0], this->enemyTag, this->cursor->transform.position.x, this->cursor->transform.position.y);
			}
			else {
				float posX = ((int)(this->cursor->transform.position.x / MAP_CHIP_SIZE) * MAP_CHIP_SIZE) + (MAP_CHIP_SIZE / 2);
				float posY = ((int)(this->cursor->transform.position.y / MAP_CHIP_SIZE) * MAP_CHIP_SIZE) + (MAP_CHIP_SIZE / 2);
				CObjGene::SetItemParameter(this->item[this->mapPointX][this->mapPointY][0], this->itemTag, posX, posY);
			}
		}
		if (Input_GetKeyPress('1')) {
			if (this->setMode == 0) {
				CObjGene::SetEnemyParameter(this->enemy[this->mapPointX][this->mapPointY][1], this->enemyTag, this->cursor->transform.position.x, this->cursor->transform.position.y);
			}
			else {
				float posX = ((int)(this->cursor->transform.position.x / MAP_CHIP_SIZE) * MAP_CHIP_SIZE) + (MAP_CHIP_SIZE / 2);
				float posY = ((int)(this->cursor->transform.position.y / MAP_CHIP_SIZE) * MAP_CHIP_SIZE) + (MAP_CHIP_SIZE / 2);
				CObjGene::SetItemParameter(this->item[this->mapPointX][this->mapPointY][1], this->itemTag, posX, posY);
			}
		}
		if (Input_GetKeyPress('2')) {
			if (this->setMode == 0) {
				CObjGene::SetEnemyParameter(this->enemy[this->mapPointX][this->mapPointY][2], this->enemyTag, this->cursor->transform.position.x, this->cursor->transform.position.y);
			}
			else {
				float posX = ((int)(this->cursor->transform.position.x / MAP_CHIP_SIZE) * MAP_CHIP_SIZE) + (MAP_CHIP_SIZE / 2);
				float posY = ((int)(this->cursor->transform.position.y / MAP_CHIP_SIZE) * MAP_CHIP_SIZE) + (MAP_CHIP_SIZE / 2);
				CObjGene::SetItemParameter(this->item[this->mapPointX][this->mapPointY][2], this->itemTag, posX, posY);
			}
		}
		if (Input_GetKeyPress('3')) {
			if (this->setMode == 0) {
				CObjGene::SetEnemyParameter(this->enemy[this->mapPointX][this->mapPointY][3], this->enemyTag, this->cursor->transform.position.x, this->cursor->transform.position.y);
			}
			else {
				float posX = ((int)(this->cursor->transform.position.x / MAP_CHIP_SIZE) * MAP_CHIP_SIZE) + (MAP_CHIP_SIZE / 2);
				float posY = ((int)(this->cursor->transform.position.y / MAP_CHIP_SIZE) * MAP_CHIP_SIZE) + (MAP_CHIP_SIZE / 2);
				CObjGene::SetItemParameter(this->item[this->mapPointX][this->mapPointY][3], this->itemTag, posX, posY);
			}
		}
		if (Input_GetKeyPress('4')) {
			if (this->setMode == 0) {
				CObjGene::SetEnemyParameter(this->enemy[this->mapPointX][this->mapPointY][4], this->enemyTag, this->cursor->transform.position.x, this->cursor->transform.position.y);
			}
			else {
				float posX = ((int)(this->cursor->transform.position.x / MAP_CHIP_SIZE) * MAP_CHIP_SIZE) + (MAP_CHIP_SIZE / 2);
				float posY = ((int)(this->cursor->transform.position.y / MAP_CHIP_SIZE) * MAP_CHIP_SIZE) + (MAP_CHIP_SIZE / 2);
				CObjGene::SetItemParameter(this->item[this->mapPointX][this->mapPointY][4], this->itemTag, posX, posY);
			}
		}
		if (Input_GetKeyPress('5')) {
			if (this->setMode == 0) {
				CObjGene::SetEnemyParameter(this->enemy[this->mapPointX][this->mapPointY][5], this->enemyTag, this->cursor->transform.position.x, this->cursor->transform.position.y);
			}
			else {
				float posX = ((int)(this->cursor->transform.position.x / MAP_CHIP_SIZE) * MAP_CHIP_SIZE) + (MAP_CHIP_SIZE / 2);
				float posY = ((int)(this->cursor->transform.position.y / MAP_CHIP_SIZE) * MAP_CHIP_SIZE) + (MAP_CHIP_SIZE / 2);
				CObjGene::SetItemParameter(this->item[this->mapPointX][this->mapPointY][5], this->itemTag, posX, posY);
			}
		}
		if (Input_GetKeyPress('6')) {
			if (this->setMode == 0) {
				CObjGene::SetEnemyParameter(this->enemy[this->mapPointX][this->mapPointY][6], this->enemyTag, this->cursor->transform.position.x, this->cursor->transform.position.y);
			}
			else {
				float posX = ((int)(this->cursor->transform.position.x / MAP_CHIP_SIZE) * MAP_CHIP_SIZE) + (MAP_CHIP_SIZE / 2);
				float posY = ((int)(this->cursor->transform.position.y / MAP_CHIP_SIZE) * MAP_CHIP_SIZE) + (MAP_CHIP_SIZE / 2);
				CObjGene::SetItemParameter(this->item[this->mapPointX][this->mapPointY][6], this->itemTag, posX, posY);
			}
		}
		if (Input_GetKeyPress('7')) {
			if (this->setMode == 0) {
				CObjGene::SetEnemyParameter(this->enemy[this->mapPointX][this->mapPointY][7], this->enemyTag, this->cursor->transform.position.x, this->cursor->transform.position.y);
			}
			else {
				float posX = ((int)(this->cursor->transform.position.x / MAP_CHIP_SIZE) * MAP_CHIP_SIZE) + (MAP_CHIP_SIZE / 2);
				float posY = ((int)(this->cursor->transform.position.y / MAP_CHIP_SIZE) * MAP_CHIP_SIZE) + (MAP_CHIP_SIZE / 2);
				CObjGene::SetItemParameter(this->item[this->mapPointX][this->mapPointY][7], this->itemTag, posX, posY);
			}
		}
		if (Input_GetKeyPress('8')) {
			if (this->setMode == 0) {
				CObjGene::SetEnemyParameter(this->enemy[this->mapPointX][this->mapPointY][8], this->enemyTag, this->cursor->transform.position.x, this->cursor->transform.position.y);
			}
			else {
				float posX = ((int)(this->cursor->transform.position.x / MAP_CHIP_SIZE) * MAP_CHIP_SIZE) + (MAP_CHIP_SIZE / 2);
				float posY = ((int)(this->cursor->transform.position.y / MAP_CHIP_SIZE) * MAP_CHIP_SIZE) + (MAP_CHIP_SIZE / 2);
				CObjGene::SetItemParameter(this->item[this->mapPointX][this->mapPointY][8], this->itemTag, posX, posY);
			}
		}
		if (Input_GetKeyPress('9')) {
			if (this->setMode == 0) {
				CObjGene::SetEnemyParameter(this->enemy[this->mapPointX][this->mapPointY][9], this->enemyTag, this->cursor->transform.position.x, this->cursor->transform.position.y);
			}
			else {
				float posX = ((int)(this->cursor->transform.position.x / MAP_CHIP_SIZE) * MAP_CHIP_SIZE) + (MAP_CHIP_SIZE / 2);
				float posY = ((int)(this->cursor->transform.position.y / MAP_CHIP_SIZE) * MAP_CHIP_SIZE) + (MAP_CHIP_SIZE / 2);
				CObjGene::SetItemParameter(this->item[this->mapPointX][this->mapPointY][9], this->itemTag, posX, posY);
			}
		}

		for (int x = startX; x < endX; x++) {
			for (int y = startY; y < endY; y++) {
				this->mapChip_Draw->SetVertex(this->mapChip[x][y]);
				this->mapChipHit_Draw->SetVertex(this->mapChipHit[x][y]);
			}
		}

		this->mapChip_Draw->DrawAct();
		this->mapChipHit_Draw->DrawAct();

		this->anchorObject->transform.position = *this->anchor[this->mapPointX][this->mapPointY];
		this->anchor_Draw->SetVertex(this->anchorObject);
		this->anchor_Draw->DrawAct();

		for (int index = 0; index < ITEM_MAX; index++) {
			this->item_Draw->SetVertex(this->item[this->mapPointX][this->mapPointY][index]);
		}
		this->item_Draw->DrawAct();

		for (int index = 0; index < ENEMY_MAX; index++) {
			this->enemy_Draw->SetVertex(this->enemy[this->mapPointX][this->mapPointY][index]);
		}
		this->enemy_Draw->DrawAct();

	}
	else if (this->mode == 1) {
		Float2 float2 = CDraw::camera;
		int chipPosX = float2.x / MAP_CHIP_SIZE;
		int chipPosY = float2.y / MAP_CHIP_SIZE;
		int startX = chipPosX - 10;
		int startY = chipPosY - 6;
		int endX = chipPosX + 11;
		int endY = chipPosY + 7;

		if (startX < 0) {
			startX = 0;
		}
		if (startY < 0) {
			startY = 0;
		}
		if (endX > MAPCHIP_NUM) {
			endX = MAPCHIP_NUM;
		}
		if (endY > MAPCHIP_NUM) {
			endY = MAPCHIP_NUM;
		}

		if (Input_GetKeyPress('G')) {
			bool endFlg = false;
			for (int x = startX; x < endX; x++) {
				for (int y = startY; y < endY; y++) {
					float leftX = this->mapChipMT[x][y]->transform.position.x - this->mapChipMT[x][y]->transform.size.x / 2;
					float topY = this->mapChipMT[x][y]->transform.position.y + this->mapChipMT[x][y]->transform.size.y / 2;
					float rightX = leftX + this->mapChipMT[x][y]->transform.size.x;
					float bottomY = topY - this->mapChipMT[x][y]->transform.size.y;

					if (this->cursor->transform.position.x > leftX && this->cursor->transform.position.x < rightX) {
						if (this->cursor->transform.position.y > bottomY && this->cursor->transform.position.y < topY) {
							this->animX = this->mapChipMT[x][y]->animator.frameX;
							this->animY = this->mapChipMT[x][y]->animator.frameY;
							endFlg = true;
						}
					}

				}
				if (endFlg) {
					break;
				}
			}
		}

		for (int x = startX; x < endX; x++) {
			for (int y = startY; y < endY; y++) {
				this->mapChipMT_Draw->SetVertex(this->mapChipMT[x][y]);
			}
		}

		this->mapChipMT_Draw->DrawAct();
	}
	else if (this->mode == 2) {

		if (Input_GetKeyPress('0')) {
			for (int index = 0; index < ITEMMTMAX; index++) {
				float leftX = this->itemMT[index]->transform.position.x - this->itemMT[index]->transform.size.x / 2;
				float topY = this->itemMT[index]->transform.position.y + this->itemMT[index]->transform.size.y / 2;
				float rightX = leftX + this->itemMT[index]->transform.size.x;
				float bottomY = topY - this->itemMT[index]->transform.size.y;
				if (this->cursor->transform.position.x > leftX && this->cursor->transform.position.x < rightX) {
					if (this->cursor->transform.position.y > bottomY && this->cursor->transform.position.y < topY) {
						this->itemTag = this->itemMT[index]->tag;
					}
				}
			}
		}

		for (int index = 0; index < ITEMMTMAX; index++) {
			this->itemMT_Draw->SetVertex(this->itemMT[index]);
		}
		this->itemMT_Draw->DrawAct();
	}
	else {

		if (Input_GetKeyPress('0')) {
			for (int index = 0; index < ENEMYMTMAX; index++) {
				float leftX = this->enemyMT[index]->transform.position.x - this->enemyMT[index]->transform.size.x / 2;
				float topY = this->enemyMT[index]->transform.position.y + this->enemyMT[index]->transform.size.y / 2;
				float rightX = leftX + this->enemyMT[index]->transform.size.x;
				float bottomY = topY - this->enemyMT[index]->transform.size.y;
				if (this->cursor->transform.position.x > leftX && this->cursor->transform.position.x < rightX) {
					if (this->cursor->transform.position.y > bottomY && this->cursor->transform.position.y < topY) {
						this->enemyTag = this->enemyMT[index]->tag;
						if (this->enemyTag == TAG_ENEMY_DESTROY) {
							this->enemyTag = TAG_ENEMY_NULL;
						}
					}
				}
			}
		}
		if (Input_GetKeyPress('1')) {
			for (int index = 0; index < ENEMYMTMAX; index++) {
				float leftX = this->enemyMT[index]->transform.position.x - this->enemyMT[index]->transform.size.x / 2;
				float topY = this->enemyMT[index]->transform.position.y + this->enemyMT[index]->transform.size.y / 2;
				float rightX = leftX + this->enemyMT[index]->transform.size.x;
				float bottomY = topY - this->enemyMT[index]->transform.size.y;
				if (this->cursor->transform.position.x > leftX && this->cursor->transform.position.x < rightX) {
					if (this->cursor->transform.position.y > bottomY && this->cursor->transform.position.y < topY) {
						this->enemyTag = this->enemyMT[index]->tag;
					}
				}
			}

		}

		for (int index = 0; index < ENEMYMTMAX; index++) {
			this->enemyMT_Draw->SetVertex(this->enemyMT[index]);
		}
		this->enemyMT_Draw->DrawAct();
	}

	if (!Input_GetKeyPress('F')) {
		this->cursor_Draw->SetVertex(this->cursor);
		this->cursor_Draw->DrawAct();
	}

	if (Input_GetKeyPress(VK_CONTROL) && Input_GetKeyPress('S')) {
		FILE *fp;
		fopen_s(&fp, mapFilePath[filePath], "w");

		for (int y = 0; y < MAP_SIZE_Y; y++) {
			for (int x = 0; x < MAP_SIZE_X; x++) {
				fprintf(fp, "%d,%d\n", (this->mapChip[x][y]->animator.frameX + this->mapChip[x][y]->animator.frameY * MAPCHIP_NUM), this->mapChipHit[x][y]->animator.frameX + (this->mapChipHit[x][y]->animator.frameY * 6));
			}
		}

		fclose(fp);

		fopen_s(&fp, anchorFilePath[filePath], "w");

		for (int y = 0; y < MAP_SIZE_Y / MAP_ONE_SIZE_Y; y++) {
			for (int x = 0; x < MAP_SIZE_X / MAP_ONE_SIZE_X; x++) {
				fprintf(fp, "%d,%d\n", (int)this->anchor[x][y]->x, (int)this->anchor[x][y]->y);
			}
		}

		fclose(fp);

		fopen_s(&fp, enemyFilePath[filePath], "w");

		for (int y = 0; y < MAP_SIZE_Y / MAP_ONE_SIZE_Y; y++) {
			for (int x = 0; x < MAP_SIZE_X / MAP_ONE_SIZE_X; x++) {
				for (int index = 0; index < ENEMY_MAX; index++) {
					fprintf(fp, "%d,%d,%d\n", this->enemy[x][y][index]->tag, (int)this->enemy[x][y][index]->transform.position.x, (int)this->enemy[x][y][index]->transform.position.y);
				}
			}
		}

		fclose(fp);

		fopen_s(&fp, itemFilePath[filePath], "w");

		for (int y = 0; y < MAP_SIZE_Y / MAP_ONE_SIZE_Y; y++) {
			for (int x = 0; x < MAP_SIZE_X / MAP_ONE_SIZE_X; x++) {
				for (int index = 0; index < ITEM_MAX; index++) {
					fprintf(fp, "%d,%d,%d\n", this->item[x][y][index]->tag, (int)this->item[x][y][index]->transform.position.x, (int)this->item[x][y][index]->transform.position.y);
				}
			}
		}

		fclose(fp);

		gameOrder = GAME_ORDER_NONE;
	}

	// ダブル・バッファのディスプレイ領域へのコピー命令
	Direct3D_GetSwapChain()->Present(0, 0);

	return gameOrder;
}

void CPlay::UnInit() {
	delete this->mapChipHit_Draw;
	for (int x = 0; x < MAP_SIZE_X; x++) {
		for (int y = 0; y < MAP_SIZE_Y; y++) {
			delete this->mapChipHit[x][y];
		}
	}

	delete this->mapChip_Draw;
	for (int x = 0; x < MAP_SIZE_X; x++) {
		for (int y = 0; y < MAP_SIZE_Y; y++) {
			delete this->mapChip[x][y];
		}
	}

	delete this->mapChipMT_Draw;
	for (int x = 0; x < MAPCHIP_NUM; x++) {
		for (int y = 0; y < MAPCHIP_NUM; y++) {
			delete this->mapChipMT[x][y];
		}
	}

	delete this->cursor_Draw;
	delete this->cursor;

	delete this->anchor_Draw;
	delete this->anchorObject;
	for (int y = 0; y < MAP_SIZE_Y / MAP_ONE_SIZE_Y; y++) {
		for (int x = 0; x < MAP_SIZE_X / MAP_ONE_SIZE_X; x++) {
			delete this->anchor[x][y];
		}
	}

	for (int x = 0; x < MAP_SIZE_X / MAP_ONE_SIZE_X; x++) {
		for (int y = 0; y < MAP_SIZE_Y / MAP_ONE_SIZE_Y; y++) {
			for (int index = 0; index < ENEMY_MAX; index++) {
				delete this->enemy[x][y][index];
			}
		}
	}
	delete this->enemy_Draw;

	for (int x = 0; x < MAP_SIZE_X / MAP_ONE_SIZE_X; x++) {
		for (int y = 0; y < MAP_SIZE_Y / MAP_ONE_SIZE_Y; y++) {
			for (int index = 0; index < ITEM_MAX; index++) {
				delete this->item[x][y][index];
			}
		}
	}
	delete this->item_Draw;

	for (int index = 0; index < ENEMYMTMAX; index++) {
		delete this->enemyMT[index];
	}
	delete this->enemyMT_Draw;

	for (int index = 0; index < ITEMMTMAX; index++) {
		delete this->itemMT[index];
	}
	delete this->itemMT_Draw;

}

#pragma endregion

#pragma region // ゲームの結果画面

bool CResult::Init() {
	bool isSuccess;

	return true;
}

int CResult::Update() {
	int gameOrder = GAME_ORDER_CONTINUE;

	Input_Update();  // このゲームで使うキーの押下状態を調べて保存

	return gameOrder;
}

void CResult::UnInit() {
}

#pragma endregion

#pragma region // CGame (ゲーム全体)

CGame::CGame(const HWND *hWnd) {
	this->pGameMode[GAME_MODE_TITLE] = new CTitle;
	this->pGameMode[GAME_MODE_PLAY] = new CPlay;
	this->pGameMode[GAME_MODE_RESULT] = new CResult;

	for (int index = 0; index < GAME_MODE_NUM; index++) {
		this->pGameMode[index]->SethWnd(hWnd);
	}

	this->isInit = false;
	this->gameOrder = GAME_ORDER_NONE;
	this->gameMode = GAME_MODE_PLAY;
}

CGame::~CGame() {
	for (int index = 0; index < GAME_MODE_NUM; index++) {
		delete this->pGameMode[index];
	}
}

bool CGame::Update() {
	bool isContinue = true;

	if (!this->isInit) {
		isContinue = this->pGameMode[this->gameMode]->Init();
		this->isInit = true;
	}
	else {
		this->gameOrder = this->pGameMode[this->gameMode]->Update();
		if (!(this->gameOrder & GAME_ORDER_CONTINUE)) {
			this->pGameMode[this->gameMode]->UnInit();
			this->isInit = false;

			if (this->gameOrder & GAME_ORDER_MODECHANGE_TITLE) {
				this->gameMode = GAME_MODE_TITLE;
			}
			else if (this->gameOrder & GAME_ORDER_MODECHANGE_PLAY) {
				this->gameMode = GAME_MODE_PLAY;
			}
			else if (this->gameOrder & GAME_ORDER_MODECHANGE_RESULT) {
				this->gameMode = GAME_MODE_RESULT;
			}
			else {
				isContinue = false;
			}
		}
	}

	return isContinue;
}

#pragma endregion

