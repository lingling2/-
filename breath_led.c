#include<reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned long PeriodCnt = 0;
unsigned char HighRH = 0;
unsigned char HighRL = 0;
unsigned char LowRH = 0;
unsigned char LowRL = 0;
unsigned char T1RH = 0;
unsigned char T1RL = 0;


void ConfigTimer1(unsigned char ms); //定时不大于70ms;

void ConfigPWM(unsigned int fr, unsigned char dc);

void main()
{
	EA = 1;
	ENLED = 0;
	ADDR0 = 0;
	ADDR1 = 1;
	ADDR2 = 1;
	ADDR3 = 1;
	
	ConfigPWM(100,10);
	ConfigTimer1(50);
	while(1);
}
/* config frequancy and duty ratio(cycle)*/
void ConfigPWM(unsigned int fr, unsigned char dc)
{
	unsigned int high, low;
	PeriodCnt = (11059200/12) / fr;
	high = (PeriodCnt * dc) / 100;
	low = PeriodCnt - high;
	high = 65536 - high + 12;
	low = 65536 - low + 12;
	HighRH = (unsigned char)(high>>8);
	HighRL = (unsigned char)high;
	LowRH = (unsigned char)(low>>8);
	LowRL = (unsigned char)low;
	
	TMOD &= 0xF0;
	TMOD |= 0x01;
	
	TH0 = HighRH;
	TL0 = HighRL;
	ET0 = 1;
	TR0 = 1;
	
	P0 = 0xFF;
}

void AdjustDutyCycle(unsigned char dc)
{
	unsigned int high,low;
	
	high = (PeriodCnt * dc) /100;
	low = PeriodCnt - high;
	high = 65536 - high + 12;
	low = 65536 - low + 12;
	HighRH = (unsigned char)(high>>8);
	HighRL = (unsigned char)high;
	LowRH = (unsigned char)(low>>8);
	LowRL = (unsigned char)low;
}

void ConfigTimer1(unsigned char ms)
{
	unsigned long tmp;
	
	tmp = 11059200 / 12;
	tmp = (tmp * ms) /1000;
	tmp = 65536 - tmp + 12;
	T1RH = (unsigned char)(tmp>>8);
	T1RL = (unsigned char)tmp;
	TMOD &= 0x0F;
	TMOD |= 0x10;
	TH1 = T1RH;
	TL1 = T1RL;
	ET1 = 1;
	TR1 = 1;
}

void InterruptTimer0() interrupt 1
{
	if(P0 == 0xFF)
	{
		TH0 = LowRH;
		TL0 = LowRL;
		P0 = 0x00;
	}
	else
	{
		TH0 = HighRH;
		TL0 = HighRL;
		P0 = 0xFF;
	}
}

void InterruptTimer1() interrupt 3
{
	static bit dir = 0;
	static unsigned char index = 5;
	
	TH1 = T1RH;
	TL1 = T1RL;
	AdjustDutyCycle(index);
	if(dir == 0)
	{
		index += 5;
		if(index >= 95)
		{
			dir = 1;
		}
	}
	else
	{
		index -= 5;
		if(index == 0)
		{
			dir = 0;
		}
	}
}