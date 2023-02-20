#include "701play_Objects.h"



void Objects::Textures() {
	texs[0] = dxe::Texture::CreateFromFile("graphics/enemy01.bmp");
	texs[1] = dxe::Texture::CreateFromFile("graphics/enemy02.bmp");
	texs[5] = dxe::Texture::CreateFromFile("graphics/enemy03.bmp");
	texs[2] = dxe::Texture::CreateFromFile("graphics/blue2.bmp");
	texs[3] = dxe::Texture::CreateFromFile("graphics/blue1.bmp");
	texs[4] = dxe::Texture::CreateFromFile("graphics/box.bmp");
}

void Objects::POP_Objects(int ObjectNo, float size, int TextureCode, bool enemy) {
	//�w�肳�ꂽObject�̑傫���ɂ���
	obj[ObjectNo] = dxe::Mesh::CreateBoxMV(size);
	//�w�肳�ꂽObject�̃e�N�X�`���ɂ���
	obj[ObjectNo]->setTexture(texs[TextureCode]);
	//Random�ȍ��W������
	obj_x[ObjectNo] = (rand() % 50 - 25) * 150;
	obj_y[ObjectNo] = (rand() % 50 - 25) * 150;

	if (enemy) {
		obj_x[ObjectNo] = 0;
		obj_y[ObjectNo] = 0;
	}

	//�K���ȍ��W�ɔz�u����
	obj[ObjectNo]->pos_ = { obj_x[ObjectNo],size/2, obj_y[ObjectNo] };
}




//
//Object�̍X�V
//
void Objects::Move_Object() {
	GameManager* gamemanager = GameManager::GetInstance();

	for (int ObjectNo = 1; ObjectNo < OBJ_MAX; ObjectNo++) {
		if (obj[ObjectNo] != nullptr) {
			//�ԃA�C�e���̏���
			if (ObjectNo == 1) {
				Move_Object_RedBox(ObjectNo);
			}
			//�A�C�e���̌���
			else {
				Move_Object_BlueBox(ObjectNo);
			}
		}
	}
	
}


//RedBox�̊�{�I�ȋ����Ɋւ���v���O����(i�ɂ̓I�u�W�F�N�g�ԍ������͂���邱�Ƃ�z�肵�Ă���)
void Objects::Move_Object_RedBox(int ObjectNo) {

	obj[ObjectNo]->rot_q_ = obj[OBJ_Player]->rot_q_;

	DISTANSE(ObjectNo);

	//�ڐG
	if (tnl::IsIntersectSphere(obj[OBJ_Player]->pos_, 100, obj[ObjectNo]->pos_, 100)) {
		HIT_Player(ObjectNo);

	}

	//�ҋ@
	else {
		obj_reaction[ObjectNo]--;
		if (obj_reaction[ObjectNo] < 1) {
			obj_reaction[ObjectNo] = 1;
			obj[ObjectNo]->setTexture(texs[0]);
		}
	}
	
	NOCKBACK(ObjectNo);
	DERAY();
}
void Objects::DISTANSE(int ObjectNo) {
	GameManager* gamemanager = GameManager::GetInstance();
	int dis = 0;
	for (int F = 0; F == 0; dis++) {
		if (tnl::IsIntersectSphere(obj[OBJ_Player]->pos_, dis, obj[ObjectNo]->pos_, 0))
			F = 1;
		if (dis > 5001)break;
	}

	if (dis > RANGE_FAR) {
		if (gamemanager->Re != 3)
			gamemanager->Sc = gamemanager->Sc * 10;
		gamemanager->Re = 3;
	}


	if (dis < 5001)
		obj[ObjectNo]->pos_ = tnl::Vector3::Lerp(obj[ObjectNo]->pos_, obj[OBJ_Player]->pos_, 0.02f);

}

