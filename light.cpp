//================================================
//
//C++_STG(��)[light.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "light.h"
#include "main.h"

//***************************
//�萔�̒�`
//***************************
namespace
{
const int MAX_LIGHT = 3;	//���C�g�̍ő吔
}//namespace�͂����܂�

//***************************
//�X�^�e�B�b�N�ϐ��錾
//***************************
namespace
{
D3DLIGHT9 s_alight[MAX_LIGHT];	//���C�g���
}//namespace�͂����܂�

//***************************
//�v���g�^�C�v�錾
//***************************
namespace
{
void SetLight(int nNum, D3DXCOLOR Diffuse, D3DXVECTOR3 vecDirection);
}//namespace�͂����܂�

//================================================
//���C�g�̏���������
//================================================
void InitLight(void)
{
	//���C�g���N���A����
	ZeroMemory(&s_alight[0], sizeof(s_alight));

	//���C�g�P�̐ݒ�
	SetLight(0,										//�ǂ̃��C�g��
			 D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),		//�g�U��
			 D3DXVECTOR3(0.2f, -0.8f, -0.4f));		//���C�g�̕���

	//���C�g�Q�̐ݒ�
	SetLight(1,										//�ǂ̃��C�g��
			 D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),		//�g�U��
			 D3DXVECTOR3(1.0f, 1.0f, 1.0f));		//���C�g�̕���

	////���C�g�R�̐ݒ�
	//SetLight(2,										//�ǂ̃��C�g��
	//		 D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),		//�g�U��
	//		 D3DXVECTOR3(0.0f, 1.0f, 0.f));			//���C�g�̕���
}

//================================================
//���C�g�̏I������
//================================================
void UninitLight(void)
{

}

//================================================
//���C�g�̍X�V����
//================================================
void UpdateLight(void)
{

}

namespace
{
//------------------------------------------------
//���C�g�̐ݒ菈��
//------------------------------------------------
static void SetLight(int nNum, D3DXCOLOR Diffuse, D3DXVECTOR3 vecDirection)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXVECTOR3 vecDir;							//���C�g�̕����x�N�g��

	//���C�g�̎�ނ�ݒ�
	s_alight[nNum].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g�U����ݒ�
	s_alight[nNum].Diffuse = Diffuse;

	//���C�g�̕�����ݒ�
	vecDir = vecDirection;

	//���K������(�傫��1�̃x�N�g���ɂ���)
	D3DXVec3Normalize(&vecDir, &vecDir);

	//���C�g�̕���������
	s_alight[nNum].Direction = vecDir;

	//���C�g��ݒ肷��
	pDevice->SetLight(nNum, &s_alight[nNum]);

	//���C�g��L���ɂ���
	pDevice->LightEnable(nNum, TRUE);
}
}//namespace�͂����܂