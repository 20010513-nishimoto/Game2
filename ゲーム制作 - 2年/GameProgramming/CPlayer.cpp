#include "CPlayer.h"
#include "CKey.h"
#include "CBullet.h"
#include "CInput.h"
#include <math.h>

#define G  1

#define VJ0 18

//extern：他のソースファイルの外部変数にアクセスする宣言
extern CTexture Texture;

CPlayer* CPlayer::spInstance = 0;

#define ANICNT 30

CPlayer::CPlayer()
: mFx(1.0f), mFy(0.0f)
, FireCount(0)
, mAniCnt(0)
, mVj(0)
, mJump(0)
{
	mTag = EPLAYER;
	spInstance = this;
	
}

void CPlayer::Update() {

	

	//staticメソッドはどこからでも呼べる
	if (CKey::Push('A')) {
		x -= 3;
		mFx = -1;
		mFy = 0;
		if (x - w < -400) {
			x = -400 + w;
		}
	}
	if (CKey::Push('D')) {
		x += 3;
		mFx = 1;
		mFy = 0;
		if (x + w > 400) {
			x = 400 - w;
		}
	}
	//ジャンプ可能か
	if (mJump == 0 && CKey::Push('J')){
		//ジャンプ力を速度に設定
		mVj = VJ0;
		//フラグに1加算
		mJump++;
	}
	//速度に重力加速度加算
	mVj -= G;
	//速度分移動
	y += mVj;
	

	//スペースキーで弾発射
	//0より大きいとき1減算する
	if (FireCount > 0) {
		FireCount--;
	}
	//FireContが0で、かつ、スペースキーで弾発射
	else if( CKey::Once(' ')) {
		CBullet *Bullet = new CBullet();
		//発射位置の設定
		Bullet->x = x;
		Bullet->y = y;
		//移動の値を設定
		Bullet->mFx = mFx * 5;
		Bullet->mFy = mFy * 5;
		//有効にする
		Bullet->mEnabled = true;
		//プレイヤーの弾を設定
		Bullet->mTag = CRectangle::EPLAYERBULLET;
		FireCount = 10;
	}
}

void CPlayer::Render() {
	mAniCnt++;
	mAniCnt %= ANICNT;

	if (mAniCnt < ANICNT / 2)
	{
		if (mFx >= 0)
		{
		CRectangle::Render(Texture, 130, 162, 162, 130);
	}
	else
	{
		CRectangle::Render(Texture, 162, 130, 162, 130);
	}
}
else
{
	if (mFx >= 0)
	{
		CRectangle::Render(Texture, 162, 194, 162, 130);
	}
	else
	{
		CRectangle::Render(Texture, 194, 162, 162, 130);
	}
  }
}

void CPlayer::Collision(CRectangle *ri, CRectangle *ry) {
	if (ry->mTag == EBLOCK) {
		int mx, my;
		if (CRectangle::Collision(ry, &mx, &my)) {
			//abs(x) xの絶対値を求める
			//移動量が少ない方向だけ移動させる
			if (abs(mx) < abs(my)) {
				//Rectをxだけ移動する
				x += mx;
			}
			else {
				//Rectをyだけ移動する
				y += my;
				//着地
				mVj = 0;
				if (my > 0)
				{
					//ジャンプ可能
					mJump = 0;
				}
			}
		}
	}
}
