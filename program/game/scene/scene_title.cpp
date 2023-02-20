#include "../game_manager.h"
#include "scene_title.h"
#include "902scene_play.h"


void SceneTitle::initialzie() {
}

void SceneTitle::update(float delta_time)
{
	SetFontSize(64);
	DrawStringEx(50, 100, 0xffffffffff6fffff, "ＫＮＯＣＫ　ＯＵＴ！！");
	//色が変わる　　　　　 NNNNNNNNNNRNGNBN, "\nQuit");
	SetFontSize(32);
	DrawStringEx(50, 200, 0xffffff, "巨大な敵、REDBOXから逃げながら\nENERGYを入手できるBLUEBOXをゲットし\n高速でREDBOXに突っ込み\nREDBOXを吹っ飛ばそう！");
	DrawStringEx(50, 200, 0xffff00, "\n\n\n\nQ:ダッシュ\nW:前進\nD:左旋回\nF:右旋回\n勝利条件:画面↑ 体当たりでENEMYLIFEを0にする");
	GameManager* mgr = GameManager::GetInstance();

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		mgr->chengeScene( new ScenePlay() );
	}

}

void SceneTitle::render()
{
	DrawStringEx(50, 50, -1, "scene title");
}
