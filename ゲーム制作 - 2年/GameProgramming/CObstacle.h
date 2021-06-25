#ifndef COBSTACLE_H
#define COBSTACLE_H

#include "CRectangle.h"


/*
CObstacle
障害物クラス
CRectangleクラスを継承する
親：CRectangleクラス
子：CObstacleクラス
*/
class CObstacle : public CRectangle {
public:
	int mFx, mFy;	//移動量

	//デフォルトコンストラクタ
	CObstacle();
	//更新処理
	void Update();

	//描画処理
	void Render();

	void Collision(CRectangle *i, CRectangle *y);

};

#endif
