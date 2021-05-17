#ifndef CMAP_H
#define CMAP_H

#include "CRectangle.h"

extern CTexture Texture;

class CMap : public CRectangle {
public:
	void Render() {
		if (mEnabled) {
			CRectangle::Render(Texture, 48, 95, 191, 144);
		}
	}
	void Collision(CRectangle *i, CRectangle *y) {
		
		//�e��Collision���\�b�h���Ăяo��
		if (CRectangle::Collision(*y)) {
			if (mTag == EERASE)
			{
				switch (y->mTag) {
				case EENEMY:
					mEnabled = false;
					break;
				case EPLAYERBULLET:
					//�v���C���[�̒e�ɓ�����ƁA�����ɂ���
					mEnabled = false;
					break;
				case EPLAYER:
					mEnabled = false;
					break;
				}
			}
			

		}
		

	}
};

#endif
