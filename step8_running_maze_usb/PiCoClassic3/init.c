
#include "init.h"
#include "glob_var.h"
//#include "sci.h"

extern void init_usb(void);
extern void wait_ms(int wtime); 

void init_clock(void)
{

	SYSTEM.PRCR.WORD = 0xa50b;		//�N���b�N�\�[�X�I���̕ی�̉���

	SYSTEM.PLLCR.WORD = 0x0F00;		/* PLL ���{�~16 ����1���� (12.000MHz * 16 = 192MHz)*/
	SYSTEM.PLLCR2.BYTE = 0x00;		/* PLL ENABLE */
	
	SYSTEM.PLLWTCR.BYTE     = 0x0F;		/* 4194304cycle(Default) */
	
	
	// ICK   : 192/2 = 96MHz 		// �V�X�e���N���b�N CPU DMAC DTC ROM RAM
	// PCLKA : 192/2 = 96MHz 		// ���Ӄ��W���[���N���b�NA ETHERC�AEDMAC�ADEU
	// PCLKB : 192/4 = 48MHz 		// ���Ӄ��W���[���N���b�NB ��L�ȊO PCLKB=PCLK
/*	
	SYSTEM.SCKCR.BIT.FCK=0x02;		//FCLK MAX 50MHz  192/4
	SYSTEM.SCKCR.BIT.ICK=0x01;		//ICLK MAX 100MHz 192/2
	SYSTEM.SCKCR.BIT.PSTOP1=0x01;		//BCLK �o�͒�~
	SYSTEM.SCKCR.BIT.PSTOP0=0x01;		//SDCLK �o�͒�~
	SYSTEM.SCKCR.BIT.BCK=0x02;		//BCLK MAX 100MHz ICLK�ȉ��ɂ���K�v������192/4
	SYSTEM.SCKCR.BIT.PCKA=0x01;		//PCLKA MAX 100MHz 192/2
	SYSTEM.SCKCR.BIT.PCKB=0x02;		//PCLKB MAX 50MHz 192/4
	//��L�̐ݒ�ł͐�����clock�ݒ肪�ł��Ȃ����߉��L�̂悤�Ɉꊇ�Őݒ肷�邱��
*/
	SYSTEM.SCKCR.LONG = 0x21C21211;		//FCK1/4 ICK1/2 BCLK��~ SDCLK��~ BCK1/4 PCLKA1/2 PCLKB1/4
/*
	SYSTEM.SCKCR2.BIT.UCK=0x03;		//UCLK MAX 48MHz 192/4
	SYSTEM.SCKCR2.BIT.IEBCK=0x02;		//IECLK MAX 50MHz 192/4
*/
	SYSTEM.SCKCR2.WORD = 0x0032;		/* UCLK1/4 IEBCK1/4 */
	SYSTEM.BCKCR.BYTE = 0x01;		/* BCLK = 1/2 */
	
	SYSTEM.SCKCR3.WORD = 0x0400;		//PLL��H�I��

}

