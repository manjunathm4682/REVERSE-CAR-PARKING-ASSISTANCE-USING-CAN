#include <LPC21XX.h>
#include "header.h"

#define TRIG (1<<6)      //P0.6
#define ECHO (1<<7)      //P0.7
#define echo ((IOPIN0>>7)&1)

CAN2 v1,r1;
u32 flag,f=0;
//flag : interrupt flag
//f : 1 when data-frame. other-wise will be 0
//v1 : v1 is CAN-frame structure

int main()
{
	float distance=0;
  
	can2_init();											       //CAN driver initialization
	uart0_init(9600);												 //uart0 initialization
	config_vic();														 //Interrupt Service Routine initialization
	en_int();
	
	IO0DIR |= TRIG;		                       //Set P0.3(ECHO) as input (explicitly)
	uart0_tx_string("welcome\r\n");

	while(1)
	{
		if(flag==1)														 //when interrupt flag become one 
		{
			uart0_tx_string("interrupt triggered\r\n");
			f=0;
			if(v1.rtr==1)                 			 //if it is remote frame
			{
				uart0_tx_string("remote frame received\r\n");

				//Output 10us HIGH on TRIG pin
			
				IO0SET = TRIG;
				delay_us(10);
				IO0CLR = TRIG;

				while(!echo);    									 //Wait for a HIGH on ECHO pin
				T0TC=T0PC=0;
				T0TCR=1;        									 //Start counting
				while(echo);    									 //Wait for a LOW on ECHO pin
				T0TCR=0;        									 //Stop counting and save value(us) in echoTime
				distance = T0TC;
				distance = (0.0343 * distance)/2;  //Find the distance
				//distance=T0TC/59;
				uart0_tx_integer(distance);
				uart0_tx_string("\r\n");
				delay_ms(50);                      //wait 50 ms for next update		

				r1.id=v1.id;
				r1.dlc=v1.dlc;
				r1.rtr=0;
				r1.byteA=distance;
				can2_tx(r1);  
				uart0_tx_string("ultrasonic sensor data transmitted\r\n");
			}
			
			if(v1.rtr==0)												 //if it is data-frame
			{
				flag=0;
				uart0_tx_string("data frame received\r\n");
			}
			
		}
	}
}
