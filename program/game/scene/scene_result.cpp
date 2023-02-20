#include "../game_manager.h"
#include "scene_result.h"
#include "scene_title.h"
#include "902scene_play.h"

void SceneResult::initialzie() {
}

void SceneResult::update(float delta_time)
{
	




	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		mgr->Re = 0;
		mgr->Sc = 0;
		mgr->time_score = 0;
		mgr->chengeScene(new SceneTitle());
	}

		

		if (effect_range > 0)
			effect_range--;
		else {
			if (mgr->time_score > 0) {
				mgr->Sc = mgr->Sc * 1.01f;
				mgr->time_score--;
			}
			else {
				if (init == false){
					int x = mgr->Sc;
					for (int i = 0; i < SC_MAX; i++) {
						if (mgr->Sc_s[i] < x) {
							int c;
							c = mgr->Sc_s[i]; mgr->Sc_s[i] = x; x = c;
						}
						init = true;
					}

				}
			}

		}
}

void SceneResult::render()
{/*
	unsigned int Re = 1;
	Re=Result(1);
	unsigned int Sc = 1;
	Sc= Score(Sc);
	*/

	int col;

	if (mgr->Sc > 1000000) col = 0xffffffffffffffff;

	DrawStringEx(50, 50, -1, "scene result\n");
	switch (mgr->Re) {
	case 0:
		DrawStringEx(50, 50, 0xffffffffffffffff, "\nQuit");
		break;
	case 1:
		DrawStringEx(50, 50, -1, "\nあなたは推進機の過剰使用により撃墜しました\nScore　%d", mgr->Sc);
		break;
	case 2:
		DrawStringEx(50, 50, -1, "\n60秒経過しました\nScore　%d", mgr->Sc);
		break;
	case 3:
		DrawStringEx(50, 50, -1, "\nGAME CLEAR!!\nScore　%d", mgr->Sc);
		break;
	case 10:
		DrawStringEx(50, 50, -1, "\nゲームは中断されました\nScore　%d", mgr->Sc);
		break;
	}

	if(mgr->time_score!=0)
	DrawStringEx(50, 50, -1, "\n\n\ntime BONUS %d", mgr->time_score);
	
	

	

	if (init == true) {
		for (int i = 0; i < SC_MAX; i++) {
			if (mgr->Sc_s[i] == mgr->Sc)
				DrawStringEx(50 * 2, 50 * (i + 3), 0xff00ff, "\nNo.%d:%d", i + 1, mgr->Sc_s[i]);
			else
				DrawStringEx(50 * 2, 50 * (i + 3), -1, "\nNo.%d:%d", i + 1, mgr->Sc_s[i]);
		}
	}
}