#include<reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char code image[][]={
	{0xFF,0x99,0x00,0x00,0x00,0x81,0xC3,0xE7},
	{0xFF,0xFF,0xDB,0x81,0x81,0xC3,0xE7,0xFF},
	{0xFF,0xFF,0xFF,0xDB,0xC3,0xE7,0xFF,0xFF},
	{0xFF,0xFF,0xFF,0xFF,0xE7,0xE7,0xFF,0xFF},
	{0xFF,0xFF,0xFF,0xFF,0xE7,0xE7,0xFF,0xFF},
	{0xFF,0xFF,0xFF,0xFF,0xE7,0xE7,0xFF,0xFF},
	{0xFF,0xFF,0xFF,0xDB,0xC3,0xE7,0xFF,0xFF},
	{0xFF,0xFF,0xDB,0x81,0x81,0xC3,0xE7,0xFF},
}
void main(){
	EA = 1;
	ENLED = 0;
	ADDR3 = 0;
	
	TMOD = 0x01;
	TH0 = 0xFC;
	TL0 = 0x67;		//定时
	
	ET0 = 1;
	TR0 = 1;		//使能中断再开启定时器
	while(1);
}

//定时器中断服务函数
void InterruptTimer0() interrupt 1{
	static unsigned char i = 0;
	static unsigned char index = 0;
	static unsigned char tmr = 0;
	
	TH0 = 0xFC;
	TL0 = 0x67;
	
	P0 = 0xFF;
	switch(i){
		case 0:ADDR0=0;ADDR1=0;ADDR2=0;i++;P0=image[index][0];break;
		case 1:ADDR0=1;ADDR1=0;ADDR2=0;i++;P0=image[index][1];break;
		case 2:ADDR0=0;ADDR1=1;ADDR2=0;i++;P0=image[index][2];break;
		case 3:ADDR0=1;ADDR1=1;ADDR2=0;i++;P0=image[index][3];break;
		case 4:ADDR0=0;ADDR1=0;ADDR2=1;i++;P0=image[index][4];break;
		case 5:ADDR0=1;ADDR1=0;ADDR2=1;i++;P0=image[index][5];break;
		case 6:ADDR0=0;ADDR1=1;ADDR2=1;i++;P0=image[index][6];break;
		case 7:ADDR0=1;ADDR1=1;ADDR2=1;i=0;P0=image[index][7];break;
		default:break;
	}
	tmr++;
	if(tmr>=200){
		tmr = 0;
		index++;
		if(index>=8){
			index = 0;
		}
	}
}
