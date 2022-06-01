//================================================
//
//C++_STG(仮)[title.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "title.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "mode.h"

//***************************
//列挙型の定義
//***************************
namespace
{
/* タイトルで使用するテクスチャの種類 */
typedef enum
{
	TEX_TITLE_BG = 0,	//背景
	TEX_TITLE_LOGO,		//タイトルロゴ
	TEX_TITLE_START,	//ゲーム開始
	TEX_TITLE_TUTORIAL,	//チュートリアル
	TEX_TITLE_END,		//ゲーム終了
	TEX_TITLE_MAX
}TEX_TITLE;

/* タイトルロゴの状態 */
typedef enum
{
	TITLELOGO_POP = 0,	//出現状態
	TITLELOGO_NORMAL,	//通常状態
	TITLELOGO_MAX
}TITLELOGO;

/* タイトルメニュー */
typedef enum
{
	TITLE_MENU_START = 0,	//ゲーム開始
	TITLE_MENU_TUTORIAL,	//チュートリアル
	TITLE_MENU_END,			//ゲーム終了
	TITLE_MENU_MAX
}TITLE_MENU;
}//namespaceはここまで

 //***************************
 //構造体の定義
 //***************************
namespace
{
/* タイトルメニュー */
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXCOLOR col;		//色
}TitleMenu;
}//namespaceはここまで

//***************************
//定数の定義
//***************************
namespace
{
/* タイトルメニュー */
const int	TITLE_MENU_SPACE		= 90;	//間隔
const float TITLE_MENU_WIDTH	= 150.0f;	//幅
const float TITLE_MENU_HEIGHT	= 75.0f;	//高さ
const float MENU_FADE_SPEED		= 0.015f;	//点滅スピード(通常)
const float MENU_FADE_HIGHSPEED = 0.4f;		//点滅スピード(高速)

/* タイトルロゴ */
const float LOGO_WIDTH	= 400.0f;	//幅
const float LOGO_HEIGHT = 230.0f;	//高さ
const float LOGO_SPEED	= 3.0f;		//スピード
}//namespaceはここまで

//***************************
//スタティック変数
//***************************
namespace
{
LPDIRECT3DTEXTURE9		s_apTexture[TEX_TITLE_MAX];		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9	s_pVtxBuff = NULL;				//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9	s_pVtxBuffTitleMenu = NULL;		//			"

/* タイトルメニュー */
TitleMenu	s_aTitleMenu[TITLE_MENU_MAX];	//タイトルメニューの情報
TITLE_MENU	s_MenuType;						//タイトルメニューの種類
FADE		s_fadeTitleMenu;				//タイトルメニューの点滅状態

/* タイトルロゴ */
D3DXVECTOR3 s_posTitleLogo;			//タイトルロゴの位置
TITLELOGO	s_TitleLogo;			//タイトルロゴの状態
bool		s_bGameEnd = false;		//ゲームを終了するかどうか
}//namespaceはここまで

//***************************
//プロトタイプ宣言
//***************************
namespace
{
void UpdateNormal(void);
void UpdatePop(void);
void SelectMenu(VERTEX_2D *pVtx, TitleMenu *pTM);
void BlinkMenu(TitleMenu *pTM);
}//namespaceはここまで

