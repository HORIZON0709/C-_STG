//================================================
//
//C++_STG(��)[title.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "title.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "mode.h"

//***************************
//�񋓌^�̒�`
//***************************
namespace
{
/* �^�C�g���Ŏg�p����e�N�X�`���̎�� */
typedef enum
{
	TEX_TITLE_BG = 0,	//�w�i
	TEX_TITLE_LOGO,		//�^�C�g�����S
	TEX_TITLE_START,	//�Q�[���J�n
	TEX_TITLE_TUTORIAL,	//�`���[�g���A��
	TEX_TITLE_END,		//�Q�[���I��
	TEX_TITLE_MAX
}TEX_TITLE;

/* �^�C�g�����S�̏�� */
typedef enum
{
	TITLELOGO_POP = 0,	//�o�����
	TITLELOGO_NORMAL,	//�ʏ���
	TITLELOGO_MAX
}TITLELOGO;

/* �^�C�g�����j���[ */
typedef enum
{
	TITLE_MENU_START = 0,	//�Q�[���J�n
	TITLE_MENU_TUTORIAL,	//�`���[�g���A��
	TITLE_MENU_END,			//�Q�[���I��
	TITLE_MENU_MAX
}TITLE_MENU;
}//namespace�͂����܂�

 //***************************
 //�\���̂̒�`
 //***************************
namespace
{
/* �^�C�g�����j���[ */
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXCOLOR col;		//�F
}TitleMenu;
}//namespace�͂����܂�

//***************************
//�萔�̒�`
//***************************
namespace
{
/* �^�C�g�����j���[ */
const int	TITLE_MENU_SPACE		= 90;	//�Ԋu
const float TITLE_MENU_WIDTH	= 150.0f;	//��
const float TITLE_MENU_HEIGHT	= 75.0f;	//����
const float MENU_FADE_SPEED		= 0.015f;	//�_�ŃX�s�[�h(�ʏ�)
const float MENU_FADE_HIGHSPEED = 0.4f;		//�_�ŃX�s�[�h(����)

/* �^�C�g�����S */
const float LOGO_WIDTH	= 400.0f;	//��
const float LOGO_HEIGHT = 230.0f;	//����
const float LOGO_SPEED	= 3.0f;		//�X�s�[�h
}//namespace�͂����܂�

//***************************
//�X�^�e�B�b�N�ϐ�
//***************************
namespace
{
LPDIRECT3DTEXTURE9		s_apTexture[TEX_TITLE_MAX];		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	s_pVtxBuff = NULL;				//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	s_pVtxBuffTitleMenu = NULL;		//			"

/* �^�C�g�����j���[ */
TitleMenu	s_aTitleMenu[TITLE_MENU_MAX];	//�^�C�g�����j���[�̏��
TITLE_MENU	s_MenuType;						//�^�C�g�����j���[�̎��
FADE		s_fadeTitleMenu;				//�^�C�g�����j���[�̓_�ŏ��

/* �^�C�g�����S */
D3DXVECTOR3 s_posTitleLogo;			//�^�C�g�����S�̈ʒu
TITLELOGO	s_TitleLogo;			//�^�C�g�����S�̏��
bool		s_bGameEnd = false;		//�Q�[�����I�����邩�ǂ���
}//namespace�͂����܂�

//***************************
//�v���g�^�C�v�錾
//***************************
namespace
{
void UpdateNormal(void);
void UpdatePop(void);
void SelectMenu(VERTEX_2D *pVtx, TitleMenu *pTM);
void BlinkMenu(TitleMenu *pTM);
}//namespace�͂����܂�

