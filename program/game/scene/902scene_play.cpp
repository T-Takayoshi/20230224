//大まかな仕組みを構築し、scean_play.hのデータ、処理を与える

#include "../game_manager.h"
#include "scene_result.h"
#include "902scene_play.h"



#include <ctime>        // time
#include <cstdlib>      // srand,rand


//　コンストラクタ
ScenePlay::ScenePlay()
{
	// 新規Objectsの生成
	objects = new Objects;


}

//int Keys[256]; // キーが押されているフレーム数を格納する
// キーの入力状態を更新する
void ScenePlay::initialzie() {
	gamemanager = GameManager::GetInstance();

	POP_camera();
	POP_Objects();

	POP_PLALANE();

}








void ScenePlay::update(float delta_time) {

	second += delta_time;

	



	GetKeys();

	if ((gamemanager->Re == 0) || (gamemanager->Re == 3)) {

		//シーンチェンジ
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			gamemanager->Re = 10;
			gamemanager->chengeScene(new SceneResult());
		}

		objects->Move_Object();
		Move_Camera();


		if (objects->peed_up > 100)objects->spead[0] = 100 * 0.1; else objects->spead[0] = objects->peed_up * 0.1; {
			objects->spead[1] = objects->gofront_spead * 0.1;
		}

		tnl::Vector3 mv = tnl::Vector3::TransformCoord({ 0,0,objects->spead[1] }, objects->obj[OBJ_Player]->rot_q_);
		objects->obj[OBJ_Player]->pos_ += mv * (2.0f + objects->spead[0]);

		



		camera->update();
		if (second >= 180)gamemanager->Re = 2;




		DrawStringEx(WIDE / 2 - 100, 100, -1, "\nScore %d", gamemanager->Sc);


		if (second < 120) {
			DrawStringEx(WIDE / 2 - 100, 100, 0xfffffffff, "time %.2f", second);
		}
		else {
			int i = second;
			if (second - i > 0.2f)
				DrawStringEx(WIDE / 2 - 100, 100, 0xfffffff00, "time %.2f", second);
		}
	}

	//ゲーム終了の分岐
	if (gamemanager->Re != 0) {
		if (second_gameend == 0) {
			second_gameend = second;
		}
		switch (gamemanager->Re)
		{
		case 2:
			DrawStringEx(WIDE / 2 - 100, 100, 0xfffffff00, "time %.2f", second);
			break;
		case 3:
			gamemanager->time_score = 180 - second;
			break;
		}


		if (second > second_gameend + second_set) {
			second = 0;
			objects->peed_up = 0;
			gamemanager->chengeScene(new SceneResult());
		}

	}

}



