//================================================
//
//C++_STG(仮)[particle.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "particle.h"

//***************************
//定数の定義
//***************************
namespace
{
const int MAX_PARTICLE = 256;	//パーティクルの最大数
}//namespaceはここまで

//***************************
//構造体の定義
//***************************
namespace
{
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//向き
	float fWidth;		//幅
	float fHeight;		//高さ
	bool bUse;			//使用しているかどうか
}Particle;
}//namespaceはここまで

//***************************
//スタティック変数宣言
//***************************
namespace
{
Particle s_aParticle[MAX_PARTICLE];		//パーティクル情報
}//namespaceはここまで

//================================================
//パーティクルの初期化処理
//================================================
void InitParticle(void)
{
	//情報の初期化
	memset(s_aParticle, NULL,sizeof(s_aParticle));
}

//================================================
//パーティクルの更新処理
//================================================
void UpdateParticle(void)
{

}

//================================================
//パーティクルの設定処理
//================================================
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, float fWidth, float fHeight)
{
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		Particle *p = &s_aParticle[i];		//ポインタに変身

		if (p->bUse)
		{//使用されている
			continue;
		}

		/*↓ 使用されていない ↓*/

		p->pos		= pos;
		p->move		= move;
		p->rot		= rot;
		p->fWidth	= fWidth;
		p->fHeight	= fHeight;
		p->bUse		= true;		//使用されている状態にする
	}
}