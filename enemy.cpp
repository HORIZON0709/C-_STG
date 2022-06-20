//================================================
//
//C++_STG(仮)[enemy.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "enemy.h"

#include "rectangle3D.h"
#include "texture.h"
#include "input.h"

//***************************
//静的メンバ変数宣言
//***************************
CEnemy* CEnemy::m_apEnemy[MAX_ENEMY] = {};	//ポインタ

//================================================
//情報を取得
//================================================
CEnemy** CEnemy::GetInfo()
{
	return &m_apEnemy[0];
}

//================================================
//コンストラクタ
//================================================
CEnemy::CEnemy()
{
	
}

//================================================
//デストラクタ
//================================================
CEnemy::~CEnemy()
{
}

//================================================
//初期化
//================================================
void CEnemy::Init()
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (m_apEnemy[i] != nullptr)
		{//NULLチェック
			continue;
		}

		/* nullptrの場合 */

		m_apEnemy[i] = new CEnemy;	//メモリの動的確保

		//矩形のインデックスの設定
		m_apEnemy[i]->m_nIdx = SetRectangle3D(TEXTURE_百鬼あやめ_1);

		//位置とサイズの初期設定
		m_apEnemy[i]->m_pos = D3DXVECTOR3((100.0f * i), 100.0f, -20.0f);
		m_apEnemy[i]->m_size = D3DXVECTOR3(150.0f, 150.0f, 0.0f);

		/* 矩形の設定 */
		SetPosRectangle3D(m_apEnemy[i]->m_nIdx, m_apEnemy[i]->m_pos);	//位置
		SetSizeRectangle3D(m_apEnemy[i]->m_nIdx, m_apEnemy[i]->m_size);	//サイズ
	}
}

//================================================
//終了
//================================================
void CEnemy::Uninit()
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		// 使うのを止める
		StopUseRectangle3D(m_apEnemy[i]->m_nIdx);

		if (m_apEnemy[i] == nullptr)
		{//NULLチェック
			continue;
		}

		/* nullptrではない場合 */

		//メモリの解放
		delete m_apEnemy[i];
		m_apEnemy[i] = nullptr;
	}
}

//================================================
//更新
//================================================
void CEnemy::Update()
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (m_apEnemy[i] == nullptr)
		{//NULLチェック
			continue;
		}

		/* nullptrではない場合 */

		//位置の更新
		SetPosRectangle3D(m_apEnemy[i]->m_nIdx, m_apEnemy[i]->m_pos);
	}
}

//================================================
//描画
//================================================
void CEnemy::Draw()
{
	// 矩形の描画
	DrawRectangle3D();
}