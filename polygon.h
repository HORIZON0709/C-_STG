//================================================
//
//ミツケテネ[Polygon3D.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "main.h"

//***************************
//ポリゴンクラスの定義
//***************************
class CPolygon3D
{/* 基本クラス */
public: /* コンストラクタ・デストラクタ */
	CPolygon3D();
	~CPolygon3D();

public: /* 静的メンバ関数 */
	static CPolygon3D* GetInfo();	//情報を取得

public: /* メンバ関数 */
	void Init();	//初期化
	void Uninit();	//終了
	void Update();	//更新
	void Draw();	//描画

private: /* 静的メンバ変数 */
	static CPolygon3D* m_pPolygon;	//ポインタ

private: /* メンバ変数 */
	D3DXVECTOR3 m_pos;					//位置
	D3DXVECTOR3 m_size;					//サイズ
	int m_nIdx;							//矩形のインデックス
	D3DXMATRIX m_mtxWorld;				//ワールドマトリックス
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャへのポインタ
};

#endif