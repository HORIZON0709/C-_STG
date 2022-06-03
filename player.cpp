//================================================
//
//C++_STG(��)[player.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "player.h"
#include "bullet.h"

#include "rectangle3D.h"
#include "texture.h"
#include "input.h"
#include "sound.h"

#include <assert.h>

//***************************
//�ÓI�����o�ϐ��錾
//***************************
CPlayer* CPlayer::m_pPlayer = nullptr;	//�|�C���^
float CPlayer::MOVE_SPEED = 8.0f;		//�ړ��X�s�[�h

//================================================
//�����擾
//================================================
CPlayer* CPlayer::GetInfo()
{
	return m_pPlayer;
}

//================================================
//�R���X�g���N�^
//================================================
CPlayer::CPlayer()
{
	//�����o�ϐ��̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nIdx = 0;
	m_mtxWorld = {};
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;
	m_pPlayer = nullptr;
	m_nInterval = 0;
	nBulletType = 0;
}

//================================================
//�f�X�g���N�^
//================================================
CPlayer::~CPlayer()
{
	/* �����Ȃ� */
}

//================================================
//������
//================================================
void CPlayer::Init()
{
	if (m_pPlayer != nullptr)
	{//NULL�`�F�b�N
		return;
	}

	/* nullptr�̏ꍇ */

	m_pPlayer = new CPlayer;	//�������̓��I�m��

	//�����o�ϐ��̏�����
	m_pPlayer->m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pPlayer->m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pPlayer->m_nIdx = 0;
	m_pPlayer->m_mtxWorld = {};
	m_pPlayer->m_pVtxBuff = nullptr;
	m_pPlayer->m_pTexture = nullptr;
	m_pPlayer->m_nInterval = 0;
	m_pPlayer->nBulletType = 0;

	//��`�̃C���f�b�N�X�̐ݒ�
	m_pPlayer->m_nIdx = SetRectangle3D(TEXTURE_�S�S�����_4);

	//�ʒu�ƃT�C�Y�̏����ݒ�
	m_pPlayer->m_pos = D3DXVECTOR3(0.0f, 0.0f, -20.0f);
	m_pPlayer->m_size = D3DXVECTOR3(100.0f, 100.0f, 0.0f);

	/* ��`�̐ݒ� */
	SetPosRectangle3D(m_pPlayer->m_nIdx, m_pPlayer->m_pos);		//�ʒu
	SetSizeRectangle3D(m_pPlayer->m_nIdx, m_pPlayer->m_size);	//�T�C�Y
}

//================================================
//�I��
//================================================
void CPlayer::Uninit()
{
	// �g���̂��~�߂�
	StopUseRectangle3D(m_pPlayer->m_nIdx);

	if (m_pPlayer == nullptr)
	{//NULL�`�F�b�N
		return;
	}

	/* nullptr�ł͂Ȃ��ꍇ */

	//�������̉��
	delete m_pPlayer;
	m_pPlayer = nullptr;
}

//================================================
//�X�V
//================================================
void CPlayer::Update()
{
	if (GetKeyboardTrigger(DIK_F3))
	{//�^�C�v�؂�ւ�
		m_pPlayer->nBulletType++;	//�^�C�v��i�߂�

		if (m_pPlayer->nBulletType >= (int)BULLET_TYPE::MAX)
		{//�^�C�v���̍ő吔�ȏ�ɂȂ�����(���������)
			m_pPlayer->nBulletType = 0;		//�n�߂ɖ߂�
		}
	}

	//�ړ�
	Move();

	//�e�̔���
	Shot();

	//�ʒu�̍X�V
	SetPosRectangle3D(m_pPlayer->m_nIdx, m_pPlayer->m_pos);
}

//================================================
//�`��
//================================================
void CPlayer::Draw()
{
	// ��`�̕`��
	DrawRectangle3D();
}

//================================================
//�ړ�
//================================================
void CPlayer::Move()
{
	if (GetMoveKeyPress(MOVE_KEY_LEFT))
	{//���ړ�
		m_pPlayer->m_pos.x -= MOVE_SPEED;
	}
	else if (GetMoveKeyPress(MOVE_KEY_RIGHT))
	{//�E�ړ�
		m_pPlayer->m_pos.x += MOVE_SPEED;
	}

	if (GetMoveKeyPress(MOVE_KEY_UP))
	{//��ړ�
		m_pPlayer->m_pos.y += MOVE_SPEED;
	}
	else if (GetMoveKeyPress(MOVE_KEY_DOWN))
	{//���ړ�
		m_pPlayer->m_pos.y -= MOVE_SPEED;
	}
}

//================================================
//�e�̔���
//================================================
void CPlayer::Shot()
{
	/* �e�̐ݒ�p�ϐ� */
	D3DXVECTOR3 pos = m_pPlayer->m_pos;						//�ʒu
	D3DXVECTOR3 move = D3DXVECTOR3(10.0f, 5.0f, 0.0f);		//�ړ���

	if (GetKeyboardPress(DIK_SPACE))
	{//������(�Ƃ������������ςȂ�)
		m_pPlayer->m_nInterval++;	//�J�E���g�A�b�v

		if (m_pPlayer->m_nInterval < SHOT_INTERVAL)
		{//�Ԋu�̃J�E���g���K��l���z���Ă��Ȃ�
			return;
		}

		/* �Ԋu�J�E���g���K��l���z������ */

		CBullet bullet;

		switch ((BULLET_TYPE)m_pPlayer->nBulletType)
		{
		case BULLET_TYPE::NORMAL: /* �ʏ� */

			/* �e�̔��� */
			bullet.Set(pos, D3DXVECTOR3(move.x, 0.0f, 0.0f));
			//SetBullet(pos, D3DXVECTOR3(move.x, 0.0f, 0.0f));
			break;
		case BULLET_TYPE::DOUBLE: /* 2������ */
			
			/* �e�̔��� */
			bullet.Set(D3DXVECTOR3(pos.x, pos.y + 15.0f, pos.z), D3DXVECTOR3(move.x, 0.0f, 0.0f));
			bullet.Set(D3DXVECTOR3(pos.x, pos.y - 15.0f, pos.z), D3DXVECTOR3(move.x, 0.0f, 0.0f));

			//SetBullet(D3DXVECTOR3(pos.x, pos.y + 15.0f, pos.z), D3DXVECTOR3(move.x, 0.0f, 0.0f));	//��
			//SetBullet(D3DXVECTOR3(pos.x, pos.y - 15.0f, pos.z), D3DXVECTOR3(move.x, 0.0f, 0.0f));	//��
			break;
		case BULLET_TYPE::TRIPLE: /* 3���� */
			
			/* �e�̔��� */
			bullet.Set(pos, D3DXVECTOR3(move.x, move.y, 0.0f));
			bullet.Set(pos, D3DXVECTOR3(move.x, 0.0f, 0.0f));
			bullet.Set(pos, D3DXVECTOR3(move.x, -move.y, 0.0f));

			//SetBullet(pos, D3DXVECTOR3(move.x, move.y, 0.0f));	//�΂ߏ����
			//SetBullet(pos, D3DXVECTOR3(move.x, 0.0f, 0.0f));	//��������
			//SetBullet(pos, D3DXVECTOR3(move.x, -move.y, 0.0f));	//�΂߉�����
			break;
		default: /* ���̑� */
			assert(false);
			break;
		}

		m_pPlayer->m_nInterval = 0;	//�J�E���g���Z�b�g
	}
}