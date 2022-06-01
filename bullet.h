//================================================
//
//C++_STG(仮)[bullet.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//***************************
//弾クラスの定義
//***************************
class CBullet
{
public: /* 定数の定義 */
	static const int MAX_BULLET = 48;	//弾の最大数
	static const int MAX_LIFE = 150;	//弾の寿命

private: /* 静的メンバ変数 */
	static CBullet* m_apBullet[MAX_BULLET];		//弾の情報

public: /* コンストラクタ・デストラクタ */
	CBullet();
	~CBullet();

public:/* メンバ関数 */
	void Init();	//初期化
	void Uninit();	//終了
	void Update();	//更新
	void Draw();	//描画
public:/* Set系 */
	/*
	セット
	const D3DXVECTOR3 pos ---> 位置
	const D3DXVECTOR3 move ---> 移動量
	*/
	void Set(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);

private: /* メンバ変数 */
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_move;		//移動量
	D3DXVECTOR3 m_size;		//サイズ
	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス
	int m_nIdx;				//矩形のインデックス
	int m_nLife;			//寿命
	bool m_bUse;			//使用の有無
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;		//頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9		m_pTexture;		//テクスチャへのポインタ
};

//***************************
//プロトタイプ宣言
//***************************
//void InitBullet(void);
//void UninitBullet(void);
//void UpdateBullet(void);
//void DrawBullet(void);
//void SetBullet(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);

#endif