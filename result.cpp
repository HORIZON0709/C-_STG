//================================================
//
//C++_STG(仮)[result.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "result.h"
#include "input.h"
#include "fade.h"
#include "mode.h"

//***************************
//列挙型の定義
//***************************
namespace
{
/* ゲーム結果 */
typedef enum
{
	GAME_OVER = 0,		//ゲームオーバー
	GAME_CLEAR,			//ゲームクリア
	GAME_MAX
}GAME_RESULT;
}//namespaceはここまで

//***************************
//スタティック変数
//***************************
namespace
{
LPDIRECT3DTEXTURE9		s_apTexture[GAME_MAX];		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9	s_pVtxBuff = NULL;			//頂点バッファへのポインタ
}//namespaceはここまで

//================================================
//リザルトの初期化処理
//================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	VERTEX_2D *pVtx;							//頂点情報へのポインタ

	//テクスチャポインタの初期化
	memset(s_apTexture, NULL, sizeof(s_apTexture));

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/GameOver.png",
								&s_apTexture[GAME_OVER]);

	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/GameClear.png",
								&s_apTexture[GAME_CLEAR]);

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
//リザルトの終了処理
//================================================
void UninitResult(void)
{
	for (int i = 0; i < GAME_MAX; i++)
	{
		if (s_apTexture[i] != NULL)
		{//テクスチャの破棄
			s_apTexture[i]->Release();
			s_apTexture[i] = NULL;
		}
	}

	if (s_pVtxBuff != NULL)
	{//頂点バッファの破棄
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}
}

//================================================
//リザルトの更新処理
//================================================
void UpdateResult(void)
{
	if ((GetFade() == FADE_NONE) && (GetKeyboardTrigger(DIK_RETURN)))
	{//フェードしていないとき & Enterキーが押されたら
		//タイトル画面に移行
		ChangeMode(MODE_TITLE);
	}
}

//================================================
//リザルトの描画処理
//================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, s_apTexture[GAME_CLEAR]);

	//リザルトの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
							0,						//描画する最初の頂点インデックス
							2);						//描画するプリミティブ数
}