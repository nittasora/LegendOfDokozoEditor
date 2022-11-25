//*****************************************************************************
// DX21�@�T���v���\�[�X
// WinMain�֐���WndProc�֐�
//*****************************************************************************

#undef UNICODE  // Unicode�ł͂Ȃ��A�}���`�o�C�g�������g��

#include "CGame.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define	CLASS_NAME		"�T���v��"				// �E�C���h�E�N���X�̖��O
#define WINDOW_NAME		"�X�P���g���v���O����"	// �E�B���h�E�̖��O

//*****************************************************************************
// �֐��̃v���g�^�C�v�錾
//*****************************************************************************

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


//=============================================================================
// ���C���֐�
//  (WINAPI : Win32API�֐����Ăяo�����̋K��)
//  hInstance     : ���̃A�v���P�[�V�����̃C���X�^���X�n���h��(���ʎq)
//  hPrevInstance : ���NULL(16bit����̖��c��)
//  lpCmdLine     : �R�}���h���C������󂯎���������ւ̃|�C���^
//  nCmdShow      : �A�v���P�[�V�����̏����E�C���h�E�\�����@�̎w��
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				// WNDCLASSEX�̃������T�C�Y���w��
		CS_CLASSDC,						// �\������E�C���h�E�̃X�^�C����ݒ�
		WndProc,						// �E�B���h�E�v���V�[�W���̃A�h���X(�֐���)���w��
		0,								// �ʏ�͎g�p���Ȃ��̂�"0"���w��
		0,								// �ʏ�͎g�p���Ȃ��̂�"0"���w��
		hInstance,						// WinMain�̃p�����[�^�̃C���X�^���X�n���h����ݒ�
		NULL,							// �g�p����A�C�R�����w��(Windows�������Ă���A�C�R�����g���Ȃ�NULL)
		LoadCursor(NULL, IDC_ARROW),	// �}�E�X�J�[�\�����w��
		(HBRUSH)(COLOR_WINDOW + 1),		// �E�C���h�E�̃N���C�A���g�̈�̔w�i�F��ݒ�
		NULL,							// Window�ɂ��郁�j���[��ݒ�
		CLASS_NAME,						// �E�C���h�E�N���X�̖��O
		NULL							// �������A�C�R�����ݒ肳�ꂽ�ꍇ�̏����L�q
	};

	// �E�B���h�E�N���X�̓o�^
	RegisterClassExA(&wcex);

	// �E�C���h�E���쐬
	HWND hWnd = CreateWindowEx(0,						// �g���E�B���h�E�X�^�C��
		CLASS_NAME,				// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,			// �E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,	// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,			// �E�B���h�E�̍���w���W
		CW_USEDEFAULT,			// �E�B���h�E�̍���x���W 
		SCREEN_WIDTH,			// �E�B���h�E�̕�
		SCREEN_HEIGHT,			// �E�B���h�E�̍���
		NULL,					// �e�E�B���h�E�̃n���h��
		NULL,					// ���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,				// �C���X�^���X�n���h��
		NULL);					// �E�B���h�E�쐬�f�[�^

	// Direct3D�̏������������Ăяo��
	HRESULT hr = Direct3D_Initialize(hWnd);

	if (FAILED(hr)) {
		MessageBoxA(hWnd, "Direct3D�̏������Ɏ��s", "�G���[", MB_OK | MB_ICONERROR);
		goto INIT_ERROR;
	}

	//	hr = Input_Initialize(hInstance, hWnd);

	if (FAILED(hr)) {
		MessageBoxA(hWnd, "Direct Input�̏������Ɏ��s", "�G���[", MB_OK | MB_ICONERROR);
		goto INIT_ERROR;
	}

	// �E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);	// �w�肳�ꂽ�E�B���h�E�̕\����Ԃ�ݒ�(�E�B���h�E��\��)
	UpdateWindow(hWnd);			// �E�B���h�E�̏�Ԃ𒼂��ɔ��f(�E�B���h�E�̃N���C�A���g�̈���X�V)

	BOOL isSucceed;
	// �Q�[���̏������������Ăяo��
	//isSucceed = Game_Initialize();

	CGame *_CGame;
	_CGame = new CGame(&hWnd);

	//if (isSucceed == FALSE) {
	//	MessageBoxA(hWnd, "Game�̏������Ɏ��s", "�G���[", MB_OK | MB_ICONERROR);
	//	goto INIT_ERROR;
	//}

	MSG msg;

	// ���b�Z�[�W���[�v�@���@�Q�[���̃��C�����[�v
	// ��P�����F���b�Z�[�W���
	// ��Q�����F�E�B���h�E�̃n���h��
	// ��R�����F�ŏ��̃��b�Z�[�W
	// ��S�����F�Ō�̃��b�Z�[�W
	while (true) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) != 0)
		{
			if (msg.message == WM_QUIT) {
				break;
			}
			else {
				// �Ăяo�����X���b�h�̃��b�Z�[�W�L���[���烁�b�Z�[�W���擾
				TranslateMessage(&msg);					// ���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);					// �E�B���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else {  // ���b�Z�[�W�������������Ă��Ȃ���
			// ���@�Q�[���Ɋւ���v���O�����������ꏊ

			// 60FPS�Ȃ��16�~���b�ɂP��Aif������������
			if (GameTimer_ReachedNextFrame() == TRUE) {
				//	Input_Update();
				if (!_CGame->Update()) {
					break;
				}
			}
			// ���@�Q�[���Ɋւ���v���O�����������ꏊ
		}
	}

	delete _CGame;

