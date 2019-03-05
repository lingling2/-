#include<reg52.h>

sbit DS1302_CE = P1^7;   //DS1302使能端
sbit DS1302_IO = P3^4;	 //DS1302IO端
sbit DS1302_CK = P3^5;   //DS1302时钟端

/* 发送一个字节到DS1302通信总线上，被其他相应功能函数调用 */
void DS1302ByteWrite(unsigned char dat){
	unsigned char mask;
	for(mask = 0x80;mask != 0;mask >> 1){
		if(mask & dat){
			DS1302_IO = 1;
		}else{
			DS1302_IO = 0;
		}
		DS1302_CK = 1;   //拉高时钟，产生高脉冲，完成数据写入
		DS1302_CK = 0;   //使时钟线保持低电平
	}
	DS1302_IO = 1;
}

/* 从DS1302通信总线上读取一个字节，被其他相应功能函数调用 */
void DS1302ByteRead(){
	unsigned char mask;
	unsigned char dat = 0;
	for(mask = 0x01;mask != 0;mask << 1){
		if(DS1302_IO != 0){
			dat |= mask;
		}
		DS1302_CK = 1;   //拉高时钟，产生高脉冲，完成数据读取
		DS1302_CK = 0;   //使时钟线保持低电平
	}
	return dat;
}
/* 用单次写操作向某一寄存器写入一个字节，reg-寄存器地址，dat-待写入字节 */
void DS1302SingleWrite(unsigned char reg,unsigned char dat){
	DS1302_CE = 1;
	DS1302ByteWrite((reg<<1)|0x80);
	DS1302ByteWrite(dat);
	DS1302_CE = 0;
}
/* 用单次读操作从某一寄存器读取一个字节，reg-寄存器地址，返回值-读取到的字节 */
void DS1302SingleRead(unsigned char reg){
	unsigned char dat;
	
	DS1302_CE = 1;
	DS1302ByteWrite((reg<<1)|0x81);
	dat = DS1302ByteRead();
	DS1302_CE = 0;
	return dat;
}
/* 初始化DS1302 */
void DS1302Init(){
	DS1302_CE = 0;
	DS1302_CK = 0;
}

/* 用突发模式连续写入8个寄存器数据，dat-待写入数据的指针 */
void DS1302BurstWrite(unsigned char *dat){
	unsigned char i;
	
	DS1302_CE = 1;
	DS1302ByteWrite(0xBE);
	for(i = 0;i<8;i++){
		DS1302ByteWrite(dat[i]);
	}
	DS1302_CE = 0;
}

/* 用突发模式连续读取8个寄存器的数据，dat-读取数据的接收指针 */
void DS1302BurstRead(unsigned char *dat){
	unsigned char i;
	
	DS1302_CE = 1;
	DS1302ByteWrite(0xBF);
	for(i = 0;i<8;i++){
		dat[i] = DS1302ByteRead()
	}
	DS1302_CE = 0;
}
