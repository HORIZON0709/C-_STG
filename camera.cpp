//================================================
//
//C++_STG(��)[camera.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "camera.h"
#include "input.h"
#include "player.h"
#include "polygon3D.h"

//***************************
//�萔�̒�`
//***************************
namespace
{
const float CAMERA_MOVE = 2.0f;		//�J�����̈ړ���
const float CAMERA_ROT	= 0.05f;	//�J�����̐����
const float MAX_FAR		= 1000.0f;	//�t�@�[
const float MAX_NEAR	= 10.0f;	//�j�A
}//namespace�͂����܂�

//***************************
//�X�^�e�B�b�N�ϐ��錾
//***************************
namespace
{
Camera s_camera;	//�J�������
}//namespace�͂����܂�

//***************************
//�v���g�^�C�v�錾
//***************************
static void CameraMove(void);
static void CameraReset(void);
static void AllDirections(void);
static void AngleNormalization(void);

//================================================
//�J�����̏���������
//================================================
void InitCamera(void)
{
	//���_�E�����_�E�������ݒ肷��
	s_camera.posV = D3DXVECTOR3(-280.0f, 0.0f, -100.0f);
	s_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	s_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�����̏�����
	s_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	//���_���璍���_�̋����̐ݒ�
	float fX = (s_camera.posR.x - s_camera.posV.x);
	float fZ = (s_camera.posR.z - s_camera.posV.z);
	s_camera.fDistance	= sqrtf((fX * fX) + (fZ * fZ));		//�O�����ŋ������v�Z
}

//================================================
//�J�����̏I������
//================================================
void UninitCamera(void)
{

}

//================================================
//�J�����̍X�V����
//================================================
void UpdateCamera(void)
{
	//�J�����̈ړ�
	CameraMove();

	if (!GetKeyboardPress(DIK_M))
	{//�J�����ړ����ꎞ��~�ł����
		s_camera.posV.x += sinf(s_camera.rot.y + (D3DX_PI * 0.5f)) * 0.4f;
		s_camera.posV.z += cosf(s_camera.rot.y + (D3DX_PI * 0.5f)) * 0.4f;
	}
}

//================================================
//�J�����̐ݒ菈��
//================================================
void SetCamera(void)
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&s_camera.mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&s_camera.mtxView,
						&s_camera.posV,
						&s_camera.posR,
						&s_camera.vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &s_camera.mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&s_camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixOrthoLH(&s_camera.mtxProjection,
						(float)SCREEN_WIDTH,
						(float)SCREEN_HEIGHT,
						MAX_NEAR,
						MAX_FAR);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &s_camera.mtxProjection);
}

//================================================
//�J�����̈ړ�
//================================================
static void CameraMove(void)
{
#ifdef _DEBUG	//�f�o�b�O�̎�����

	//�J�����̃��Z�b�g
	CameraReset();

	//�O�㍶�E�̈ړ�
	AllDirections();
	
#endif
	//�p�x�̐��K��
	AngleNormalization();

	//�����_
	s_camera.posR.x = s_camera.posV.x + sinf(s_camera.rot.y) * s_camera.fDistance;
	s_camera.posR.z = s_camera.posV.z + cosf(s_camera.rot.y) * s_camera.fDistance;
	s_camera.posR.y = s_camera.posV.y + tanf(s_camera.rot.x) * s_camera.fDistance;
}

//================================================
//�J�����̃��Z�b�g
//================================================
static void CameraReset(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{//Enter�L�[
		//�J�����̏���������
		InitCamera();
	}
}

//================================================
//�O�㍶�E�̈ړ�
//================================================
static void AllDirections(void)
{
	//if (GetKeyboardPress(DIK_LEFT))
	//{//���L�[
	//	if (GetKeyboardPress(DIK_UP))
	//	{//����
	//		s_camera.posV.x -= sinf(s_camera.rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;
	//		s_camera.posV.z -= cosf(s_camera.rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;
	//	}
	//	else if (GetKeyboardPress(DIK_DOWN))
	//	{//����
	//		s_camera.posV.x -= sinf(s_camera.rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;
	//		s_camera.posV.z -= cosf(s_camera.rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;
	//	}
	//	else
	//	{//��
	//		s_camera.posV.x -= sinf(s_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;
	//		s_camera.posV.z -= cosf(s_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_RIGHT))
	//{//���L�[
	//	if (GetKeyboardPress(DIK_UP))
	//	{//�E��
	//		s_camera.posV.x += sinf(s_camera.rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;
	//		s_camera.posV.z += cosf(s_camera.rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;
	//	}
	//	else if (GetKeyboardPress(DIK_DOWN))
	//	{//�E��
	//		s_camera.posV.x += sinf(s_camera.rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;
	//		s_camera.posV.z += cosf(s_camera.rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;
	//	}
	//	else
	//	{//�E
	//		s_camera.posV.x += sinf(s_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;
	//		s_camera.posV.z += cosf(s_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_UP))
	//{//���L�[(�O)
	//	s_camera.posV.x += sinf(s_camera.rot.y) * CAMERA_MOVE;
	//	s_camera.posV.z += cosf(s_camera.rot.y) * CAMERA_MOVE;
	//}
	//else if (GetKeyboardPress(DIK_DOWN))
	//{//���L�[(��)
	//	s_camera.posV.x -= sinf(s_camera.rot.y) * CAMERA_MOVE;
	//	s_camera.posV.z -= cosf(s_camera.rot.y) * CAMERA_MOVE;
	//}

	if (GetKeyboardPress(DIK_T))
	{//�㏸
		s_camera.posV.y += 5.0f;
	}
	else if (GetKeyboardPress(DIK_G))
	{//���~
		s_camera.posV.y -= 5.0f;
	}

	//if (GetKeyboardPress(DIK_Y))
	//{//�O��]
	//	s_camera.rot.x += 0.01f;
	//}
	//else if (GetKeyboardPress(DIK_H))
	//{//���]
	//	s_camera.rot.x -= 0.01f;
	//}
}

//================================================
//�p�x�̐��K��
//================================================
static void AngleNormalization(void)
{
	//Y��
	if (s_camera.rot.y > D3DX_PI)
	{//��( 180��)�𒴂����ꍇ
		s_camera.rot.y -= (D3DX_PI * 2.0f);
	}
	else if (s_camera.rot.y < -D3DX_PI)
	{//-��( -180��)�𒴂����ꍇ
		s_camera.rot.y += (D3DX_PI * 2.0f);
	}

	//X��
	if (s_camera.rot.x > D3DX_PI)
	{//��( 180��)�𒴂����ꍇ
		s_camera.rot.x -= (D3DX_PI * 2.0f);
	}
	else if (s_camera.rot.x < -D3DX_PI)
	{//-��( -180��)�𒴂����ꍇ
		s_camera.rot.x += (D3DX_PI * 2.0f);
	}
}

//================================================
//�J�����̏��̎擾
//================================================
Camera *GetCamera(void)
{
	return &s_camera;
}