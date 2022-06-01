//================================================
//
//C++_STG(��)[result.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "result.h"
#include "input.h"
#include "fade.h"
#include "mode.h"

//***************************
//�񋓌^�̒�`
//***************************
namespace
{
/* �Q�[������ */
typedef enum
{
	GAME_OVER = 0,		//�Q�[���I�[�o�[
	GAME_CLEAR,			//�Q�[���N���A
	GAME_MAX
}GAME_RESULT;
}//namespace�͂����܂�

//***************************
//�X�^�e�B�b�N�ϐ�
//***************************
namespace
{
LPDIRECT3DTEXTURE9		s_apTexture[GAME_MAX];		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	s_pVtxBuff = NULL;			//���_�o�b�t�@�ւ̃|�C���^
}//namespace�͂����܂�

//================================================
//���U���g�̏���������
//================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	VERTEX_2D *pVtx;							//���_���ւ̃|�C���^

	//�e�N�X�`���|�C���^�̏�����
	memset(s_apTexture, NULL, sizeof(s_apTexture));

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/GameOver.png",
								&s_apTexture[GAME_OVER]);

	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/GameClear.png",
								&s_apTexture[GAME_CLEAR]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&s_pVtxBuff,
								NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	SetRhw(pVtx, 1.0f);
	
	//���_�J���[�̐ݒ�
	SetCol2D(pVtx, 1.0f, 1.0f, 1.0f, 1.0f);
	
	//�e�N�X�`�����W�̐ݒ�
	SetTex2D(pVtx, 0.0f, 1.0f, 0.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	s_pVtxBuff->Unlock();
}

//================================================
//���U���g�̏I������
//================================================
void UninitResult(void)
{
	for (int i = 0; i < GAME_MAX; i++)
	{
		if (s_apTexture[i] != NULL)
		{//�e�N�X�`���̔j��
			s_apTexture[i]->Release();
			s_apTexture[i] = NULL;
		}
	}

	if (s_pVtxBuff != NULL)
	{//���_�o�b�t�@�̔j��
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}
}

//================================================
//���U���g�̍X�V����
//================================================
void UpdateResult(void)
{
	if ((GetFade() == FADE_NONE) && (GetKeyboardTrigger(DIK_RETURN)))
	{//�t�F�[�h���Ă��Ȃ��Ƃ� & Enter�L�[�������ꂽ��
		//�^�C�g����ʂɈڍs
		ChangeMode(MODE_TITLE);
	}
}

//================================================
//���U���g�̕`�揈��
//================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, s_apTexture[GAME_CLEAR]);

	//���U���g�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
							0,						//�`�悷��ŏ��̒��_�C���f�b�N�X
							2);						//�`�悷��v���~�e�B�u��
}