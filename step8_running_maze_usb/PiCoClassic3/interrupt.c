#include "iodefine.h"
#include "portdef.h"
#include "parameters.h"
#include "interrupt.h"
#include "static_parameters.h"
#include "macro.h"
#include "glob_var.h"


void int_cmt0(void)
{
	float spd_r, spd_l;		//�ŏI�I�ȑ��x
	
	battery_save(getBatteryVolt());	//�o�b�e���Ď�


	speed+=r_accel; 			//��������

	if(speed > max_speed)			//�ō����x�𐧌�
	{
		speed = max_speed;
	}
	
	if(speed < MIN_SPEED){			//�Œᑬ�x�𐧌�(MTU�̎����ݒ背�W�X�^�̒l���`0xffff�܂łł��邽��)
		speed = MIN_SPEED;
	}

		//�Z���T����
	if(con_wall.enable == true)		//�ǐ��䂪������Ă��邩�`�F�b�N
	{
		
		con_wall.p_error = con_wall.error;	//�ߋ��̕΍���ۑ�
		
		
		//���E�̃Z���T���A���ꂼ��g�����Ԃł��邩�ǂ����`�F�b�N���āA�p������̕΍����v�Z
		if( ( sen_r.is_control == true ) && ( sen_l.is_control == true ) )
		{									//�����Ƃ��L���������ꍇ�̕΍����v�Z
			con_wall.error = sen_r.error - sen_l.error;
		}
		else								//�Е��������͗����̃Z���T�������������ꍇ�̕΍����v�Z
		{
			con_wall.error = 2.0 * (sen_r.error - sen_l.error);	//�Е������g�p���Ȃ��̂�2�{����
		}
		
		
		//DI����v�Z
		con_wall.diff = con_wall.error - con_wall.p_error;	//�΍��̔����l���v�Z
		con_wall.sum += con_wall.error;				//�΍��̐ϕ��l���v�Z
		
		if(con_wall.sum > con_wall.sum_max)			//�΍��̐ϕ��l�̍ő�l�𐧌�
		{
			con_wall.sum = con_wall.sum_max;
		}
		else if(con_wall.sum < (-con_wall.sum_max))		//�΍��̐ϕ��l�̍Œ�l�𐧌�
		{
			con_wall.sum = -con_wall.sum_max;
		}
		
		con_wall.control = 0.001 * speed * con_wall.kp * con_wall.error;	//����ʂ��v�Z
		
		spd_r = speed + con_wall.control;					//��������E���[�^�̑��x���Ƃ����`�Ŕ��f
		spd_l = speed - con_wall.control;					//��������E���[�^�̑��x���Ƃ����`�Ŕ��f

	}else{
		spd_r = speed;
		spd_l = speed;
	}	
	

	MTU3.TGRC = SPEED2GREG(spd_r);	//�E���x(mm/s)����W�F�l�������W�X�^�̒l�ɕϊ����āA�o�b�t�@���W�X�^�ɑ��
	MTU4.TGRC = SPEED2GREG(spd_l);	//�����x(mm/s)����W�F�l�������W�X�^�̒l�ɕϊ����āA�o�b�t�@���W�X�^�ɑ��

	timer++;						//1mS���ƂɃJ�E���g�A�b�v
}		

