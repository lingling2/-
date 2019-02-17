#include<reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char code LedChar[] = {
	0xC0,0xF9,0xA4,0xB0,0x99,0x82,0xF8,
	0x80,0x90,0x83,0xC6,0xA1,0x86,0x8E
};

unsigned char LedBuffer[] = {
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
};

void main(){
	unsigned int cnt = 0;
	unsigned long sec = 0;
	unsigned char i = 0;
	
	ADDR3 = 1;
	ENLED = 0;			//使能74HC138译码器
	
	TMOD = 0x01;		//定时器设置三步骤
	TH0 = 0xFC;			//1.设置模式
	TL0 = 0x67;			//2.设置初始值
	TR0 = 1;			//3.启动定时器
	
	while(1){
	    if(TF0 == 1){
	    	TF0 = 0;
	    	TH0 = 0xFC;
	    	TL0 = 0x67;
	    	cnt++;
	    	if(cnt>=1000){
	    		cnt = 0;
	    		sec++;
	    		LedBuffer[0] = LedChar[sec%10];
	    		LedBuffer[1] = LedChar[sec/10%10];
	    		LedBuffer[2] = LedChar[sec/100%10];
	    		LedBuffer[3] = LedChar[sec/1000%10];
	    		LedBuffer[4] = LedChar[sec/10000%10];
	    		LedBuffer[5] = LedChar[sec/100000%10];
	    	}
	    	//P0 = 0xFF;    //解决鬼影的方法：关闭段选
	    	ENLED = 1;		//解决鬼影的方法：关闭位选
	    	switch(i){
	    		case 0:
	    			ADDR0 = 0;
	    			ADDR1 = 0;
	    			ADDR2 = 0;
	    			i++;
	    			P0 = LedBuffer[0];
	    			break;
	    		case 1:
	    			ADDR0 = 1;
	    			ADDR1 = 0;
	    			ADDR2 = 0;
	    			i++;
	    			P0 = LedBuffer[1];
	    			break;
	    		case 2:
	    			ADDR0 = 0;
	    			ADDR1 = 1;
	    			ADDR2 = 0;
	    			i++;
	    			P0 = LedBuffer[2];
	    			break;
	    		case 3:
	    			ADDR0 = 1;
	    			ADDR1 = 1;
	    			ADDR2 = 0;
	    			i++;
	    			P0 = LedBuffer[3];
	    			break;
	    		case 4:
	    			ADDR0 = 0;
	    			ADDR1 = 0;
	    			ADDR2 = 1;
	    			i++;
	    			P0 = LedBuffer[4];
	    			break;
	    		case 5:
	    			ADDR0 = 1;
	    			ADDR1 = 0;
	    			ADDR2 = 1;
	    			i++;
	    			P0 = LedBuffer[5];
	    			break;
	    		default:
	    			break;
	    	}
	    	ENLED = 0;
		}
	}
}
