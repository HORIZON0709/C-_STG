//================================================
//
//C++_STG(仮)[enemy.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "polygon3D.h"

//***************************
//敵クラスの定義
//***************************
class CEnemy : public CPolygon3D
{/* CPolygon3Dの派生クラス */
private: /* 定数の定義 */
	static const int MAX_ENEMY = 4;	//敵の最大数

public: /* 静的メンバ関数 */
	static CEnemy** GetInfo();	//情報を取得

public: /* コンストラクタ・デストラクタ */
	CEnemy();
	~CEnemy() override;

public: /* オーバーライド関数 */
	void Init() override;	//初期化
	void Uninit() override;	//終了
	void Update() override;	//更新
	void Draw() override;	//描画

private: /* 静的メンバ変数 */
	static CEnemy* m_apEnemy[MAX_ENEMY];	//敵情報

private: /* メンバ変数 */

};

#endif