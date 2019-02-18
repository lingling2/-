#include<reg52.h>

sbit PIN_RXD = P3^0;		//接收引脚定义
sbit PIN_TXD - P3^1;		//发送引脚定义

bit RxdOrTxd = 0;			//指示当前状态为接收还是发送
bit RxdEnd = 0;				//接收结束标志
bit TxdEnd = 0;				//发送结束标志

unsigned char RxdBuf = 0;   //接收缓冲器
unsigned char TxdBuf = 0;   //发送缓冲器

void ConfigUART(unsigned int baud);
void StartTXD(unsigned char dat);
void StartRXD();

void main(){
	EA = 1;
	ConfigUART(9600);		//配置波特率为9600
	
	while(1){
		while(PIN_RXD);     //等待起始位，即低电平出现
		StartRXD();
		
	}
}

void ConfigUART(unsigned int baud)
{
	TMOD &= 0xF0;						//清零T0的控制位
	TMOD |= 0x02;						//配置T0为模式2
	TH0 = 256 - 11059200/(baud*12);  	// 256 - (1/baud)/(12/11059200)
}
void StartRXD(){
	TL0 = 256 - ((256-TH0)>>1);
	ET0 = 1;
	TR0 = 1;
	RxdEnd = 0;
	RxdOrTxd = 0;
}

void StartTXD(unsigned char dat)
{
	TxdBuf = dat;
	TL0 = TH0;
	ET0 = 1;
	TR0 = 1;
	PIN_TXD = 0;
	TxdEnd = 0;
	RxdOrTxd = 1;
}

void InterruptTimer0() interrupt 1{
	static unsigned char cnt = 0;          //位接收或发送计数
	
	//发送处理
	if(RxdOrTxd){
		cnt++;
		if(cnt<=8){
			PIN_TXD = TxdBuf & 0x01;
			TxdBuf >>= 1;
		}
		else if(cnt == 9)
		{
			PIN_TXD = 1;
		}
		else{
			cnt = 0;
			TR0 = 0;
			TxdEnd = 1;
		}
	}
	
	//接收处理
	else{
		if(cnt == 0){
			if(!PIN_RXD){
				RxdBuf = 0;
				cnt++;
			}
			else{
				TR0 = 0;
			}
		}
	}
	else if(cnt <= 8){
		RxdBuf >>= 1;
		if(PIN_RXD){
			RxdBuf |= 0x80;
		}
		cnt++;
		else{
			cnt = 0;
			TR0 = 0;
			if(PIN_RXD){
				RxdEnd = 1;
			}
		}
	}
}