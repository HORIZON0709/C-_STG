//================================================
//
//C++_STG(��)[game.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "game.h"

#include "player.h"
#include "pause.h"
#include "camera.h"
#include "light.h"
#include "polygon.h"
#include "time.h"
#include "bullet.h"

#include "input.h"
#include "mode.h"
#include "sound.h"

//***************************
//�萔�̒�`
//***************************
namespace
{
const int TIME_LIMIT = 100;		//��������
}//namespace�͂����܂�

//***************************
//�X�^�e�B�b�N�ϐ�
//***************************
namespace
{
GAMESTATE	s_gameState = GAMESTATE_NONE;	//�Q�[���̏��
int			s_nCounterGameState = 0;		//��ԊǗ��J�E���^�[
bool		s_pPause = false;				//�|�[�Y�����ǂ���
}//namespace�͂����܂�

//================================================
//�Q�[���̏���������
//================================================
void InitGame(void)
{
	CPlayer* pPlayer = nullptr;
	CBullet* pBullet = nullptr;

	InitCamera();	//�J����
	InitLight();	//���C�g
	pBullet->Init();	//�e
	pPlayer->Init();	//�v���C���[
	InitPolygon();	//�|���S��
	InitPause();	//�|�[�Y

	//�^�C���̐ݒ�
	InitTime();
	SetTime(TIME_LIMIT);

	s_gameState			= GAMESTATE_NORMAL;		//�ʏ���
	s_nCounterGameState = 0;					//�J�E���^�[�̏�����
	s_pPause			= false;				//�|�[�Y����
}

//================================================
//�Q�[���̏I������
//================================================
void UninitGame(void)
{
	CPlayer* pPlayer = nullptr;
	CBullet* pBullet = nullptr;

	//�T�E���h�̒�~
	StopSound();

	UninitCamera();		//�J����
	UninitLight();		//���C�g
	pBullet->Uninit();		//�e
	pPlayer->Uninit();		//�v���C���[
	UninitPolygon();	//�|���S��
	UninitTime();		//�^�C��
	UninitPause();		//�|�[�Y
}

//================================================
//�Q�[���̍X�V����
//================================================
void UpdateGame(void)
{
	/****************** �|�[�Y ******************/

	if ((s_gameState == GAMESTATE_NORMAL) && GetKeyboardTrigger(DIK_P))
	{//�ʏ��� & P�L�[�������ꂽ
		s_pPause = s_pPause ? false : true;

		if (s_pPause)
		{//�|�[�Y��
			//�T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_SE_PAUSE);
		}
		else
		{//�|�[�Y���ł͂Ȃ�
			//�T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_SE_CANCEL);
		}
	}

	if (s_pPause)
	{//�|�[�Y��
		//�|�[�Y�̍X�V����
		UpdatePause();
		return;
	}

	/* �|�[�Y���łȂ���� */

	CPlayer* pPlayer = nullptr;
	CBullet* pBullet = nullptr;

	switch (s_gameState)
	{
	case GAMESTATE_NORMAL:	/* �ʏ��� */
		UpdateCamera();		//�J����
		UpdateLight();		//���C�g
		pBullet->Update();		//�e
		pPlayer->Update();		//�v���C���[
		UpdatePolygon();	//�|���S��
		UpdateTime();		//�^�C��
		break;

	case GAMESTATE_END:		/* �I����� */

		s_nCounterGameState++;		//�J�E���^�[��i�߂�

		if (s_nCounterGameState >= 60)
		{//��莞�Ԃ�������
			s_gameState = GAMESTATE_NONE;		//�������Ă��Ȃ����

			//���U���g��ʂ�
			ChangeMode(MODE_RESULT);
		}
		break;
	}
}

//================================================
//�Q�[���̕`�揈��
//================================================
void DrawGame(void)
{
	CPlayer* pPlayer = nullptr;
	CBullet* pBullet = nullptr;

	//�J�����̐ݒ�
	SetCamera();

	DrawPolygon();	//�|���S��
	pPlayer->Draw();	//�v���C���[
	DrawTime();		//�^�C��
	pBullet->Draw();	//�e

	if (s_pPause)
	{//�|�[�Y��
		//�|�[�Y�̕`�揈��
		DrawPause();
	}
}

//================================================
//�Q�[���̐ݒ菈��
//================================================
void SetGameState(GAMESTATE state)
{
	s_gameState	= state;
	s_nCounterGameState = 0;
}

//================================================
//�Q�[���̎擾����
//================================================
GAMESTATE GetGamaState(void)
{
	return s_gameState;
}

//================================================
//�|�[�Y�̗L�������ݒ�
//================================================
void SetEnablePause(bool bPause)
{
	s_pPause = bPause;
}