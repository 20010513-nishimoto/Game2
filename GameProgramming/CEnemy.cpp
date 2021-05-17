#include "CEnemy.h"
#include "CTexture.h"
#include "CPlayer.h"
//extern�F���̃\�[�X�t�@�C���̊O���ϐ��ɃA�N�Z�X����錾
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
	//mEnabled��false�Ȃ�߂�
	if (!mEnabled) return;
	//60�t���[����1�񔭎�
	if (mFireCount > 2) {
		mFireCount--;
	}
	else {
		//�e��4���l���֔��˂���
		if (CPlayer::spInstance->y<y) {
			CBullet *EBullet = new CBullet();
			//���W�ݒ�
			EBullet->x = x;
			EBullet->y = y;
			//�ړ��ʐݒ�
			EBullet->mFx = 0;
			EBullet->mFy = -1;
			//�L���ɂ���
			EBullet->mEnabled = true;
			EBullet->mTag = EENEMYBULLET;
		}
		if (CPlayer::spInstance->x>x) {
			CBullet *EBullet = new CBullet();
			//���W�ݒ�
		    EBullet->x = x;
			EBullet->y = y;
			//�ړ��ʐݒ�
			EBullet->mFx = 1;
			EBullet->mFy = 0;
			//�L���ɂ���
			EBullet->mEnabled = true;
			EBullet->mTag = EENEMYBULLET;
		}
		mFireCount = 300;
	}
	x += mFx;
	y += mFy;
}
/*
�e��Collision���I�[�o�[���C�h����
�Փ˂���ƈړ������𔽑΂ɂ���
*/
bool CEnemy::Collision(const CRectangle &r) {
	//mEnabled��false�Ȃ�߂�
	if (!mEnabled) return false;
	//�e��Collision���\�b�h���Ăяo��
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
		case EBLOCK:
			//�Փ˂��Ă���Δ��]
			mFx *= -1;
			x += mFx;
			mFy = -1;
			y -= 1 * h;
			

			break;
		case EPLAYERBULLET:
			//�v���C���[�̒e�ɓ�����ƁA�����ɂ���
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
