//================================================
//
//C++_STG(��)[main.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "main.h"
#include "input.h"

#include "camera.h"
#include "polygon.h"
#include "player.h"

#include "fade.h"
#include "title.h"
#include "mode.h"
#include "sound.h"

#include <stdio.h>

//================================================
//�}�N����`
//================================================
#define CLASS_NAME		"WindowsClass"	//�E�C���h�E�N���X�̖��O
#define WINDOW_NAME		"C++_STG(��)"	//�E�C���h�E�̖��O(�L���v�V�����ɕ\��)

//================================================
//�X�^�e�B�b�N�ϐ�
//================================================
static LPDIRECT3D9			s_pD3D = NULL;				//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
static LPDIRECT3DDEVICE9	s_pD3DDevice = NULL;		//Direct3D�f�o�C�X�ւ̃|�C���^
static LPD3DXFONT			s_pFont = NULL;				//�t�H���g�ւ̃|�C���^
static int					s_nCountFPS = 0;			//FPS�J�E���^�[
static bool					s_bDebug;					//�f�o�b�O�\��
static bool					s_bWireFrame;				//���C���[�t���[��
static bool					s_bEnd;

//================================================
//�v���g�^�C�v�錾
//================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawDebug(void);

//================================================
//���C���֐�
//================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };		//��ʃT�C�Y�̍\����
	HWND hWnd;											//�E�C���h�E�n���h��(���ʎq)
	MSG msg;											//���b�Z�[�W���i�[����ϐ�
	DWORD dwCurrentTime;								//���ݎ���
	DWORD dwExecLastTime;								//�Ō�ɏ�����������
	DWORD dwFrameCount;									//�t���[���J�E���g
	DWORD dwFPSLastTime;								//�Ō��FPS���v����������

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,							//�E�C���h�E�̃X�^�C��
		WindowProc,							//�E�C���h�E�v���V�[�W��
		0,									//0�ɂ���(�ʏ�͎g�p���Ȃ�)
		0,									//0�ɂ���(�ʏ�͎g�p���Ȃ�)
		hInstance,							//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),		//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),			//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),			//�N���C�A���g�̈�̔w�i�F
		NULL,								//���j���[�o�[
		CLASS_NAME,							//�E�C���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION),		//�t�@�C���̃A�C�R��
	};

	//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�C���h�E�𐶐�
	hWnd = CreateWindowEx(0,							//�g���E�C���h�E�X�^�C��
							CLASS_NAME,					//�E�C���h�E�N���X�̖��O
							WINDOW_NAME,				//�E�C���h�E�̖��O
							WS_OVERLAPPEDWINDOW,		//�E�C���h�E�X�^�C��
							CW_USEDEFAULT,				//�E�C���h�E�̍���X���W
							CW_USEDEFAULT,				//�E�C���h�E�̍���Y���W
							(rect.right - rect.left),	//�E�C���h�E�̕�
							(rect.bottom - rect.top),	//�E�C���h�E�̍���
							NULL,						//�e�E�C���h�E�̃n���h��
							NULL,						//���j���[�n���h���܂��͎q�E�C���h�EID
							hInstance,					//�C���X�^���X�n���h��
							NULL);						//�E�C���h�E�쐬�f�[�^

	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//���������������s�����ꍇ
		return -1;
	}

	//����\��ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0;					//����������
	dwExecLastTime = timeGetTime();		//���ݎ������擾(�ۑ�)
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//�E�C���h�E�̕\��
	ShowWindow(hWnd,nCmdShow);		//�E�C���h�E�\����Ԃ�ݒ�
	UpdateWindow(hWnd);

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);		//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);		//�E�C���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();		//���ݎ������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				//FPS���v��
				s_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;		//FPS���v������������ۑ�
				dwFrameCount = 0;					//�t���[���J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60����1�b�o��
				dwExecLastTime = dwCurrentTime;		//�����J�n�̎���[���ݎ���]��ۑ�

				//�X�V����
				Update();

				//�`�揈��
				Draw();

				if (s_bEnd)
				{
					break;
				}

				dwFrameCount++;		//�t���[���J�E���g�����Z
			}
		}
	}

	//�I������
	Uninit();

	//����\��߂�
	timeEndPeriod(1);

	//�E�C���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME,wcex.hInstance);

	return (int)msg.wParam;
}

