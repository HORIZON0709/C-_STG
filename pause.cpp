//================================================
//
//C++_STG(仮)[pause.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "pause.h"
#include "input.h"
#include "game.h"
#include "sound.h"
#include "fade.h"
#include "mode.h"

//***************************
//マクロ定義
//***************************
namespace
{
const int NUM_PAUSE			= 4;		//ポーズの種類
const int PAUSEMENU_WIDTH	= 300;		//ポーズメニューの幅
const int PAUSEMENU_HEIGHT	= 100;		//ポーズメニューの高さ
const int PAUSEMENU_SPACE	= 220;		//ポーズメニューの間隔
const int PAUSE_WIDTH		= 200;		//ポーズの幅
const int PAUSE_HEIGHT		= 200;		//ポーズの高さ
}//namespaceはここまで

//***************************
//スタティック変数
//***************************
namespace
{
LPDIRECT3DTEXTURE9		s_apTexture[NUM_PAUSE];			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffPause = NULL;			//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffPauseMenu = NULL;		//頂点バッファへのポインタ
PAUSE_MENU				s_pauseMenu;					//ポーズメニュー
PauseMenu				s_aPauseMenu[PAUSE_MENU_MAX];	//ポーズメニューの情報
D3DXVECTOR3				s_posPause;						//ポーズの位置
}//namespaceはここまで

//***************************
//プロトタイプ宣言
//***************************
namespace
{
void SelectMenu(VERTEX_2D *pVtx, PauseMenu *pPM);
}//namespaceはここまで

//================================================
//ポーズの初期化処理
//================================================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	VERTEX_2D *pVtx;							//頂点情報へのポインタ

	//テクスチャポインタの初期化
	memset(s_apTexture, NULL, sizeof(s_apTexture));

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/Back_To_Game.png",
								&s_apTexture[0]);

	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/Restart.png",
								&s_apTexture[1]);

	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/Back_To_Title.png",
								&s_apTexture[2]);

	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/pause100.png",
								&s_apTexture[3]);

	//情報の初期化
	for (int i = 0; i < PAUSE_MENU_MAX; i++)
	{
		float fPosX = (float)(SCREEN_WIDTH / 2);				//ポーズメニューの位置( X )
		float fPosY = (float)(150.0f + (i * PAUSEMENU_SPACE));	//ポーズメニューの位置( Y )

		s_aPauseMenu[i].pos = D3DXVECTOR3(fPosX, fPosY, 0.0f);
		s_aPauseMenu[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//変数の初期化
	s_pauseMenu = PAUSE_MENU_CONTINUE;					//ポーズメニュー
	s_posPause	= D3DXVECTOR3(640.0f, 360.0f, 0.0f);	//ポーズの位置

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&s_pVtxBuffPause,
								NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * PAUSE_MENU_MAX,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&s_pVtxBuffPauseMenu,
								NULL);

	/********************* 半透明ポリゴン & ポーズ背景 *********************/

	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < 2; i++)
	{
		if (i == 0)
		{//ポーズの半透明ポリゴン
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		}
		else if (i == 1)
		{//ポーズ
			//頂点座標の設定
			float fLeft		= (s_posPause.x - PAUSE_WIDTH);
			float fRight	= (s_posPause.x + PAUSE_WIDTH);
			float fTop		= (s_posPause.y - PAUSE_HEIGHT);
			float fBottom	= (s_posPause.y + PAUSE_HEIGHT);

			pVtx[0].pos = D3DXVECTOR3(fLeft,  fTop,	   0.0f);
			pVtx[1].pos = D3DXVECTOR3(fRight, fTop,	   0.0f);
			pVtx[2].pos = D3DXVECTOR3(fLeft,  fBottom, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(fRight, fBottom, 0.0f);
		}

		//rhwの設定
		SetRhw(pVtx, 1.0f);

		if (i == 0)
		{//ポーズの半透明ポリゴン
			//頂点カラーの設定
			SetCol2D(pVtx, 0.0f, 0.0f, 0.0f, 0.75f);
		}
		else if (i == 1)
		{//ポーズ
			//頂点カラーの設定
			SetCol2D(pVtx, 0.3f, 0.0f, 0.0f, 0.0f);
		}

		//テクスチャ座標の設定
		SetTex2D(pVtx, 0.0f, 1.0f, 0.0f, 1.0f);

		pVtx += 4;		//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	s_pVtxBuffPause->Unlock();

	/********************* ポーズメニュー *********************/

	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < PAUSE_MENU_MAX; i++)
	{//ポーズメニュー
		PauseMenu *pPM = &s_aPauseMenu[i];		//ポインタに変身

		//頂点座標の設定
		float fLeft		= (pPM->pos.x - PAUSEMENU_WIDTH);
		float fRight	= (pPM->pos.x + PAUSEMENU_WIDTH);
		float fTop		= (pPM->pos.y - PAUSEMENU_HEIGHT);
		float fBottom	= (pPM->pos.y + PAUSEMENU_HEIGHT);

		pVtx[0].pos = D3DXVECTOR3(fLeft,  fTop,	   0.0f);
		pVtx[1].pos = D3DXVECTOR3(fRight, fTop,	   0.0f);
		pVtx[2].pos = D3DXVECTOR3(fLeft,  fBottom, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(fRight, fBottom, 0.0f);

		//rhwの設定
		SetRhw(pVtx, 1.0f);

		//頂点カラーの設定
		SetCol2D(pVtx, 1.0f, 1.0f, 1.0f, 0.3f);

		//テクスチャ座標の設定
		SetTex2D(pVtx, 0.0f, 1.0f, 0.0f, 1.0f);

		pVtx += 4;		//ポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	s_pVtxBuffPauseMenu->Unlock();
}

//================================================
//ポーズの終了処理
//================================================
void UninitPause(void)
{
	//サウンドの停止
	StopSound();

	/********************* テクスチャの破棄 *********************/

	for (int i = 0; i < NUM_PAUSE; i++)
	{
		if (s_apTexture[i] != NULL)
		{
			s_apTexture[i]->Release();
			s_apTexture[i] = NULL;
		}
	}

	/********************* 頂点バッファの破棄 *********************/
	
	if (s_pVtxBuffPause != NULL)
	{//半透明ポリゴン & ポーズ背景
		s_pVtxBuffPause->Release();
		s_pVtxBuffPause = NULL;
	}

	if (s_pVtxBuffPauseMenu != NULL)
	{//ポーズメニューの方
		s_pVtxBuffPauseMenu->Release();
		s_pVtxBuffPauseMenu = NULL;
	}
}

//================================================
//ポーズの更新処理
//================================================
void UpdatePause(void)
{
	VERTEX_2D *pVtx = NULL;							//頂点情報へのポインタ
	PauseMenu *pPM = &s_aPauseMenu[s_pauseMenu];	//ポインタに変身

	//ポーズメニューの選択
	SelectMenu(pVtx, pPM);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (s_pauseMenu * 4);		//ポインタを該当の位置まで進める

	//頂点カラーの設定
	SetCol2D(pVtx, pPM->col.r, pPM->col.g, pPM->col.b, pPM->col.a);

	//頂点バッファをアンロックする
	s_pVtxBuffPauseMenu->Unlock();
}

//================================================
//ポーズの描画処理
//================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	/********************* 半透明ポリゴン & ポーズ背景 *********************/

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, s_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < 2; i++)
	{
		if (i == 0)
		{//ポーズの半透明ポリゴン
			//テクスチャの設定
			pDevice->SetTexture(0, NULL);
		}
		else if (i == 1)
		{//ポーズ
			//テクスチャの設定
			pDevice->SetTexture(0, s_apTexture[3]);
		}

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
								i * 4,					//描画する最初の頂点インデックス
								2);						//描画するプリミティブ数
	}

	/********************* ポーズメニューの方 *********************/

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, s_pVtxBuffPauseMenu, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < PAUSE_MENU_MAX; i++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, s_apTexture[i]);

		//ポーズの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
								i * 4,					//描画する最初の頂点インデックス
								2);						//描画するプリミティブ数
	}
}

