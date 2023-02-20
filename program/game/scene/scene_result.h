#include "scene_base.h"

class SceneResult : public SceneBase {
public:

	GameManager* mgr = GameManager::GetInstance();

	SceneResult() {}
	~SceneResult() {}

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

	int effect_range = 60;

	bool init = false;
};