//================================================
//�^�C�g���̏���������
//================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	VERTEX_2D *pVtx;							//���_���ւ̃|�C���^

	//�e�N�X�`���|�C���^�̏�����
	memset(s_apTexture, NULL, sizeof(s_apTexture));

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/Title_BG.png",
								&s_apTexture[TEX_TITLE_BG]);		//�w�i

	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/Title.png",
								&s_apTexture[TEX_TITLE_LOGO]);		//�^�C�g�����S

	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/GameStart.png",
								&s_apTexture[TEX_TITLE_START]);		//�Q�[���J�n

	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/Tutorial.png",
								&s_apTexture[TEX_TITLE_TUTORIAL]);	//�`���[�g���A��

	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/GameEnd.png",
								&s_apTexture[TEX_TITLE_END]);		//�Q�[���I��

	//���̏�����
	for (int i = 0; i < TITLE_MENU_MAX; i++)
	{
		float fPosX = (float)(SCREEN_WIDTH / 2);				//�^�C�g�����j���[�̈ʒu( X )
		float fPosY = (float)(480 + (i * TITLE_MENU_SPACE));		//�^�C�g�����j���[�̈ʒu( Y )

		s_aTitleMenu[i].pos = D3DXVECTOR3(fPosX, fPosY, 0.0f);
		s_aTitleMenu[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//�ϐ��̏�����
	s_MenuType		= TITLE_MENU_START;									//���j���[�^�C�v
	s_fadeTitleMenu	= FADE_IN;											//���j���[�̓_�ŏ��
	s_posTitleLogo  = D3DXVECTOR3((SCREEN_WIDTH / 2), -250.0f, 0.0f);	//�^�C�g�����S�̈ʒu
	s_TitleLogo		= TITLELOGO_POP;									//�^�C�g�����S�̏��

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&s_pVtxBuff,
								NULL);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TITLE_MENU_MAX,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&s_pVtxBuffTitleMenu,
								NULL);

	/********************* �w�i�摜 & �^�C�g�����S *********************/

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < 2; i++)
	{
		if (i == 0)
		{//�w�i
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		}
		else if (i == 1)
		{//�^�C�g�����S
			//���_���W�̐ݒ�
			float fLeft		= (s_posTitleLogo.x - LOGO_WIDTH);
			float fRight	= (s_posTitleLogo.x + LOGO_WIDTH);
			float fTop		= (s_posTitleLogo.y - LOGO_HEIGHT);
			float fBottom	= (s_posTitleLogo.y + LOGO_HEIGHT);

			pVtx[0].pos = D3DXVECTOR3(fLeft,  fTop,	   0.0f);
			pVtx[1].pos = D3DXVECTOR3(fRight, fTop,	   0.0f);
			pVtx[2].pos = D3DXVECTOR3(fLeft,  fBottom, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(fRight, fBottom, 0.0f);
		}

		//rhw�̐ݒ�
		SetRhw(pVtx, 1.0f);

		//���_�J���[�̐ݒ�
		SetCol2D(pVtx, 1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		SetTex2D(pVtx, 0.0f, 1.0f, 0.0f, 1.0f);

		pVtx += 4;		//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	s_pVtxBuff->Unlock();

	/********************* �^�C�g�����j���[ *********************/

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuffTitleMenu->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TITLE_MENU_MAX; i++)
	{//�^�C�g�����j���[
		TitleMenu *pTM = &s_aTitleMenu[i];		//�|�C���^�ɕϐg

		//���_���W�̐ݒ�
		float fLeft		= (pTM->pos.x - TITLE_MENU_WIDTH);
		float fRight	= (pTM->pos.x + TITLE_MENU_WIDTH);
		float fTop		= (pTM->pos.y - TITLE_MENU_HEIGHT);
		float fBottom	= (pTM->pos.y + TITLE_MENU_HEIGHT);

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
	s_pVtxBuffTitleMenu->Unlock();
}

//================================================
//�^�C�g���̏I������
//================================================
void UninitTitle(void)
{
	//�T�E���h�̒�~
	StopSound();

	/********************* �e�N�X�`���̔j�� *********************/

	for (int i = 0; i < TEX_TITLE_MAX; i++)
	{
		if (s_apTexture[i] != NULL)
		{
			s_apTexture[i]->Release();
			s_apTexture[i] = NULL;
		}
	}

	/********************* ���_�o�b�t�@�̔j�� *********************/

	if (s_pVtxBuff != NULL)
	{//�w�i�摜 & �^�C�g�����S
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}

	if (s_pVtxBuffTitleMenu != NULL)
	{//�^�C�g�����j���[
		s_pVtxBuffTitleMenu->Release();
		s_pVtxBuffTitleMenu = NULL;
	}
}

//================================================
//�^�C�g���̍X�V����
//================================================
void UpdateTitle(void)
{
	switch (s_TitleLogo)
	{//�^�C�g�����S�̏��
	case TITLELOGO_NORMAL:	//�ʏ���
		UpdateNormal();		//�ʏ��Ԃ̍X�V
		break;

	case TITLELOGO_POP:		//�o�����
		UpdatePop();	//�o����Ԃ̍X�V
		break;
	}
}

//================================================
//�^�C�g���̕`�揈��
//================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	/********************* �w�i�摜 & �^�C�g�����S *********************/

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < 2; i++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, s_apTexture[i]);
	
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
								i * 4,					//�`�悷��ŏ��̒��_�C���f�b�N�X
								2);						//�`�悷��v���~�e�B�u��
	}
	
	/********************* �^�C�g�����j���[ *********************/

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, s_pVtxBuffTitleMenu, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < (int)(TEX_TITLE_MAX - 2); i++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, s_apTexture[i + 2]);

		if (s_TitleLogo == TITLELOGO_NORMAL)
		{//�^�C�g�����S���ʏ��ԂɂȂ�����
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
									i * 4,					//�`�悷��ŏ��̒��_�C���f�b�N�X
									2);						//�`�悷��v���~�e�B�u��

		}
	}
}

