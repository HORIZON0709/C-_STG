//================================================
//
//C++_STG(仮)[player.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "polygon3D.h"

//***************************
//プレイヤークラスの定義
//***************************
class CPlayer : public CPolygon3D
{/* CPolygon3Dの派生クラス */
private: /* 列挙型の定義 */
	enum class BULLET_TYPE
	{//弾の種類
		NORMAL = 0,
		DOUBLE,
		TRIPLE,
		MAX
	};

private: /* 定数の定義 */
	static const int SHOT_INTERVAL = 15;	//弾発射の間隔( 60フレーム = 1秒 )
	static const float MOVE_SPEED;			//移動スピード

public: /* 静的メンバ関数 */
	static CPlayer* GetInfo();	//情報を取得

public: /* コンストラクタ・デストラクタ */
	CPlayer();
	~CPlayer() override;

public: /* オーバーライド関数 */
	void Init() override;	//初期化
	void Uninit() override;	//終了
	void Update() override;	//更新
	void Draw() override;	//描画
private: /* メンバ関数 */
	void Move();	//移動
	void Shot();	//弾の発射

private: /* 静的メンバ変数 */
	static CPlayer* m_pPlayer;	//プレイヤー情報

private: /* メンバ変数 */
	int m_nInterval;	//弾発射の間隔をカウントする
	int nBulletType;	//弾の種類
};

#endif