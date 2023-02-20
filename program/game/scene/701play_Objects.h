#include "../../dxlib_ext/dxlib_ext.h"

#include "scene_base.h"
#include "../game_manager.h"

#include "601play_manager.h"

#define SAFE_DELETE(p)  {delete p; p = nullptr;}//セーフデリートを用いてオブジェクトを除去します。deleteした対象にnullptrを即時入れることで存在しないオブジェクトを読み込みゲームが落ちるという事故をなくします





class Objects {
private:

	//オブジェクトのサイズを所得する
	float size;

public:

	Objects() {}
	~Objects() {}

	void Textures();
	void POP_Objects(int, float, int ,bool);
	Shared<dxe::Texture> texs[6];//テクスチャの数の指定
	

	//オブジェクトのテクスチャの所得

	//仮移動。用件が済んだらprivateへ
	float obj_reaction[OBJ_MAX]{ 0 };//各オブジェクト特有特定の条件に合わせ、reactionを行う
	dxe::Mesh* obj[OBJ_MAX]{ 0 };
	float obj_x[OBJ_MAX]{ 0 }, obj_y[OBJ_MAX]{ 0 };//各オブジェクトのX,Y座標を扱う

	//RedBoxに使う関数
	tnl::Vector3 nockback[OBJ_MAX];//nockbackを実装
	int RESISTANCE = 1000;//敵の抵抗
	int RESISTANCE_DELAY = RESISTANCE;//遅延表記
	int DELAY = 0;//表示調整用
	int TIME_SUTAIN = 30;//オブジェクトの色をもとに戻す時間を表す関数
	int RANGE_FAR = 5000;//敵をここまで後退させたら勝利と判断するための関数

	//Playerに使う関数
	int  peed_up = 0;//全体的な速度を上げる関数
	int gofront_spead = 0;//前進に関する関数
	int energy = 200;//ENERGY残量
	float spead[2] = { 0 };//速度に関する関数
	
	//コマンド入力
	void GetKeys_F();
	void GetKeys_D();

	//
//Objectの更新
// 
//
	
	void Move_Object();


	void Move_Object_RedBox(int);
	void DISTANSE(int);
	void HIT_Player(int ObjectNo);
	void NOCKBACK(int);
	void DERAY();


	void Move_Object_BlueBox(int);

};
