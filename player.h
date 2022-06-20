//================================================
//
//C++_STG(��)[player.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "polygon3D.h"

//***************************
//�v���C���[�N���X�̒�`
//***************************
class CPlayer : public CPolygon3D
{/* CPolygon3D�̔h���N���X */
private: /* �񋓌^�̒�` */
	enum class BULLET_TYPE
	{//�e�̎��
		NORMAL = 0,
		DOUBLE,
		TRIPLE,
		MAX
	};

private: /* �萔�̒�` */
	static const int SHOT_INTERVAL = 15;	//�e���˂̊Ԋu( 60�t���[�� = 1�b )
	static const float MOVE_SPEED;			//�ړ��X�s�[�h

public: /* �ÓI�����o�֐� */
	static CPlayer* GetInfo();	//�����擾

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CPlayer();
	~CPlayer() override;

public: /* �I�[�o�[���C�h�֐� */
	void Init() override;	//������
	void Uninit() override;	//�I��
	void Update() override;	//�X�V
	void Draw() override;	//�`��
private: /* �����o�֐� */
	void Move();	//�ړ�
	void Shot();	//�e�̔���

private: /* �ÓI�����o�ϐ� */
	static CPlayer* m_pPlayer;	//�v���C���[���

private: /* �����o�ϐ� */
	int m_nInterval;	//�e���˂̊Ԋu���J�E���g����
	int nBulletType;	//�e�̎��
};

#endif