void  Objects::HIT_Player(int ObjectNo) {

	obj[ObjectNo]->setTexture(texs[1]);//���g�̐F��ڐG�����Ƃ��̐F�ɕύX


	nockback[ObjectNo] = obj[ObjectNo]->pos_ - obj[OBJ_Player]->pos_;//�ڐG����������F������
	nockback[ObjectNo].normalize();//��L�̃v���O������P�ʃx�N�g���ɕύX����

	nockback[ObjectNo] *= ((spead[1] * spead[0]) / ((RESISTANCE)+0.3f));//Player�̑��x���v�Z���A���g�̗̑͂����Ƃɐ�����΂����͂�ݒ肷��

	//
	tnl::Vector3 av = (obj[OBJ_Player]->pos_ - obj[ObjectNo]->pos_);
	tnl::Vector3 bv = (obj[ObjectNo]->pos_ - obj[OBJ_Player]->pos_);
	av.normalize();
	bv.normalize();

	tnl::Vector3  v1 = obj[ObjectNo]->pos_ + (av * 200.0f);
	tnl::Vector3  v2 = obj[OBJ_Player]->pos_ + (bv * 200.0f);

	obj[OBJ_Player]->pos_ = v1;
	obj[ObjectNo]->pos_ = v2;


	obj_reaction[ObjectNo] = TIME_SUTAIN;

	peed_up = (peed_up / 10) * 7;

	for (int i = spead[1] * spead[0]; i > 0; i--) {
		//���g�̗̑͂����炷
		if (RESISTANCE > 0)
			RESISTANCE--;

		//���g�̗̑͂̕\����ς���֐��B�`�掞�Ɏg�p
		DELAY += RESISTANCE_DELAY - RESISTANCE;
		RESISTANCE_DELAY = RESISTANCE;
	}
}

void  Objects::NOCKBACK(int ObjectNo) {
	nockback[ObjectNo] *= 0.95f;

	obj[ObjectNo]->pos_ += nockback[ObjectNo] * 10;
	if (RESISTANCE == 0 || DELAY > 150) {

		obj[ObjectNo]->setTexture(texs[5]);
	}
}

void  Objects::DERAY() {
	GameManager* gamemanager = GameManager::GetInstance();
	if (DELAY > 0) {
		gamemanager->Sc += DELAY;
		DELAY--;
	}
}

//BlueBox�̊�{�I�ȋ����Ɋւ���v���O����(i�ɂ̓I�u�W�F�N�g�ԍ������͂���邱�Ƃ�z�肵�Ă���)
void Objects::Move_Object_BlueBox(int i) {
	GameManager* gamemanager = GameManager::GetInstance();

	//�ҋ@���
	if (tnl::IsIntersectSphere(obj[OBJ_Player]->pos_, 80, obj[i]->pos_, 80)) {

		obj[i]->pos_ = tnl::Vector3::Lerp(obj[i]->pos_, obj[OBJ_Player]->pos_, 0.1f);
	}
	if (tnl::IsIntersectSphere(obj[OBJ_Player]->pos_, 50, obj[i]->pos_, 30 && obj_reaction[i] == 0)) {



		if (obj_reaction[i] == 0) gamemanager->Sc += 500;
		obj_reaction[i] = 1;




	}
	//�ڐG�iPlayer�ɂ���Ă��̃A�C�e�����E�����ꂽ�ꍇ�ғ��j
	if (obj_reaction[i] >= 1) {
		obj[i]->setTexture(texs[3]);//�E�����̐F�ɕύX
		obj[i]->pos_ = tnl::Vector3::Lerp(obj[i]->pos_, obj[OBJ_Player]->pos_, 0.09f);//Player��
		obj_reaction[i] += 2;
		obj[i]->rot_q_ *= tnl::Quaternion::RotationAxis({ 0, obj_reaction[i], 0 }, tnl::ToRadian(obj_reaction[i]));
		tnl::Vector3 mv = tnl::Vector3::TransformCoord({ 0,1,0 }, obj[i]->rot_q_);
		obj[i]->pos_ += mv * 10.0f;

		if (obj_reaction[i] > 80) {//BlueBox�����̐��l�܂œ��B�����ꍇ
			energy += 70;//Player�ɍ��̐��l��^���܂�
			SAFE_DELETE(obj[i]);//���g�����ł����܂�
		}
	}
}