#include<LPC21XX.H>
#include "header.h" 

#define THRE ((U0LSR>>5)&1)
#define RDR (U0LSR&1)

void uart0_init(u32 baud)
{
  u32 pclk,res;
  int a[]={15,60,30,15,15};
  pclk=a[VPBDIV]*1000000;
  res=pclk/(16*baud);

  PINSEL0|=5;        //p0.0 tx and p0.1 rx
  U0LCR=0x83;		 // 8N1 DLAB=1;
  U0DLL=res&0xFF;		//lower byte
  U0DLM=(res>>8)&0xFF;  //upper byte
  U0LCR=0x03;         //DLAB=0;
}

void uart0_tx(u8 data)
{
  U0THR=data;
  while(THRE==0);
}

u8 uart0_rx(void)
{
   while(RDR==0);
   return U0RBR;
}

void uart0_tx_string(char *ptr)
{
  while(*ptr)
  {
   U0THR=*ptr;
	 while(THRE==0);
	 ptr++;
  }
}

void uart0_hex(u8 ascii)
 {
    u8 i;  
    uart0_tx(0+48);
	  uart0_tx('x');

    i=(ascii>>4)&0x0F;
	  uart0_tx(i+48);
	  i=(ascii&0x0F);
	if(i>9)
	{
	   i=i-9;
	   uart0_tx(64+i); 	  
	}
	else
	   uart0_tx(i+48);

 }
 
void uart0_rx_string(char *ptr,u8 len)
{
   s32 i;
   for(i=0;i<len;i++)
   {
      while(RDR==0);
	    ptr[i]=U0RBR;
	    
		  if(ptr[i]=='\r')
	      break;
	 }
	ptr[i]='\0';
}

void uart0_tx_integer(int num)
{
  int len,i,j;
  char s[10],t;
  //sprintf(a,"%d",num);
  if(num==0)
  {
      uart0_tx('0');
       return;
  }          
   for(i=0;num;num=num/10,i++)
      s[i]=(num%10)+48;
	s[i]='\0';
    for(len=0;s[len]!='\0';len++);

    for(i=0,j=len-1; i<j ;i++,j--)
	  {
     t=s[i];
		 s[i]=s[j];
		 s[j]=t;
	  }

  uart0_tx_string(s);
}

void uart0_tx_float(float f)
{
  int n;
  if(f==0)
  {
   uart0_tx_string("0.00");
	 return;
  }
   n=f;
   uart0_tx_integer(n);
   n=(f-n)*100;
   uart0_tx('.');
   uart0_tx_integer(n);
}
