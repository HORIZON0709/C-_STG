//================================================
//
//C++_STG(仮)[bullet.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "polygon3D.h"

//***************************
//弾クラスの定義
//***************************
class CBullet : public CPolygon3D
{/* Cpolygon3Dの派生クラス */
public: /* 定数の定義 */
	static const int MAX_BULLET = 48;	//弾の最大数
	static const int MAX_LIFE = 150;	//弾の寿命

public: /* コンストラクタ・デストラクタ */
	CBullet();
	~CBullet()override;

public:/* メンバ関数 */
	void Init()override;	//初期化
	void Uninit()override;	//終了
	void Update()override;	//更新
	void Draw()override;	//描画
public:/* Set系 */
	/*
	セット
	const D3DXVECTOR3 pos ---> 位置
	const D3DXVECTOR3 move ---> 移動量
	*/
	void Set(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 size);

private: /* 静的メンバ変数 */
	static CBullet* m_apBullet[MAX_BULLET];		//弾の情報

private: /* メンバ変数 */
	D3DXVECTOR3 m_move;	//移動量
	int m_nLife;		//寿命
	bool m_bUse;		//使用の有無
};

#endif