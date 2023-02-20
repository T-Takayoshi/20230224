//scean_play.cpp�Ƀf�[�^��^����
//scean_play.cpp�ōs���������ׂ����܂Ƃ߂�

#include "scene_base.h"
#include "701play_Objects.h"
//#include "801play_player.h"
//1221�ŐV��



//const int OBJ_MAX = 101;//�I�u�W�F�N�g�͂��̐��܂Ő�������܂�

#define SAFE_DELETE(p)  {delete p; p = nullptr;}//�Z�[�t�f���[�g��p���ăI�u�W�F�N�g���������܂��Bdelete�����Ώۂ�nullptr�𑦎�����邱�Ƃő��݂��Ȃ��I�u�W�F�N�g��ǂݍ��݃Q�[����������Ƃ������̂��Ȃ����܂�



//�v���C��ʑS�̂̏���
class ScenePlay : public SceneBase {
	//���̃y�[�W���ŏ����ł�����̂͂�����Ɋi�[����Ă���܂��B
private:
	Objects* objects;
	GameManager* gamemanager;//GameManager���̃f�[�^���Ăяo���܂�

	int Itemsize = 30, Enemysize = 200, Playersize = 50;
	int ItemTexture = 2, EnemyTexture = 0, PlayerTexture = 4;
	
	//
	//Object�Ɋւ���֐����̐���
	//
	dxe::Camera* camera = nullptr;//�J�����̐���
	
	//
	//�I�u�W�F�N�g�Ƃ͓Ɨ����ē����֐����̐���
	//
	//���ԂɊւ���֐�
	float second = 0;//���ԁi�b�j�Ɋւ���֐�
	float second_gameend = 0;//���ԁi�b�j�Ɋւ���֐� ���̊֐��̓Q�[���I������second���L�����A�i�s���ԂƔ�r����Ƃ��ɂ�������
	const float second_set = 2;////���ԁi�b�j�Ɋւ���֐����O�ɋL������second_gameend��second�̍����r����Ƃ��Ɏg�p

	int	GRAPHIC_MAX = 500;//�`����E�������֐�

	//Player�̏�Ԃ������`��̍ۂɒ������w�肷��֐�(�����炭�ق��̂��̂ɂ����p�͉\)
	int CENTER(int x) { return x / 2; }
	float CENTER(float x) { return x / 2; }

	


	int WIDE = 1000;
	int HEIGHT = 600;



	//initialzie���ł̏���------------------------------------------------------------------------------------------------------------------------



	//
	//�J�����̍쐬
	//
	void POP_camera() {
		camera = new dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

		//�J�����̏����ʒu�̐ݒ�B�����ʒu��ς��邱�Ƃōŏ��̃J�����̓�����^���邱�Ƃ��ł��A
		//�V�[���J�n���O�̉��o���؂₩�ɂł���
		camera->pos_ = { 0, 1000, 0 };
	}

	
	//
	//�I�u�W�F�N�g�Q�̍쐬
	//

	//�I�u�W�F�N�g�Q�̍쐬
	void POP_Objects();


	void POP_PLALANE();

	//updete���ł̏���------------------------------------------------------------------------------------------------------------------------

	//
	//�L�[�{�[�h���͏����������� 
	//
	void GetKeys() {
		GetKeys_W();
		GetKeys_Q();
		GetKeys_D();
		GetKeys_F();
	}

	//�L�[�����������班�����O�i�Ȃ���Ό���
	void GetKeys_W() {

		if (tnl::Input::IsKeyDown(eKeys::KB_W)) {
			if (objects->gofront_spead <= 40) {
				objects->gofront_spead++;
			}
		}
		else if (objects->gofront_spead > 0)objects->gofront_spead--;
	}

	//�L�[�����������班���������Ȃ���Ό���
	void GetKeys_Q() {

		if ((tnl::Input::IsKeyDown(eKeys::KB_Q)) && (objects->energy > 0)) {
			objects->peed_up++;
			objects->energy--;
		}
		else if (objects->peed_up > 0)objects->peed_up--;
	}
	//�L�[���������Ƃɂ���č�����
	void GetKeys_D() {
		if (tnl::Input::IsKeyDown(eKeys::KB_D)) {
			objects->obj[OBJ_Player]->rot_q_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(-1 - 0.2f * objects->spead[0]));
		}
	}
	//�L�[���������Ƃɂ���ĉE����
	void GetKeys_F() {
		if (tnl::Input::IsKeyDown(eKeys::KB_F)) {
			objects->obj[OBJ_Player]->rot_q_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(1 + 0.2f * objects->spead[0]));
		}
	}

	

	//
	//�J�����̍X�V
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



	//�f�o�b�N���O�@�������m�F�������ϐ��������ɓ��͂��邱�ƂŊm�F���邱�Ƃ��\
	void DEBUG_LOG(int x) {
		DrawStringEx(50, 50, -1, "\DEBUG_LOG[%d]", x);
	}
	void DEBUG_LOG(float x) {
		DrawStringEx(50, 50, -1, "\DEBUG_LOG[%f]", x);
	}


	dxe::Mesh* plane = nullptr;



};


