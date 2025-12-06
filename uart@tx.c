#include<lpc21xx.h>
#include<stdlib.h>
#include<stdio.h>
#define lcd_p 0x00000ff0
#define rs 1<<12
#define e 1<<13
void lcd_init(void);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_string(char *);
void lcd_integer(int);
void lcd_tistring(char *);
void uart_con(void);
void uart_tx(unsigned char);
unsigned uart_rx(void);
void delay(int ms)
{
T0PR=15000-1;
T0TCR=0X01;
while(T0TC<ms);
T0TCR=0X03;
T0TCR=0X00;
}

//unsigned char string(unsigned char *);


int main()
{
 
unsigned char txbyt;
char s[20];
lcd_init();
uart_con();
while(1)
{
int b=0;
  lcd_cmd(0x01);
 //if((IOPIN0&(1<<2))==0)
{

while(1)
{
txbyt=uart_rx();
if((txbyt=='\n')||(txbyt=='\r'))
{
s[b]='\0';
break;
}
txbyt=txbyt^32;
s[b]=txbyt;
uart_tx(txbyt);
b++;
}

lcd_cmd(0x01);
lcd_cmd(0xc0);
lcd_string(s);
lcd_cmd(0x80);
lcd_tistring("count:");
delay(1000);
lcd_tistring("enter new string");
delay(500);
}

}
}
void uart_con(void)
{
PINSEL0 |=0X05;
U0LCR=0X83 ;
U0DLL=97;
U0DLM=0;
U0LCR=0X03;
}
void uart_tx(unsigned char data)
{
while(((U0LSR>>5)&1)==0);
U0THR=data;
}
unsigned uart_rx(void)
{
while(((U0LSR&0X01))==0);
return U0RBR;
}
void lcd_init(void)
{
IODIR0 |=lcd_p|rs|e;
lcd_cmd(0x01);
lcd_cmd(0x02);
lcd_cmd(0x0c);
lcd_cmd(0x38);
lcd_cmd(0x80);
}
void lcd_cmd(unsigned char d)
{
IOCLR0=lcd_p;
IOSET0=d<<4;
IOCLR0=rs;
IOSET0=e;
delay(2);
IOCLR0=e;
}
void lcd_data(unsigned char d)
{
IOCLR0=lcd_p;
IOSET0=d<<4;
IOSET0=rs;
IOSET0=e;
delay(2);
IOCLR0=e;
}

void lcd_string(char *s)
{
int c=0;
int j=0,i;
char buf[5];
while(s[j]!='\0')
{
if((s[j]=='a')||(s[j]=='e')||(s[j]=='i')||(s[j]=='o')||(s[j]=='u')||(s[j]=='A')||(s[j]=='E')||(s[j]=='I')||(s[j]=='O')||(s[j]=='U')	 )
{ 
c++;
}
lcd_data(s[j]);
j++;
}

lcd_cmd(0x86);
sprintf(buf,"%d",c);
for(i=0;buf[i]!='\0';i++)
{ 
c++;
lcd_data(buf[i]);
}
}
void lcd_tistring(char *s)
{
while(*s)
{
lcd_data(*s++);
}
}



   
