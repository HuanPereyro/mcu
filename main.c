/*------------------------------------------------------------------------------
TIMER & LED

Copyright 2013 Ivanov Nikita <dr.ivanov@nxt.ru>.
------------------------------------------------------------------------------*/

#include <stdio.h>     /* prototype declarations for I/O functions */
#include "aduc842.h"

sbit LED = P3^4;

void delay(unsigned int ms){

	TMOD 	= 0x90;
	PLLCON	= 0x10;		// 16 division

	TH1 	= 63133 >> 8; // TH1 | TL1 Ц hight and lower bite of timer 1. SFR = 0x8D | 0x8B
	TL1		= 63133;	

	TF1		= 0;		// overflow	 
	TR1		= 1; 		// start timer

	while(ms--) {
		while (!TF1);
		TF1		= 0;
	}

	TR1		= 0;

	return;
}

/*void delay (unsigned int dcms) {                    // dcms = секунда * 10^-4
  unsigned int H, L, rep=1;
  unsigned char CPUD = PLLCON & 0x03;         // CPU core clock divider (биты CD2..CD0 регистра PLLCON)
  unsigned long int cnt = ((unsigned long int) dcms * 1677) >> CPUD;    
                                                    // 1677 - число тактов при f=16,77ћ√ц, за врем€ = 0,1 мсек 
  
  if (cnt > 0xFFFF) { 
    rep = cnt / 0x10000 + 1;
    cnt = cnt / rep;
  }
  else rep = 1;
  if (cnt == 0) return;
  cnt = 0x10000 - cnt;

  H = cnt / 0x100;
  L = cnt % 0x100;

  TR0 = 0;
  TMOD = (TMOD & 0xF0) + 1;
  while(rep--) { 
    TH0 = H;
    TL0 = L;
    TR0=1;
    while (!TF0);
    TF0=0;
  }
  TMOD = (TMOD & 0xF0);
  return;
}*/

void blik (void) {
	delay(5000);
	LED = ~LED;
} 

/*------------------------------------------------
The main C function.  Program execution starts
here after stack initialization.
------------------------------------------------*/
void main (void) {

 	while(1) blik();

}


