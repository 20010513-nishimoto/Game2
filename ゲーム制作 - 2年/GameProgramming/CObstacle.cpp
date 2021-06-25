#include "CObstacle.h"
#include "CTexture.h"
//extern�F���̃\�[�X�t�@�C���̊O���ϐ��ɃA�N�Z�X����錾
extern CTexture Texture;

//�f�t�H���g�R���X�g���N�^
CObstacle::CObstacle()
: mFx(0), mFy(0)
{
	mEnabled = false;
	w = 10;	//���ݒ�
	h = 10;	//�����ݒ�
}

//�X�V����
void CObstacle::Update() {
	//�L���Ȏ�
	if (mEnabled) {
		//�ړ�
		x += mFx;
		y += mFy;
		if (x > 400 || x < -400 || y > 300 || y < -300)
			mEnabled = false;
	}
}

//�`�揈��
void CObstacle::Render() {
	//�L���Ȏ�
	if (mEnabled) {
		//�e�̕`�惁�\�b�h���Ă�
		CRectangle::Render(Texture, 192, 207, 112, 97);
	}
}

void CObstacle::Collision(CRectangle *i, CRectangle *y) {
	//if (i->mEnabled && y->mEnabled) {
	if (y->mTag == EBLOCK) {
		if (i->Collision(*y)) {
			mEnabled = false;
			return;
		}
	}
	if (y->mTag == EERASE) {
		if (i->Collision(*y)) {
			mEnabled = false;
			return;
		}
	}
	if (i->mTag == EENEMYCOBSTACLE && y->mTag == EPLAYER) {
		if (i->Collision(*y)) {
			mEnabled = false;
			return;
		}

	}
	if (i->mTag == EPLAYERCOBSTACLE && y->mTag == EENEMY) {
		if (i->Collision(*y)) {
			mEnabled = false;
			return;
		}

	}
	//}
}
