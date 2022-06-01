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
//ポリゴン構造体の定義
//***************************
typedef struct
{
	D3DXVECTOR3	pos;		//位置
	D3DXVECTOR3	size;		//サイズ
	int			idx;		//矩形のインデックス
	D3DXMATRIX	mtxWorld;	//ワールドマトリックス
}Polygon3D;

//***************************
//プロトタイプ宣言
//***************************
void InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);
Polygon3D* GetPolygon(void);

#endif