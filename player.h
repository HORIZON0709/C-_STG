//================================================
//
//C++_STG(��)[player.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//***************************
//�v���C���[�N���X�̒�`
//***************************
class CPlayer
{/* ��{�N���X */
private: /* �񋓌^�̒�` */
	enum class BULLET_TYPE
	{//�e�̎��
		NORMAL = 0,
		DOUBLE,
		TRIPLE,
		MAX
	};

private: /* ���Z�q�I�[�o�[���[�h */
	CPlayer operator ++ ();		//�u ++ �v

private: /* �萔�̒�` */
	static const int SHOT_INTERVAL = 15;	//�e���˂̊Ԋu( 60�t���[�� = 1�b )
	static float MOVE_SPEED;				//�ړ��X�s�[�h

public: /* �ÓI�����o�֐� */
	static CPlayer* GetInfo();	//�����擾

private: /* �ÓI�����o�ϐ� */
	static CPlayer* m_pPlayer;	//�v���C���[���

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CPlayer();
	~CPlayer();

public: /* �����o�֐� */
	void Init();	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��
private:
	void Move();	//�ړ�
	void Shot();	//�e�̔���

private: /* �����o�ϐ� */
	D3DXVECTOR3	m_pos;						//�ʒu
	D3DXVECTOR3	m_size;						//�T�C�Y
	int m_nIdx;								//��`�̃C���f�b�N�X
	D3DXMATRIX	m_mtxWorld;					//���[���h�}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`���ւ̃|�C���^
	int m_nInterval;						//�e���˂̊Ԋu���J�E���g����
	int nBulletType;						//�e�̎��
};

#endif