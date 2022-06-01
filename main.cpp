//================================================
//
//C++_STG(仮)[main.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "main.h"
#include "input.h"

#include "camera.h"
#include "polygon.h"
#include "player.h"

#include "fade.h"
#include "title.h"
#include "mode.h"
#include "sound.h"

#include <stdio.h>

//================================================
//マクロ定義
//================================================
#define CLASS_NAME		"WindowsClass"	//ウインドウクラスの名前
#define WINDOW_NAME		"C++_STG(仮)"	//ウインドウの名前(キャプションに表示)

//================================================
//スタティック変数
//================================================
static LPDIRECT3D9			s_pD3D = NULL;				//Direct3Dオブジェクトへのポインタ
static LPDIRECT3DDEVICE9	s_pD3DDevice = NULL;		//Direct3Dデバイスへのポインタ
static LPD3DXFONT			s_pFont = NULL;				//フォントへのポインタ
static int					s_nCountFPS = 0;			//FPSカウンター
static bool					s_bDebug;					//デバッグ表示
static bool					s_bWireFrame;				//ワイヤーフレーム
static bool					s_bEnd;

//================================================
//プロトタイプ宣言
//================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawDebug(void);

//================================================
//メイン関数
//================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };		//画面サイズの構造体
	HWND hWnd;											//ウインドウハンドル(識別子)
	MSG msg;											//メッセージを格納する変数
	DWORD dwCurrentTime;								//現在時刻
	DWORD dwExecLastTime;								//最後に処理した時刻
	DWORD dwFrameCount;									//フレームカウント
	DWORD dwFPSLastTime;								//最後にFPSを計測した時刻

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,							//ウインドウのスタイル
		WindowProc,							//ウインドウプロシージャ
		0,									//0にする(通常は使用しない)
		0,									//0にする(通常は使用しない)
		hInstance,							//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),		//タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),			//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),			//クライアント領域の背景色
		NULL,								//メニューバー
		CLASS_NAME,							//ウインドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION),		//ファイルのアイコン
	};

	//ウインドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウインドウを生成
	hWnd = CreateWindowEx(0,							//拡張ウインドウスタイル
							CLASS_NAME,					//ウインドウクラスの名前
							WINDOW_NAME,				//ウインドウの名前
							WS_OVERLAPPEDWINDOW,		//ウインドウスタイル
							CW_USEDEFAULT,				//ウインドウの左上X座標
							CW_USEDEFAULT,				//ウインドウの左上Y座標
							(rect.right - rect.left),	//ウインドウの幅
							(rect.bottom - rect.top),	//ウインドウの高さ
							NULL,						//親ウインドウのハンドル
							NULL,						//メニューハンドルまたは子ウインドウID
							hInstance,					//インスタンスハンドル
							NULL);						//ウインドウ作成データ

	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//初期化処理が失敗した場合
		return -1;
	}

	//分解能を設定
	timeBeginPeriod(1);

	dwCurrentTime = 0;					//初期化する
	dwExecLastTime = timeGetTime();		//現在時刻を取得(保存)
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//ウインドウの表示
	ShowWindow(hWnd,nCmdShow);		//ウインドウ表示状態を設定
	UpdateWindow(hWnd);

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);		//仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg);		//ウインドウプロシージャへメッセージを送出
			}
		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();		//現在時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
				//FPSを計測
				s_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;		//FPSを計測した時刻を保存
				dwFrameCount = 0;					//フレームカウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60分の1秒経過
				dwExecLastTime = dwCurrentTime;		//処理開始の時刻[現在時刻]を保存

				//更新処理
				Update();

				//描画処理
				Draw();

				if (s_bEnd)
				{
					break;
				}

				dwFrameCount++;		//フレームカウントを加算
			}
		}
	}

	//終了処理
	Uninit();

	//分解能を戻す
	timeEndPeriod(1);

	//ウインドウクラスの登録を解除
	UnregisterClass(CLASS_NAME,wcex.hInstance);

	return (int)msg.wParam;
}

//================================================
//ウインドウプロシージャ
//================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };			//ウインドウの領域(短形)


	if (s_bEnd)
	{
		//ウインドウを破棄する (WM_DESTROYメッセージを送る)
		DestroyWindow(hWnd);
	}

	switch (uMsg)
	{
	case WM_DESTROY:	//ウインドウ破棄のメッセージ

		//WM_QOITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:	//キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE:		//[ESC]キーが押された

			//ウインドウを破棄する (WM_DESTROYメッセージを送る)
			DestroyWindow(hWnd);
			break;
		}
		break;
	}

	if (EndGame())
	{//ゲーム終了の合図が来たら
		//ウインドウを破棄してゲーム終了
		DestroyWindow(hWnd);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//規定の処理を返す
}