void init_io(void)
{
	//LED
	PORTB.PDR.BIT.B0 = IO_OUT;//LED0
	PORTA.PDR.BIT.B6 = IO_OUT;//LED1
	PORTA.PDR.BIT.B4 = IO_OUT;//LED2
	PORTA.PDR.BIT.B0 = IO_OUT;//LED3
	PORTB.PDR.BIT.B1 = IO_OUT;//BLED0
	PORTA.PDR.BIT.B3 = IO_OUT;//BLED1
	//Sensor
	PORT5.PDR.BIT.B4 = IO_OUT;//SLED_L
	PORT0.PDR.BIT.B5 = IO_OUT;//SLED_R
	PORT2.PDR.BIT.B7 = IO_OUT;//SLED_FL
	PORTB.PDR.BIT.B5 = IO_OUT;//SLED_FR
	//MOT_POWER
	PORT1.PDR.BIT.B5 = IO_OUT;//motor Enable
	//MOT_CWCCW
	PORTC.PDR.BIT.B5 = IO_OUT;//Rmotor
	PORTC.PDR.BIT.B6 = IO_OUT;//Lmotor
	
	//Buzzer�̃|�[�g�̏�����
	PORTB.PDR.BIT.B3 = IO_OUT;
	BUZZER = 1;	
	

	MPC.PWPR.BIT.B0WI=0;
	MPC.PWPR.BIT.PFSWE=1;
	MPC.PB3PFS.BIT.PSEL=1;	//MTIOC0A
	MPC.P17PFS.BIT.PSEL=1;	//MTIOC3A�Ƃ��Ďg�p
	MPC.PE2PFS.BIT.PSEL=1;	//MTIOC4A

	MPC.PE0PFS.BIT.ASEL=1;	//A/D �d��
	MPC.PE1PFS.BIT.ASEL=1;	//A/D SEN_FR
	MPC.P44PFS.BIT.ASEL=1;	//A/D SEN_FL
	MPC.P46PFS.BIT.ASEL=1;	//A/D SEN_R
	MPC.P42PFS.BIT.ASEL=1;	//A/D SEN_L
	MPC.PWPR.BYTE=0x80;
	
	PORTB.PMR.BIT.B3=1;	//SP PWM
	PORT1.PMR.BIT.B7=1;	//�EPWM
	PORTE.PMR.BIT.B2=1;	//��PWM
	
	PORTE.PMR.BIT.B0=1;	//A/D
	PORTE.PMR.BIT.B1=1;	//A/D
	PORT4.PMR.BIT.B4=1;	//A/D
	PORT4.PMR.BIT.B6=1;	//A/D
	PORT4.PMR.BIT.B2=1;	//A/D
}

void init_cmt(void)
{
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP(CMT0) = 0;
	MSTP(CMT1) = 0;
    	SYSTEM.PRCR.WORD = 0xA500;	
	
	//CMT0�͐��䊄�荞�ݗp�^�C�}�Ƃ��Ďg�p
	CMT0.CMCR.BIT.CKS=1;	// PCLK/32 1.5MHz
	CMT0.CMCR.BIT.CMIE=1;	//���荞�݂�����
	CMT0.CMCNT=0;		//�J�E���^�[�̃N���A
	CMT0.CMCOR=1500-1;	//1kHz

	IEN(CMT0,CMI0) = 1;	//���荞�ݗv�������� 
	IPR(CMT0,CMI0) = 15;	//���荞�ݗD��x 15���ō�
	IR(CMT0,CMI0)=0;	//���荞�݃X�e�[�^�t���O���N���A
	
	//CMT1�̓Z���T�[����p�^�C�}�Ƃ��Ďg�p
	CMT1.CMCR.BIT.CKS=1;	// PCLK/32 1.5MHz
	CMT1.CMCR.BIT.CMIE=1;	//���荞�݂�����
	CMT1.CMCNT=0;		//�J�E���^�[�̃N���A
	CMT1.CMCOR=(1500/4)-1;	//4kHz

	IEN(CMT1,CMI1) = 1;	//���荞�ݗv�������� 
	IPR(CMT1,CMI1) = 14;	//���荞�ݗD��x�����_�ɐݒ�
	IR(CMT1,CMI1)=0;	//���荞�݃X�e�[�^�t���O���N���A

	CMT.CMSTR0.BIT.STR0=1;	//�J�E���g�X�^�[�g
	CMT.CMSTR0.BIT.STR1=1;	//�J�E���g�X�^�[�g
	
}


