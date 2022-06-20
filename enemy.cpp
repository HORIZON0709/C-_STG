//================================================
//
//C++_STG(��)[enemy.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "enemy.h"

#include "rectangle3D.h"
#include "texture.h"
#include "input.h"

//***************************
//�ÓI�����o�ϐ��錾
//***************************
CEnemy* CEnemy::m_apEnemy[MAX_ENEMY] = {};	//�|�C���^

//================================================
//�����擾
//================================================
CEnemy** CEnemy::GetInfo()
{
	return &m_apEnemy[0];
}

//================================================
//�R���X�g���N�^
//================================================
CEnemy::CEnemy()
{
	
}

//================================================
//�f�X�g���N�^
//================================================
CEnemy::~CEnemy()
{
}

//================================================
//������
//================================================
void CEnemy::Init()
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (m_apEnemy[i] != nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�̏ꍇ */

		m_apEnemy[i] = new CEnemy;	//�������̓��I�m��

		//��`�̃C���f�b�N�X�̐ݒ�
		m_apEnemy[i]->m_nIdx = SetRectangle3D(TEXTURE_�S�S�����_1);

		//�ʒu�ƃT�C�Y�̏����ݒ�
		m_apEnemy[i]->m_pos = D3DXVECTOR3((100.0f * i), 100.0f, -20.0f);
		m_apEnemy[i]->m_size = D3DXVECTOR3(150.0f, 150.0f, 0.0f);

		/* ��`�̐ݒ� */
		SetPosRectangle3D(m_apEnemy[i]->m_nIdx, m_apEnemy[i]->m_pos);	//�ʒu
		SetSizeRectangle3D(m_apEnemy[i]->m_nIdx, m_apEnemy[i]->m_size);	//�T�C�Y
	}
}

//================================================
//�I��
//================================================
void CEnemy::Uninit()
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		// �g���̂��~�߂�
		StopUseRectangle3D(m_apEnemy[i]->m_nIdx);

		if (m_apEnemy[i] == nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�ł͂Ȃ��ꍇ */

		//�������̉��
		delete m_apEnemy[i];
		m_apEnemy[i] = nullptr;
	}
}

//================================================
//�X�V
//================================================
void CEnemy::Update()
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (m_apEnemy[i] == nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�ł͂Ȃ��ꍇ */

		//�ʒu�̍X�V
		SetPosRectangle3D(m_apEnemy[i]->m_nIdx, m_apEnemy[i]->m_pos);
	}
}

//================================================
//�`��
//================================================
void CEnemy::Draw()
{
	// ��`�̕`��
	DrawRectangle3D();
}