//================================================
//初期化処理
//================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;	//プレゼンテーションパラメータ

	//Direct3Dオブジェクトの生成
	s_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (s_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(s_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));		//パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;							//ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							//ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;							//バックバッファの形式
	d3dpp.BackBufferCount = 1;										//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;							//デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;										//ウインドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//インターバル

	//Direct3Dデバイスの生成(描画処理と頂点処理をハードウェアで行う)
	if (FAILED(s_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
									D3DDEVTYPE_HAL,
									hWnd,
									D3DCREATE_HARDWARE_VERTEXPROCESSING,
									&d3dpp,
									&s_pD3DDevice)))
	{
		//Direct3Dデバイスの生成(描画処理はハードウェア、頂点処理はCPUで行う)
		if (FAILED(s_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
										D3DDEVTYPE_HAL,
										hWnd,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										&d3dpp,
										&s_pD3DDevice)))
		{
			//Direct3Dデバイスの生成(描画処理と頂点処理をCPUで行う)
			if (FAILED(s_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
											D3DDEVTYPE_REF,
											hWnd,
											D3DCREATE_SOFTWARE_VERTEXPROCESSING,
											&d3dpp,
											&s_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//レンダースタートの設定
	s_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	s_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	s_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	s_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーステートの設定
	s_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	s_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	s_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	s_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	s_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	s_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	s_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//デバック表示用のフォントの生成
	D3DXCreateFont(s_pD3DDevice, 25, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
					OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
					"HGPゴシックE", &s_pFont);

	//入力系の初期化処理
	if (FAILED(InitInput(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//サウンド
	InitSound(hWnd);

	// モードの初期化
	InitMode();

	//フェードの設定
	InitFade();

	// モードの変更
	ChangeMode(MODE_GAME);

	s_bWireFrame = false;	//非表示
	s_bDebug	 = true;	//表示

	return S_OK;
}

//================================================
//終了処理
//================================================
void Uninit(void)
{
	//入力系
	UninitInput();

	//サウンド
	UninitSound();

	//モード
	UninitMode();

	//フェード
	UninitFade();

	//デバック表示用フォントの破棄
	if (s_pFont != NULL)
	{
		s_pFont->Release();
		s_pFont = NULL;
	}

	//Direct3Dデバイスの破棄
	if (s_pD3DDevice != NULL)
	{
		s_pD3DDevice->Release();
		s_pD3DDevice = NULL;
	}

	//Direct3Dオブジェクトの破棄
	if (s_pD3D != NULL)
	{
		s_pD3D->Release();
		s_pD3D = NULL;
	}
}

//================================================
//更新処理
//================================================
void Update(void)
{
	//デバッグ表示の切り替え
	if (GetKeyboardTrigger(DIK_F1))
	{//F1キー
		s_bDebug = s_bDebug ? false : true;		//表示:非表示の切り替え
	}

	//ワイヤーフレームの切り替え
	if (GetKeyboardTrigger(DIK_F2))
	{//F2キー
		s_bWireFrame = s_bWireFrame ? false : true;		//表示:非表示の切り替え

		if (s_bWireFrame)
		{//表示中
			//ワイヤーフレームモードの設定
			s_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		}
		else
		{//非表示中
			//元に戻す
			s_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}
	}

	//入力系
	UpdateInput();

	//モード
	UpdateMode();
	SetMode();

	//フェード
	UpdateFade();
}

//================================================
//描画処理
//================================================
void Draw(void)
{
	//画面クリア(バックバッファ＆Zバッファのクリア)
	s_pD3DDevice->Clear(0, NULL,
						(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
						D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画処理
	if (SUCCEEDED(s_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合

		//モード
		DrawMode();
		
		//フェード
		DrawFade();

#ifdef _DEBUG	//デバッグの時だけ

		if (s_bDebug)
		{
			//デバッグ表示
			DrawDebug();
		}

#endif

		//描画終了
		s_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	s_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//================================================
//デバイスの取得
//================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return s_pD3DDevice;
}

//================================================
// 終了フラグ
//================================================
bool* GetEnd(void)
{
	return &s_bEnd;
}

//================================================
//デバッグ表示
//================================================
void DrawDebug(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[4096];		//文字列
	int nLength = 0;		//文字数を測るやつ

	//FPS
	sprintf(&aStr[nLength], "FPS ： %2d\n", s_nCountFPS);
	nLength = (int)strlen(&aStr[0]);	//現在の文字数を取得

	/* カメラ */

	Camera* pC = GetCamera();	//カメラ情報のポインタ

	//見出し
	sprintf(&aStr[nLength], "\n[  カメラ  ]\n");
	nLength = (int)strlen(&aStr[0]);

	//視点の位置
	sprintf(&aStr[nLength], " 視点の位置[ %.2f : %.2f : %.2f ] \n",pC->posV.x, pC->posV.y, pC->posV.z);
	nLength = (int)strlen(&aStr[0]);

	//視点の向き
	sprintf(&aStr[nLength], " 視点の向き[ %.2f : %.2f : %.2f ] \n", pC->rot.x, pC->rot.y, pC->rot.z);
	nLength = (int)strlen(&aStr[0]);

	/* ポリゴン */

	Polygon3D* pPol = GetPolygon();		//ポリゴン情報のポインタ

	//見出し
	sprintf(&aStr[nLength], "\n[  ポリゴン  ]\n");
	nLength = (int)strlen(&aStr[0]);

	//位置
	sprintf(&aStr[nLength], " 位置[ %.2f : %.2f : %.2f ] \n", pPol->pos.x, pPol->pos.y, pPol->pos.z);
	nLength = (int)strlen(&aStr[0]);

	/* プレイヤー */

	//CPlayer* pPlayer = CPlayer::GetInfo();;		//プレイヤー情報のポインタ
	//pPlayer->Init();

	////見出し
	//sprintf(&aStr[nLength], "\n[  プレイヤー  ]\n");
	//nLength = (int)strlen(&aStr[0]);

	////位置
	//sprintf(&aStr[nLength], " 位置[ %.2f : %.2f : %.2f ] \n", pPlayer->m_pos.x, pPlayer->m_pos.y, pPlayer->m_pos.z);
	//nLength = (int)strlen(&aStr[0]);

	/* その他 */

	//見出し
	sprintf(&aStr[nLength], "\n[  その他操作  ]\n");
	nLength = (int)strlen(&aStr[0]);

	//カメラのリセット
	sprintf(&aStr[nLength], " Enter   ： カメラのリセット\n");
	nLength = (int)strlen(&aStr[0]);

	//デバッグ表示の切り替え
	sprintf(&aStr[nLength], " F1       ： デバッグ表示\n");
	nLength = (int)strlen(&aStr[0]);

	//テキストの描画
	s_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(200, 0, 200, 255));
}

//================================================
//各頂点のrhwの設定( 頂点情報[2D], float )
//================================================
void SetRhw(VERTEX_2D *pVtx, float fRhw)
{
	pVtx[0].rhw = fRhw;
	pVtx[1].rhw = fRhw;
	pVtx[2].rhw = fRhw;
	pVtx[3].rhw = fRhw;
}

//================================================
//頂点カラーの設定( 頂点情報[2D], 赤, 緑, 青, α値 )
//================================================
void SetCol2D(VERTEX_2D *pVtx, float fRed, float fGreen, float fBlue, float fAlpha)
{
	pVtx[0].col = D3DXCOLOR(fRed, fGreen, fBlue, fAlpha);
	pVtx[1].col = D3DXCOLOR(fRed, fGreen, fBlue, fAlpha);
	pVtx[2].col = D3DXCOLOR(fRed, fGreen, fBlue, fAlpha);
	pVtx[3].col = D3DXCOLOR(fRed, fGreen, fBlue, fAlpha);
}

//================================================
//テクスチャ座標の設定( 頂点情報[2D], 左, 右, 上, 下 )
//================================================
void SetTex2D(VERTEX_2D *pVtx, float fLeft, float fRight, float fUp, float fDown)
{
	pVtx[0].tex = D3DXVECTOR2(fLeft, fUp);
	pVtx[1].tex = D3DXVECTOR2(fRight, fUp);
	pVtx[2].tex = D3DXVECTOR2(fLeft, fDown);
	pVtx[3].tex = D3DXVECTOR2(fRight, fDown);
}