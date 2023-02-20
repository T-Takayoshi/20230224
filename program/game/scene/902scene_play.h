//scean_play.cppにデータを与える
//scean_play.cppで行う処理を細かくまとめる

#include "scene_base.h"
#include "701play_Objects.h"
//#include "801play_player.h"
//1221最新作



//const int OBJ_MAX = 101;//オブジェクトはこの数まで生成されます

#define SAFE_DELETE(p)  {delete p; p = nullptr;}//セーフデリートを用いてオブジェクトを除去します。deleteした対象にnullptrを即時入れることで存在しないオブジェクトを読み込みゲームが落ちるという事故をなくします



//プレイ画面全体の処理
class ScenePlay : public SceneBase {
	//このページ内で処理できるものはこちらに格納されております。
private:
	Objects* objects;
	GameManager* gamemanager;//GameManager内のデータを呼び出します

	int Itemsize = 30, Enemysize = 200, Playersize = 50;
	int ItemTexture = 2, EnemyTexture = 0, PlayerTexture = 4;
	
	//
	//Objectに関する関数等の生成
	//
	dxe::Camera* camera = nullptr;//カメラの生成
	
	//
	//オブジェクトとは独立して動く関数等の生成
	//
	//時間に関する関数
	float second = 0;//時間（秒）に関する関数
	float second_gameend = 0;//時間（秒）に関する関数 この関数はゲーム終了時のsecondを記憶し、進行時間と比較するときにもちいる
	const float second_set = 2;////時間（秒）に関する関数事前に記憶したsecond_gameendとsecondの差を比較するときに使用

	int	GRAPHIC_MAX = 500;//描画限界を示す関数

	//Playerの状態を示す描画の際に中央を指定する関数(おそらくほかのものにも活用は可能)
	int CENTER(int x) { return x / 2; }
	float CENTER(float x) { return x / 2; }

	


	int WIDE = 1000;
	int HEIGHT = 600;



	//initialzie内での処理------------------------------------------------------------------------------------------------------------------------



	//
	//カメラの作成
	//
	void POP_camera() {
		camera = new dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

		//カメラの初期位置の設定。初期位置を変えることで最初のカメラの動きを与えることができ、
		//シーン開始直前の演出を華やかにできる
		camera->pos_ = { 0, 1000, 0 };
	}

	
	//
	//オブジェクト群の作成
	//

	//オブジェクト群の作成
	void POP_Objects();


	void POP_PLALANE();

	//updete内での処理------------------------------------------------------------------------------------------------------------------------

	//
	//キーボード入力情報を所得する 
	//
	void GetKeys() {
		GetKeys_W();
		GetKeys_Q();
		GetKeys_D();
		GetKeys_F();
	}

	//キーを所得したら少しずつ前進なければ減衰
	void GetKeys_W() {

		if (tnl::Input::IsKeyDown(eKeys::KB_W)) {
			if (objects->gofront_spead <= 40) {
				objects->gofront_spead++;
			}
		}
		else if (objects->gofront_spead > 0)objects->gofront_spead--;
	}

	//キーを所得したら少しずつ加速なければ減衰
	void GetKeys_Q() {

		if ((tnl::Input::IsKeyDown(eKeys::KB_Q)) && (objects->energy > 0)) {
			objects->peed_up++;
			objects->energy--;
		}
		else if (objects->peed_up > 0)objects->peed_up--;
	}
	//キーを押すことによって左旋回
	void GetKeys_D() {
		if (tnl::Input::IsKeyDown(eKeys::KB_D)) {
			objects->obj[OBJ_Player]->rot_q_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(-1 - 0.2f * objects->spead[0]));
		}
	}
	//キーを押すことによって右旋回
	void GetKeys_F() {
		if (tnl::Input::IsKeyDown(eKeys::KB_F)) {
			objects->obj[OBJ_Player]->rot_q_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(1 + 0.2f * objects->spead[0]));
		}
	}

	

	//
	//カメラの更新
	//
	void Move_Camera() {
		tnl::Vector3 ofs = tnl::Vector3::TransformCoord({ 0,100,-300 }, objects->obj[OBJ_Player]->rot_q_);
		camera->pos_ = tnl::Vector3::Lerp(camera->pos_, objects->obj[OBJ_Player]->pos_ + ofs, 0.1f);
		camera->target_ = objects->obj[OBJ_Player]->pos_;
	}


	

//--------------------------------------------------------------------------------------------------------------------------------------
public:
	ScenePlay();
	~ScenePlay() {
		delete camera;
		for (int i = 0; i < OBJ_MAX; ++i) SAFE_DELETE(objects->obj[i]);
		SAFE_DELETE(objects);
	}
	
	void initialzie() override;
	void update(float delta_time) override;
	void render() override;



	//デバックログ　挙動を確認したい変数をここに入力することで確認することが可能
	void DEBUG_LOG(int x) {
		DrawStringEx(50, 50, -1, "\DEBUG_LOG[%d]", x);
	}
	void DEBUG_LOG(float x) {
		DrawStringEx(50, 50, -1, "\DEBUG_LOG[%f]", x);
	}


	dxe::Mesh* plane = nullptr;



};


