//================================================
//
//C++_STG(仮)[time.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "time.h"
#include "game.h"
#include "fade.h"

//***************************
//定数の定義
//***************************
namespace
{
const int TIME_MAX		= 3;	//タイムの最大桁数
const int TIME_WIDTH	= 40;	//タイムの幅
const int TIME_HEIGHT	= 50;	//タイムの高さ
}//namespaceはここまで

//***************************
//スタティック変数
//***************************
namespace
{
LPDIRECT3DTEXTURE9		s_pTexture = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9	s_pVtxBuff = NULL;		//頂点バッファへのポインタ
D3DXVECTOR3				s_posTime;				//タイムの位置
int						s_nTime;				//タイムの値
int						s_nCntTime;				//タイムのカウント
}//namespaceはここまで

//***************************
//プロトタイプ宣言
//***************************
namespace
{
void SubTime(int nValue);
}//namespaceはここまで

//================================================
//タイムの初期化処理
//================================================
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//デバイスの取得
	VERTEX_2D *pVtx;								//頂点情報へのポインタ

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/number000.png",
								&s_pTexture);

	//スコアの情報の初期化
	s_posTime	= D3DXVECTOR3(600.0f, 10.0f, 0.0f);		//位置を初期化
	s_nTime		= 0;									//値を初期化
	s_nCntTime	= 0;									//カウントを初期化

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TIME_MAX,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&s_pVtxBuff,
								NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < TIME_MAX; nCnt++)
	{
		//頂点座標の設定
		float fLeft		= (s_posTime.x + (nCnt * TIME_WIDTH));
		float fRight	= (s_posTime.x + (nCnt * TIME_WIDTH) + TIME_WIDTH);
		float fTop		= (s_posTime.y);
		float fBottom	= (s_posTime.y + TIME_HEIGHT);

		pVtx[0].pos = D3DXVECTOR3(fLeft,  fTop,	   0.0f);
		pVtx[1].pos = D3DXVECTOR3(fRight, fTop,	   0.0f);
		pVtx[2].pos = D3DXVECTOR3(fLeft,  fBottom, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(fRight, fBottom, 0.0f);

		//rhwの設定
		SetRhw(pVtx, 1.0f);

		//頂点カラーの設定
		SetCol2D(pVtx, 1.0f, 1.0f, 0.0f, 1.0f);
		
		//テクスチャ座標の設定
		SetTex2D(pVtx, 0.0f, 0.1f, 0.0f, 1.0f);

		pVtx += 4;		//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	s_pVtxBuff->Unlock();
}

//================================================
//タイムの終了処理
//================================================
void UninitTime(void)
{
	for (int nCnt = 0; nCnt < TIME_MAX; nCnt++)
	{
		if (s_pTexture != NULL)
		{//テクスチャの破棄
			s_pTexture->Release();
			s_pTexture = NULL;
		}
	}
	
	if (s_pVtxBuff != NULL)
	{//頂点バッファの破棄
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}
}

//================================================
//タイムの更新処理
//================================================
void UpdateTime(void)
{
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (s_nTime <= 10 && s_nTime >= 0)
	{//残り時間10秒の時
		for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
		{
			//頂点カラーの更新
			SetCol2D(pVtx, 1.0f, 0.0f, 0.0f, 1.0f);
			
			pVtx += 4;		//ポインタを4つ分進める
		}
	}

	//頂点バッファをアンロックする
	s_pVtxBuff->Unlock();

	s_nCntTime++;		//カウントアップ

	if (s_nCntTime % 60 == 0)
	{//時間経過
		SubTime(1);
	}

	//タイムオーバー時の画面遷移
	if (GetFade() == FADE_NONE)
	{//フェードしていないとき
		if (s_nTime <= 0)
		{//タイムオーバーになったら
			//終了状態に設定
			SetGameState(GAMESTATE_END);
		}
	}
}

//================================================
//タイムの描画処理
//================================================
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < TIME_MAX; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, s_pTexture);

		//タイムの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
								nCnt * 4,				//描画する最初の頂点インデックス
								2 * TIME_MAX);			//描画するプリミティブ数
	}
}

//================================================
//タイムの設定処理
//================================================
void SetTime(int nTime)
{
	VERTEX_2D *pVtx;			//頂点情報へのポインタ
	int aPosTexU[TIME_MAX];		//各桁の数字を格納

	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	s_nTime		= nTime;
	aPosTexU[0] = s_nTime % 1000 / 100;
	aPosTexU[1] = s_nTime % 100 / 10;
	aPosTexU[2] = s_nTime % 10 / 1;

	//テクスチャ座標の設定
	for (int nCnt = 0; nCnt < TIME_MAX; nCnt++)
	{
		SetTex2D(pVtx, 0.0f + (aPosTexU[nCnt] * 0.1f), 
					   0.1f + (aPosTexU[nCnt] * 0.1f), 
					   0.0f,
					   1.0f);

		pVtx += 4;		//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	s_pVtxBuff->Unlock();
}

//================================================
//タイムの取得
//================================================
int GetTime(void)
{
	return s_nTime;
}

namespace
{
//------------------------------------------------
//タイムの減算処理
//------------------------------------------------
static void SubTime(int nValue)
{
	VERTEX_2D *pVtx;			//頂点情報へのポインタ
	int aPosTexU[TIME_MAX];		//各桁の数字を格納

	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (s_nTime > 0)
	{//タイムが0より大きい
		s_nTime -= nValue;
	}

	aPosTexU[0] = s_nTime % 1000 / 100;
	aPosTexU[1] = s_nTime % 100 / 10;
	aPosTexU[2] = s_nTime % 10 / 1;

	//テクスチャ座標の設定
	for (int nCnt = 0; nCnt < TIME_MAX; nCnt++)
	{
		SetTex2D(pVtx, 0.0f + (aPosTexU[nCnt] * 0.1f),
			0.1f + (aPosTexU[nCnt] * 0.1f),
			0.0f,
			1.0f);

		pVtx += 4;		//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	s_pVtxBuff->Unlock();
}
}//namespaceはここまで