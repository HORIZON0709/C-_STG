//================================================
//
//C++_STG(��)[bullet.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//***************************
//�e�N���X�̒�`
//***************************
class CBullet
{
public: /* �萔�̒�` */
	static const int MAX_BULLET = 48;	//�e�̍ő吔
	static const int MAX_LIFE = 150;	//�e�̎���

private: /* �ÓI�����o�ϐ� */
	static CBullet* m_apBullet[MAX_BULLET];		//�e�̏��

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CBullet();
	~CBullet();

public:/* �����o�֐� */
	void Init();	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��
public:/* Set�n */
	/*
	�Z�b�g
	const D3DXVECTOR3 pos ---> �ʒu
	const D3DXVECTOR3 move ---> �ړ���
	*/
	void Set(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);

private: /* �����o�ϐ� */
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_size;		//�T�C�Y
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X
	int m_nIdx;				//��`�̃C���f�b�N�X
	int m_nLife;			//����
	bool m_bUse;			//�g�p�̗L��
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9		m_pTexture;		//�e�N�X�`���ւ̃|�C���^
};

//***************************
//�v���g�^�C�v�錾
//***************************
//void InitBullet(void);
//void UninitBullet(void);
//void UpdateBullet(void);
//void DrawBullet(void);
//void SetBullet(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);

#endif