namespace
{
//------------------------------------------------
//ポーズメニューの選択
//------------------------------------------------
static void SelectMenu(VERTEX_2D *pVtx, PauseMenu *pPM)
{
	if (GetFade() != FADE_NONE)
	{//フェードしているとき
		return;
	}

	/* フェードしていないとき */

	/********************* 選択中のメニューの色を変える *********************/

		//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardTrigger(DIK_W))
	{//Wキーが押された
		//サウンドの再生
		PlaySound(SOUND_LABEL_SE_SELECT);

		//白にする
		pPM->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);

		pVtx += (s_pauseMenu * 4);		//ポインタを該当の位置まで進める

		 //頂点カラーの設定
		SetCol2D(pVtx, pPM->col.r, pPM->col.g, pPM->col.b, pPM->col.a);

		//1つ上を選ぶ
		s_pauseMenu = (PAUSE_MENU)(((s_pauseMenu - 1) + 3) % 3);
	}

	if (GetKeyboardTrigger(DIK_S))
	{//Sキーが押された
		//サウンドの再生
		PlaySound(SOUND_LABEL_SE_SELECT);

		//白にする
		pPM->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);

		pVtx += (s_pauseMenu * 4);		//ポインタを該当の位置まで進める

		//頂点カラーの設定
		SetCol2D(pVtx, pPM->col.r, pPM->col.g, pPM->col.b, pPM->col.a);

		//1つ下を選ぶ
		s_pauseMenu = (PAUSE_MENU)(((s_pauseMenu + 1) + 3) % 3);
	}

	//頂点バッファをアンロックする
	s_pVtxBuffPauseMenu->Unlock();

	pPM = &s_aPauseMenu[s_pauseMenu];	//選択中のメニュー

	//選択部分の色を変える
	pPM->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	/********************* 選択したメニュー毎の処理 *********************/

	if (GetKeyboardTrigger(DIK_RETURN))
	{//Enterキーが押された
		switch (s_pauseMenu)
		{
		case PAUSE_MENU_CONTINUE:	//ゲームに戻る
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_CANCEL);

			//ポーズ解除
			SetEnablePause(false);
			break;

		case PAUSE_MENU_RETRY:		//ゲームをやり直す
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_DECIDE);

			//ゲーム画面に移行
			ChangeMode(MODE_GAME);
			break;

		case PAUSE_MENU_QUIT:		//タイトル画面に戻る
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_DECIDE);

			//タイトル画面に移行
			ChangeMode(MODE_TITLE);
			break;
		}
	}
}
}//namespaceはここまで