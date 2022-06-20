//================================================
//
//C++_STG(仮)[game.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "game.h"

#include "player.h"
#include "pause.h"
#include "camera.h"
#include "light.h"
#include "polygon3D.h"
#include "time.h"
#include "bullet.h"
#include "enemy.h"

#include "input.h"
#include "mode.h"
#include "sound.h"

//***************************
//定数の定義
//***************************
namespace
{
const int TIME_LIMIT = 100;		//制限時間
}//namespaceはここまで

//***************************
//スタティック変数
//***************************
namespace
{
GAMESTATE	s_gameState = GAMESTATE_NONE;	//ゲームの状態
int			s_nCounterGameState = 0;		//状態管理カウンター
bool		s_pPause = false;				//ポーズ中かどうか

CPolygon3D s_polygon;
CPlayer s_player;
CBullet s_bullet;
CEnemy s_enemy;
}//namespaceはここまで

//================================================
//ゲームの初期化処理
//================================================
void InitGame(void)
{
	InitCamera();	//カメラ
	InitLight();	//ライト
	s_polygon.Init();	//ポリゴン
	s_player.Init();	//プレイヤー
	s_bullet.Init();	//弾
	s_enemy.Init();		//敵
	InitPause();	//ポーズ

	//タイムの設定
	InitTime();
	SetTime(TIME_LIMIT);

	s_gameState			= GAMESTATE_NORMAL;		//通常状態
	s_nCounterGameState = 0;					//カウンターの初期化
	s_pPause			= false;				//ポーズ解除
}

//================================================
//ゲームの終了処理
//================================================
void UninitGame(void)
{
	//サウンドの停止
	StopSound();

	UninitCamera();		//カメラ
	UninitLight();		//ライト
	s_bullet.Uninit();		//弾
	s_player.Uninit();		//プレイヤー
	s_enemy.Uninit();		//敵
	s_polygon.Uninit();		//ポリゴン
	UninitTime();		//タイム
	UninitPause();		//ポーズ
}

//================================================
//ゲームの更新処理
//================================================
void UpdateGame(void)
{
	/****************** ポーズ ******************/

	if ((s_gameState == GAMESTATE_NORMAL) && GetKeyboardTrigger(DIK_P))
	{//通常状態 & Pキーが押された
		s_pPause = s_pPause ? false : true;

		if (s_pPause)
		{//ポーズ中
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_PAUSE);
		}
		else
		{//ポーズ中ではない
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_CANCEL);
		}
	}

	if (s_pPause)
	{//ポーズ中
		//ポーズの更新処理
		UpdatePause();
		return;
	}

	/* ポーズ中でなければ */

	switch (s_gameState)
	{
	case GAMESTATE_NORMAL:	/* 通常状態 */
		UpdateCamera();		//カメラ
		UpdateLight();		//ライト
		s_polygon.Update();		//ポリゴン
		s_bullet.Update();		//弾
		s_player.Update();		//プレイヤー
		s_enemy.Update();		//敵
		UpdateTime();		//タイム
		break;

	case GAMESTATE_END:		/* 終了状態 */

		s_nCounterGameState++;		//カウンターを進める

		if (s_nCounterGameState >= 60)
		{//一定時間たったら
			s_gameState = GAMESTATE_NONE;		//何もしていない状態

			//リザルト画面へ
			ChangeMode(MODE_RESULT);
		}
		break;
	}
}

//================================================
//ゲームの描画処理
//================================================
void DrawGame(void)
{
	//カメラの設定
	SetCamera();

	s_polygon.Draw();	//ポリゴン
	s_bullet.Draw();	//弾
	s_player.Draw();	//プレイヤー
	s_enemy.Draw();		//敵
	DrawTime();		//タイム

	if (s_pPause)
	{//ポーズ中
		//ポーズの描画処理
		DrawPause();
	}
}

//================================================
//ゲームの設定処理
//================================================
void SetGameState(GAMESTATE state)
{
	s_gameState	= state;
	s_nCounterGameState = 0;
}

//================================================
//ゲームの取得処理
//================================================
GAMESTATE GetGamaState(void)
{
	return s_gameState;
}

//================================================
//ポーズの有効無効設定
//================================================
void SetEnablePause(bool bPause)
{
	s_pPause = bPause;
}