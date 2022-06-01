//================================================
//
//C++_STG(仮)[tutorial.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "tutorial.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "mode.h"
#include "fade.h"

//***************************
//マクロ定義
//***************************
namespace
{
const int NUM_TUTORIAL = 2;		//テクスチャの種類
}//namespaceはここまで

//***************************
//スタティック変数
//***************************
namespace
{
LPDIRECT3DTEXTURE9		s_apTexture[NUM_TUTORIAL];	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9	s_pVtxBuff = NULL;			//頂点バッファへのポインタ
int						s_nCntTex;					//テクスチャのカウント
}//namespaceはここまで

//================================================
//チュートリアルの初期化処理
//================================================
void InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	VERTEX_2D *pVtx;							//頂点情報へのポインタ

	//テクスチャポインタの初期化
	memset(s_apTexture, NULL, sizeof(s_apTexture));

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/Tutorial_01.png",
								&s_apTexture[0]);

	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/Tutorial_02.png",
								&s_apTexture[1]);

	s_nCntTex = 0;	//テクスチャのカウントを初期化

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&s_pVtxBuff,
								NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	SetRhw(pVtx, 1.0f);

	//頂点カラーの設定
	SetCol2D(pVtx, 1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	SetTex2D(pVtx, 0.0f, 1.0f, 0.0f, 1.0f);

	//頂点バッファをアンロックする
	s_pVtxBuff->Unlock();
}

//================================================
//チュートリアルの終了処理
//================================================
void UninitTutorial(void)
{
	//サウンドの停止
	StopSound();

	//テクスチャの破棄
	for (int i = 0; i < NUM_TUTORIAL; i++)
	{
		if (s_apTexture[i] != NULL)
		{
			s_apTexture[i]->Release();
			s_apTexture[i] = NULL;
		}
	}

	//頂点バッファの破棄
	if (s_pVtxBuff != NULL)
	{
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}
}

//================================================
//チュートリアルの更新処理
//================================================
void UpdateTutorial(void)
{
	if (GetFade() != FADE_NONE)
	{//フェードしているとき
		return;
	}

	/* フェードしているとき */

	if (GetKeyboardTrigger(DIK_D))
	{//Dキーが押された
		//サウンドの再生
		PlaySound(SOUND_LABEL_SE_SELECT);

		s_nCntTex = 1;
	}
	else if (GetKeyboardTrigger(DIK_A))
	{//Aキーが押された
		//サウンドの再生
		PlaySound(SOUND_LABEL_SE_SELECT);

		s_nCntTex = 0;
	}
	else if (GetKeyboardTrigger(DIK_RETURN))
	{//Enterキーが押された
		//サウンドの再生
		PlaySound(SOUND_LABEL_SE_DECIDE);

		//タイトル画面に移行
		ChangeMode(MODE_TITLE);
	}
}

//================================================
//チュートリアルの描画処理
//================================================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, s_apTexture[s_nCntTex]);

	//チュートリアルの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
							0,						//描画する最初の頂点インデックス
							2);						//描画するプリミティブ数
}