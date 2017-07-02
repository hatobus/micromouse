

#ifdef PORTDEF
	
#else

#define PORTDEF

#define BUZZER	(PORTB.PODR.BIT.B3)

#define LED0	(PORTB.PODR.BIT.B0)
#define LED1	(PORTA.PODR.BIT.B6)
#define LED2	(PORTA.PODR.BIT.B4)
#define LED3	(PORTA.PODR.BIT.B0)

#define SW_R	(PORTC.PIDR.BIT.B2)
#define SW_C	(PORTC.PIDR.BIT.B3)
#define SW_L	(PORT3.PIDR.BIT.B1)

#define SLED_L	(PORT5.PODR.BIT.B4)		//���Z���TLED
#define SLED_R	(PORT0.PODR.BIT.B5)		//�E�Z���TLED
#define SLED_FL	(PORT2.PODR.BIT.B7)		//���O�Z���TLED
#define SLED_FR	(PORTB.PODR.BIT.B5)		//�E�O�Z���TLED

#define MOT_POWER	(PORT1.PODR.BIT.B5)
#define MOT_POWER_ON	MOT_POWER = 1		// �X�e�b�s���O���[�^��㎥
#define MOT_POWER_OFF	MOT_POWER = 0		// �X�e�b�s���O���[�^��E��


#define MOT_CWCCW_R	(PORTC.PODR.BIT.B5)
#define MOT_CWCCW_L	(PORTC.PODR.BIT.B6)

#define BLED0	(PORTB.PODR.BIT.B1)		//�o�b�e���d���\��LED ��
#define BLED1	(PORTA.PODR.BIT.B3)		//�o�b�e���d���\��LED ��

#endif
