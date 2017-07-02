#include "iodefine.h"

extern void _LED(int led_data);
extern void wait_ms(int wtime);

void goal_appeal(void)				//ゴールしたことをアピールする
{
	int i,j,led,wtime;
	
	wtime = 100;				//初期の待ち時間
	
	for(j = 0; j < 10; j++)			//10回繰り返す
	{
		led = 1;			//LED点灯データの初期化
		for(i = 0; i < 4; i++)
		{
			_LED(led);		//LED点灯データを書き込み
			led = led << 1;		//LED点灯データを更新
			wait_ms(wtime);		//待ち時間
		}
		led = 8;			//LED点灯データを初期化
		for(i = 0; i < 4; i++)
		{
			_LED(led);		//LED点灯データを書き込み
			led = led >> 1;		//LED点灯データを更新
			wait_ms(wtime);		//待ち時間
		}
		wtime -= 5;			//待ち時間を更新
	}
	
	wait_ms(500);				//点滅が終わった後、0.5秒待つ
	
}