void init_mtu(void)
{
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP(MTU) = 0;		//MTU���W���[��ON
    	SYSTEM.PRCR.WORD = 0xA500;	
	
	MTU.TSTR.BYTE=0;	//�^�C�}����X�g�b�v
	
	//�X�s�[�J�[�pMTU
	MTU0.TCR.BIT.CCLR=2;	//PWM TGRB�̃R���y�A�}�b�`��TCNT�N���A 
	MTU0.TCR.BIT.TPSC=1;	//PCLK/4 12MHz
	MTU0.TMDR.BIT.MD=2;	//PWM1
	MTU0.TIORH.BIT.IOA=5;	//�R���x�A�}�b�`��low������high
	MTU0.TIORH.BIT.IOB=2;	//�R���x�A�}�b�`��high
	MTU0.TGRA = 6000;	//1kHz
	MTU0.TGRB = (12000-1);
		
	//�E���[�^�pMTU�ݒ�
	MTU3.TCR.BIT.TPSC=2;	//PCLK/16 3MHz

	MTU3.TCR.BIT.CCLR=1;	//PWM TGRA�̃R���y�A�}�b�`��TCNT�N���A
	MTU3.TIORH.BIT.IOA=1;	//�����o��0���y�A�}�b�`0�o��
	MTU3.TIORH.BIT.IOB=2;	//�����o��0�R���y�A�}�b�`1�o��
	MTU3.TGRA = 12000;
	MTU3.TGRB = 50;
	MTU3.TGRC = 48000;
	MTU3.TMDR.BIT.MD=2;	//PWM1
	MTU3.TMDR.BIT.BFA = 1;	//�o�b�t�@�[���[�h�ɐݒ�
	MTU3.TIER.BIT.TGIEB = 1;//GRB�R���y�A�}�b�`�ł̊��荞�݋���
	IEN(MTU3,TGIB3) = 1;	//���荞�ݗv�������� 
	IPR(MTU3,TGIB3) = 13;	//���荞�ݗD��x�����_�ɐݒ�
	IR(MTU3,TGIB3)=0;	//���荞�݃X�e�[�^�t���O���N���A
	
	
	//�����[�^�pMTU�ݒ�
	MTU.TOER.BIT.OE4A=1;	//MTU�o�͒[�q���o�͋�����
	MTU4.TCR.BIT.TPSC=2;	//PCLK/16 3MHz

	MTU4.TCR.BIT.CCLR=1;	//PWM TGRA�̃R���y�A�}�b�`��TCNT�N���A
	MTU4.TIORH.BIT.IOA=1;	//�����o��0���y�A�}�b�`0�o��
	MTU4.TIORH.BIT.IOB=2;	//�����o��0�R���y�A�}�b�`1�o��
	MTU4.TGRA = 12000;
	MTU4.TGRB = 50;
	MTU4.TGRC = 48000;
	MTU4.TMDR.BIT.MD=2;	//PWM1
	MTU4.TMDR.BIT.BFA = 1;	//�o�b�t�@�[���[�h�ɐݒ�
	MTU4.TIER.BIT.TGIEB = 1;//GRB�R���y�A�}�b�`�ł̊��荞�݋���
	IEN(MTU4,TGIB4) = 1;	//���荞�ݗv�������� 
	IPR(MTU4,TGIB4) = 12;	//���荞�ݗD��x�����_�ɐݒ�
	IR(MTU4,TGIB4)=0;	//���荞�݃X�e�[�^�t���O���N���A


	MTU.TSTR.BIT.CST0 = 0;	//�^�C�}�X�g�b�v
	MTU.TSTR.BIT.CST3 = 0;	//�^�C�}�X�g�b�v
	MTU.TSTR.BIT.CST4 = 0;	//�^�C�}�X�g�b�v
}

void init_adc(void)
{
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP(S12AD) = 0;
    	SYSTEM.PRCR.WORD = 0xA500;	
	
	S12AD.ADCER.BIT.ADRFMT=0;//�E�Â�
	S12AD.ADCSR.BIT.CKS=0x03;//PCLK�̕����Ȃ�
//	S12AD.ADSSTR01.BIT.SST1=20;//Default 20�X�e�[�g 0.417us 0.4us�ȏオ����
}
void init_sci(void){
	SYSTEM.PRCR.WORD = 0xA502;
        MSTP(SCI1) = 0;
	SYSTEM.PRCR.WORD = 0xA500;

	SCI1.SCR.BYTE = 0x00;
	while (0x00 != (SCI1.SCR.BYTE & 0xF0));	//���荞�ݗv�����֎~�����܂ő҂�
	PORT2.PODR.BIT.B6 = 1;			//TXD��Dirction�̐؂�ւ���̒l��high
    	PORT2.PDR.BIT.B6 = 1;			//�o�͂ɐݒ�
    	PORT3.PDR.BIT.B0 = 0;			//���͂ɐݒ�
	PORT2.PMR.BIT.B6 = 0;			//�ėp�|�[�g�ɐݒ�
    	PORT3.PMR.BIT.B0 = 0;			//�ėp�|�[�g�ɐݒ�
    	MPC.PWPR.BIT.B0WI  = 0;
    	MPC.PWPR.BIT.PFSWE = 1;
    	MPC.P26PFS.BIT.PSEL = 0x0A;		//TXD1
    	MPC.P30PFS.BIT.PSEL = 0x0A;		//RXD1
    	MPC.PWPR.BIT.PFSWE = 0;
    	MPC.PWPR.BIT.B0WI  = 1;
    	PORT3.PMR.BIT.B0 = 1;			//���Ӌ@�\(RXD1)�Ƃ��Ďg�p
        SCI1.SCR.BIT.CKE = 0;
    	SCI1.SMR.BYTE = 0x00;			//1stopbit parity�Ȃ��@8bit ��������
        SCI1.SCMR.BYTE = 0xF2;			//S=32clock
    	SCI1.SEMR.BYTE = 0x00;
    	SCI1.BRR =38; 				//@48MHz 38400bps
    	SCI1.SCR.BYTE =0x30;			//���M���荞�݋֎~
	PORT2.PMR.BIT.B6 = 1;			//���Ӌ@�\(TXD1)�Ƃ��Ďg�p
	SCI1.SCR.BIT.TE = 1;
	SCI1.SCR.BIT.RE = 1;
}	

