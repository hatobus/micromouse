
#include "run.h"
#include "glob_var.h"

extern void wait_ms(int wtime);

void straight(int len, int tar_speed)	//�������s
{
	int obj_step;			//�ڕW�X�e�b�v��

	r_accel = accel;		//�����x
	step_r = step_l = 0;		//�X�e�b�v���J�E���g�̃��Z�b�g
	
	con_wall.enable = true;		//�ǐ����L���ɂ���

	obj_step = LEN2STEP(len);	//�ڕW�X�e�b�v�����Z�o

	MOT_CWCCW_R = MOT_CWCCW_L = MOT_FORWARD;		//�O���ɐi��

	MTU.TSTR.BIT.CST3 = MTU.TSTR.BIT.CST4 = 1;	//�J�E���g�X�^�[�g
	
	
	//�ڕW���x���Œᑬ�x�������Ȃ��悤�ɂ���
	if(tar_speed < MIN_SPEED)
	{
		tar_speed = MIN_SPEED;
	}
	
	//�������J�n���n�߂�Ƃ���܂ő҂�(���Ƒ���ׂ���������������ׂ��������Z���Ȃ�����E�E�E)
	while( (len - STEP2LEN(step_r + step_l) ) > ( ( (tar_speed*tar_speed) - (speed*speed) ) / (-2*1000*accel) ));

	r_accel = -accel;	//��������
	
	while((step_r + step_l) < obj_step)	;	//�ڕW�n�_�܂ő��s
	
	MTU.TSTR.BIT.CST3 = 0;				//���[�^�̃J�E���g���X�g�b�v
	MTU.TSTR.BIT.CST4 = 0;				//���[�^�̃J�E���g���X�g�b�v
	
}



void straight_for_search(int len, int tar_speed)	//�������s�A�T���p�Ƀ��Z�b�g�͊O���ɔC����
{
	//���s����len[mm] �� �ڕW���xtar_speed[mm/s] ���w�肷��B
	//�ō����x�͕ϐ�max_speed�ɗ\�ߑ�����邱��
	
	int obj_step;						//�ڕW�X�e�b�v��

	r_accel = accel;					//�����x

	con_wall.enable = true;					//�ǐ����L���ɂ���
	
	obj_step = LEN2STEP(len);				//�ڕW�X�e�b�v�����Z�o

	MOT_CWCCW_R = MOT_CWCCW_L = MOT_FORWARD;		//�O���ɐi��

	MTU.TSTR.BIT.CST3 = MTU.TSTR.BIT.CST4 = 1;		//�J�E���g�X�^�[�g
	
	
	//�ڕW���x���Œᑬ�x�������Ȃ��悤�ɂ���
	if(tar_speed < MIN_SPEED)
	{
		tar_speed = MIN_SPEED;
	}
	
	//�������J�n���n�߂�Ƃ���܂ő҂�(���Ƒ���ׂ���������������ׂ��������Z���Ȃ�����E�E�E)
	while( (len - STEP2LEN(step_r + step_l) ) > ( ( (tar_speed*tar_speed) - (speed*speed) ) / (-2*1000*accel) ));

	r_accel = -accel;					//��������
	
	while((step_r + step_l) < obj_step);			//�ڕW�n�_�܂ő��s
	
	MTU.TSTR.BIT.CST3 = 0;					//���[�^�̃J�E���g���X�g�b�v
	MTU.TSTR.BIT.CST4 = 0;					//���[�^�̃J�E���g���X�g�b�v
	
}



void rotate(t_local_dir dir, int times){			//���M�n����
//����dir[right or left]�����ɁA90�x�~times�x��]����

	int obj_step;						//�ڕW�X�e�b�v
	int tar_speed = MIN_SPEED;				//�ڕW���x(�Œ�)
	
	con_wall.enable = false;				//���M�n���񒆂͐����؂�
	
	switch(dir)						//�E�܂�肩���܂�肩�ŁA���[�^��CWCCW��؂�ւ���
	{
		case front:
		case rear:
			return;					//���M�n����Ȃ̂ŁA�O����͖���.

		case right:					//�E�ɉ��悤�ɐݒ�
			MOT_CWCCW_R = MOT_BACK;
			MOT_CWCCW_L = MOT_FORWARD;
			break;

		case left:					//���ɉ��悤�ɐݒ�
			MOT_CWCCW_R = MOT_FORWARD;
			MOT_CWCCW_L = MOT_BACK;
			break;
	}


	//�Œᑬ�x��ݒ�
	if(tar_speed < MIN_SPEED)
	{
		tar_speed = MIN_SPEED;
	}

	r_accel = TURN_ACCEL;					//��]�̉����x������
	speed = MIN_SPEED;					//���x�����Z�b�g
	step_r = step_l = 0;					//�X�e�b�v�������Z�b�g
	
	obj_step = LEN2STEP(times*TREAD_CIRCUIT);		//�ڕW�X�e�b�v���Z�o

	wait_ms(250);						//�����Ȃ���Ǝp���������̂ŁA�����ҋ@

	MTU.TSTR.BIT.CST3 = MTU.TSTR.BIT.CST4 = 1;		//�J�E���g�X�^�[�g
	
	//�����J�n���ׂ��ʒu�ɒB����܂ő҂�
	while( ((times*TREAD_CIRCUIT) - STEP2LEN(step_r + step_l) ) > ( ( (tar_speed*tar_speed) - (speed*speed) ) / (-2*1000*TURN_ACCEL) ));
	r_accel = -TURN_ACCEL;	//�����J�n
	
	//��~����ʒu�ɒB����܂ő҂�
	while((step_r + step_l) < obj_step)	;
	
	
	//���[�^��~
	MTU.TSTR.BIT.CST3 = 0;					//���[�^�̃J�E���g���X�g�b�v
	MTU.TSTR.BIT.CST4 = 0;					//���[�^�̃J�E���g���X�g�b�v


	//�^�[���㏭���҂�
	wait_ms(250);
	
	//�X�s�[�h���Œᑬ�x�ɒ���
	speed = MIN_SPEED;
	
}