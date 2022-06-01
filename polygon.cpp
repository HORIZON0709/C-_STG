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
//�X�^�e�B�b�N�ϐ��錾
//***************************
namespace
{
LPDIRECT3DVERTEXBUFFER9	s_pVtxBuff = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9		s_pTexture = NULL;		//�e�N�X�`���ւ̃|�C���^
Polygon3D				s_polygon;				//�|���S���̏��
}// namespace�͂����܂�

//================================================
//�|���S���̏���������
//================================================
void InitPolygon(void)
{
	memset(&s_polygon, 0, sizeof(s_polygon));

	// ��`�̐ݒ�
	s_polygon.idx = SetRectangle3D(TEXTURE_�S�S�����_3);

	//�\���̂̕ϐ��̏����ݒ�
	s_polygon.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	s_polygon.size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	{//��`�̐ݒ�
		SetPosRectangle3D(s_polygon.idx, s_polygon.pos);	//�ʒu
		SetSizeRectangle3D(s_polygon.idx, s_polygon.size);	//�T�C�Y
	}
}

//================================================
//�|���S���̏I������
//================================================
void UninitPolygon(void)
{
	// �g���̂��~�߂�
	StopUseRectangle3D(s_polygon.idx);
}

//================================================
//�|���S���̍X�V����
//================================================
void UpdatePolygon(void)
{

}

//================================================
//�|���S���̕`�揈��
//================================================
void DrawPolygon(void)
{
	// ��`�̕`��
	DrawRectangle3D();
}

//================================================
//�|���S�����̎擾
//================================================
Polygon3D* GetPolygon(void)
{
	return &s_polygon;
}