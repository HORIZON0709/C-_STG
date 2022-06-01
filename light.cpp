//================================================
//
//C++_STG(仮)[light.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "light.h"
#include "main.h"

//***************************
//定数の定義
//***************************
namespace
{
const int MAX_LIGHT = 3;	//ライトの最大数
}//namespaceはここまで

//***************************
//スタティック変数宣言
//***************************
namespace
{
D3DLIGHT9 s_alight[MAX_LIGHT];	//ライト情報
}//namespaceはここまで

//***************************
//プロトタイプ宣言
//***************************
namespace
{
void SetLight(int nNum, D3DXCOLOR Diffuse, D3DXVECTOR3 vecDirection);
}//namespaceはここまで

//================================================
//ライトの初期化処理
//================================================
void InitLight(void)
{
	//ライトをクリアする
	ZeroMemory(&s_alight[0], sizeof(s_alight));

	//ライト１の設定
	SetLight(0,										//どのライトか
			 D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),		//拡散光
			 D3DXVECTOR3(0.2f, -0.8f, -0.4f));		//ライトの方向

	//ライト２の設定
	SetLight(1,										//どのライトか
			 D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),		//拡散光
			 D3DXVECTOR3(1.0f, 1.0f, 1.0f));		//ライトの方向

	////ライト３の設定
	//SetLight(2,										//どのライトか
	//		 D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),		//拡散光
	//		 D3DXVECTOR3(0.0f, 1.0f, 0.f));			//ライトの方向
}

//================================================
//ライトの終了処理
//================================================
void UninitLight(void)
{

}

//================================================
//ライトの更新処理
//================================================
void UpdateLight(void)
{

}

namespace
{
//------------------------------------------------
//ライトの設定処理
//------------------------------------------------
static void SetLight(int nNum, D3DXCOLOR Diffuse, D3DXVECTOR3 vecDirection)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXVECTOR3 vecDir;							//ライトの方向ベクトル

	//ライトの種類を設定
	s_alight[nNum].Type = D3DLIGHT_DIRECTIONAL;

	//ライトの拡散光を設定
	s_alight[nNum].Diffuse = Diffuse;

	//ライトの方向を設定
	vecDir = vecDirection;

	//正規化する(大きさ1のベクトルにする)
	D3DXVec3Normalize(&vecDir, &vecDir);

	//ライトの方向を決定
	s_alight[nNum].Direction = vecDir;

	//ライトを設定する
	pDevice->SetLight(nNum, &s_alight[nNum]);

	//ライトを有効にする
	pDevice->LightEnable(nNum, TRUE);
}
}//namespaceはここまで