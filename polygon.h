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
public: /* 静的メンバ関数 */
	static CPolygon3D* GetInfo();	//情報を取得

public: /* コンストラクタ・デストラクタ */
	CPolygon3D();
	virtual ~CPolygon3D();

public: /* 仮想関数 */
	virtual void Init();	//初期化
	virtual void Uninit();	//終了
	virtual void Update();	//更新
	virtual void Draw();	//描画

private: /* 静的メンバ変数 */
	static CPolygon3D* m_pPolygon;	//ポインタ

protected: /* メンバ変数 */
	D3DXVECTOR3 m_pos;					//位置
	D3DXVECTOR3 m_size;					//サイズ
	int m_nIdx;							//矩形のインデックス
	D3DXMATRIX m_mtxWorld;				//ワールドマトリックス
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャへのポインタ
};

#endif