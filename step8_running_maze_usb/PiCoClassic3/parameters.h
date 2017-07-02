
#ifndef _PARAMETER

#include "static_parameters.h"

//�����I�ȃp�����[�^
#define TIRE_DIAMETER	(48.0)					//�^�C���̒��a
#define TREAD_WIDTH	(72.6)					//�g���b�h��
#define TREAD_CIRCUIT	(TREAD_WIDTH*PI/4)			//���M�n����̎��Ƀ^�C������������

//�Z���T�֘A�p�����[�^
#define WAITLOOP_SLED 300					//LED�����点�Ă���AD�ϊ����J�n����܂ł̎��ԉ҂��p�萔

#define REF_SEN_R	280					//�}�E�X����H�����ɒu�������̃Z���T�̒l
#define REF_SEN_L	415					//�}�E�X����H�����ɒu�������̃Z���T�̒l

/*#define TH_SEN_R	173					//�ǂ����邩�ۂ���臒l
#define TH_SEN_L	169					//�ǂ����邩�ۂ���臒l
#define TH_SEN_FR	145					//�ǂ����邩�ۂ���臒l
#define TH_SEN_FL	134					//�ǂ����邩�ۂ���臒l*/

#define TH_SEN_R	103					//�ǂ����邩�ۂ���臒l
#define TH_SEN_L	100					//�ǂ����邩�ۂ���臒l
#define TH_SEN_FR	150					//�ǂ����邩�ۂ���臒l
#define TH_SEN_FL	130					//�ǂ����邩�ۂ���臒l

#define CONTH_SEN_R	TH_SEN_R				//����������邩�ۂ���臒l
#define CONTH_SEN_L	TH_SEN_L				//����������邩�ۂ���臒l
//#define CON_WALL_KP	(0.5)					//�ǃZ���T�ɂ��p������̔�ᐧ��̔��萔
#define CON_WALL_KP	(0.5)

//���s�p�����[�^
#define SEARCH_SPEED	(400)					//�T���̑��x
#define SEARCH_ACCEL	(1.0)					//�T���̉����x

#define TURN_ACCEL		(0.5)				//���M�n����̉����x

//���H�֘A�p�����[�^
#define GOAL_X	9		//�S�[�����W(x)
#define GOAL_Y	9		//�S�[�����W(y)

#define _PARAMETER

#endif
