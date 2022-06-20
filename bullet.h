//================================================
//
//C++_STG(��)[bullet.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "polygon3D.h"

//***************************
//�e�N���X�̒�`
//***************************
class CBullet : public CPolygon3D
{/* Cpolygon3D�̔h���N���X */
public: /* �萔�̒�` */
	static const int MAX_BULLET = 48;	//�e�̍ő吔
	static const int MAX_LIFE = 150;	//�e�̎���

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CBullet();
	~CBullet()override;

public:/* �����o�֐� */
	void Init()override;	//������
	void Uninit()override;	//�I��
	void Update()override;	//�X�V
	void Draw()override;	//�`��
public:/* Set�n */
	/*
	�Z�b�g
	const D3DXVECTOR3 pos ---> �ʒu
	const D3DXVECTOR3 move ---> �ړ���
	*/
	void Set(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 size);

private: /* �ÓI�����o�ϐ� */
	static CBullet* m_apBullet[MAX_BULLET];		//�e�̏��

private: /* �����o�ϐ� */
	D3DXVECTOR3 m_move;	//�ړ���
	int m_nLife;		//����
	bool m_bUse;		//�g�p�̗L��
};

#endif