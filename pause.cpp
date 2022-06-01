//================================================
//
//C++_STG(��)[pause.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "pause.h"
#include "input.h"
#include "game.h"
#include "sound.h"
#include "fade.h"
#include "mode.h"

//***************************
//�}�N����`
//***************************
namespace
{
const int NUM_PAUSE			= 4;		//�|�[�Y�̎��
const int PAUSEMENU_WIDTH	= 300;		//�|�[�Y���j���[�̕�
const int PAUSEMENU_HEIGHT	= 100;		//�|�[�Y���j���[�̍���
const int PAUSEMENU_SPACE	= 220;		//�|�[�Y���j���[�̊Ԋu
const int PAUSE_WIDTH		= 200;		//�|�[�Y�̕�
const int PAUSE_HEIGHT		= 200;		//�|�[�Y�̍���
}//namespace�͂����܂�

//***************************
//�X�^�e�B�b�N�ϐ�
//***************************
namespace
{
LPDIRECT3DTEXTURE9		s_apTexture[NUM_PAUSE];			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffPause = NULL;			//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffPauseMenu = NULL;		//���_�o�b�t�@�ւ̃|�C���^
PAUSE_MENU				s_pauseMenu;					//�|�[�Y���j���[
PauseMenu				s_aPauseMenu[PAUSE_MENU_MAX];	//�|�[�Y���j���[�̏��
D3DXVECTOR3				s_posPause;						//�|�[�Y�̈ʒu
}//namespace�͂����܂�

//***************************
//�v���g�^�C�v�錾
//***************************
namespace
{
void SelectMenu(VERTEX_2D *pVtx, PauseMenu *pPM);
}//namespace�͂����܂�

//================================================
//�|�[�Y�̏���������
//================================================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	VERTEX_2D *pVtx;							//���_���ւ̃|�C���^

	//�e�N�X�`���|�C���^�̏�����
	memset(s_apTexture, NULL, sizeof(s_apTexture));

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/Back_To_Game.png",
								&s_apTexture[0]);

	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/Restart.png",
								&s_apTexture[1]);

	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/Back_To_Title.png",
								&s_apTexture[2]);

	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/pause100.png",
								&s_apTexture[3]);

	//���̏�����
	for (int i = 0; i < PAUSE_MENU_MAX; i++)
	{
		float fPosX = (float)(SCREEN_WIDTH / 2);				//�|�[�Y���j���[�̈ʒu( X )
		float fPosY = (float)(150.0f + (i * PAUSEMENU_SPACE));	//�|�[�Y���j���[�̈ʒu( Y )

		s_aPauseMenu[i].pos = D3DXVECTOR3(fPosX, fPosY, 0.0f);
		s_aPauseMenu[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//�ϐ��̏�����
	s_pauseMenu = PAUSE_MENU_CONTINUE;					//�|�[�Y���j���[
	s_posPause	= D3DXVECTOR3(640.0f, 360.0f, 0.0f);	//�|�[�Y�̈ʒu

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&s_pVtxBuffPause,
								NULL);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * PAUSE_MENU_MAX,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&s_pVtxBuffPauseMenu,
								NULL);

	/********************* �������|���S�� & �|�[�Y�w�i *********************/

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < 2; i++)
	{
		if (i == 0)
		{//�|�[�Y�̔������|���S��
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		}
		else if (i == 1)
		{//�|�[�Y
			//���_���W�̐ݒ�
			float fLeft		= (s_posPause.x - PAUSE_WIDTH);
			float fRight	= (s_posPause.x + PAUSE_WIDTH);
			float fTop		= (s_posPause.y - PAUSE_HEIGHT);
			float fBottom	= (s_posPause.y + PAUSE_HEIGHT);

			pVtx[0].pos = D3DXVECTOR3(fLeft,  fTop,	   0.0f);
			pVtx[1].pos = D3DXVECTOR3(fRight, fTop,	   0.0f);
			pVtx[2].pos = D3DXVECTOR3(fLeft,  fBottom, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(fRight, fBottom, 0.0f);
		}

		//rhw�̐ݒ�
		SetRhw(pVtx, 1.0f);

		if (i == 0)
		{//�|�[�Y�̔������|���S��
			//���_�J���[�̐ݒ�
			SetCol2D(pVtx, 0.0f, 0.0f, 0.0f, 0.75f);
		}
		else if (i == 1)
		{//�|�[�Y
			//���_�J���[�̐ݒ�
			SetCol2D(pVtx, 0.3f, 0.0f, 0.0f, 0.0f);
		}

		//�e�N�X�`�����W�̐ݒ�
		SetTex2D(pVtx, 0.0f, 1.0f, 0.0f, 1.0f);

		pVtx += 4;		//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	s_pVtxBuffPause->Unlock();

	/********************* �|�[�Y���j���[ *********************/

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < PAUSE_MENU_MAX; i++)
	{//�|�[�Y���j���[
		PauseMenu *pPM = &s_aPauseMenu[i];		//�|�C���^�ɕϐg

		//���_���W�̐ݒ�
		float fLeft		= (pPM->pos.x - PAUSEMENU_WIDTH);
		float fRight	= (pPM->pos.x + PAUSEMENU_WIDTH);
		float fTop		= (pPM->pos.y - PAUSEMENU_HEIGHT);
		float fBottom	= (pPM->pos.y + PAUSEMENU_HEIGHT);

		pVtx[0].pos = D3DXVECTOR3(fLeft,  fTop,	   0.0f);
		pVtx[1].pos = D3DXVECTOR3(fRight, fTop,	   0.0f);
		pVtx[2].pos = D3DXVECTOR3(fLeft,  fBottom, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(fRight, fBottom, 0.0f);

		//rhw�̐ݒ�
		SetRhw(pVtx, 1.0f);

		//���_�J���[�̐ݒ�
		SetCol2D(pVtx, 1.0f, 1.0f, 1.0f, 0.3f);

		//�e�N�X�`�����W�̐ݒ�
		SetTex2D(pVtx, 0.0f, 1.0f, 0.0f, 1.0f);

		pVtx += 4;		//�|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	s_pVtxBuffPauseMenu->Unlock();
}

//================================================
//�|�[�Y�̏I������
//================================================
void UninitPause(void)
{
	//�T�E���h�̒�~
	StopSound();

	/********************* �e�N�X�`���̔j�� *********************/

	for (int i = 0; i < NUM_PAUSE; i++)
	{
		if (s_apTexture[i] != NULL)
		{
			s_apTexture[i]->Release();
			s_apTexture[i] = NULL;
		}
	}

	/********************* ���_�o�b�t�@�̔j�� *********************/
	
	if (s_pVtxBuffPause != NULL)
	{//�������|���S�� & �|�[�Y�w�i
		s_pVtxBuffPause->Release();
		s_pVtxBuffPause = NULL;
	}

	if (s_pVtxBuffPauseMenu != NULL)
	{//�|�[�Y���j���[�̕�
		s_pVtxBuffPauseMenu->Release();
		s_pVtxBuffPauseMenu = NULL;
	}
}

//================================================
//�|�[�Y�̍X�V����
//================================================
void UpdatePause(void)
{
	VERTEX_2D *pVtx = NULL;							//���_���ւ̃|�C���^
	PauseMenu *pPM = &s_aPauseMenu[s_pauseMenu];	//�|�C���^�ɕϐg

	//�|�[�Y���j���[�̑I��
	SelectMenu(pVtx, pPM);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (s_pauseMenu * 4);		//�|�C���^���Y���̈ʒu�܂Ői�߂�

	//���_�J���[�̐ݒ�
	SetCol2D(pVtx, pPM->col.r, pPM->col.g, pPM->col.b, pPM->col.a);

	//���_�o�b�t�@���A�����b�N����
	s_pVtxBuffPauseMenu->Unlock();
}

//================================================
//�|�[�Y�̕`�揈��
//================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	/********************* �������|���S�� & �|�[�Y�w�i *********************/

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, s_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < 2; i++)
	{
		if (i == 0)
		{//�|�[�Y�̔������|���S��
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);
		}
		else if (i == 1)
		{//�|�[�Y
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, s_apTexture[3]);
		}

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
								i * 4,					//�`�悷��ŏ��̒��_�C���f�b�N�X
								2);						//�`�悷��v���~�e�B�u��
	}

	/********************* �|�[�Y���j���[�̕� *********************/

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, s_pVtxBuffPauseMenu, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < PAUSE_MENU_MAX; i++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, s_apTexture[i]);

		//�|�[�Y�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
								i * 4,					//�`�悷��ŏ��̒��_�C���f�b�N�X
								2);						//�`�悷��v���~�e�B�u��
	}
}

