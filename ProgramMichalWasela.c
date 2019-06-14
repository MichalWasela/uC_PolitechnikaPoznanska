

//----------library definition--------------
#include "aduc831.h"
//-------end library definition-------------

//   |0|0|0|0|0|0|0|0| -> frame
//   |7|6|4|4|3|2|1|0| -> outputs


//-----------variable definition---------------

int Counter = 0;

//-----------end variable definition-----------




//--------functions definitions---------------

//function to interrupt when on pin 3.3 is falling edge
void SwitchInterrupt(void) interrupt 2 //2 -> adress of interrupt 1
{
	TH0 = 0xB8; //SetRegisters of timers
	TL0 = 0x02;
	P3 ^= (1<<0); //toggle bit 0 from port 3 to debug
}




//interrupt generate using when overflow timer 0
void Timer0_Overflow(void) interrupt 1 // -> adress of timer 0
{
	if (P3 == 0xF7) //if pin 3.3
		{
			P3 ^= (1<<0); //toggle bit o from port 3 to debug
			Counter++;
		}	
} //end of timer0



void LED_Line(int I_Counter)
{
	
	switch (I_Counter)
  {
  case 1: 
		P2= 0xEF; //1110 1111  -> Pwr ON LED1
	break;
	
  case 2: 
		P2= 0xCF; //1100 1111  -> Pwr ON LED1 & LED2
	break;
	
  case 3: 
		P2 = 0x8F; //1000 1111  -> Pwr ON LED1 ... LED3
	break;
	
  case 4: 
		P2 = 0x0F; //0000 1111  -> Pwr ON LED1 ... LED4
	break;
	
	case 5: 
		P2 = 0xFF; //1111 1111 -> Pwr OFF all LED/CounterOverflow
		Counter = 0; //Reset counter
	break;
  
  }
} //end of LED_Line



//------------end function definition-------------------------


void main (void)
{
IT1 = 1;   //IT1 = 1 then falling edge on interrupt
EX1 = 1;   // Enable Interrupt 1
ET0 = 1;	 //Enable interrupt from timer0
EA = 1;    // Enable Global Interrupt Flag
	
//--------------definition of timer------------------
TMOD = 	0x01; //set timer as 16bit
TH0 = 0xB8;  //definition of counting time from timer0 
TL0 = 0x02; 
TR0 = 1; //start timer


// main loop
while (1)
  {
		LED_Line(Counter); //Controlling LEDs		
	}

} //end main loop









