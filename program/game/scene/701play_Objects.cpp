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
	//指定されたObjectの大きさにする
	obj[ObjectNo] = dxe::Mesh::CreateBoxMV(size);
	//指定されたObjectのテクスチャにする
	obj[ObjectNo]->setTexture(texs[TextureCode]);
	//Randomな座標を所得
	obj_x[ObjectNo] = (rand() % 50 - 25) * 150;
	obj_y[ObjectNo] = (rand() % 50 - 25) * 150;

	if (enemy) {
		obj_x[ObjectNo] = 0;
		obj_y[ObjectNo] = 0;
	}

	//適当な座標に配置する
	obj[ObjectNo]->pos_ = { obj_x[ObjectNo],size/2, obj_y[ObjectNo] };
}




//
//Objectの更新
//
void Objects::Move_Object() {
	GameManager* gamemanager = GameManager::GetInstance();

	for (int ObjectNo = 1; ObjectNo < OBJ_MAX; ObjectNo++) {
		if (obj[ObjectNo] != nullptr) {
			//赤アイテムの所得
			if (ObjectNo == 1) {
				Move_Object_RedBox(ObjectNo);
			}
			//青アイテムの効果
			else {
				Move_Object_BlueBox(ObjectNo);
			}
		}
	}
	
}


//RedBoxの基本的な挙動に関するプログラム(iにはオブジェクト番号が入力されることを想定している)
void Objects::Move_Object_RedBox(int ObjectNo) {

	obj[ObjectNo]->rot_q_ = obj[OBJ_Player]->rot_q_;

	DISTANSE(ObjectNo);

	//接触
	if (tnl::IsIntersectSphere(obj[OBJ_Player]->pos_, 100, obj[ObjectNo]->pos_, 100)) {
		HIT_Player(ObjectNo);

	}

	//待機
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

	obj[ObjectNo]->setTexture(texs[1]);//自身の色を接触したときの色に変更


	nockback[ObjectNo] = obj[ObjectNo]->pos_ - obj[OBJ_Player]->pos_;//接触した方向を認識する
	nockback[ObjectNo].normalize();//上記のプログラムを単位ベクトルに変更する

	nockback[ObjectNo] *= ((spead[1] * spead[0]) / ((RESISTANCE)+0.3f));//Playerの速度を計算し、自身の体力をもとに吹き飛ばされる力を設定する

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
		//自身の体力を減らす
		if (RESISTANCE > 0)
			RESISTANCE--;

		//自身の体力の表示を変える関数。描画時に使用
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

//BlueBoxの基本的な挙動に関するプログラム(iにはオブジェクト番号が入力されることを想定している)
void Objects::Move_Object_BlueBox(int i) {
	GameManager* gamemanager = GameManager::GetInstance();

	//待機状態
	if (tnl::IsIntersectSphere(obj[OBJ_Player]->pos_, 80, obj[i]->pos_, 80)) {

		obj[i]->pos_ = tnl::Vector3::Lerp(obj[i]->pos_, obj[OBJ_Player]->pos_, 0.1f);
	}
	if (tnl::IsIntersectSphere(obj[OBJ_Player]->pos_, 50, obj[i]->pos_, 30 && obj_reaction[i] == 0)) {



		if (obj_reaction[i] == 0) gamemanager->Sc += 500;
		obj_reaction[i] = 1;




	}
	//接触（Playerによってこのアイテムが拾得された場合稼働）
	if (obj_reaction[i] >= 1) {
		obj[i]->setTexture(texs[3]);//拾得時の色に変更
		obj[i]->pos_ = tnl::Vector3::Lerp(obj[i]->pos_, obj[OBJ_Player]->pos_, 0.09f);//Playerが
		obj_reaction[i] += 2;
		obj[i]->rot_q_ *= tnl::Quaternion::RotationAxis({ 0, obj_reaction[i], 0 }, tnl::ToRadian(obj_reaction[i]));
		tnl::Vector3 mv = tnl::Vector3::TransformCoord({ 0,1,0 }, obj[i]->rot_q_);
		obj[i]->pos_ += mv * 10.0f;

		if (obj_reaction[i] > 80) {//BlueBoxがこの数値まで到達した場合
			energy += 70;//Playerに左の数値を与えます
			SAFE_DELETE(obj[i]);//自身を消滅させます
		}
	}
}