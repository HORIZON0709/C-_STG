//================================================
//
//C++_STG(仮)[main.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _MAIN_H_		//このマクロ定義がされていなかったら
#define _MAIN_H_		//２重インクルード防止のマクロ定義

#include <windows.h>
#include "d3dx9.h"						//描画処理に必要
#define DIRECTINPUT_VERSION (0x0800)	//ビルド時の警告対処用マクロ
#include "dinput.h"						//入力処理に必要
#include "Xinput.h"						//ジョイパッド処理に必要
#include "xaudio2.h"					//サウンド処理に必要

//================================================
//ライブラリのリンク
//================================================
#pragma comment(lib,"d3d9.lib")			//描画処理に必要
#pragma comment(lib,"d3dx9.lib")		//[d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")		//DirectXコンポーネント(部品)使用に必要
#pragma comment(lib,"winmm.lib")		//システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")		//入力処理に必要
#pragma comment(lib,"xinput.lib")		//入力処理に必要

//================================================
//マクロ定義
//================================================
#define SCREEN_WIDTH		(1280)		//ウインドウの幅
#define SCREEN_HEIGHT		(720)		//ウインドウの高さ
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_LINE	(D3DFVF_XYZ | D3DFVF_DIFFUSE)

//================================================
//頂点情報[2D]の構造体を定義
//================================================
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float		rhw;	//座標変換用係数(1.0fで固定)
	D3DCOLOR	col;	//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
}VERTEX_2D;

//================================================
//頂点情報[LINE]の構造体を定義
//================================================
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	D3DCOLOR	col;	//頂点カラー
}VERTEX_LINE;

//================================================
//プロトタイプ宣言
//================================================
LPDIRECT3DDEVICE9 GetDevice(void);
bool *GetEnd(void);
void SetRhw(VERTEX_2D *pVtx, float fRhw);
void SetCol2D(VERTEX_2D *pVtx, float fRed, float fGreen, float fBlue, float fAlpha);
void SetTex2D(VERTEX_2D *pVtx, float fLeft, float fRight, float fUp, float fDown);

#endif // !_MAIN_H_