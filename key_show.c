#include 'preview.h'

KeySta = 1;

void main(){
	bit backup = 1;
	unsigned int cnt = 0;
	
	ENLED = 0;
	ADDR3 = 1;
	
	EA = 1;
	
	TMOD = 0x7F;    //使用定时器T1;
	TH1 = 0xF8;
	TL1 = 0xCD;
	
	ET1 = 1;
	RT1 = 1;
	
	ADDR2 = 0;
	ADDR1 = 0;
	ADDR0 = 0;
	
	KeyOut1 = 0;  //P2 = 0xF7;
	
	P0 = LedChar[cnt];
	
	while(1){
		if(KeySta != backup){
			if(backup == 0){
				cnt++;
				P0=LedChar[cnt%10]
			}
			backup = KeySta;
		}
	}
}


/*使用定时器T1编写中断服务函数*/
void InterruptTimer1() interrupt 3{
	static unsigned char KeyBuf = 0xFF;
	TH1 = 0xF8;
	TL1 = 0xCD;
	KeyBuf =(KeyBuf<<1)|KeyIn1;
	if(KeyBuf==0x00){
		KeySta = 0;
	}
	else if(KeyBuf==0xFF){
		KeySta = 1;
	}
	else
	{}
}