void int_cmt1(void)		//�Z���T�ǂݍ��ݗp�荞��
{
	static int state = 0;	//�ǂݍ��ރZ���T�̃��[�e�[�V�����Ǘ��p�ϐ�
	int i;
	
	switch(state)
	{
		case 0:		//�E�Z���T�ǂݍ���

			SLED_R = 1;					//LED�_��
			for(i = 0; i < WAITLOOP_SLED; i++)	;	//�t�H�g�g�����W�X�^�̉����҂����[�v
			S12AD.ADANS0.BIT.ANS0=0x0040;			//AN006
			S12AD.ADCSR.BIT.ADST=1;				//AD�ϊ��J�n
			while(S12AD.ADCSR.BIT.ADST);			//AD�ϊ��I���܂ő҂�
			SLED_R = 0;					//LED����

			sen_r.p_value = sen_r.value;			//�ߋ��̒l��ۑ�
			sen_r.value = S12AD.ADDR6;			//�l��ۑ�

			if(sen_r.value > sen_r.th_wall)			//�ǂ̗L���𔻒f
			{
				sen_r.is_wall = true;			//�E�ǂ���
			}
			else
			{
				sen_r.is_wall = false;			//�E�ǂȂ�
			}
			
			if(sen_r.value > sen_r.th_control)		//����������邩�ۂ��𔻒f
			{
				sen_r.error = sen_r.value - sen_r.ref;	//�����������ꍇ�͕΍����v�Z
				sen_r.is_control = true;		//�E�Z���T�𐧌�Ɏg��
			}
			else
			{
				sen_r.error = 0;			//����Ɏg��Ȃ��ꍇ�͕΍���0�ɂ��Ă���
				sen_r.is_control = false;		//�E�Z���T�𐧌�Ɏg��Ȃ�
			}			
			break;


		case 1:		//�O���Z���T�ǂݍ���

			SLED_FL = 1;					//LED�_��
			for(i = 0; i < WAITLOOP_SLED; i++);		//�t�H�g�g�����W�X�^�̉����҂����[�v
			S12AD.ADANS0.BIT.ANS0=0x0010;			//AN004
			S12AD.ADCSR.BIT.ADST=1;				//AD�ϊ��J�n
			while(S12AD.ADCSR.BIT.ADST);			//AD�ϊ��I���܂ő҂�
			SLED_FL = 0;					//LED����

			sen_fl.p_value = sen_fl.value;			//�ߋ��̒l��ۑ�
			sen_fl.value = S12AD.ADDR4;			//�l��ۑ�

			if(sen_fl.value > sen_fl.th_wall)		//�ǂ̗L���𔻒f
			{
				sen_fl.is_wall = true;			//���O�ǂ���
			}
			else
			{
				sen_fl.is_wall = false;			//���O�ǂȂ�
			}
			break;


		case 2:		//�O�E�Z���T�ǂݍ���
		
			SLED_FR = 1;					//LED�_��
			for(i = 0; i < WAITLOOP_SLED; i++);		//�t�H�g�g�����W�X�^�̉����҂����[�v
			S12AD.ADANS0.BIT.ANS0=0x0200;			//AN009
			S12AD.ADCSR.BIT.ADST=1;				//AD�ϊ��J�n
			while(S12AD.ADCSR.BIT.ADST);			//AD�ϊ��I���܂ő҂�
			SLED_FR = 0;					//LED����

			sen_fr.p_value = sen_fr.value;			//�ߋ��̒l��ۑ�
			sen_fr.value = S12AD.ADDR9;			//�l��ۑ�

			if(sen_fr.value > sen_fr.th_wall)		//�ǂ̗L���𔻒f
			{
				sen_fr.is_wall = true;			//�E�O�ǂ���
			}
			else
			{
				sen_fr.is_wall = false;			//�E�O�ǂȂ�
			}			
			break;


		case 3:		//���Z���T�ǂݍ���
		
			SLED_L = 1;					//LED�_��
			for(i = 0; i < WAITLOOP_SLED; i++)	;	//�t�H�g�g�����W�X�^�̉����҂����[�v
			S12AD.ADANS0.BIT.ANS0=0x0004;			//AN002
			S12AD.ADCSR.BIT.ADST=1;				//AD�ϊ��J�n
			while(S12AD.ADCSR.BIT.ADST);			//AD�ϊ��I���܂ő҂�
			SLED_L = 0;					//LED����

			sen_l.p_value = sen_l.value;			//�ߋ��̒l��ۑ�
			sen_l.value = S12AD.ADDR2;			//�l��ۑ�
			
			if(sen_l.value > sen_l.th_wall)			//�ǂ̗L���𔻒f
			{
				sen_l.is_wall = true;			//���ǂ���
			}
			else
			{
				sen_l.is_wall = false;			//���ǂȂ�
			}
			
			if(sen_l.value > sen_l.th_control)		//����������邩�ۂ��𔻒f
			{
				sen_l.error = sen_l.value - sen_l.ref;	//�����������ꍇ�͕΍����v�Z����
				sen_l.is_control = true;		//���Z���T�𐧌�Ɏg��
			}
			else
			{
				sen_l.error = 0;			//����Ɏg��Ȃ��ꍇ�͕΍���0�ɂ��Ă���
				sen_l.is_control = false;		//���Z���T�𐧌�Ɏg��Ȃ�
			}

			break;
	}
	
	state++;		//�S�񂲂ƂɌJ��Ԃ�
	if(state > 3)
	{
		state = 0;
	}
		
}

void int_mot_r(void)	//�E���[�^���P�X�e�b�v�i�ޖ��̊��荞��
{
	step_r++;				//�X�e�b�v�����J�E���g
}



void int_mot_l(void)	//�����[�^���P�X�e�b�v�i�ޖ��̊��荞��
{
	step_l++;				//�X�e�b�v�����J�E���g
}

unsigned short getBatteryVolt(void)
{
	S12AD.ADANS0.BIT.ANS0=0x0100;			//AN008
	S12AD.ADCSR.BIT.ADST=1;				//AD�ϊ��J�n
	while(S12AD.ADCSR.BIT.ADST);			//AD�ϊ��I���܂ő҂�
	return S12AD.ADDR8;
}

void battery_save(unsigned short v_value)
{
	static int bled_cnt = 0;	//�o�b�e���d���Ď��pLED��PWM�p�ϐ�
	
	//�o�b�e���d���\��
	bled_cnt++;


	if(bled_cnt > 10){
		bled_cnt= 0;
	}
	
	if( (10.0 * (v_value - BATT_MIN) / (BATT_MAX - BATT_MIN)) > bled_cnt ){
		BLED0 = 1;
		BLED1 = 0;
	}else{
		BLED0 = 0;
		BLED1 = 1;
	}
	
	if(v_value < BATT_MIN){
		SET_BUZZER_FREQ(400);	//�l�������������̎��g����ݒ�				
		ENABLE_BUZZER;		//�u�U�[�𔭐U����
		MOT_POWER_OFF;		//���[�^���~����
		LED0 = LED1 = LED2 = LED3 = SLED_L = SLED_FL = SLED_FR = SLED_R = 0;	//LED���~����
	}
}

