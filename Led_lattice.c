#include<reg52.h>
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ENLEDC_or_ENLEDS = P1^3;
sbit  ENLED= P1^4;

unsigned char T0RH = 0;
unsigned char T0RL = 0;
unsigned char T1RH = 0;
unsigned char T1RL = 0;
unsigned char code image[68][8]={
	{0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},//1
	{0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},//2
	{0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},//3
	{0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},//4
	{0xE0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},//5
	{0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},//6
	{0x80,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},//7
	{0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},//8
	
	{0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},//9
	{0x00,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF},//10
	{0x00,0x7F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF},//11
	{0x00,0x7F,0x7F,0x7F,0x7F,0xFF,0xFF,0xFF},//12
	{0x00,0x7F,0x7F,0x7F,0x7F,0x7F,0xFF,0xFF},//13
	{0x00,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0xFF},//14
	{0x00,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F},//15
	
	{0x00,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x3F},//16
	{0x00,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x1F},//17
	{0x00,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x0F},//18
	{0x00,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x07},//19
	{0x00,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x03},//20
	{0x00,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x01},//21
	{0x00,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x00},//22
	
	{0x00,0x7F,0x7F,0x7F,0x7F,0x7F,0x7E,0x00},//23
	{0x00,0x7F,0x7F,0x7F,0x7F,0x7E,0x7E,0x00},//24
	{0x00,0x7F,0x7F,0x7F,0x7E,0x7E,0x7E,0x00},//25
	{0x00,0x7F,0x7F,0x7E,0x7E,0x7E,0x7E,0x00},//26
	{0x00,0x7F,0x7E,0x7E,0x7E,0x7E,0x7E,0x00},//27
	{0x00,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x00},//8
	
	{0x00,0x7C,0x7E,0x7E,0x7E,0x7E,0x7E,0x00},//29
	{0x00,0x78,0x7E,0x7E,0x7E,0x7E,0x7E,0x00},//30
	{0x00,0x70,0x7E,0x7E,0x7E,0x7E,0x7E,0x00},//31
	{0x00,0x60,0x7E,0x7E,0x7E,0x7E,0x7E,0x00},//32
	{0x00,0x40,0x7E,0x7E,0x7E,0x7E,0x7E,0x00},//33
	{0x00,0x00,0x7E,0x7E,0x7E,0x7E,0x7E,0x00},//34
	
	{0x00,0x00,0x3E,0x7E,0x7E,0x7E,0x7E,0x00},//35
	{0x00,0x00,0x3E,0x3E,0x7E,0x7E,0x7E,0x00},//36
	{0x00,0x00,0x3E,0x3E,0x3E,0x7E,0x7E,0x00},//37
	{0x00,0x00,0x3E,0x3E,0x3E,0x3E,0x7E,0x00},//38
	{0x00,0x00,0x3E,0x3E,0x3E,0x3E,0x3E,0x00},//39
	
	{0x00,0x00,0x3E,0x3E,0x3E,0x3E,0x1E,0x00},//40
	{0x00,0x00,0x3E,0x3E,0x3E,0x3E,0x0E,0x00},//41
	{0x00,0x00,0x3E,0x3E,0x3E,0x3E,0x06,0x00},//42
	{0x00,0x00,0x3E,0x3E,0x3E,0x3E,0x02,0x00},//43
	{0x00,0x00,0x3E,0x3E,0x3E,0x3E,0x00,0x00},//44
	
	{0x00,0x00,0x3E,0x3E,0x3E,0x3C,0x00,0x00},//45
	{0x00,0x00,0x3E,0x3E,0x3C,0x3C,0x00,0x00},//46
	{0x00,0x00,0x3E,0x3C,0x3C,0x3C,0x00,0x00},//47
	{0x00,0x00,0x3C,0x3C,0x3C,0x3C,0x00,0x00},//48
	
	{0x00,0x00,0x38,0x3C,0x3C,0x3C,0x00,0x00},//49
	{0x00,0x00,0x30,0x3C,0x3C,0x3C,0x00,0x00},//50
	{0x00,0x00,0x20,0x3C,0x3C,0x3C,0x00,0x00},//51
	{0x00,0x00,0x00,0x3C,0x3C,0x3C,0x00,0x00},//52
	{0x00,0x00,0x00,0x1C,0x3C,0x3C,0x00,0x00},//53
	{0x00,0x00,0x00,0x1C,0x1C,0x3C,0x00,0x00},//54
	{0x00,0x00,0x00,0x1C,0x1C,0x1C,0x00,0x00},//55
	{0x00,0x00,0x00,0x1C,0x1C,0x0C,0x00,0x00},//56
	{0x00,0x00,0x00,0x1C,0x1C,0x04,0x00,0x00},//57
	{0x00,0x00,0x00,0x1C,0x1C,0x00,0x00,0x00},//58
	
	{0x00,0x00,0x00,0x1C,0x18,0x00,0x00,0x00},//59
	{0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00},//60
	{0x00,0x00,0x00,0x10,0x18,0x00,0x00,0x00},//61
	{0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00},//62
	{0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00},//63
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},//64
	
	{0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00},//65
	{0x00,0x00,0x3C,0x3C,0x3C,0x3C,0x00,0x00},//66
	{0x00,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x00},//67
	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},//68
	
	

void ConfigTimer0(unsigned char ms);
void ConfigTimer1(unsigned char ms);
void main(){
	EA = 1;
	ENLED = 0;
	ConfigTimer0(1);
	ConfigTimer1(2);
	while(1);
}
void ConfigTimer0(unsigned char ms){
	unsigned long tmp;
	tmp = (11059200/12)*ms;
	tmp = tmp/1000;
	tmp = 65536-tmp;
	T0RH = (unsigned char)(tmp>>8);
	T0RL = (unsigned char)tmp;
	TMOD &= 0xF0;
	TMOD |= 0x01;
	TH0 = T0RH;
	TL0 = T0RL;
	ET0 = 1;
	TR0 = 1;
}
void ConfigTimer0(unsigned char ms){
	unsigned long tmp;
	tmp = (11059200/12)*ms;
	tmp = tmp/1000;
	tmp = 65536-tmp;
	T1RH = (unsigned char)(tmp>>8);
	T1RL = (unsigned char)tmp;
	TMOD &= 0x0F;
	TMOD |= 0x10;
	TH1 = T1RH;
	TL1 = T1RL;
	ET1 = 1;
	TR1 = 1;
}
void InterruptTimer0() interrupt 1{
	static unsigned char i = 0;
	static unsigned char tmr = 0;
	static unsigned char index = 0;
	ENLEDC_or_ENLEDS = 0;
	TH0 = T0RH;
	TL0 = T0RL;
	P1 &= 0xF8;
	P1 |= i;
	P0 = 0xFF;
	P0 = image[index][i];
	i++;
	if(i>7){
		i = 0;
	}
	tmr++;
	if(tmr >= 250){
		tmr = 0;
		index++;
		if(index>=68){
			index = 0;
		}
	}
}
void InterruptTimer1() interrupt 3{
	static unsigned char i = 0;
	ENLEDC_or_ENLEDS = 1;
	TH1 = T1RH;
	TL1 = T1RL;
	P0 = ~(0x01<<i);
	i++;
	if(i>7){
		i = 0;
	}
}