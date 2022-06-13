//================================================
//
//C++_STG[polygon.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "polygon.h"

#include "rectangle3D.h"
#include "texture.h"

//***************************
//静的メンバ変数宣言
//***************************
CPolygon3D* CPolygon3D::m_pPolygon = nullptr;	//ポインタ

//================================================
//情報を取得
//================================================
CPolygon3D* CPolygon3D::GetInfo()
{
	return m_pPolygon;
}

//================================================
//コンストラクタ
//================================================
CPolygon3D::CPolygon3D():
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_nIdx(0),
	m_pVtxBuff(nullptr),
	m_pTexture(nullptr)
{
	//メンバ変数をクリア
	m_mtxWorld = {};
}

//================================================
//デストラクタ
//================================================
CPolygon3D::~CPolygon3D()
{
}

//================================================
//初期化
//================================================
void CPolygon3D::Init()
{
	if (m_pPolygon != nullptr)
	{//NULLチェック
		return;
	}

	/* nullptrの場合 */

	m_pPolygon = new CPolygon3D;	//メモリの動的確保

	//メンバ変数の初期化
	m_pPolygon->m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pPolygon->m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pPolygon->m_nIdx = 0;
	m_pPolygon->m_mtxWorld = {};
	m_pPolygon->m_pVtxBuff = nullptr;
	m_pPolygon->m_pTexture = nullptr;

	//矩形のインデックスの設定
	m_pPolygon->m_nIdx = SetRectangle3D(TEXTURE_百鬼あやめ_3);

	//位置とサイズの初期設定
	m_pPolygon->m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pPolygon->m_size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	/* 矩形の設定 */
	SetPosRectangle3D(m_pPolygon->m_nIdx, m_pPolygon->m_pos);	//位置
	SetSizeRectangle3D(m_pPolygon->m_nIdx, m_pPolygon->m_size);	//サイズ
}

//================================================
//終了
//================================================
void CPolygon3D::Uninit()
{
	// 使うのを止める
	StopUseRectangle3D(m_pPolygon->m_nIdx);

	if (m_pPolygon == nullptr)
	{//NULLチェック
		return;
	}

	/* nullptrではない場合 */

	//メモリの解放
	delete m_pPolygon;
	m_pPolygon = nullptr;
}

//================================================
//更新
//================================================
void CPolygon3D::Update()
{
	//位置の更新
	SetPosRectangle3D(m_pPolygon->m_nIdx, m_pPolygon->m_pos);
}

//================================================
//描画
//================================================
void CPolygon3D::Draw()
{
	//矩形の描画
	DrawRectangle3D();
}