//================================================
//�E�C���h�E�v���V�[�W��
//================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };			//�E�C���h�E�̗̈�(�Z�`)


	if (s_bEnd)
	{
		//�E�C���h�E��j������ (WM_DESTROY���b�Z�[�W�𑗂�)
		DestroyWindow(hWnd);
	}

	switch (uMsg)
	{
	case WM_DESTROY:	//�E�C���h�E�j���̃��b�Z�[�W

		//WM_QOIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:	//�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:		//[ESC]�L�[�������ꂽ

			//�E�C���h�E��j������ (WM_DESTROY���b�Z�[�W�𑗂�)
			DestroyWindow(hWnd);
			break;
		}
		break;
	}

	if (EndGame())
	{//�Q�[���I���̍��}��������
		//�E�C���h�E��j�����ăQ�[���I��
		DestroyWindow(hWnd);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//�K��̏�����Ԃ�
}

//================================================
//����������
//================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	//�v���[���e�[�V�����p�����[�^

	//Direct3D�I�u�W�F�N�g�̐���
	s_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (s_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(s_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));		//�p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;							//�Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							//�Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;							//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;										//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//�_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;							//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//�f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;										//�E�C���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//�C���^�[�o��

	//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_�������n�[�h�E�F�A�ōs��)
	if (FAILED(s_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
									D3DDEVTYPE_HAL,
									hWnd,
									D3DCREATE_HARDWARE_VERTEXPROCESSING,
									&d3dpp,
									&s_pD3DDevice)))
	{
		//Direct3D�f�o�C�X�̐���(�`�揈���̓n�[�h�E�F�A�A���_������CPU�ōs��)
		if (FAILED(s_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
										D3DDEVTYPE_HAL,
										hWnd,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										&d3dpp,
										&s_pD3DDevice)))
		{
			//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_������CPU�ōs��)
			if (FAILED(s_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
											D3DDEVTYPE_REF,
											hWnd,
											D3DCREATE_SOFTWARE_VERTEXPROCESSING,
											&d3dpp,
											&s_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�^�[�g�̐ݒ�
	s_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	s_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	s_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	s_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	s_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	s_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	s_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	s_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	s_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	s_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	s_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�f�o�b�N�\���p�̃t�H���g�̐���
	D3DXCreateFont(s_pD3DDevice, 25, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
					OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
					"HGP�S�V�b�NE", &s_pFont);

	//���͌n�̏���������
	if (FAILED(InitInput(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�T�E���h
	InitSound(hWnd);

	// ���[�h�̏�����
	InitMode();

	//�t�F�[�h�̐ݒ�
	InitFade();

	// ���[�h�̕ύX
	ChangeMode(MODE_GAME);

	s_bWireFrame = false;	//��\��
	s_bDebug	 = true;	//�\��

	return S_OK;
}

//================================================
//�I������
//================================================
void Uninit(void)
{
	//���͌n
	UninitInput();

	//�T�E���h
	UninitSound();

	//���[�h
	UninitMode();

	//�t�F�[�h
	UninitFade();

	//�f�o�b�N�\���p�t�H���g�̔j��
	if (s_pFont != NULL)
	{
		s_pFont->Release();
		s_pFont = NULL;
	}

	//Direct3D�f�o�C�X�̔j��
	if (s_pD3DDevice != NULL)
	{
		s_pD3DDevice->Release();
		s_pD3DDevice = NULL;
	}

	//Direct3D�I�u�W�F�N�g�̔j��
	if (s_pD3D != NULL)
	{
		s_pD3D->Release();
		s_pD3D = NULL;
	}
}

//================================================
//�X�V����
//================================================
void Update(void)
{
	//�f�o�b�O�\���̐؂�ւ�
	if (GetKeyboardTrigger(DIK_F1))
	{//F1�L�[
		s_bDebug = s_bDebug ? false : true;		//�\��:��\���̐؂�ւ�
	}

	//���C���[�t���[���̐؂�ւ�
	if (GetKeyboardTrigger(DIK_F2))
	{//F2�L�[
		s_bWireFrame = s_bWireFrame ? false : true;		//�\��:��\���̐؂�ւ�

		if (s_bWireFrame)
		{//�\����
			//���C���[�t���[�����[�h�̐ݒ�
			s_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		}
		else
		{//��\����
			//���ɖ߂�
			s_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}
	}

	//���͌n
	UpdateInput();

	//���[�h
	UpdateMode();
	SetMode();

	//�t�F�[�h
	UpdateFade();
}

//================================================
//�`�揈��
//================================================
void Draw(void)
{
	//��ʃN���A(�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A)
	s_pD3DDevice->Clear(0, NULL,
						(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
						D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`�揈��
	if (SUCCEEDED(s_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ

		//���[�h
		DrawMode();
		
		//�t�F�[�h
		DrawFade();

#ifdef _DEBUG	//�f�o�b�O�̎�����

		if (s_bDebug)
		{
			//�f�o�b�O�\��
			DrawDebug();
		}

#endif

		//�`��I��
		s_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	s_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//================================================
//�f�o�C�X�̎擾
//================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return s_pD3DDevice;
}

//================================================
// �I���t���O
//================================================
bool* GetEnd(void)
{
	return &s_bEnd;
}

//================================================
//�f�o�b�O�\��
//================================================
void DrawDebug(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[4096];		//������
	int nLength = 0;		//�������𑪂���

	//FPS
	sprintf(&aStr[nLength], "FPS �F %2d\n", s_nCountFPS);
	nLength = (int)strlen(&aStr[0]);	//���݂̕��������擾

	/* �J���� */

	Camera* pC = GetCamera();	//�J�������̃|�C���^

	//���o��
	sprintf(&aStr[nLength], "\n[  �J����  ]\n");
	nLength = (int)strlen(&aStr[0]);

	//���_�̈ʒu
	sprintf(&aStr[nLength], " ���_�̈ʒu[ %.2f : %.2f : %.2f ] \n",pC->posV.x, pC->posV.y, pC->posV.z);
	nLength = (int)strlen(&aStr[0]);

	//���_�̌���
	sprintf(&aStr[nLength], " ���_�̌���[ %.2f : %.2f : %.2f ] \n", pC->rot.x, pC->rot.y, pC->rot.z);
	nLength = (int)strlen(&aStr[0]);

	/* �|���S�� */

	Polygon3D* pPol = GetPolygon();		//�|���S�����̃|�C���^

	//���o��
	sprintf(&aStr[nLength], "\n[  �|���S��  ]\n");
	nLength = (int)strlen(&aStr[0]);

	//�ʒu
	sprintf(&aStr[nLength], " �ʒu[ %.2f : %.2f : %.2f ] \n", pPol->pos.x, pPol->pos.y, pPol->pos.z);
	nLength = (int)strlen(&aStr[0]);

	/* �v���C���[ */

	//CPlayer* pPlayer = CPlayer::GetInfo();;		//�v���C���[���̃|�C���^
	//pPlayer->Init();

	////���o��
	//sprintf(&aStr[nLength], "\n[  �v���C���[  ]\n");
	//nLength = (int)strlen(&aStr[0]);

	////�ʒu
	//sprintf(&aStr[nLength], " �ʒu[ %.2f : %.2f : %.2f ] \n", pPlayer->m_pos.x, pPlayer->m_pos.y, pPlayer->m_pos.z);
	//nLength = (int)strlen(&aStr[0]);

	/* ���̑� */

	//���o��
	sprintf(&aStr[nLength], "\n[  ���̑�����  ]\n");
	nLength = (int)strlen(&aStr[0]);

	//�J�����̃��Z�b�g
	sprintf(&aStr[nLength], " Enter   �F �J�����̃��Z�b�g\n");
	nLength = (int)strlen(&aStr[0]);

	//�f�o�b�O�\���̐؂�ւ�
	sprintf(&aStr[nLength], " F1       �F �f�o�b�O�\��\n");
	nLength = (int)strlen(&aStr[0]);

	//�e�L�X�g�̕`��
	s_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(200, 0, 200, 255));
}

//================================================
//�e���_��rhw�̐ݒ�( ���_���[2D], float )
//================================================
void SetRhw(VERTEX_2D *pVtx, float fRhw)
{
	pVtx[0].rhw = fRhw;
	pVtx[1].rhw = fRhw;
	pVtx[2].rhw = fRhw;
	pVtx[3].rhw = fRhw;
}

//================================================
//���_�J���[�̐ݒ�( ���_���[2D], ��, ��, ��, ���l )
//================================================
void SetCol2D(VERTEX_2D *pVtx, float fRed, float fGreen, float fBlue, float fAlpha)
{
	pVtx[0].col = D3DXCOLOR(fRed, fGreen, fBlue, fAlpha);
	pVtx[1].col = D3DXCOLOR(fRed, fGreen, fBlue, fAlpha);
	pVtx[2].col = D3DXCOLOR(fRed, fGreen, fBlue, fAlpha);
	pVtx[3].col = D3DXCOLOR(fRed, fGreen, fBlue, fAlpha);
}

//================================================
//�e�N�X�`�����W�̐ݒ�( ���_���[2D], ��, �E, ��, �� )
//================================================
void SetTex2D(VERTEX_2D *pVtx, float fLeft, float fRight, float fUp, float fDown)
{
	pVtx[0].tex = D3DXVECTOR2(fLeft, fUp);
	pVtx[1].tex = D3DXVECTOR2(fRight, fUp);
	pVtx[2].tex = D3DXVECTOR2(fLeft, fDown);
	pVtx[3].tex = D3DXVECTOR2(fRight, fDown);
}