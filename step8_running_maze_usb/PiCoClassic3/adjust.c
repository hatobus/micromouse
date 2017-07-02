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


void view_adc(void)		//ADコンバータの値を見る
{
	unsigned int i;
	
	MOT_POWER_OFF;		// ステッピングモータを励磁する
	
	
	while(1)
	{
		USB_PRINTF("r_sen  is\t%d\r\n",(sen_r.value));	//右センサの値
		USB_PRINTF("fr_sen is\t%d\r\n",(sen_fr.value));	//右前センサの値
		USB_PRINTF("fl_sen is\t%d\r\n",(sen_fl.value));	//左前センサの値
		USB_PRINTF("l_sen  is\t%d\r\n",(sen_l.value));	//左センサの値
		USB_PRINTF("VDD    is\t%dmV\r\n",((10+51)/10*3300*S12AD.ADDR8/4095));//電圧を表示
		
		for(i = 0; i < 0x3fffff; i++)	;		//表示間隔を設定
		
		//画面クリアシーケンス
		USB_PRINTF("\x1b[2J");				//クリアスクリーン[CLS]
		USB_PRINTF("\x1b[0;0H");			//カーソルを0,0に移動
	}
}


void straight_check(int section_check)				//タイヤ直径チェック用
{
	max_speed = SEARCH_SPEED;				//探索の速度を指定
	accel = SEARCH_ACCEL;					//加速度を指定

	wait_ms(1000);
	straight(SECTION * section_check,0);			//section_check区画進む
	
}


void go_and_turn_right(void)					//タイヤトレッド径チェック用
{
	int kaisuu = 0;
	max_speed = SEARCH_SPEED;				//探索の速度を指定
	accel = SEARCH_ACCEL;					//加速度を指定

	wait_ms(1000);						//1秒待つ
	
	while(kaisuu<1){
		//straight(SECTION*2,0);				//2区画進む
		rotate(right,1);				//その場で180度右ターン
		//straight(SECTION*2,0);				//2区画進む	
		//rotate(right,2);				//その場で180度右ターン
	}
}


void adjust_menu(void)	//調整用メニュー
{
	int mode = 1;				//メニュー用変数
	

	while(1)				//モード選択
	{

		wait_ms(CHATTERING_WAIT*3);	//チャタリング防止の待ち時間
		DISABLE_BUZZER;
		while( !(SW_L & SW_C & SW_R) ) ;
		wait_ms(CHATTERING_WAIT);	//チャタリング防止の待ち時間

		_LED(mode);			//現在のモードを車体前方のＬＥＤに表示する
		
		while( SW_L & SW_C & SW_R )	//何れかのスイッチが押されるまで待つ
		{
			wait_ms(33);
			LED3 ^= 1;		//反転(チカチカさせる)
			
		}
		LED3 = 0;
						//以降で、どのスイッチが押されたか判断

		if(SW_L == SW_ON)		//左スイッチが押されていたら次のモードに進む
		{
			mode++;
			if(mode > 7)		//モードは15番までなので、それを超えないようにする
			{
				mode = 7;
			}else{
				SET_BUZZER_FREQ(INC_FREQ);				
				ENABLE_BUZZER;
			}
		}
		else if(SW_R == SW_ON)		//右スイッチが押されていたら前のモードに戻る
		{
			mode--;
			if(mode < 1)		//モードは1番からなので、それ以下にならないようにする
			{
				mode = 1;
			}else{
				SET_BUZZER_FREQ(DEC_FREQ);//ブザーの周波数を決定
				ENABLE_BUZZER;		//ブザーを発振させる
			}
		}
		else if(SW_C == SW_ON)		//中央スイッチが押されていたら、現在のモードを実行する
		{
			SET_BUZZER_FREQ(DEC_FREQ);	//決定スイッチが押されたときの音を鳴らす
			ENABLE_BUZZER;			//ブザーを発振させる
			wait_ms(CHATTERING_WAIT*8);
			SET_BUZZER_FREQ(INC_FREQ);	//音(周波数)を変更する
			wait_ms(CHATTERING_WAIT*8);
			DISABLE_BUZZER;			//ブザーの発振を停止させる
			if(exec_by_mode_adjust(mode) == 1)
			{
				return;			//現在のモードを実行する

			}
		}
	}
}



int exec_by_mode_adjust(int mode)
{
//引数modeを受取り、そのモードに入る。
//戻り値が1の場合は、大本のメニューに戻る

	switch(mode)
	{
		case 1:
			view_adc();		//A/D変換の結果をSCI1から出力する
			break;
			
		case 2:
			straight_check(9);  	 //9区画直線を走る
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
			return 1;		//モード７は元のメニューに戻る
			break;
	}
	
	return 0;
}
