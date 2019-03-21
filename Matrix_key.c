#include<reg52.h>

sbit KEY_IN_1 = P2^4;
sbit KEY_IN_2 = P2^5;
sbit KEY_IN_3 = P2^6;
sbit KEY_IN_4 = P2^7;

sbit KEY_OUT_1 = P2^3;
sbit KEY_OUT_2 = p2^2;
sbit KEY_OUT_3 = P2^1;
sbit KEY_OUT_4 = P2^0;
unsigned char T0RH = 0;
unsigned char T0RL = 0;

unsigned char KeySta[4][4] = {
	{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}
};

unsigned char code KeyCodeMap[4][4] = {
	{0x31,0x32,0x33,0x26},
	{0x34,0x35,0x36,0x25},
	{0x37,0x38,0x39,0x28},
	{0x30,0x1B,0x0D,0x27}
};

void configTimer0(unsigned char ms)
{
	unsigned int tmp;
	tmp = (11059200/12);
	tmp = (tmp * ms)/1000;
	tmp = 65536 - tmp;
	T0RH = (unsigned char)(tmp>>8);
	T0RL = (unsigned char)tmp;
	TH0 = T0RH;
	TL0 = T0RL;
	TMOD &= 0xF0;
	TMOD |= 0x01;
	ET0 = 1;
	TR0 = 1;
}
void KeyAction(unsigned char keycode)
{
	/* by judgeing the keycode,do something */
}

void KeyDribver()
{
	unsigned char i,j;
	static unsigned char KeyBackup[4][4] = {
		{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}
	};
	
	for(i = 0; i<4; i++)
	{
		for(j = 0; j<4; j++)
		{
			if(KeyBackup[i][j] != KeySta[i][j]){
				if(KeyBackup[i][j] != 0){
					KeyAction(KeyCodeMap[i][j]);
				}
				KeyBackup[i][j] = KeySta[i][j];
			}
		}
	}
}

/* Be called in interrupt function,Be called 1000 times per second*/
void KeyScan()
{
	unsigned char i;
	static unsigned char keyout = 0;
	static unsigned char keybuf[4][4] = {
		{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},
		{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF}
	}

	keybuf[keyout][0] = (keybuf[keyout][0] << 1)|KEY_IN_1;
	keybuf[keyout][1] = (keybuf[keyout][1] << 1)|KEY_IN_2;
	keybuf[keyout][2] = (keybuf[keyout][2] << 1)|KEY_IN_3;
	keybuf[keyout][3] = (keybuf[keyout][3] << 1)|KEY_IN_4;
	
	for(i = 0;i < 4;i++)
	{
		if((keybuf[keyout][i]&0x0F)==0x00){
			KeySta[keyout][i] = 0;
		}
		else if((keybuf[keyout][i]&0x0F)==0x0F){
			KeySta[keyout][i] = 1;
		}
	}
	keyout++;
	keyout = keyout & 0x03;
	switch(keyout)
	{
		case 0:KEY_OUT_1 = 0;KEY_OUT_4 = 1;break;
		case 1:KEY_OUT_1 = 1;KEY_OUT_2 = 0;break;
		case 2:KEY_OUT_2 = 1;KEY_OUT_3 = 0;break;
		case 3:KEY_OUT_1 = 1;KEY_OUT_4 = 0;break;
		default:break;
	}
}