//�O���[�o���ϐ�����ӏ��Ő錾����B
//glob_var.c�Ŏ��̂����(_GLOB_VAR��define)�A���̃O���[�o���ϐ����g�p����t�@�C�������glob_var.h��include����B

#include "mytypedef.h"
#include "parameters.h"

//global�ϐ����ꊇ�Ŏ��̂�extern�錾����B
//include����_GLOB_VAR����`����Ă���Ύ��̐錾�A��`����Ă��Ȃ���ΊO���錾�ƂȂ�B
#ifdef _GLOB_VAR
#define GLOBAL
#else
#define GLOBAL extern
#endif

GLOBAL t_sensor			sen_r, sen_l, sen_fr, sen_fl;		//�Z���T�\����
GLOBAL t_control		con_wall;				//����\����
GLOBAL unsigned int		step_r, step_l;				//�X�e�b�v��(���荞�ݓ��ŃJ�E���g�A�b�v)
GLOBAL float			accel;					//�����x(�ݒ�l�������Ȃ�)
GLOBAL float			r_accel;				//�����x(���ۂ̒l����������)
GLOBAL float			max_speed;				//�ō����x(�ݒ�l)
GLOBAL float			speed;					//���x(���݂̒l)
GLOBAL t_position		mypos;					//���ȍ��W
GLOBAL t_wall			wall[MAZESIZE_X][MAZESIZE_Y];		//�ǂ̏����i�[����\���̔z��
GLOBAL unsigned char		map[MAZESIZE_X][MAZESIZE_Y];		//�����}�b�v
GLOBAL unsigned int		timer;					//1mS���ƂɃJ�E���g�A�b�v�����ϐ�.
GLOBAL unsigned short		voltage;				//�d����AD�ϊ��l