namespace
{
//------------------------------------------------
//�|�[�Y���j���[�̑I��
//------------------------------------------------
static void SelectMenu(VERTEX_2D *pVtx, PauseMenu *pPM)
{
	if (GetFade() != FADE_NONE)
	{//�t�F�[�h���Ă���Ƃ�
		return;
	}

	/* �t�F�[�h���Ă��Ȃ��Ƃ� */

	/********************* �I�𒆂̃��j���[�̐F��ς��� *********************/

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardTrigger(DIK_W))
	{//W�L�[�������ꂽ
		//�T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_SELECT);

		//���ɂ���
		pPM->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);

		pVtx += (s_pauseMenu * 4);		//�|�C���^���Y���̈ʒu�܂Ői�߂�

		 //���_�J���[�̐ݒ�
		SetCol2D(pVtx, pPM->col.r, pPM->col.g, pPM->col.b, pPM->col.a);

		//1���I��
		s_pauseMenu = (PAUSE_MENU)(((s_pauseMenu - 1) + 3) % 3);
	}

	if (GetKeyboardTrigger(DIK_S))
	{//S�L�[�������ꂽ
		//�T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_SELECT);

		//���ɂ���
		pPM->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);

		pVtx += (s_pauseMenu * 4);		//�|�C���^���Y���̈ʒu�܂Ői�߂�

		//���_�J���[�̐ݒ�
		SetCol2D(pVtx, pPM->col.r, pPM->col.g, pPM->col.b, pPM->col.a);

		//1����I��
		s_pauseMenu = (PAUSE_MENU)(((s_pauseMenu + 1) + 3) % 3);
	}

	//���_�o�b�t�@���A�����b�N����
	s_pVtxBuffPauseMenu->Unlock();

	pPM = &s_aPauseMenu[s_pauseMenu];	//�I�𒆂̃��j���[

	//�I�𕔕��̐F��ς���
	pPM->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	/********************* �I���������j���[���̏��� *********************/

	if (GetKeyboardTrigger(DIK_RETURN))
	{//Enter�L�[�������ꂽ
		switch (s_pauseMenu)
		{
		case PAUSE_MENU_CONTINUE:	//�Q�[���ɖ߂�
			//�T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_SE_CANCEL);

			//�|�[�Y����
			SetEnablePause(false);
			break;

		case PAUSE_MENU_RETRY:		//�Q�[������蒼��
			//�T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_SE_DECIDE);

			//�Q�[����ʂɈڍs
			ChangeMode(MODE_GAME);
			break;

		case PAUSE_MENU_QUIT:		//�^�C�g����ʂɖ߂�
			//�T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_SE_DECIDE);

			//�^�C�g����ʂɈڍs
			ChangeMode(MODE_TITLE);
			break;
		}
	}
}
}//namespace�͂����܂