//================================================
//タイトルの初期化処理
//================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	VERTEX_2D *pVtx;							//頂点情報へのポインタ

	//テクスチャポインタの初期化
	memset(s_apTexture, NULL, sizeof(s_apTexture));

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/Title_BG.png",
								&s_apTexture[TEX_TITLE_BG]);		//背景

	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/Title.png",
								&s_apTexture[TEX_TITLE_LOGO]);		//タイトルロゴ

	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/GameStart.png",
								&s_apTexture[TEX_TITLE_START]);		//ゲーム開始

	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/Tutorial.png",
								&s_apTexture[TEX_TITLE_TUTORIAL]);	//チュートリアル

	D3DXCreateTextureFromFile(pDevice,
								"data/TEXTURE/GameEnd.png",
								&s_apTexture[TEX_TITLE_END]);		//ゲーム終了

	//情報の初期化
	for (int i = 0; i < TITLE_MENU_MAX; i++)
	{
		float fPosX = (float)(SCREEN_WIDTH / 2);				//タイトルメニューの位置( X )
		float fPosY = (float)(480 + (i * TITLE_MENU_SPACE));		//タイトルメニューの位置( Y )

		s_aTitleMenu[i].pos = D3DXVECTOR3(fPosX, fPosY, 0.0f);
		s_aTitleMenu[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//変数の初期化
	s_MenuType		= TITLE_MENU_START;									//メニュータイプ
	s_fadeTitleMenu	= FADE_IN;											//メニューの点滅状態
	s_posTitleLogo  = D3DXVECTOR3((SCREEN_WIDTH / 2), -250.0f, 0.0f);	//タイトルロゴの位置
	s_TitleLogo		= TITLELOGO_POP;									//タイトルロゴの状態

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&s_pVtxBuff,
								NULL);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TITLE_MENU_MAX,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&s_pVtxBuffTitleMenu,
								NULL);

	/********************* 背景画像 & タイトルロゴ *********************/

	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < 2; i++)
	{
		if (i == 0)
		{//背景
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		}
		else if (i == 1)
		{//タイトルロゴ
			//頂点座標の設定
			float fLeft		= (s_posTitleLogo.x - LOGO_WIDTH);
			float fRight	= (s_posTitleLogo.x + LOGO_WIDTH);
			float fTop		= (s_posTitleLogo.y - LOGO_HEIGHT);
			float fBottom	= (s_posTitleLogo.y + LOGO_HEIGHT);

			pVtx[0].pos = D3DXVECTOR3(fLeft,  fTop,	   0.0f);
			pVtx[1].pos = D3DXVECTOR3(fRight, fTop,	   0.0f);
			pVtx[2].pos = D3DXVECTOR3(fLeft,  fBottom, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(fRight, fBottom, 0.0f);
		}

		//rhwの設定
		SetRhw(pVtx, 1.0f);

		//頂点カラーの設定
		SetCol2D(pVtx, 1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		SetTex2D(pVtx, 0.0f, 1.0f, 0.0f, 1.0f);

		pVtx += 4;		//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	s_pVtxBuff->Unlock();

	/********************* タイトルメニュー *********************/

	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuffTitleMenu->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TITLE_MENU_MAX; i++)
	{//タイトルメニュー
		TitleMenu *pTM = &s_aTitleMenu[i];		//ポインタに変身

		//頂点座標の設定
		float fLeft		= (pTM->pos.x - TITLE_MENU_WIDTH);
		float fRight	= (pTM->pos.x + TITLE_MENU_WIDTH);
		float fTop		= (pTM->pos.y - TITLE_MENU_HEIGHT);
		float fBottom	= (pTM->pos.y + TITLE_MENU_HEIGHT);

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
	s_pVtxBuffTitleMenu->Unlock();
}

//================================================
//タイトルの終了処理
//================================================
void UninitTitle(void)
{
	//サウンドの停止
	StopSound();

	/********************* テクスチャの破棄 *********************/

	for (int i = 0; i < TEX_TITLE_MAX; i++)
	{
		if (s_apTexture[i] != NULL)
		{
			s_apTexture[i]->Release();
			s_apTexture[i] = NULL;
		}
	}

	/********************* 頂点バッファの破棄 *********************/

	if (s_pVtxBuff != NULL)
	{//背景画像 & タイトルロゴ
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}

	if (s_pVtxBuffTitleMenu != NULL)
	{//タイトルメニュー
		s_pVtxBuffTitleMenu->Release();
		s_pVtxBuffTitleMenu = NULL;
	}
}

//================================================
//タイトルの更新処理
//================================================
void UpdateTitle(void)
{
	switch (s_TitleLogo)
	{//タイトルロゴの状態
	case TITLELOGO_NORMAL:	//通常状態
		UpdateNormal();		//通常状態の更新
		break;

	case TITLELOGO_POP:		//出現状態
		UpdatePop();	//出現状態の更新
		break;
	}
}

//================================================
//タイトルの描画処理
//================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	/********************* 背景画像 & タイトルロゴ *********************/

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < 2; i++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, s_apTexture[i]);
	
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
								i * 4,					//描画する最初の頂点インデックス
								2);						//描画するプリミティブ数
	}
	
	/********************* タイトルメニュー *********************/

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, s_pVtxBuffTitleMenu, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < (int)(TEX_TITLE_MAX - 2); i++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, s_apTexture[i + 2]);

		if (s_TitleLogo == TITLELOGO_NORMAL)
		{//タイトルロゴが通常状態になったら
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
									i * 4,					//描画する最初の頂点インデックス
									2);						//描画するプリミティブ数

		}
	}
}

