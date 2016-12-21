#include <stdlib.h>
#include "LED8X32.h"

void LED8X32::HT1632C_Writer(unsigned char Data,unsigned char cnt)	  //HT1632C发送数据函数，高位在前
{
	unsigned char i;
	for(i=0;i<cnt;i++)
	{

  		digitalWrite(WR, LOW);
		if(Data&0x80)
		digitalWrite(DA, HIGH);
		else
		digitalWrite(DA, LOW);
		Data<<=1;
		digitalWrite(WR, HIGH);
	}
}
void LED8X32::HT1632C_Writer_CMD(unsigned char cmd)//发送命令函�?
{
	digitalWrite(CS, LOW);
	LED8X32::HT1632C_Writer(0x80,3);		//命令�?00
	LED8X32::HT1632C_Writer(cmd,9);		//命令数据，第9位为0
	digitalWrite(CS, HIGH);
}
void LED8X32::HT1632C_Writer_AllDATA(unsigned char Addr,unsigned char p[],unsigned char cnt)//指定地址写入连续数据，cnt为写入数据个数，�?位算
{
	unsigned char i;
	digitalWrite(CS, LOW);
	LED8X32::HT1632C_Writer(0xa0,3);
	LED8X32::HT1632C_Writer(Addr<<1,7);
	for(i=0;i<cnt;i++)
		{
		LED8X32::HT1632C_Writer(*p,8);
			p++;
		}
	digitalWrite(CS, HIGH);
}

void LED8X32::HT1632C_Writer_Fen(unsigned char x)
{
	unsigned char i;
	digitalWrite(CS, LOW);
	LED8X32::HT1632C_Writer(0xa0,3);
	LED8X32::HT1632C_Writer(0x1e<<1,7);
	if(x==0){
			LED8X32::HT1632C_Writer(0x00,8);
			LED8X32::HT1632C_Writer(0x00,8);
			}
	else    {
			LED8X32::HT1632C_Writer(0x66,8);
			LED8X32::HT1632C_Writer(0x66,8);
			}
	digitalWrite(CS, HIGH);
}

void LED8X32::HT1632C_clr(void)	//清屏函数
{
	unsigned char i;
	digitalWrite(CS, LOW);
	HT1632C_Writer(0xa0,3);
	LED8X32::HT1632C_Writer(0x00,7);
	for(i=0;i<32;i++)
		LED8X32::HT1632C_Writer(0x00,8);
	digitalWrite(CS, HIGH);
}
void LED8X32::HT1632C_Init(void)		//HT1632C初始化函�?
{
	pinMode(CS, OUTPUT);
	pinMode(WR, OUTPUT);
	pinMode(RD, OUTPUT);
	pinMode(DA, OUTPUT);
	digitalWrite(CS, HIGH);
	digitalWrite(WR, HIGH);
	digitalWrite(RD, HIGH);
	digitalWrite(DA, HIGH);
	HT1632C_Writer_CMD(SYS_DIS);
	HT1632C_Writer_CMD(COM_OPTION);
	HT1632C_Writer_CMD(RC_MASTER_MODE);
//	HT1632C_Writer_CMD(SLAVE_MODE);
	HT1632C_Writer_CMD(SYS_EN);
	HT1632C_Writer_CMD(LED_ON);
//	HT1632C_Writer_CMD(PWM_DUTY);
	HT1632C_Writer_CMD(BLINK_OFF);
//	HT1632C_Writer_CMD(BLINK_ON);
}

