//================================================
//
//C++_STG(��)[main.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _MAIN_H_		//���̃}�N����`������Ă��Ȃ�������
#define _MAIN_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

#include <windows.h>
#include "d3dx9.h"						//�`�揈���ɕK�v
#define DIRECTINPUT_VERSION (0x0800)	//�r���h���̌x���Ώ��p�}�N��
#include "dinput.h"						//���͏����ɕK�v
#include "Xinput.h"						//�W���C�p�b�h�����ɕK�v
#include "xaudio2.h"					//�T�E���h�����ɕK�v

//================================================
//���C�u�����̃����N
//================================================
#pragma comment(lib,"d3d9.lib")			//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")		//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")		//DirectX�R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")		//�V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")		//���͏����ɕK�v
#pragma comment(lib,"xinput.lib")		//���͏����ɕK�v

//================================================
//�}�N����`
//================================================
#define SCREEN_WIDTH		(1280)		//�E�C���h�E�̕�
#define SCREEN_HEIGHT		(720)		//�E�C���h�E�̍���
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_LINE	(D3DFVF_XYZ | D3DFVF_DIFFUSE)

//================================================
//���_���[2D]�̍\���̂��`
//================================================
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float		rhw;	//���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR	col;	//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_2D;

//================================================
//���_���[LINE]�̍\���̂��`
//================================================
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	D3DCOLOR	col;	//���_�J���[
}VERTEX_LINE;

//================================================
//�v���g�^�C�v�錾
//================================================
LPDIRECT3DDEVICE9 GetDevice(void);
bool *GetEnd(void);
void SetRhw(VERTEX_2D *pVtx, float fRhw);
void SetCol2D(VERTEX_2D *pVtx, float fRed, float fGreen, float fBlue, float fAlpha);
void SetTex2D(VERTEX_2D *pVtx, float fLeft, float fRight, float fUp, float fDown);

#endif // !_MAIN_H_