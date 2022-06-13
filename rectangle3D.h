//**************************************************
//
//Hackathon[rectangle3D.h]
//Author:katsuki mizuki
//Author:Kishimoto Eiji
//
//**************************************************
#ifndef _RECTANGLE3D_H_	//このマクロ定義がされてなかったら
#define _RECTANGLE3D_H_	//２重インクルード防止のマクロ定義

//***************************
//インクルード
//***************************
#include "main.h"
#include "texture.h"

//***************************
//マクロ定義
//***************************
// 頂点フォーマット[3D] 位置・法線・カラー・テクスチャ
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

struct VERTEX_3D
{/* 頂点情報[3D] */
	D3DXVECTOR3	pos;	//頂点座標
	D3DXVECTOR3	nor;	//法線ベクトル
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2	tex;	//テクスチャ座標
};

//***************************
//3D矩形描画クラスの定義
//***************************
class CRectAngle3D
{/* 基本クラス */
public: /* 構造体の定義 */
	struct VERTEX_3D
	{/* 頂点情報[3D] */
		D3DXVECTOR3	pos;	//頂点座標
		D3DXVECTOR3	nor;	//法線ベクトル
		D3DCOLOR col;		//頂点カラー
		D3DXVECTOR2	tex;	//テクスチャ座標
	};
private:
	struct MyRectangle3D
	{/* 3D矩形 */
		LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャ
		LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファ
		D3DXMATRIX m_mtxWorld;				//ワールドマトリックス
		D3DXVECTOR3 m_pos;					//位置
		D3DXVECTOR3 m_rot;					//向き
		bool m_bUse;						//使用しているかどうか
		bool m_bDraw;						//描画するかどうか
		bool m_bAdd;						//加算合成するかどうか
	};

private:/* 定数の定義 */
	static const int MAX_RECTANGLE3D = 1024;	//矩形の最大数
	static const int NUM_VERTEX = 4;			//頂点の数
	static const int NUM_POLYGON = 2;			//ポリゴンの数

public: /* コンストラクタ・デストラクタ */
	CRectAngle3D();
	~CRectAngle3D();

public: /* メンバ関数 */
	void Init();	//初期化
	void Uninit();	//終了
	void Draw();	//描画

	/* テクスチャの設定 */
	int Set(TEXTURE texture);						//設定
	int SetWithTex(LPDIRECT3DTEXTURE9 pTexture);	//設定[ テクスチャあり ]

	/* 使用停止 */
	void StopUse(int nIdx);	//使うのを止める

	/* 矩形描画に関する設定 */
	void SetPos(int nIdx, const D3DXVECTOR3& pos);		//位置の設定
	void SetRot(int nIdx, const D3DXVECTOR3& rot);		//向きの設定
	void SetSize(int nIdx, const D3DXVECTOR3& size);	//サイズの設定
	void SetColor(int nIdx, const D3DXCOLOR& color);	//色の設定
	void SetTex(int nIdx, const D3DXVECTOR2& texU, const D3DXVECTOR2& texV);	//テクスチャの設定

	/* 判断 */
	void WhetherToDraw(int nIdx, bool bDraw);	//描画するかどうか
	void WhetherToAdd(int nIdx, bool bAdd);		//加算合成するかどうか

	/* テクスチャの変更 */
	void ChangeTexture(int nIdx, TEXTURE texture);	//テクスチャの変更
	void ChangeTextureWithTex(int nIdx, LPDIRECT3DTEXTURE9 pTexture);	//テクスチャの変更[ テクスチャあり ]

	/* 取得 */
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(int nIdx);	//頂点バッファの取得

private:/* 静的メンバ変数 */
	MyRectangle3D m_rectangle3D[MAX_RECTANGLE3D];	// 矩形の情報
};

//***************************
// プロトタイプ宣言
//***************************
/* 初期化 */
void InitRectangle3D(void);

/* 終了 */
void UninitRectangle3D(void);

/* 描画 */
void DrawRectangle3D(void);

/*
	設定
	引数 : TEXTURE inTexture / 列挙型 種類
*/
int SetRectangle3D(TEXTURE inTexture);

/*
	設定 [ テクスチャあり ]
	引数 : LPDIRECT3DTEXTURE9 pTexture / テクスチャ
*/
int SetRectangle3DWithTex(LPDIRECT3DTEXTURE9 pTexture);

/*
	使うのを止める
	引数 : int inIdx / インデックス
*/
void StopUseRectangle3D(int inIdx);

/*
	位置の設定
	引数1 : int inIdx / インデックス
	引数2 : D3DXVECTOR3& inPos / 中心の位置
*/
void SetPosRectangle3D(int inIdx, const D3DXVECTOR3& inPos);

/*
	向きの設定
	引数1 : int inIdx / インデックス
	引数2 : D3DXVECTOR3& inRot / 向き
*/
void SetRotRectangle3D(int inIdx, const D3DXVECTOR3& inRot);

/*
	サイズの設定
	引数1 : int inIdx / インデックス
	引数2 : D3DXVECTOR3& inSize / サイズ
*/
void SetSizeRectangle3D(int inIdx, const D3DXVECTOR3& inSize);

/*
	色の設定
	引数1 : int inIdx / インデックス
	引数2 : D3DXCOLOR& inColor / 色
*/
void SetColorRectangle3D(int inIdx, const D3DXCOLOR& inColor);

/*
	テクスチャ座標の設定
	引数1 : int inIdx / インデックス
	引数2 : D3DXVECTOR2& inTexU / x = 左端, y = 右端
	引数3 : D3DXVECTOR2& inTexV / x = 上端, y = 下端
*/
void SetTexRectangle3D(int inIdx, const D3DXVECTOR2& inTexU, const D3DXVECTOR2& inTexV);

/*
	描画するかどうか
	引数1 : int inIdx / インデックス
	引数2 : bool inDraw / 描画するかどうか
*/
void SetDrawRectangle3D(int inIdx, bool inDraw);

/*
	加算合成するかどうか
	引数1 : int inIdx / インデックス
	引数2 : bool inAdd / 加算合成するかどうか
*/
void SetAddRectangle3D(int inIdx, bool inAdd);

/*
	テクスチャの変更
	引数1 : int inIdx / インデックス
	引数2 : TEXTURE inTexture / 列挙型 種類
*/
void ChangeTextureRectangle3D(int inIdx, TEXTURE inTexture);

/*
	テクスチャの変更 [ テクスチャあり ]
	引数1  : int inIdx / インデックス
	引数2  : TEXTURE pTexture / 列挙型 種類
*/
void ChangeTextureRectangle3DWithTex(int inIdx, LPDIRECT3DTEXTURE9 pTexture);

/*
	頂点バッファの取得
	引数  : int inIdx / インデックス
	返値  : LPDIRECT3DVERTEXBUFFER9 / 頂点バッファ
*/
LPDIRECT3DVERTEXBUFFER9 GetVtxBuffRectangle3D(int inIdx);

#endif // !_RECTANGLE3D_H_
