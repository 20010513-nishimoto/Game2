#ifndef COBSTACLE_H
#define COBSTACLE_H

#include "CRectangle.h"


/*
CObstacle
��Q���N���X
CRectangle�N���X���p������
�e�FCRectangle�N���X
�q�FCObstacle�N���X
*/
class CObstacle : public CRectangle {
public:
	int mFx, mFy;	//�ړ���

	//�f�t�H���g�R���X�g���N�^
	CObstacle();
	//�X�V����
	void Update();

	//�`�揈��
	void Render();

	void Collision(CRectangle *i, CRectangle *y);

};

#endif
