#include "../../dxlib_ext/dxlib_ext.h"

#include "scene_base.h"
#include "../game_manager.h"

#include "601play_manager.h"

#define SAFE_DELETE(p)  {delete p; p = nullptr;}//�Z�[�t�f���[�g��p���ăI�u�W�F�N�g���������܂��Bdelete�����Ώۂ�nullptr�𑦎�����邱�Ƃő��݂��Ȃ��I�u�W�F�N�g��ǂݍ��݃Q�[����������Ƃ������̂��Ȃ����܂�





class Objects {
private:

	//�I�u�W�F�N�g�̃T�C�Y����������
	float size;

public:

	Objects() {}
	~Objects() {}

	void Textures();
	void POP_Objects(int, float, int ,bool);
	Shared<dxe::Texture> texs[6];//�e�N�X�`���̐��̎w��
	

	//�I�u�W�F�N�g�̃e�N�X�`���̏���

	//���ړ��B�p�����ς񂾂�private��
	float obj_reaction[OBJ_MAX]{ 0 };//�e�I�u�W�F�N�g���L����̏����ɍ��킹�Areaction���s��
	dxe::Mesh* obj[OBJ_MAX]{ 0 };
	float obj_x[OBJ_MAX]{ 0 }, obj_y[OBJ_MAX]{ 0 };//�e�I�u�W�F�N�g��X,Y���W������

	//RedBox�Ɏg���֐�
	tnl::Vector3 nockback[OBJ_MAX];//nockback������
	int RESISTANCE = 1000;//�G�̒�R
	int RESISTANCE_DELAY = RESISTANCE;//�x���\�L
	int DELAY = 0;//�\�������p
	int TIME_SUTAIN = 30;//�I�u�W�F�N�g�̐F�����Ƃɖ߂����Ԃ�\���֐�
	int RANGE_FAR = 5000;//�G�������܂Ō�ނ������珟���Ɣ��f���邽�߂̊֐�

	//Player�Ɏg���֐�
	int  peed_up = 0;//�S�̓I�ȑ��x���グ��֐�
	int gofront_spead = 0;//�O�i�Ɋւ���֐�
	int energy = 200;//ENERGY�c��
	float spead[2] = { 0 };//���x�Ɋւ���֐�
	
	//�R�}���h����
	void GetKeys_F();
	void GetKeys_D();

	//
//Object�̍X�V
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
