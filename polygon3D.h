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
//�|���S���N���X�̒�`
//***************************
class CPolygon3D
{/* ��{�N���X */
public: /* �ÓI�����o�֐� */
	static CPolygon3D* GetInfo();	//�����擾

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CPolygon3D();
	virtual ~CPolygon3D();

public: /* ���z�֐� */
	virtual void Init();	//������
	virtual void Uninit();	//�I��
	virtual void Update();	//�X�V
	virtual void Draw();	//�`��

private: /* �ÓI�����o�ϐ� */
	static CPolygon3D* m_pPolygon;	//�|�C���^

protected: /* �����o�ϐ� */
	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3 m_size;					//�T�C�Y
	int m_nIdx;							//��`�̃C���f�b�N�X
	D3DXMATRIX m_mtxWorld;				//���[���h�}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���ւ̃|�C���^
};

#endif