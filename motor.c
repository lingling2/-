#include 'preview.h'

unsigned char code BeatCode[8]={
	0xFE,0xFC,0xFD,0xF9,0xFB,0xF3,0xF7,0xF6
};

void main(){
	
	EA = 1;
	
	TMOD = 0x01;
	TH0 = 0xFC;
	TL0 = 0x67;  //定时1ms
	
	ET0 = 1;
	TR0 = 1;	//先使能中断，再开启定时器
	
	
	while(1){
		
		//\********** Do other things **********\//
		
	}
}

void InterruptTimer0() interrupt 1{
	unsigned char index = 0;
	P1 = BeatCode[index];
		index=index&0x07;
}