void ScenePlay::render()
{

	plane->render(camera);

	if ((gamemanager->Re == 0) || (gamemanager->Re == 3)) {
		objects->obj[OBJ_Player]->render(camera);

		for (int i = 0; i < 100; i++) {
			if (objects->obj[i] != nullptr) objects->obj[i]->render(camera);
		}


		//ENERGY残量
		SetFontSize(80);
		if (objects->energy > 100)DrawStringEx(0, HEIGHT, 0x00ffff, "ENERGY[%d]", objects->energy);
		else if (objects->energy == 0)DrawStringEx(0, HEIGHT, 0xff0000, "ENERGY[%d]", objects->energy);
		else DrawStringEx(0, 600, 0xffff00, "ENERGY[%d]", objects->energy);

		for (int i = 0; i < objects->energy; i++) {
			if (i % 10 == 0 || i <= 5) {
				int m = i - CENTER(GRAPHIC_MAX);
				int m_ax = 1 + (m * m / 200);
				for (int k = m_ax; k > -0; k--) {

					if (i < GRAPHIC_MAX + 10) {
						if (1) {

							if (i > 100) { DrawStringEx(10 + k, HEIGHT - 50 - i, 0x00ffff, "-"); }
							else { DrawStringEx(10 + k, HEIGHT - 50 - i, 0xffff00, "-"); }
						}
					}
				}
			}
			if (i > 500)break;//軽量化処理のbreak ここで省略しないと余分な描画によってものすごく重くなる
		}
		SetFontSize(30);



		//ブーストヒート率
		SetFontSize(80);
		if (objects->peed_up > 100)DrawStringEx(WIDE - 400, HEIGHT, 0xff0000, "BOOST[%d]", objects->peed_up);
		else if (objects->peed_up > 50)DrawStringEx(WIDE - 400, HEIGHT, 0xffff00, "BOOST[%d]", objects->peed_up);
		else DrawStringEx(WIDE - 400, HEIGHT, -1, "BOOST[%d]", objects->peed_up);

		for (int i = 0; i < objects->peed_up; i++) {
			if (i % 2 == 0 && i > 0) {
				int m = i * 5 - CENTER(GRAPHIC_MAX);
				int m_ax = 1 + (m * m / 200);
				for (int k = m_ax; k > -0; k--) {
					if (i < (GRAPHIC_MAX / 5) + 10) {
						if (objects->peed_up > 100) {
							DrawStringEx(WIDE - 40 - k, HEIGHT - 50 - i * 5, 0xff8800, "-");
						}
						else if (objects->peed_up > 50) {
							DrawStringEx(WIDE - 40 - k, HEIGHT - 50 - i * 5, 0xffff00, "-");
						}
						else {
							DrawStringEx(WIDE - 40 - k, HEIGHT - 50 - i * 5, -1, "-");
						}
					}
				}
			}
			if (i > 100)break;//軽量化処理のbreak ここで省略しないと余分な描画によってものすごく重くなる
		}

		SetFontSize(30);



		//速度計
		SetFontSize(80);
		if (objects->peed_up > 100)DrawStringEx(WIDE - 400, 600, 0x00ffff, "BOOST[%d]", objects->peed_up);
		else if (objects->peed_up == 0)DrawStringEx(WIDE - 400, 600, 0xff0000, "BOOST[%d]", objects->peed_up);
		else DrawStringEx(WIDE - 400, 600, 0xffff00, "BOOST[%d]", objects->peed_up);

		for (int i = -1; i < (int)((objects->spead[0] + 1) * (objects->spead[1] + 1)); i++) {

			if (i > 0) {
				int m = i * 10 - CENTER(GRAPHIC_MAX);
				int m_ax = 1 + (m * m / 200);
				for (int k = m_ax; k > -0; k--) {
					if (i < (GRAPHIC_MAX / 5) + 10) {
						SetFontSize(40);
						DrawStringEx(WIDE - 30 - k, HEIGHT - 50 + 20 - i * 10, 0x00ffff, "-");
					}
				}
			}
			if (i > 49)break;
		}

		if (gamemanager->Re == 3) {
			SetFontSize(80);
			DrawStringEx(WIDE / 10, HEIGHT / 2, 0x00ffff, "ＫＮＯＣＫ　ＯＵＴ！！");
		}

	}
	SetFontSize(30 + (objects->DELAY / 10));

	DrawStringEx(400 - (objects->DELAY / 5), 50, -1, "ENEMY LIFE %d", objects->RESISTANCE);

	SetFontSize(30);

	//DrawGridGround(50, 20);
}


void ScenePlay::POP_Objects() {

	objects->Textures();

	for (int ObjectNo = 0; ObjectNo < OBJ_MAX; ObjectNo++) {//オブジェクト最大数を所得しオブジェトをその数まで生成する

		//条件分岐　条件に合致した場合はPlayer、REDBOXを、それ以外はBlueBoxとして処理をする
		if (ObjectNo == OBJ_Player) {//Object番号がPlayerを示していた場合
			objects->POP_Objects(ObjectNo, Playersize, PlayerTexture,false);
		}
		else if (ObjectNo == OBJ_RedBox) {//Object番号がRedBoxを示していた場合
			objects->POP_Objects(ObjectNo, Enemysize, EnemyTexture,true);
		}
		else {
			objects->POP_Objects(ObjectNo, Itemsize, ItemTexture, false);
		}
	}
}

void ScenePlay::POP_PLALANE() {
	plane = dxe::Mesh::CreatePlane({ 10000, 10000, 0 });
	plane->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	plane->pos_ = tnl::Vector3::TransformCoord({ 0,-40,0 }, objects->obj[OBJ_Player]->rot_q_);
	plane->setTexture(dxe::Texture::CreateFromFile("graphics/weed.jpg"));

}

