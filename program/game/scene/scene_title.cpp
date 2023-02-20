#include "../game_manager.h"
#include "scene_title.h"
#include "902scene_play.h"


void SceneTitle::initialzie() {
}

void SceneTitle::update(float delta_time)
{
	SetFontSize(64);
	DrawStringEx(50, 100, 0xffffffffff6fffff, "�j�m�n�b�j�@�n�t�s�I�I");
	//�F���ς��@�@�@�@�@ NNNNNNNNNNRNGNBN, "\nQuit");
	SetFontSize(32);
	DrawStringEx(50, 200, 0xffffff, "����ȓG�AREDBOX���瓦���Ȃ���\nENERGY�����ł���BLUEBOX���Q�b�g��\n������REDBOX�ɓ˂�����\nREDBOX�𐁂���΂����I");
	DrawStringEx(50, 200, 0xffff00, "\n\n\n\nQ:�_�b�V��\nW:�O�i\nD:������\nF:�E����\n��������:��ʁ� �̓������ENEMYLIFE��0�ɂ���");
	GameManager* mgr = GameManager::GetInstance();

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		mgr->chengeScene( new ScenePlay() );
	}

}

void SceneTitle::render()
{
	DrawStringEx(50, 50, -1, "scene title");
}
