#include<LPC21XX.H>
#include "header.h"
extern CAN2 v1;
extern u32 flag,f;
__irq void can2_rx_Handler(void)
{
  v1.id=C2RID;
  v1.dlc= (C2RFS>>16)&0x0f;
  v1.rtr=(C2RFS>>30)&1;
  if(v1.rtr==0)
  {
   f=1;
   v1.byteA=C2RDA;
	 v1.byteB=C2RDB;
  }
  C2CMR=(1<<2);
  flag=1;
  VICVectAddr=0;
}

void config_vic(void)
{
   VICIntSelect=0;
   VICVectCntl0=27|(1<<5);
   VICVectAddr0=(u32)can2_rx_Handler;
   VICIntEnable|=(1<<27);
}

void en_int(void)
{
   C2IER=1;
}