void init_parameters(void)
{
			
	sen_r.ref = REF_SEN_R;				//�E�Z���T�̃��t�@�����X�l��������
	sen_l.ref = REF_SEN_L;				//���Z���T�̃��t�@�����X�l��������
	
	sen_r.th_wall = TH_SEN_R;			//�E�Z���T�̕ǗL�����f��臒l��������
	sen_l.th_wall = TH_SEN_L;			//���Z���T�̕ǗL�����f��臒l��������
	
	sen_fr.th_wall = TH_SEN_FR;			//�E�O�Z���T�̕ǗL�����f��臒l��������
	sen_fl.th_wall = TH_SEN_FL;			//���O�Z���T�̕ǗL�����f��臒l��������
	
	sen_r.th_control = CONTH_SEN_R;			//�E�Z���T�̕ǐ��䂩���邩�ۂ���臒l��������
	sen_l.th_control = CONTH_SEN_L;			//���Z���T�̕ǐ��䂩���邩�ۂ���臒l��������
	
	con_wall.kp = CON_WALL_KP;			//�ǔ�ᐧ��̔��萔��������
}


void init_maze(void)	//���H���̏�����
{
	int i,j;
	
	for(i = 0; i < MAZESIZE_X; i++)
	{
		for(j = 0; j < MAZESIZE_Y; j++)
		{
			wall[i][j].north = wall[i][j].east = wall[i][j].south = wall[i][j].west = UNKNOWN;	//���H�̑S�̂��킩��Ȃ�����ݒ肷��
		}
	}
	
	for(i = 0; i < MAZESIZE_X; i++)
	{
		wall[i][0].south = WALL;		//�l���̕ǂ�ǉ�����(��)
		wall[i][MAZESIZE_Y-1].north = WALL;	//�l���̕ǂ�ǉ�����(�k)
	}
	
	for(j = 0; j < MAZESIZE_Y; j++)
	{
		wall[0][i].west = WALL;			//�l���̕ǂ�ǉ�����(��)
		wall[MAZESIZE_X-1][i].east = WALL;	//�l���̕ǂ�ǉ�����(��)
	}
	
	wall[0][0].east = wall[1][0].west = WALL;	//�X�^�[�g�n�_�̉E�̕ǂ�ǉ�����
	
}

void init_all(void)
{
	init_clock();	//CPU�̓�����g����ݒ�
	init_io();	//I/O(Input / Output)�|�[�g��ݒ�
	init_cmt();	//CMT(Compare Match Timer)��ݒ�(�Z���T���荞�݁A���ԑ҂��p�B)
	init_mtu();	//MTU(Multi Function Timer Pulse Unit)
	init_adc();	//ADC(Analog Digital Converter)������
//	init_sci();	//SCI(Serial Communication Interface)������
	init_parameters();	//�p�����[�^�̏�����
	init_maze();	//���H���̏�����

	SET_BUZZER_FREQ(INC_FREQ);	//�l�������������̎��g����ݒ�				
	ENABLE_BUZZER;			//�u�U�[�𔭐U������
	wait_ms(80);			//�K���ȑ҂�����
	DISABLE_BUZZER;			//�u�U�[�̔��U���~������

	init_usb();
}

