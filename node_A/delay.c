#include<LPC21XX.H>
void delay_ms(unsigned int ms)
{
  int a[]={15,60,30,15,15};
  unsigned int pclk;
  pclk=a[VPBDIV]*1000;

  T0PC=0;
  T0PR=pclk-1;
  T0TC=0;
  T0TCR=1;
  while(T0TC<ms);
  T0TCR=0;
}
void delay_s(unsigned int s)
{
  int a[]={15,60,30,15,15};
  unsigned int pclk;
  pclk=a[VPBDIV]*1000000;

  T0PC=0;
  T0PR=pclk-1;
  T0TC=0;
  T0TCR=1;
  while(T0TC<s);
  T0TCR=0;
}
