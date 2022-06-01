//================================================
//
//C++_STG(��)[particle.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "particle.h"

//***************************
//�萔�̒�`
//***************************
namespace
{
const int MAX_PARTICLE = 256;	//�p�[�e�B�N���̍ő吔
}//namespace�͂����܂�

//***************************
//�\���̂̒�`
//***************************
namespace
{
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//����
	float fWidth;		//��
	float fHeight;		//����
	bool bUse;			//�g�p���Ă��邩�ǂ���
}Particle;
}//namespace�͂����܂�

//***************************
//�X�^�e�B�b�N�ϐ��錾
//***************************
namespace
{
Particle s_aParticle[MAX_PARTICLE];		//�p�[�e�B�N�����
}//namespace�͂����܂�

//================================================
//�p�[�e�B�N���̏���������
//================================================
void InitParticle(void)
{
	//���̏�����
	memset(s_aParticle, NULL,sizeof(s_aParticle));
}

//================================================
//�p�[�e�B�N���̍X�V����
//================================================
void UpdateParticle(void)
{

}

//================================================
//�p�[�e�B�N���̐ݒ菈��
//================================================
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, float fWidth, float fHeight)
{
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		Particle *p = &s_aParticle[i];		//�|�C���^�ɕϐg

		if (p->bUse)
		{//�g�p����Ă���
			continue;
		}

		/*�� �g�p����Ă��Ȃ� ��*/

		p->pos		= pos;
		p->move		= move;
		p->rot		= rot;
		p->fWidth	= fWidth;
		p->fHeight	= fHeight;
		p->bUse		= true;		//�g�p����Ă����Ԃɂ���
	}
}