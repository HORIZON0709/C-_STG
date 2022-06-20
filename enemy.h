//================================================
//
//C++_STG(��)[enemy.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "polygon3D.h"

//***************************
//�G�N���X�̒�`
//***************************
class CEnemy : public CPolygon3D
{/* CPolygon3D�̔h���N���X */
private: /* �萔�̒�` */
	static const int MAX_ENEMY = 4;	//�G�̍ő吔

public: /* �ÓI�����o�֐� */
	static CEnemy** GetInfo();	//�����擾

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CEnemy();
	~CEnemy() override;

public: /* �I�[�o�[���C�h�֐� */
	void Init() override;	//������
	void Uninit() override;	//�I��
	void Update() override;	//�X�V
	void Draw() override;	//�`��

private: /* �ÓI�����o�ϐ� */
	static CEnemy* m_apEnemy[MAX_ENEMY];	//�G���

private: /* �����o�ϐ� */

};

#endif