#include "../game_manager.h"
#include "scene_title.h"
#include "902scene_play.h"


void SceneTitle::initialzie() {
}

void SceneTitle::update(float delta_time)
{
	SetFontSize(64);
	DrawStringEx(50, 100, 0xffffffffff6fffff, "‚j‚m‚n‚b‚j@‚n‚t‚sII");
	//F‚ª•Ï‚í‚é@@@@@ NNNNNNNNNNRNGNBN, "\nQuit");
	SetFontSize(32);
	DrawStringEx(50, 200, 0xffffff, "‹‘å‚È“GAREDBOX‚©‚ç“¦‚°‚È‚ª‚ç\nENERGY‚ð“üŽè‚Å‚«‚éBLUEBOX‚ðƒQƒbƒg‚µ\n‚‘¬‚ÅREDBOX‚É“Ë‚Áž‚Ý\nREDBOX‚ð‚Á”ò‚Î‚»‚¤I");
	DrawStringEx(50, 200, 0xffff00, "\n\n\n\nQ:ƒ_ƒbƒVƒ…\nW:‘Oi\nD:¶ù‰ñ\nF:‰Eù‰ñ\nŸ—˜ðŒ:‰æ–Êª ‘Ì“–‚½‚è‚ÅENEMYLIFE‚ð0‚É‚·‚é");
	GameManager* mgr = GameManager::GetInstance();

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		mgr->chengeScene( new ScenePlay() );
	}

}

void SceneTitle::render()
{
	DrawStringEx(50, 50, -1, "scene title");
}