//================================================
//ゲーム終了の合図
//================================================
bool EndGame(void)
{
	return s_bGameEnd;
}

namespace
{
//------------------------------------------------
//通常状態の更新
//------------------------------------------------
static void UpdateNormal(void)
{
	VERTEX_2D *pVtx = NULL;							//頂点情報へのポインタ
	TitleMenu *pTM = &s_aTitleMenu[s_MenuType];		//ポインタに変身

	//タイトルメニューの選択
	SelectMenu(pVtx, pTM);

	//タイトルメニューの点滅
	BlinkMenu(pTM);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuffTitleMenu->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (s_MenuType * 4);	//ポインタを該当の位置まで進める

	//頂点カラーの設定
	SetCol2D(pVtx, pTM->col.r, pTM->col.g, pTM->col.b, pTM->col.a);

	//頂点バッファをアンロックする
	s_pVtxBuffTitleMenu->Unlock();
}

//------------------------------------------------
//出現状態の更新
//------------------------------------------------
static void UpdatePop(void)
{
	float fHomePos = (float)(SCREEN_HEIGHT / 6 * 1.9f);	//タイトルロゴの定位置

	//タイトルロゴを徐々に降ろす
	s_posTitleLogo.y += LOGO_SPEED;

	if (s_posTitleLogo.y >= fHomePos || GetKeyboardTrigger(DIK_RETURN))
	{//定位置を越したら or Enterキーが押されたら
		//定位置にする
		s_posTitleLogo.y = fHomePos;

		//通常状態にする
		s_TitleLogo = TITLELOGO_NORMAL;
	}

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4;		//タイトルロゴにする

	//頂点座標の更新
	float fLeft		= (s_posTitleLogo.x - LOGO_WIDTH);
	float fRight	= (s_posTitleLogo.x + LOGO_WIDTH);
	float fTop		= (s_posTitleLogo.y - LOGO_HEIGHT);
	float fBottom	= (s_posTitleLogo.y + LOGO_HEIGHT);

	pVtx[0].pos = D3DXVECTOR3(fLeft, fTop, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(fRight, fTop, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(fLeft, fBottom, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(fRight, fBottom, 0.0f);

	//頂点バッファをアンロックする
	s_pVtxBuff->Unlock();
}

//------------------------------------------------
//タイトルメニューの選択
//------------------------------------------------
static void SelectMenu(VERTEX_2D *pVtx, TitleMenu *pTM)
{
	if (GetFade() != FADE_NONE)
	{//フェードしているとき
		return;
	}

	/* フェードしていないとき */

	/********************* 選択中のメニューの色を変える *********************/

		//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuffTitleMenu->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardTrigger(DIK_W))
	{//Wキーが押された
		//サウンドの再生
		PlaySound(SOUND_LABEL_SE_SELECT);

		//白にする
		pTM->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);

		pVtx += (s_MenuType * 4);		//ポインタを該当の位置まで進める

		 //頂点カラーの設定
		SetCol2D(pVtx, pTM->col.r, pTM->col.g, pTM->col.b, pTM->col.a);

		//1つ上を選ぶ
		s_MenuType = (TITLE_MENU)(((s_MenuType - 1) + 3) % 3);
	}

	if (GetKeyboardTrigger(DIK_S))
	{//Sキーが押された
		//サウンドの再生
		PlaySound(SOUND_LABEL_SE_SELECT);

		//白にする
		pTM->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);

		pVtx += (s_MenuType * 4);		//ポインタを該当の位置まで進める

		//頂点カラーの設定
		SetCol2D(pVtx, pTM->col.r, pTM->col.g, pTM->col.b, pTM->col.a);

		//1つ下を選ぶ
		s_MenuType = (TITLE_MENU)(((s_MenuType + 1) + 3) % 3);
	}

	//頂点バッファをアンロックする
	s_pVtxBuffTitleMenu->Unlock();

	pTM = &s_aTitleMenu[s_MenuType];	//選択中のメニュー

	//選択部分の色を変える
	pTM->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	/********************* 選択したメニュー毎の処理 *********************/

	if (s_TitleLogo == TITLELOGO_NORMAL && GetKeyboardTrigger(DIK_RETURN))
	{//タイトルロゴが通常状態 & Enterキーが押された
		switch (s_MenuType)
		{
		case TITLE_MENU_START:	//ゲーム開始
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_DECIDE);

			//ゲーム画面に移行
			ChangeMode(MODE_GAME);
			break;

		case TITLE_MENU_TUTORIAL:	//チュートリアル
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_DECIDE);

			//チュートリアル画面に移行
			ChangeMode(MODE_TUTORIAL);
			break;

		case TITLE_MENU_END:	//ゲーム終了

			//ゲーム終了の合図
			s_bGameEnd = true;
			bool* end = GetEnd();
			*end = true;
			break;
		}
	}
}

