#include "input.h"
#include <Windows.h>


#define MAX_KEYS  256

static short gOldKeys[MAX_KEYS];
static short gKeys[MAX_KEYS];

void Input_Update()
{
	// 前のフレームのキー状態を保存
	memcpy_s(gOldKeys, sizeof(gOldKeys), gKeys, sizeof(gKeys));

	for (int i = 0; i < MAX_KEYS; i++) {
		gKeys[i] = GetAsyncKeyState(i);
	}

	// 現在フレームのキー状態を取得
	//gKeys[VK_UP] = GetAsyncKeyState(VK_UP);
	//gKeys[VK_DOWN] = GetAsyncKeyState(VK_DOWN);
	//gKeys[VK_LEFT] = GetAsyncKeyState(VK_LEFT);
	//gKeys[VK_RIGHT] = GetAsyncKeyState(VK_RIGHT);
	//gKeys[VK_LBUTTON] = GetAsyncKeyState(VK_LBUTTON);
	//gKeys[VK_RBUTTON] = GetAsyncKeyState(VK_RBUTTON);
	//gKeys[VK_SHIFT] = GetAsyncKeyState(VK_SHIFT);
	//gKeys[VK_RETURN] = GetAsyncKeyState(VK_RETURN);
	//gKeys['A'] = GetAsyncKeyState('A');
	//gKeys['D'] = GetAsyncKeyState('D');
	//gKeys['W'] = GetAsyncKeyState('W');
	//gKeys['S'] = GetAsyncKeyState('S');
	//gKeys['F'] = GetAsyncKeyState('F');
	//gKeys['G'] = GetAsyncKeyState('G');
	//gKeys['H'] = GetAsyncKeyState('H');
	//gKeys['M'] = GetAsyncKeyState('M');
	//gKeys['J'] = GetAsyncKeyState('J');
	//gKeys['V'] = GetAsyncKeyState('V');
	//gKeys['T'] = GetAsyncKeyState('T');
	//gKeys['0'] = GetAsyncKeyState('0');
	//gKeys['1'] = GetAsyncKeyState('1');
	//gKeys['2'] = GetAsyncKeyState('2');
	//gKeys['3'] = GetAsyncKeyState('3');
	//gKeys['4'] = GetAsyncKeyState('4');
	//gKeys['5'] = GetAsyncKeyState('5');
	//gKeys['6'] = GetAsyncKeyState('6');
	//gKeys['7'] = GetAsyncKeyState('7');
	//gKeys['8'] = GetAsyncKeyState('8');
	//gKeys['9'] = GetAsyncKeyState('9');
	//gKeys['E'] = GetAsyncKeyState('E');
	//gKeys['I'] = GetAsyncKeyState('I');
}

bool Input_GetKeyPress(int vkey)
{
	return gKeys[vkey] & 0x8000;
}

bool Input_GetKeyTrigger(int vkey)
{
	return (gKeys[vkey] & 0x8000) != 0 && (gOldKeys[vkey] & 0x8000) == 0;
}
