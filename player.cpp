//================================================
//
//C++_STG(仮)[player.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "player.h"
#include "bullet.h"

#include "rectangle3D.h"
#include "texture.h"
#include "input.h"
#include "sound.h"

#include <assert.h>

//***************************
//静的メンバ変数宣言
//***************************
CPlayer* CPlayer::m_pPlayer = nullptr;	//ポインタ
const float CPlayer::MOVE_SPEED = 8.0f;		//移動スピード

//================================================
//情報を取得
//================================================
CPlayer* CPlayer::GetInfo()
{
	return m_pPlayer;
}

//================================================
//コンストラクタ
//================================================
CPlayer::CPlayer():
	m_nInterval(0), 
	nBulletType(0)
{
}

//================================================
//デストラクタ
//================================================
CPlayer::~CPlayer()
{
}

//================================================
//初期化
//================================================
void CPlayer::Init()
{
	if (m_pPlayer != nullptr)
	{//NULLチェック
		return;
	}

	/* nullptrの場合 */

	m_pPlayer = new CPlayer;	//メモリの動的確保

	//メンバ変数の初期化
	m_pPlayer->m_nInterval = SHOT_INTERVAL;
	m_pPlayer->nBulletType = (int)BULLET_TYPE::NORMAL;

	//矩形のインデックスの設定
	m_pPlayer->m_nIdx = SetRectangle3D(TEXTURE_百鬼あやめ_4);

	//位置とサイズの初期設定
	m_pPlayer->m_pos = D3DXVECTOR3(0.0f, 0.0f, -20.0f);
	m_pPlayer->m_size = D3DXVECTOR3(100.0f, 100.0f, 0.0f);

	/* 矩形の設定 */
	SetPosRectangle3D(m_pPlayer->m_nIdx, m_pPlayer->m_pos);		//位置
	SetSizeRectangle3D(m_pPlayer->m_nIdx, m_pPlayer->m_size);	//サイズ
}

//================================================
//終了
//================================================
void CPlayer::Uninit()
{
	// 使うのを止める
	StopUseRectangle3D(m_pPlayer->m_nIdx);

	if (m_pPlayer == nullptr)
	{//NULLチェック
		return;
	}

	/* nullptrではない場合 */

	//メモリの解放
	delete m_pPlayer;
	m_pPlayer = nullptr;
}

//================================================
//更新
//================================================
void CPlayer::Update()
{
	if (GetKeyboardTrigger(DIK_F3))
	{//タイプ切り替え
		m_pPlayer->nBulletType = (m_pPlayer->nBulletType + 1) % (int)BULLET_TYPE::MAX;
	}

	//移動
	Move();

	//弾の発射
	Shot();

	//位置の更新
	SetPosRectangle3D(m_pPlayer->m_nIdx, m_pPlayer->m_pos);
}

//================================================
//描画
//================================================
void CPlayer::Draw()
{
	// 矩形の描画
	DrawRectangle3D();
}

//================================================
//移動
//================================================
void CPlayer::Move()
{
	if (GetMoveKeyPress(MOVE_KEY_LEFT))
	{//左移動
		m_pPlayer->m_pos.x -= MOVE_SPEED;
	}
	else if (GetMoveKeyPress(MOVE_KEY_RIGHT))
	{//右移動
		m_pPlayer->m_pos.x += MOVE_SPEED;
	}

	if (GetMoveKeyPress(MOVE_KEY_UP))
	{//上移動
		m_pPlayer->m_pos.y += MOVE_SPEED;
	}
	else if (GetMoveKeyPress(MOVE_KEY_DOWN))
	{//下移動
		m_pPlayer->m_pos.y -= MOVE_SPEED;
	}
}

//================================================
//弾の発射
//================================================
void CPlayer::Shot()
{
	/* 弾の設定用変数 */
	D3DXVECTOR3 pos = m_pPlayer->m_pos;					//位置
	D3DXVECTOR3 move = D3DXVECTOR3(10.0f, 5.0f, 0.0f);	//移動量
	D3DXVECTOR3 size = D3DXVECTOR3(25.0f, 25.0f, 0.0f);	//サイズ

	if (GetKeyboardPress(DIK_SPACE))
	{//長押し(というか押しっぱなし)
		m_pPlayer->m_nInterval++;	//カウントアップ

		if (m_pPlayer->m_nInterval < SHOT_INTERVAL)
		{//間隔のカウントが規定値を越していない
			return;
		}

		/* 間隔カウントが規定値を越したら */

		CBullet bullet;

		switch ((BULLET_TYPE)m_pPlayer->nBulletType)
		{
		case BULLET_TYPE::NORMAL: /* 通常 */

			/* 弾の発射 */
			bullet.Set(pos, D3DXVECTOR3(move.x, 0.0f, 0.0f), size);
			break;

		case BULLET_TYPE::DOUBLE: /* 2発同時 */
			
			/* 弾の発射 */
			bullet.Set(D3DXVECTOR3(pos.x, pos.y + 15.0f, pos.z), D3DXVECTOR3(move.x, 0.0f, 0.0f), size);
			bullet.Set(D3DXVECTOR3(pos.x, pos.y - 15.0f, pos.z), D3DXVECTOR3(move.x, 0.0f, 0.0f), size);
			break;

		case BULLET_TYPE::TRIPLE: /* 3方向 */
			
			/* 弾の発射 */
			bullet.Set(pos, D3DXVECTOR3(move.x, move.y, 0.0f), size);	//斜め上
			bullet.Set(pos, D3DXVECTOR3(move.x, 0.0f, 0.0f), size);		//水平
			bullet.Set(pos, D3DXVECTOR3(move.x, -move.y, 0.0f), size);	//斜め下
			break;

		default: /* その他 */
			assert(false);
			break;
		}

		m_pPlayer->m_nInterval = 0;	//カウントリセット
	}
}