INIT_ERROR:
	//	Input_Release();

		// Direct3D�̊J���������Ăяo��
	Direct3D_Release();

	// �E�B���h�E�N���X�̓o�^������
	//  ��P�����F�E�C���h�E�N���X��
	//  ��Q�����F�A�v���P�[�V�����C���X�^���X�̃n���h��
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// �E�C���h�E�v���V�[�W��
//  (CALLBACK : Win32API�֐����Ăяo�����̋K��)
//  hWnd   : �E�B���h�E�̃n���h��
//  uMsg   : ���b�Z�[�W�̎��ʎq
//  wParam : ���b�Z�[�W�̍ŏ��̃p�����[�^
//  lParam : ���b�Z�[�W��2�Ԗڂ̃p�����[�^
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int sts;
	switch (uMsg)
	{
	case WM_DESTROY:		// �E�B���h�E�j���̃��b�Z�[�W
		PostQuitMessage(0);			// "WM_QUIT"���b�Z�[�W��Ԃ��@���@�A�v���I��
		break;

	case WM_KEYDOWN:  // �����L�[�������ꂽ��
		switch (wParam)
		{
		case VK_ESCAPE:  // ESC�L�[��������
			int sts = MessageBoxA(hWnd, "�I�����܂���?", "�I���m�F", MB_YESNO);
			if (sts == IDYES) {
				DestroyWindow(hWnd);  // �E�C���h�E���I��������֐��Ăяo��
			}
			break;
		}
		break;

	case WM_CLOSE:  // x�{�^���������ꂽ��
		sts = MessageBoxA(hWnd, "�I�����܂���?", "�I���m�F", MB_YESNO);
		if (sts == IDYES) {
			DestroyWindow(hWnd);  // �E�C���h�E���I��������֐��Ăяo��
		}
		break;

	case WM_ACTIVATE:  // �E�C���h�E���A�N�e�B�u�܂��͔�A�N�e�B�u�ɕω������ꍇ
		if (LOWORD(wParam) != WA_INACTIVE) {  // �A�N�e�B�u�ɂȂ����ꍇ
			GameTimer_OnResume();
		}
		break;

	case WM_EXITSIZEMOVE: // �E�C���h�E�̃T�C�Y�ύX�܂��͈ړ������������ꍇ
		GameTimer_OnResume();
		break;

	default:
		// ���case�ȊO�̏ꍇ�̏��������s
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return 0;
}