//------------------------------------------------
//タイトルメニューの点滅
//------------------------------------------------
static void BlinkMenu(TitleMenu *pTM)
{
	if (GetFade() == FADE_NONE)
	{//フェードしていない
		if (s_fadeTitleMenu == FADE_IN)
		{//透明にするとき
			pTM->col.a -= MENU_FADE_SPEED;		//透明にしていく

			if (pTM->col.a <= 0.0f)
			{//0.0fを過ぎたら
				pTM->col.a = 0.0f;				//0.0fに戻す
				s_fadeTitleMenu = FADE_OUT;		//不透明にする状態に
			}
		}
		else if (s_fadeTitleMenu == FADE_OUT)
		{//不透明にするとき
			pTM->col.a += MENU_FADE_SPEED;		//不透明にしていく

			if (pTM->col.a >= 1.0f)
			{//1.0fを過ぎたら
				pTM->col.a = 1.0f;				//1.0fに戻す
				s_fadeTitleMenu = FADE_IN;		//透明にする状態に
			}
		}
	}
	else if (GetFade() == FADE_OUT)
	{//フェードアウト状態のとき
		if (s_fadeTitleMenu == FADE_IN)
		{//透明にするとき
			pTM->col.a -= MENU_FADE_HIGHSPEED;	//透明にしていく

			if (pTM->col.a <= 0.0f)
			{//0.0fを過ぎたら
				pTM->col.a = 0.0f;				//0.0fに戻す
				s_fadeTitleMenu = FADE_OUT;		//不透明にする状態に
			}
		}
		else if (s_fadeTitleMenu == FADE_OUT)
		{//不透明にするとき
			pTM->col.a += MENU_FADE_HIGHSPEED;	//不透明にしていく

			if (pTM->col.a >= 1.0f)
			{//1.0fを過ぎたら
				pTM->col.a = 1.0f;				//1.0fに戻す
				s_fadeTitleMenu = FADE_IN;		//透明にする状態に
			}
		}
	}
}
}//namespaceはここまで