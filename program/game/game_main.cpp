#include <time.h>
#include "game_main.h"
#include "game_manager.h"

void gameMain(float delta_time) {
	GameManager* mgr = GameManager::GetInstance();
	mgr->update(delta_time);
}

void gameEnd() {
	GameManager::Destroy();
}
