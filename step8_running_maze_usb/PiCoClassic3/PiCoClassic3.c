/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c or Main.cpp                                    */
/*  DATE        :Tue, Oct 31, 2006                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
//#include "typedefine.h"

#include "iodefine.h"
#include "portdef.h"
#include "macro.h"
#include "mytypedef.h"
#include "parameters.h"
#include "init.h"
#include "glob_var.h"
#include "run.h"

#ifdef __cplusplus
//#include <ios>                        // Remove the comment when you use ios
//_SINT ios_base::Init::init_cnt;       // Remove the comment when you use ios
#endif

void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif


void exec_by_mode(int mode);

extern void init_all(void);
extern void wait_ms(int wtime);
extern void search_lefthand(void);
extern void search_adachi(int gx, int gy);
extern void goal_appeal(void);
extern void fast_run(int x, int y);
extern void adjust_menu(void);
extern void USB_CHECK(void);

void _LED(int led_data)
{
	LED0 = led_data&0x01;
	LED1 = (led_data>>1)&0x01;
	LED2 = (led_data>>2)&0x01;
	LED3 = (led_data>>3)&0x01;
}


void main(void)
{
	int mode;
	
	init_all();			//������

	DISABLE_BUZZER;			//�u�U�[���~�߂�

	mode = 1;

	while(1)	//���[�h�I���X�C�b�`
	{
		MOT_POWER_OFF;		

		wait_ms(CHATTERING_WAIT*3);		//�`���^�����O�h�~�̑҂�����
		DISABLE_BUZZER;				//�u�U�[���~�߂�

		while( !(SW_L & SW_C & SW_R) );	//�X�C�b�`���������܂ő҂�

		wait_ms(CHATTERING_WAIT);		//�`���^�����O�h�~�̑҂�����

		_LED(mode);				//���݂̃��[�h���ԑ̑O���̂k�d�c�ɕ\������

		while( (SW_L & SW_C & SW_R))		//���ꂩ�̃X�C�b�`���������܂ő҂�
		{
			USB_CHECK();
		}		
	
							//�ȍ~�ŁA�ǂ̃X�C�b�`�������ꂽ�����f

		if(SW_L == SW_ON)			//���X�C�b�`��������Ă����玟�̃��[�h�ɐi��
		{
			mode++;
			if(mode > 15)			//���[�h��15�Ԃ܂łȂ̂ŁA����𒴂��Ȃ��悤�ɂ���
			{
				mode = 1;
			}else{
				SET_BUZZER_FREQ(INC_FREQ);	//�l�������������̎��g����ݒ�				
				ENABLE_BUZZER;			//�u�U�[�𔭐U������
			}
		}
		else if(SW_R == SW_ON)	//�E�X�C�b�`��������Ă�����O�̃��[�h�ɖ߂�
		{
			mode--;
			if(mode < 1)	//���[�h��1�Ԃ���Ȃ̂ŁA����ȉ��ɂȂ�Ȃ��悤�ɂ���
			{
				mode = 15;
			}else{
				SET_BUZZER_FREQ(DEC_FREQ);	//�l�������������̎��g��������
				ENABLE_BUZZER;			//�u�U�[�𔭐U������
			}
		}
		else if(SW_C == SW_ON)	//�����X�C�b�`��������Ă�����A���݂̃��[�h�����s����
		{
			SET_BUZZER_FREQ(DEC_FREQ);		//����X�C�b�`�������ꂽ�Ƃ��̉���炷
			ENABLE_BUZZER;				//�u�U�[�𔭐U������
			wait_ms(80);				//�K���ȑ҂�����
			SET_BUZZER_FREQ(INC_FREQ);		//��(���g��)��ύX����
			wait_ms(80);				//�K���ȑ҂�����
			DISABLE_BUZZER;				//�u�U�[�̔��U���~������
			exec_by_mode(mode);			//���݂̃��[�h�����s����
		}
	}
}

void exec_by_mode(int mode)	//���[�h�ԍ��ɏ]���Ď��s����
{
	MOT_POWER_ON;
	wait_ms(1000);
	
	switch(mode)
	{
		case 1:		//����@
			search_lefthand();
			break;
			
		case 2:		//�����@�ōs���ċA���Ă���
			mypos.x = mypos.y = 0;			//���W��������
			mypos.dir = north;			//���p��������
			search_adachi(GOAL_X,GOAL_Y);		//�S�[���܂ő����@
			rotate(right,2);			//�S�[��������180�x��]����
			mypos.dir = (mypos.dir+6) % 4;		//���p���X�V
			goal_appeal();				//�S�[���������Ƃ��A�s�[��
			search_adachi(0,0);			//�X�^�[�g�n�_�܂ő����@�ŋA���Ă���
			rotate(right,2);			//�A���Ă�����180�x��]
			break;
		
		case 3:		//�ŒZ���s
			mypos.x = mypos.y = 0;			//���W��������
			mypos.dir = north;			//���p��������
			accel = 1.5;				//�����x��ݒ�
			fast_run(GOAL_X,GOAL_Y);		//�S�[���܂ōŒZ���s
			mypos.dir = (mypos.dir+6) % 4;		//���p���X�V
			rotate(right,2);			//�S�[��������180�x��]
			goal_appeal();				//�S�[���������Ƃ��A�s�[��
			fast_run(0,0);				//�X�^�[�g�n�_�܂ōŒZ���s
			rotate(right,2);			//�A���Ă�����180�x��]
			break;
			
			//�ȉ����[�h15�ȊO�͋󂫁B�����ł��낢�����Ă݂Ă��������B
			
		case 4:
			break;
			
		case 5:
			break;
			
		case 6:
			break;
			
		case 7:
			break;
			
		case 8:
			break;
			
		case 9:
			break;
			
		case 10:
			break;
			
		case 11:
			break;
			
		case 12:
			break;
			
		case 13:
			break;
			
		case 14:
			break;
			
		case 15:
			adjust_menu();	//�������j���[�ɍs��
			break;
					
	}
	
	MOT_POWER_OFF;
}

#ifdef __cplusplus
void abort(void)
{

}
#endif
