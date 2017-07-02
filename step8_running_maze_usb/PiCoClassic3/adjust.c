#include "iodefine.h"
#include "mytypedef.h"
#include "portdef.h"
#include "parameters.h"
#include "macro.h"
#include "glob_var.h"
#include "run.h"

int exec_by_mode_adjust(int mode);

extern void _LED(int led_data);
extern void wait_ms(int wtime);
extern void USB_PRINTF(char *format, ...);


void view_adc(void)		//AD�R���o�[�^�̒l������
{
	unsigned int i;
	
	MOT_POWER_OFF;		// �X�e�b�s���O���[�^��㎥����
	
	
	while(1)
	{
		USB_PRINTF("r_sen  is\t%d\r\n",(sen_r.value));	//�E�Z���T�̒l
		USB_PRINTF("fr_sen is\t%d\r\n",(sen_fr.value));	//�E�O�Z���T�̒l
		USB_PRINTF("fl_sen is\t%d\r\n",(sen_fl.value));	//���O�Z���T�̒l
		USB_PRINTF("l_sen  is\t%d\r\n",(sen_l.value));	//���Z���T�̒l
		USB_PRINTF("VDD    is\t%dmV\r\n",((10+51)/10*3300*S12AD.ADDR8/4095));//�d����\��
		
		for(i = 0; i < 0x3fffff; i++)	;		//�\���Ԋu��ݒ�
		
		//��ʃN���A�V�[�P���X
		USB_PRINTF("\x1b[2J");				//�N���A�X�N���[��[CLS]
		USB_PRINTF("\x1b[0;0H");			//�J�[�\����0,0�Ɉړ�
	}
}


void straight_check(int section_check)				//�^�C�����a�`�F�b�N�p
{
	max_speed = SEARCH_SPEED;				//�T���̑��x���w��
	accel = SEARCH_ACCEL;					//�����x���w��

	wait_ms(1000);
	straight(SECTION * section_check,0);			//section_check���i��
	
}


void go_and_turn_right(void)					//�^�C���g���b�h�a�`�F�b�N�p
{
	int kaisuu = 0;
	max_speed = SEARCH_SPEED;				//�T���̑��x���w��
	accel = SEARCH_ACCEL;					//�����x���w��

	wait_ms(1000);						//1�b�҂�
	
	while(kaisuu<1){
		//straight(SECTION*2,0);				//2���i��
		rotate(right,1);				//���̏��180�x�E�^�[��
		//straight(SECTION*2,0);				//2���i��	
		//rotate(right,2);				//���̏��180�x�E�^�[��
	}
}


void adjust_menu(void)	//�����p���j���[
{
	int mode = 1;				//���j���[�p�ϐ�
	

	while(1)				//���[�h�I��
	{

		wait_ms(CHATTERING_WAIT*3);	//�`���^�����O�h�~�̑҂�����
		DISABLE_BUZZER;
		while( !(SW_L & SW_C & SW_R) ) ;
		wait_ms(CHATTERING_WAIT);	//�`���^�����O�h�~�̑҂�����

		_LED(mode);			//���݂̃��[�h���ԑ̑O���̂k�d�c�ɕ\������
		
		while( SW_L & SW_C & SW_R )	//���ꂩ�̃X�C�b�`���������܂ő҂�
		{
			wait_ms(33);
			LED3 ^= 1;		//���](�`�J�`�J������)
			
		}
		LED3 = 0;
						//�ȍ~�ŁA�ǂ̃X�C�b�`�������ꂽ�����f

		if(SW_L == SW_ON)		//���X�C�b�`��������Ă����玟�̃��[�h�ɐi��
		{
			mode++;
			if(mode > 7)		//���[�h��15�Ԃ܂łȂ̂ŁA����𒴂��Ȃ��悤�ɂ���
			{
				mode = 7;
			}else{
				SET_BUZZER_FREQ(INC_FREQ);				
				ENABLE_BUZZER;
			}
		}
		else if(SW_R == SW_ON)		//�E�X�C�b�`��������Ă�����O�̃��[�h�ɖ߂�
		{
			mode--;
			if(mode < 1)		//���[�h��1�Ԃ���Ȃ̂ŁA����ȉ��ɂȂ�Ȃ��悤�ɂ���
			{
				mode = 1;
			}else{
				SET_BUZZER_FREQ(DEC_FREQ);//�u�U�[�̎��g��������
				ENABLE_BUZZER;		//�u�U�[�𔭐U������
			}
		}
		else if(SW_C == SW_ON)		//�����X�C�b�`��������Ă�����A���݂̃��[�h�����s����
		{
			SET_BUZZER_FREQ(DEC_FREQ);	//����X�C�b�`�������ꂽ�Ƃ��̉���炷
			ENABLE_BUZZER;			//�u�U�[�𔭐U������
			wait_ms(CHATTERING_WAIT*8);
			SET_BUZZER_FREQ(INC_FREQ);	//��(���g��)��ύX����
			wait_ms(CHATTERING_WAIT*8);
			DISABLE_BUZZER;			//�u�U�[�̔��U���~������
			if(exec_by_mode_adjust(mode) == 1)
			{
				return;			//���݂̃��[�h�����s����

			}
		}
	}
}



int exec_by_mode_adjust(int mode)
{
//����mode������A���̃��[�h�ɓ���B
//�߂�l��1�̏ꍇ�́A��{�̃��j���[�ɖ߂�

	switch(mode)
	{
		case 1:
			view_adc();		//A/D�ϊ��̌��ʂ�SCI1����o�͂���
			break;
			
		case 2:
			straight_check(9);  	 //9��撼���𑖂�
			break;
		
		case 3:
			go_and_turn_right();
			break;
			
		case 4:
			break;
			
		case 5:
			break;
			
		case 6:
			break;
			
		case 7:
			return 1;		//���[�h�V�͌��̃��j���[�ɖ߂�
			break;
	}
	
	return 0;
}
