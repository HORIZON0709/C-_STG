//================================================
//
//C++_STG[bullet.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "bullet.h"
//#include "player.h"

#include "rectangle3D.h"
#include "texture.h"

//***************************
//�ÓI�����o�ϐ��錾
//***************************
CBullet* CBullet::m_apBullet[MAX_BULLET] = {};	//�|�C���^

//================================================
//�R���X�g���N�^
//================================================
CBullet::CBullet()
{
	//�����o�ϐ��̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mtxWorld = {};
	m_nIdx = 0;
	m_nLife = 0;
	m_bUse = false;
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;
}

//================================================
//�f�X�g���N�^
//================================================
CBullet::~CBullet()
{
	/* �������� */
}

//================================================
//������
//================================================
void CBullet::Init()
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (m_apBullet[i] != nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�̏ꍇ */

		//�������̓��I�m��
		m_apBullet[i] = new CBullet;

		//�����o�ϐ��̏�����
		m_apBullet[i]->m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_apBullet[i]->m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_apBullet[i]->m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_apBullet[i]->m_mtxWorld = {};
		m_apBullet[i]->m_nIdx = 0;
		m_apBullet[i]->m_nLife = 0;
		m_apBullet[i]->m_bUse = false;
		m_apBullet[i]->m_pVtxBuff = nullptr;
		m_apBullet[i]->m_pTexture = nullptr;

		// ��`�̃C���f�b�N�X�̐ݒ�
		m_apBullet[i]->m_nIdx = SetRectangle3D(TEXTURE_�S�S�����_6);

		/* ��`�̐ݒ� */
		SetPosRectangle3D(m_apBullet[i]->m_nIdx, m_apBullet[i]->m_pos);		//�ʒu
		SetSizeRectangle3D(m_apBullet[i]->m_nIdx, m_apBullet[i]->m_size);	//�T�C�Y
	}
}

//================================================
//�I��
//================================================
void CBullet::Uninit()
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		// �g���̂��~�߂�
		StopUseRectangle3D(m_apBullet[i]->m_nIdx);

		if (m_apBullet[i] == nullptr)
		{//NULL�`�F�b�N
			return;
		}

		/* nullptr�ł͂Ȃ��ꍇ */

		//�������̉��
		delete m_apBullet[i];
		m_apBullet[i] = nullptr;
	}
}

//================================================
//�X�V
//================================================
void CBullet::Update()
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (!m_apBullet[i]->m_bUse)
		{//�g�p���Ă��Ȃ�
			continue;
		}

		/* �g�p���Ă��� */

		m_apBullet[i]->m_pos += m_apBullet[i]->m_move;	//�e�̈ړ�

		m_apBullet[i]->m_nLife--;	//���������炷

		if (m_apBullet[i]->m_nLife <= 0)
		{//�������s����
			StopUseRectangle3D(m_apBullet[i]->m_nIdx);	//��`�̎g�p���~
			m_apBullet[i]->m_bUse = false;				//�w�g�p���Ȃ��x�ɕύX
		}

		/* ��`�̍X�V */
		SetPosRectangle3D(m_apBullet[i]->m_nIdx, m_apBullet[i]->m_pos);		//�ʒu
		SetSizeRectangle3D(m_apBullet[i]->m_nIdx, m_apBullet[i]->m_size);	//�T�C�Y
	}
}

//================================================
//�`��
//================================================
void CBullet::Draw()
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (!m_apBullet[i]->m_bUse)
		{//�g�p���Ă��Ȃ�
			continue;
		}

		/* �g�p���Ă��� */

		// ��`�̕`��
		DrawRectangle3D();
	}
}

//================================================
//�Z�b�g
//================================================
void CBullet::Set(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (m_apBullet[i]->m_bUse)
		{//�g�p���Ă���
			continue;
		}

		/* �g�p���Ă��Ȃ� */

		m_apBullet[i]->m_pos = pos;								//�ʒu
		m_apBullet[i]->m_move = move;							//�ړ���
		m_apBullet[i]->m_size = D3DXVECTOR3(50.0f, 50.0f, 0.0);	//�T�C�Y
		m_apBullet[i]->m_nLife = MAX_LIFE;						//����
		m_apBullet[i]->m_bUse = true;							//�w�g�p����x�ɕύX

		// ��`�̃C���f�b�N�X�̐ݒ�
		m_apBullet[i]->m_nIdx = SetRectangle3D(TEXTURE_�S�S�����_6);

		//�Z�b�g�����ʒu����A���_���W��ݒ�
		SetPosRectangle3D(m_apBullet[i]->m_nIdx, m_apBullet[i]->m_pos);
		SetSizeRectangle3D(m_apBullet[i]->m_nIdx, m_apBullet[i]->m_size);
		break;
	}
}