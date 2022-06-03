//================================================
//
//C++_STG[bullet.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "bullet.h"
//#include "player.h"

#include "rectangle3D.h"
#include "texture.h"

//***************************
//静的メンバ変数宣言
//***************************
CBullet* CBullet::m_apBullet[MAX_BULLET] = {};	//ポインタ

//================================================
//コンストラクタ
//================================================
CBullet::CBullet()
{
	//メンバ変数のクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mtxWorld = {};
	m_nIdx = 0;
	m_nLife = 0;
	m_bUse = false;
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;
}

//================================================
//デストラクタ
//================================================
CBullet::~CBullet()
{
	/* 処理無し */
}

//================================================
//初期化
//================================================
void CBullet::Init()
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (m_apBullet[i] != nullptr)
		{//NULLチェック
			continue;
		}

		/* nullptrの場合 */

		//メモリの動的確保
		m_apBullet[i] = new CBullet;

		//メンバ変数の初期化
		m_apBullet[i]->m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_apBullet[i]->m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_apBullet[i]->m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_apBullet[i]->m_mtxWorld = {};
		m_apBullet[i]->m_nIdx = 0;
		m_apBullet[i]->m_nLife = 0;
		m_apBullet[i]->m_bUse = false;
		m_apBullet[i]->m_pVtxBuff = nullptr;
		m_apBullet[i]->m_pTexture = nullptr;

		// 矩形のインデックスの設定
		m_apBullet[i]->m_nIdx = SetRectangle3D(TEXTURE_百鬼あやめ_6);

		/* 矩形の設定 */
		SetPosRectangle3D(m_apBullet[i]->m_nIdx, m_apBullet[i]->m_pos);		//位置
		SetSizeRectangle3D(m_apBullet[i]->m_nIdx, m_apBullet[i]->m_size);	//サイズ
	}
}

//================================================
//終了
//================================================
void CBullet::Uninit()
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		// 使うのを止める
		StopUseRectangle3D(m_apBullet[i]->m_nIdx);

		if (m_apBullet[i] == nullptr)
		{//NULLチェック
			return;
		}

		/* nullptrではない場合 */

		//メモリの解放
		delete m_apBullet[i];
		m_apBullet[i] = nullptr;
	}
}

//================================================
//更新
//================================================
void CBullet::Update()
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (!m_apBullet[i]->m_bUse)
		{//使用していない
			continue;
		}

		/* 使用している */

		m_apBullet[i]->m_pos += m_apBullet[i]->m_move;	//弾の移動

		m_apBullet[i]->m_nLife--;	//寿命を減らす

		if (m_apBullet[i]->m_nLife <= 0)
		{//寿命が尽きた
			StopUseRectangle3D(m_apBullet[i]->m_nIdx);	//矩形の使用を停止
			m_apBullet[i]->m_bUse = false;				//『使用しない』に変更
		}

		/* 矩形の更新 */
		SetPosRectangle3D(m_apBullet[i]->m_nIdx, m_apBullet[i]->m_pos);		//位置
		SetSizeRectangle3D(m_apBullet[i]->m_nIdx, m_apBullet[i]->m_size);	//サイズ
	}
}

//================================================
//描画
//================================================
void CBullet::Draw()
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (!m_apBullet[i]->m_bUse)
		{//使用していない
			continue;
		}

		/* 使用している */

		// 矩形の描画
		DrawRectangle3D();
	}
}

//================================================
//セット
//================================================
void CBullet::Set(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (m_apBullet[i]->m_bUse)
		{//使用している
			continue;
		}

		/* 使用していない */

		m_apBullet[i]->m_pos = pos;								//位置
		m_apBullet[i]->m_move = move;							//移動量
		m_apBullet[i]->m_size = D3DXVECTOR3(50.0f, 50.0f, 0.0);	//サイズ
		m_apBullet[i]->m_nLife = MAX_LIFE;						//寿命
		m_apBullet[i]->m_bUse = true;							//『使用する』に変更

		// 矩形のインデックスの設定
		m_apBullet[i]->m_nIdx = SetRectangle3D(TEXTURE_百鬼あやめ_6);

		//セットした位置から、頂点座標を設定
		SetPosRectangle3D(m_apBullet[i]->m_nIdx, m_apBullet[i]->m_pos);
		SetSizeRectangle3D(m_apBullet[i]->m_nIdx, m_apBullet[i]->m_size);
		break;
	}
}