//================================================
//�Q�[���I���̍��}
//================================================
bool EndGame(void)
{
	return s_bGameEnd;
}

namespace
{
//------------------------------------------------
//�ʏ��Ԃ̍X�V
//------------------------------------------------
static void UpdateNormal(void)
{
	VERTEX_2D *pVtx = NULL;							//���_���ւ̃|�C���^
	TitleMenu *pTM = &s_aTitleMenu[s_MenuType];		//�|�C���^�ɕϐg

	//�^�C�g�����j���[�̑I��
	SelectMenu(pVtx, pTM);

	//�^�C�g�����j���[�̓_��
	BlinkMenu(pTM);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuffTitleMenu->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (s_MenuType * 4);	//�|�C���^���Y���̈ʒu�܂Ői�߂�

	//���_�J���[�̐ݒ�
	SetCol2D(pVtx, pTM->col.r, pTM->col.g, pTM->col.b, pTM->col.a);

	//���_�o�b�t�@���A�����b�N����
	s_pVtxBuffTitleMenu->Unlock();
}

//------------------------------------------------
//�o����Ԃ̍X�V
//------------------------------------------------
static void UpdatePop(void)
{
	float fHomePos = (float)(SCREEN_HEIGHT / 6 * 1.9f);	//�^�C�g�����S�̒�ʒu

	//�^�C�g�����S�����X�ɍ~�낷
	s_posTitleLogo.y += LOGO_SPEED;

	if (s_posTitleLogo.y >= fHomePos || GetKeyboardTrigger(DIK_RETURN))
	{//��ʒu���z������ or Enter�L�[�������ꂽ��
		//��ʒu�ɂ���
		s_posTitleLogo.y = fHomePos;

		//�ʏ��Ԃɂ���
		s_TitleLogo = TITLELOGO_NORMAL;
	}

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4;		//�^�C�g�����S�ɂ���

	//���_���W�̍X�V
	float fLeft		= (s_posTitleLogo.x - LOGO_WIDTH);
	float fRight	= (s_posTitleLogo.x + LOGO_WIDTH);
	float fTop		= (s_posTitleLogo.y - LOGO_HEIGHT);
	float fBottom	= (s_posTitleLogo.y + LOGO_HEIGHT);

	pVtx[0].pos = D3DXVECTOR3(fLeft, fTop, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(fRight, fTop, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(fLeft, fBottom, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(fRight, fBottom, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	s_pVtxBuff->Unlock();
}

//------------------------------------------------
//�^�C�g�����j���[�̑I��
//------------------------------------------------
static void SelectMenu(VERTEX_2D *pVtx, TitleMenu *pTM)
{
	if (GetFade() != FADE_NONE)
	{//�t�F�[�h���Ă���Ƃ�
		return;
	}

	/* �t�F�[�h���Ă��Ȃ��Ƃ� */

	/********************* �I�𒆂̃��j���[�̐F��ς��� *********************/

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuffTitleMenu->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardTrigger(DIK_W))
	{//W�L�[�������ꂽ
		//�T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_SELECT);

		//���ɂ���
		pTM->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);

		pVtx += (s_MenuType * 4);		//�|�C���^���Y���̈ʒu�܂Ői�߂�

		 //���_�J���[�̐ݒ�
		SetCol2D(pVtx, pTM->col.r, pTM->col.g, pTM->col.b, pTM->col.a);

		//1���I��
		s_MenuType = (TITLE_MENU)(((s_MenuType - 1) + 3) % 3);
	}

	if (GetKeyboardTrigger(DIK_S))
	{//S�L�[�������ꂽ
		//�T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_SELECT);

		//���ɂ���
		pTM->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);

		pVtx += (s_MenuType * 4);		//�|�C���^���Y���̈ʒu�܂Ői�߂�

		//���_�J���[�̐ݒ�
		SetCol2D(pVtx, pTM->col.r, pTM->col.g, pTM->col.b, pTM->col.a);

		//1����I��
		s_MenuType = (TITLE_MENU)(((s_MenuType + 1) + 3) % 3);
	}

	//���_�o�b�t�@���A�����b�N����
	s_pVtxBuffTitleMenu->Unlock();

	pTM = &s_aTitleMenu[s_MenuType];	//�I�𒆂̃��j���[

	//�I�𕔕��̐F��ς���
	pTM->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	/********************* �I���������j���[���̏��� *********************/

	if (s_TitleLogo == TITLELOGO_NORMAL && GetKeyboardTrigger(DIK_RETURN))
	{//�^�C�g�����S���ʏ��� & Enter�L�[�������ꂽ
		switch (s_MenuType)
		{
		case TITLE_MENU_START:	//�Q�[���J�n
			//�T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_SE_DECIDE);

			//�Q�[����ʂɈڍs
			ChangeMode(MODE_GAME);
			break;

		case TITLE_MENU_TUTORIAL:	//�`���[�g���A��
			//�T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_SE_DECIDE);

			//�`���[�g���A����ʂɈڍs
			ChangeMode(MODE_TUTORIAL);
			break;

		case TITLE_MENU_END:	//�Q�[���I��

			//�Q�[���I���̍��}
			s_bGameEnd = true;
			bool* end = GetEnd();
			*end = true;
			break;
		}
	}
}

//------------------------------------------------
//�^�C�g�����j���[�̓_��
//------------------------------------------------
static void BlinkMenu(TitleMenu *pTM)
{
	if (GetFade() == FADE_NONE)
	{//�t�F�[�h���Ă��Ȃ�
		if (s_fadeTitleMenu == FADE_IN)
		{//�����ɂ���Ƃ�
			pTM->col.a -= MENU_FADE_SPEED;		//�����ɂ��Ă���

			if (pTM->col.a <= 0.0f)
			{//0.0f���߂�����
				pTM->col.a = 0.0f;				//0.0f�ɖ߂�
				s_fadeTitleMenu = FADE_OUT;		//�s�����ɂ����Ԃ�
			}
		}
		else if (s_fadeTitleMenu == FADE_OUT)
		{//�s�����ɂ���Ƃ�
			pTM->col.a += MENU_FADE_SPEED;		//�s�����ɂ��Ă���

			if (pTM->col.a >= 1.0f)
			{//1.0f���߂�����
				pTM->col.a = 1.0f;				//1.0f�ɖ߂�
				s_fadeTitleMenu = FADE_IN;		//�����ɂ����Ԃ�
			}
		}
	}
	else if (GetFade() == FADE_OUT)
	{//�t�F�[�h�A�E�g��Ԃ̂Ƃ�
		if (s_fadeTitleMenu == FADE_IN)
		{//�����ɂ���Ƃ�
			pTM->col.a -= MENU_FADE_HIGHSPEED;	//�����ɂ��Ă���

			if (pTM->col.a <= 0.0f)
			{//0.0f���߂�����
				pTM->col.a = 0.0f;				//0.0f�ɖ߂�
				s_fadeTitleMenu = FADE_OUT;		//�s�����ɂ����Ԃ�
			}
		}
		else if (s_fadeTitleMenu == FADE_OUT)
		{//�s�����ɂ���Ƃ�
			pTM->col.a += MENU_FADE_HIGHSPEED;	//�s�����ɂ��Ă���

			if (pTM->col.a >= 1.0f)
			{//1.0f���߂�����
				pTM->col.a = 1.0f;				//1.0f�ɖ߂�
				s_fadeTitleMenu = FADE_IN;		//�����ɂ����Ԃ�
			}
		}
	}
}
}//namespace�͂����܂