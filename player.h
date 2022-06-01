//================================================
//
//C++_STG(仮)[player.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//***************************
//プレイヤークラスの定義
//***************************
class CPlayer
{/* 基本クラス */
private: /* 列挙型の定義 */
	enum class BULLET_TYPE
	{//弾の種類
		NORMAL = 0,
		DOUBLE,
		TRIPLE,
		MAX
	};

private: /* 演算子オーバーロード */
	CPlayer operator ++ ();		//「 ++ 」

private: /* 定数の定義 */
	static const int SHOT_INTERVAL = 15;	//弾発射の間隔( 60フレーム = 1秒 )
	static float MOVE_SPEED;				//移動スピード

public: /* 静的メンバ関数 */
	static CPlayer* GetInfo();	//情報を取得

private: /* 静的メンバ変数 */
	static CPlayer* m_pPlayer;	//プレイヤー情報

public: /* コンストラクタ・デストラクタ */
	CPlayer();
	~CPlayer();

public: /* メンバ関数 */
	void Init();	//初期化
	void Uninit();	//終了
	void Update();	//更新
	void Draw();	//描画
private:
	void Move();	//移動
	void Shot();	//弾の発射

private: /* メンバ変数 */
	D3DXVECTOR3	m_pos;						//位置
	D3DXVECTOR3	m_size;						//サイズ
	int m_nIdx;								//矩形のインデックス
	D3DXMATRIX	m_mtxWorld;					//ワールドマトリックス
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;		//頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャへのポインタ
	int m_nInterval;						//弾発射の間隔をカウントする
	int nBulletType;						//弾の種類
};

#endif