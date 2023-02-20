#pragma once
#include "../dxlib_ext/dxlib_ext.h"


const int SC_MAX = 10;



class SceneBase;
class GameManager {
private :
	GameManager();
	~GameManager();

	int img_black_ = 0;

	static GameManager* instance_;

	// ��ʑJ�ډ��o�̎���
	const float SCENE_TRANSITION_FIX_TIME = 0.5f;
	float scene_transition_time_ = 0;
	float scene_transition_alpha_ = 1.0f ;

	tnl::Sequence<GameManager> sequence_ = tnl::Sequence<GameManager>(this, &GameManager::seqSceneInTransition);

	// ��ʑJ��( �t�F�[�h�C���v���Z�X )
	bool seqSceneInTransition(const float delta_time);

	// �Q�[���v���Z�X
	bool seqGameProcess( const float delta_time );

	// ��ʑJ��( �t�F�[�h�A�E�g�v���Z�X )
	bool seqSceneOutTransition(const float delta_time);

	// ���݂̃V�[��
	SceneBase* scene_now_ = nullptr;
	// �\��V�[��
	SceneBase* scene_next_ = nullptr;

public :

	// �C���X�^���X�̎擾
	static GameManager* GetInstance();

	// �j��
	static void Destroy();

	// �X�V
	void update(float delta_time);

	// �V�[���̕ύX
	// arg1... SceneBase ���p�������N���X�C���X�^���X
	void chengeScene(SceneBase* next);

public :

	// �Q�[���S�̂ŎQ�Ƃ������ϐ��͂����ŗp��



	int Re=0, Sc=0;//�Q�[�����I�������Ƃ��̗v���ƃX�R�A��\��

	int Sc_s[SC_MAX]={ 2000000,1700000,1500000,1200000,1000000 ,200000,100000 ,50000,20000,10000};

	int time_score=0;
};



