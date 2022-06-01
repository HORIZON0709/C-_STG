//================================================
//
//C++_STG(仮)[particle.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

//***************************
//プロトタイプ宣言
//***************************
void InitParticle(void);
void UpdateParticle(void);
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, float fWidth, float fHeight);

#endif