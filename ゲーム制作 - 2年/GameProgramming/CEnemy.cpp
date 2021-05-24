#include "CEnemy.h"
#include "CTexture.h"
#include "CPlayer.h"
//extern：他のソースファイルの外部変数にアクセスする宣言
extern CTexture Texture;
int CEnemy::sNum = 0;
CEnemy::CEnemy()
: mFx(1.0f), mFy(0.0f), mFireCount(60)
{
	mTag = EENEMY;
	w = 25;
	h = 25;
	sNum++;
}
CEnemy::~CEnemy(){
	sNum--;
}

void CEnemy::Update() {
	//mEnabledがfalseなら戻る
	if (!mEnabled) return;
	//60フレームに1回発射
	if (mFireCount > 2) {
		mFireCount--;
	}
	else {
		//弾を4発四方へ発射する
		if (CPlayer::spInstance->y<y) {
			CBullet *EBullet = new CBullet();
			//座標設定
			EBullet->x = x;
			EBullet->y = y;
			//移動量設定
			EBullet->mFx = 0;
			EBullet->mFy = -1;
			//有効にする
			EBullet->mEnabled = true;
			EBullet->mTag = EENEMYBULLET;
		}
		if (CPlayer::spInstance->x>x) {
			CBullet *EBullet = new CBullet();
			//座標設定
		    EBullet->x = x;
			EBullet->y = y;
			//移動量設定
			EBullet->mFx = 1;
			EBullet->mFy = 0;
			//有効にする
			EBullet->mEnabled = true;
			EBullet->mTag = EENEMYBULLET;
		}
		mFireCount = 300;
	}
	x += mFx;
	y += mFy;
}
/*
親のCollisionをオーバーライドする
衝突すると移動方向を反対にする
*/
bool CEnemy::Collision(const CRectangle &r) {
	//mEnabledがfalseなら戻る
	if (!mEnabled) return false;
	//親のCollisionメソッドを呼び出す
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
		case EBLOCK:
			//衝突していれば反転
			mFx *= -1;
			x += mFx;
			mFy = -1;
			y -= 1 * h;
			

			break;
		case EPLAYERBULLET:
			//プレイヤーの弾に当たると、無効にする
			mEnabled = false;
			break;
		case EPLAYER:
			mEnabled = false;
			break;
		}
		return true;
	}
	else
	{
		mFy = 0;
	}
	return false;
}

void CEnemy::Render() {
	if (mEnabled) {
		CRectangle::Render(Texture, 146 - 16, 146 + 16, 178 + 16, 178 - 16);
	}
}

void CEnemy::Collision(CRectangle *i, CRectangle *y) {
	Collision(*y);
}
