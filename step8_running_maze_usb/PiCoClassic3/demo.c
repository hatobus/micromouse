#include "iodefine.h"

extern void _LED(int led_data);
extern void wait_ms(int wtime);

void goal_appeal(void)				//�S�[���������Ƃ��A�s�[������
{
	int i,j,led,wtime;
	
	wtime = 100;				//�����̑҂�����
	
	for(j = 0; j < 10; j++)			//10��J��Ԃ�
	{
		led = 1;			//LED�_���f�[�^�̏�����
		for(i = 0; i < 4; i++)
		{
			_LED(led);		//LED�_���f�[�^����������
			led = led << 1;		//LED�_���f�[�^���X�V
			wait_ms(wtime);		//�҂�����
		}
		led = 8;			//LED�_���f�[�^��������
		for(i = 0; i < 4; i++)
		{
			_LED(led);		//LED�_���f�[�^����������
			led = led >> 1;		//LED�_���f�[�^���X�V
			wait_ms(wtime);		//�҂�����
		}
		wtime -= 5;			//�҂����Ԃ��X�V
	}
	
	wait_ms(500);				//�_�ł��I�������A0.5�b�҂�
	
}
