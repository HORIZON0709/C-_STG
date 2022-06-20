//================================================
//
//C++_STG(仮)[camera.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "camera.h"
#include "input.h"
#include "player.h"
#include "polygon3D.h"

//***************************
//定数の定義
//***************************
namespace
{
const float CAMERA_MOVE = 2.0f;		//カメラの移動量
const float CAMERA_ROT	= 0.05f;	//カメラの旋回量
const float MAX_FAR		= 1000.0f;	//ファー
const float MAX_NEAR	= 10.0f;	//ニア
}//namespaceはここまで

//***************************
//スタティック変数宣言
//***************************
namespace
{
Camera s_camera;	//カメラ情報
}//namespaceはここまで

//***************************
//プロトタイプ宣言
//***************************
static void CameraMove(void);
static void CameraReset(void);
static void AllDirections(void);
static void AngleNormalization(void);

//================================================
//カメラの初期化処理
//================================================
void InitCamera(void)
{
	//視点・注視点・上方向を設定する
	s_camera.posV = D3DXVECTOR3(-280.0f, 0.0f, -100.0f);
	s_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	s_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//向きの初期化
	s_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	//視点から注視点の距離の設定
	float fX = (s_camera.posR.x - s_camera.posV.x);
	float fZ = (s_camera.posR.z - s_camera.posV.z);
	s_camera.fDistance	= sqrtf((fX * fX) + (fZ * fZ));		//三平方で距離を計算
}

//================================================
//カメラの終了処理
//================================================
void UninitCamera(void)
{

}

//================================================
//カメラの更新処理
//================================================
void UpdateCamera(void)
{
	//カメラの移動
	CameraMove();

	if (!GetKeyboardPress(DIK_M))
	{//カメラ移動を一時停止できるよ
		s_camera.posV.x += sinf(s_camera.rot.y + (D3DX_PI * 0.5f)) * 0.4f;
		s_camera.posV.z += cosf(s_camera.rot.y + (D3DX_PI * 0.5f)) * 0.4f;
	}
}

//================================================
//カメラの設定処理
//================================================
void SetCamera(void)
{
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&s_camera.mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&s_camera.mtxView,
						&s_camera.posV,
						&s_camera.posR,
						&s_camera.vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &s_camera.mtxView);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&s_camera.mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixOrthoLH(&s_camera.mtxProjection,
						(float)SCREEN_WIDTH,
						(float)SCREEN_HEIGHT,
						MAX_NEAR,
						MAX_FAR);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &s_camera.mtxProjection);
}

//================================================
//カメラの移動
//================================================
static void CameraMove(void)
{
#ifdef _DEBUG	//デバッグの時だけ

	//カメラのリセット
	CameraReset();

	//前後左右の移動
	AllDirections();
	
#endif
	//角度の正規化
	AngleNormalization();

	//注視点
	s_camera.posR.x = s_camera.posV.x + sinf(s_camera.rot.y) * s_camera.fDistance;
	s_camera.posR.z = s_camera.posV.z + cosf(s_camera.rot.y) * s_camera.fDistance;
	s_camera.posR.y = s_camera.posV.y + tanf(s_camera.rot.x) * s_camera.fDistance;
}

//================================================
//カメラのリセット
//================================================
static void CameraReset(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{//Enterキー
		//カメラの初期化処理
		InitCamera();
	}
}

//================================================
//前後左右の移動
//================================================
static void AllDirections(void)
{
	//if (GetKeyboardPress(DIK_LEFT))
	//{//←キー
	//	if (GetKeyboardPress(DIK_UP))
	//	{//左上
	//		s_camera.posV.x -= sinf(s_camera.rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;
	//		s_camera.posV.z -= cosf(s_camera.rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;
	//	}
	//	else if (GetKeyboardPress(DIK_DOWN))
	//	{//左下
	//		s_camera.posV.x -= sinf(s_camera.rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;
	//		s_camera.posV.z -= cosf(s_camera.rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;
	//	}
	//	else
	//	{//左
	//		s_camera.posV.x -= sinf(s_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;
	//		s_camera.posV.z -= cosf(s_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_RIGHT))
	//{//→キー
	//	if (GetKeyboardPress(DIK_UP))
	//	{//右上
	//		s_camera.posV.x += sinf(s_camera.rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;
	//		s_camera.posV.z += cosf(s_camera.rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;
	//	}
	//	else if (GetKeyboardPress(DIK_DOWN))
	//	{//右下
	//		s_camera.posV.x += sinf(s_camera.rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;
	//		s_camera.posV.z += cosf(s_camera.rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;
	//	}
	//	else
	//	{//右
	//		s_camera.posV.x += sinf(s_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;
	//		s_camera.posV.z += cosf(s_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_UP))
	//{//↑キー(前)
	//	s_camera.posV.x += sinf(s_camera.rot.y) * CAMERA_MOVE;
	//	s_camera.posV.z += cosf(s_camera.rot.y) * CAMERA_MOVE;
	//}
	//else if (GetKeyboardPress(DIK_DOWN))
	//{//↓キー(後)
	//	s_camera.posV.x -= sinf(s_camera.rot.y) * CAMERA_MOVE;
	//	s_camera.posV.z -= cosf(s_camera.rot.y) * CAMERA_MOVE;
	//}

	if (GetKeyboardPress(DIK_T))
	{//上昇
		s_camera.posV.y += 5.0f;
	}
	else if (GetKeyboardPress(DIK_G))
	{//下降
		s_camera.posV.y -= 5.0f;
	}

	//if (GetKeyboardPress(DIK_Y))
	//{//前回転
	//	s_camera.rot.x += 0.01f;
	//}
	//else if (GetKeyboardPress(DIK_H))
	//{//後回転
	//	s_camera.rot.x -= 0.01f;
	//}
}

//================================================
//角度の正規化
//================================================
static void AngleNormalization(void)
{
	//Y軸
	if (s_camera.rot.y > D3DX_PI)
	{//π( 180°)を超えた場合
		s_camera.rot.y -= (D3DX_PI * 2.0f);
	}
	else if (s_camera.rot.y < -D3DX_PI)
	{//-π( -180°)を超えた場合
		s_camera.rot.y += (D3DX_PI * 2.0f);
	}

	//X軸
	if (s_camera.rot.x > D3DX_PI)
	{//π( 180°)を超えた場合
		s_camera.rot.x -= (D3DX_PI * 2.0f);
	}
	else if (s_camera.rot.x < -D3DX_PI)
	{//-π( -180°)を超えた場合
		s_camera.rot.x += (D3DX_PI * 2.0f);
	}
}

//================================================
//カメラの情報の取得
//================================================
Camera *GetCamera(void)
{
	return &s_camera;
}