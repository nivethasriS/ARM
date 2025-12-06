#include<lpc21xx.h>
void uart_con(void);
void uart_inte(void);
int i=0;
void uart0_isr(void) __irq
{
  if(i<27)
  {
 i++;
U0THR='A'+i;

}


VICVectAddr=0;

  }
int main()
{
uart_con();
uart_inte();
VICIntEnable=1<<6;
U0THR='A';
while(1);
}
void uart_con(void)
{
PINSEL0=0X05;
U0LCR=0X83;
U0DLL=97;
U0DLM=0;
U0LCR=0X03;
}
void uart_inte(void)
{
VICIntSelect=0;
VICVectCntl1=(0x20)|6;
VICVectAddr1=(int)uart0_isr;
U0IER=1<<1;
}

