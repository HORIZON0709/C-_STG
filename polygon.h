//================================================
//
//�~�c�P�e�l[Polygon3D.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "main.h"

//***************************
//�|���S���\���̂̒�`
//***************************
typedef struct
{
	D3DXVECTOR3	pos;		//�ʒu
	D3DXVECTOR3	size;		//�T�C�Y
	int			idx;		//��`�̃C���f�b�N�X
	D3DXMATRIX	mtxWorld;	//���[���h�}�g���b�N�X
}Polygon3D;

//***************************
//�v���g�^�C�v�錾
//***************************
void InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);
Polygon3D* GetPolygon(void);

#endif