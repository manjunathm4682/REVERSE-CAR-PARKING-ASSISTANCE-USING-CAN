extern void delay_ms(unsigned int );
extern void delay_sec(unsigned int );
void delay_us(unsigned int );
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
typedef signed int s32;

//---------------------uart protocol----------
#define THRE ((U0LSR>>5)&1)
#define RDR (U0LSR&1)
extern void uart0_init(u32 baud);
extern void uart0_tx(u8 data);
extern u8 uart0_rx(void);
extern void uart0_tx_string(char *);
extern void uart0_rx_string(char *,u8 );
extern void uart0_hex(u8 );
extern void uart0_tx_integer(int );
extern void uart0_tx_float(float );
extern u8 uart0_rx(void);

extern void en_uart0_interrupt(void);
extern void config_vic_for_uart0(void);

//----------------can protocol----------
#define TCS ((C2GSR>>3)&1)
#define RBS (C2GSR&1)

typedef struct canframe
{
	u32 id;
	u32 dlc;
	u32 rtr;
	u32 byteA;
	u32 byteB;
}CAN2;
extern void config_vic(void);
extern void en_int(void);
extern void can2_init(void);
extern void can2_tx(CAN2 );
extern void can2_rx(CAN2 *);
