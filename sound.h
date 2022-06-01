//================================================
//
//C++_STG(��)[sound.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//================================================
// �T�E���h�t�@�C��
//================================================
typedef enum
{
	SOUND_LABEL_SE_PAUSE,		//�|�[�Y��
	SOUND_LABEL_SE_SELECT,		//�Z���N�g��
	SOUND_LABEL_SE_DECIDE,		//���艹
	SOUND_LABEL_SE_CANCEL,		//�L�����Z����
	SOUND_LABEL_SE_JUMP,		//�W�����v��
	SOUND_LABEL_SE_ITEMGET,		//�A�C�e���擾��
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//================================================
// �v���g�^�C�v�錾
//================================================
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif