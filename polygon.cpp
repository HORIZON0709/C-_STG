//================================================
//
//C++_STG[polygon.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "polygon.h"
#include "rectangle3D.h"
#include "texture.h"

//***************************
//スタティック変数宣言
//***************************
namespace
{
LPDIRECT3DVERTEXBUFFER9	s_pVtxBuff = NULL;		//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9		s_pTexture = NULL;		//テクスチャへのポインタ
Polygon3D				s_polygon;				//ポリゴンの情報
}// namespaceはここまで

//================================================
//ポリゴンの初期化処理
//================================================
void InitPolygon(void)
{
	memset(&s_polygon, 0, sizeof(s_polygon));

	// 矩形の設定
	s_polygon.idx = SetRectangle3D(TEXTURE_百鬼あやめ_3);

	//構造体の変数の初期設定
	s_polygon.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	s_polygon.size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	{//矩形の設定
		SetPosRectangle3D(s_polygon.idx, s_polygon.pos);	//位置
		SetSizeRectangle3D(s_polygon.idx, s_polygon.size);	//サイズ
	}
}

//================================================
//ポリゴンの終了処理
//================================================
void UninitPolygon(void)
{
	// 使うのを止める
	StopUseRectangle3D(s_polygon.idx);
}

//================================================
//ポリゴンの更新処理
//================================================
void UpdatePolygon(void)
{

}

//================================================
//ポリゴンの描画処理
//================================================
void DrawPolygon(void)
{
	// 矩形の描画
	DrawRectangle3D();
}

//================================================
//ポリゴン情報の取得
//================================================
Polygon3D* GetPolygon(void)
{
	return &s_polygon;
}