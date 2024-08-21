#include<LPC21XX.H>
#include"header.h"
#define sw1 ((IOPIN0>>14)&1)
#define buzzer (1<<21)   //p0.21
#define LED (1<<17)      //p0.17

CAN2 v1,t,t1;
u32 flag,c=0,flag1=0; 
//t is for transmit remote-frame and t1 is for transmit data-frame
//v1 is can frame structure to store received-data
//flag : interrupt occured flag 
//flag1 & c: this indicates "data-frame" or "remote-frame"

int main()
{
		
	can2_init();											//CAN Initialization
	uart0_init(9600);									//uart0 initialization
	config_vic();											//Interrupt Service Routine initialization
	en_int();													//Enabling the CAN RX interrupt

	t.id=0x45;                        //for remote frame
	t.rtr=1;
	t.dlc=4;	 
	
	t1.id=0x23;												//for data frame
	t1.rtr=0;
	t1.dlc=4;
	t1.byteA=0x44332211;

	IODIR0=buzzer|LED;
	IOCLR0=buzzer;
	IOSET0=LED;
	uart0_tx_string("welcome\r\n");
	while(1)
	{
		if(sw1==0)
		{
			while(sw1==0);
			c^=1;
			uart0_tx_integer(c);
			uart0_tx_string("\r\n");
			if(c)
			{  
			    flag1=1;
			    uart0_tx_string("remote frame transmited\r\n");
				  can2_tx(t);												
			}
			else
			{
				flag1=0;
				can2_tx(t1);											
				uart0_tx_string("data frame transmited\r\n"); 
			}
		}

		if(flag==1)
		{
		  flag=0;
			
			if(flag1==1)
			{
				uart0_tx_string("frame received\r\n");
				if((v1.byteA<=400) && (v1.byteA>=300))
				{
					uart0_tx_string("400-300\r\n");
					IOSET0=buzzer;
					IOCLR0=LED;
					delay_ms(1000);
					IOCLR0=buzzer;
					IOSET0=LED;
					delay_ms(1000);
				}
				if((v1.byteA<=299) && (v1.byteA>=200))
				{
					uart0_tx_string("299-200\r\n");
					IOSET0=buzzer;
					IOCLR0=LED;
					delay_ms(500);
					IOCLR0=buzzer;
					IOSET0=LED;
					delay_ms(500);
				}
				if((v1.byteA<=199) && (v1.byteA>=100))
				{
					uart0_tx_string("199-100\r\n");
					IOSET0=buzzer;
					IOCLR0=LED;
					delay_ms(100);
					IOCLR0=buzzer;
					IOSET0=LED;
					delay_ms(100);
				}
				if((v1.byteA<=99) && (v1.byteA>=50))
				{
					uart0_tx_string("99-50\r\n");
					IOSET0=buzzer;
					IOCLR0=LED;
					delay_ms(50);
					IOCLR0=buzzer;
					IOSET0=LED;	
					delay_ms(50);

				}
				if((v1.byteA<=50))
				{
					uart0_tx_string("50\r\n");
					IOSET0=buzzer;
					IOCLR0=LED;
				}
				else
				{
					IOCLR0=buzzer;
					IOSET0=LED;
				}
				
		  }						//flag1
	  }							//flag
  } 							//while
}									//main
