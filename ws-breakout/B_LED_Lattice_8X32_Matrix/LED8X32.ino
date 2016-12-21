// Do not remove the include below
/*
#define CS 2  //片�?引脚
#define RD 3  //读取 引脚(悬空)
#define WR 4  //写入 引脚
#define DA 5  //数据 引脚
*/
#include "LED8X32.h"
#include <Wire.h>
#include "DS1307.h"
LED8X32 LED8X32m1;
DS1307 clock;//define a object of DS1307 class
// the setup routine runs once when you press reset:
void setup() {
	unsigned char i;

	LED8X32m1.HT1632C_Init();	 //初始�?
	LED8X32m1.HT1632C_clr();	 //清屏
	LED8X32m1.HT1632C_Writer_CMD(PWM_DUTY|10); //显示亮度

//	LED8X32m1.HT1632C_Writer_AllDATA(0,abc+5,32);

	clock.begin();
	clock.fillByYMD(2013,1,19);//Jan 19,2013
	clock.fillByHMS(15,28,30);//15:28 30"
	clock.fillDayOfWeek(SAT);//Saturday
	clock.setTime();//write time to the RTC chip
	delay(10);

 	for(i=0;i<100;i++)	//100%
		{
 		LED8X32m1.HT1632C_Writer_AllDATA(0 ,tab0[i%1000/100],8);
		LED8X32m1.HT1632C_Writer_AllDATA(16,tab0[i%100/10],8);
		LED8X32m1.HT1632C_Writer_AllDATA(32,tab0[i%10%10],8);
 		LED8X32m1.HT1632C_Writer_AllDATA(48,tab0[10],8);
		delay(40);
		}

	for(i=0;i<168;i++)//网址左移
		{
		LED8X32m1.HT1632C_Writer_AllDATA(0,abc+i,32);
		delay(50);
		}


}

// the loop routine runs over and over again forever:
void loop() {
	unsigned char i=0;
	while(1){
	clock.getTime();//更新时间
	LED8X32m1.HT1632C_Writer_AllDATA(0 ,tab1[clock.hour/10],8);
	LED8X32m1.HT1632C_Writer_AllDATA(16,tab1[clock.hour%10],8);
	LED8X32m1.HT1632C_Writer_AllDATA(32,tab2[clock.minute/10],8);
	LED8X32m1.HT1632C_Writer_AllDATA(48,tab2[clock.minute%10],8);
	LED8X32m1.HT1632C_Writer_Fen(i);//走秒闪烁
	delay(800);
	if(i==0)i=1;else i=0;
	}

}
