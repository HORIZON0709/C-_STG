//================================================
//
//C++_STG[polygon.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "polygon.h"

#include "rectangle3D.h"
#include "texture.h"

//***************************
//�ÓI�����o�ϐ��錾
//***************************
CPolygon3D* CPolygon3D::m_pPolygon = nullptr;	//�|�C���^

//================================================
//�����擾
//================================================
CPolygon3D* CPolygon3D::GetInfo()
{
	return m_pPolygon;
}

//================================================
//�R���X�g���N�^
//================================================
CPolygon3D::CPolygon3D():
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_nIdx(0),
	m_pVtxBuff(nullptr),
	m_pTexture(nullptr)
{
	//�����o�ϐ����N���A
	m_mtxWorld = {};
}

//================================================
//�f�X�g���N�^
//================================================
CPolygon3D::~CPolygon3D()
{
}

//================================================
//������
//================================================
void CPolygon3D::Init()
{
	if (m_pPolygon != nullptr)
	{//NULL�`�F�b�N
		return;
	}

	/* nullptr�̏ꍇ */

	m_pPolygon = new CPolygon3D;	//�������̓��I�m��

	//�����o�ϐ��̏�����
	m_pPolygon->m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pPolygon->m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pPolygon->m_nIdx = 0;
	m_pPolygon->m_mtxWorld = {};
	m_pPolygon->m_pVtxBuff = nullptr;
	m_pPolygon->m_pTexture = nullptr;

	//��`�̃C���f�b�N�X�̐ݒ�
	m_pPolygon->m_nIdx = SetRectangle3D(TEXTURE_�S�S�����_3);

	//�ʒu�ƃT�C�Y�̏����ݒ�
	m_pPolygon->m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pPolygon->m_size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	/* ��`�̐ݒ� */
	SetPosRectangle3D(m_pPolygon->m_nIdx, m_pPolygon->m_pos);	//�ʒu
	SetSizeRectangle3D(m_pPolygon->m_nIdx, m_pPolygon->m_size);	//�T�C�Y
}

//================================================
//�I��
//================================================
void CPolygon3D::Uninit()
{
	// �g���̂��~�߂�
	StopUseRectangle3D(m_pPolygon->m_nIdx);

	if (m_pPolygon == nullptr)
	{//NULL�`�F�b�N
		return;
	}

	/* nullptr�ł͂Ȃ��ꍇ */

	//�������̉��
	delete m_pPolygon;
	m_pPolygon = nullptr;
}

//================================================
//�X�V
//================================================
void CPolygon3D::Update()
{
	//�ʒu�̍X�V
	SetPosRectangle3D(m_pPolygon->m_nIdx, m_pPolygon->m_pos);
}

//================================================
//�`��
//================================================
void CPolygon3D::Draw()
{
	//��`�̕`��
	DrawRectangle3D();
}