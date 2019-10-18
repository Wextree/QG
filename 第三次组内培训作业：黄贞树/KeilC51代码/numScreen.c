#include <reg52.h>
void delay(unsigned int);
void display(unsigned int);
unsigned char code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
void main()
{
  unsigned int i;
  for(i=0;i<=9999;i++)
  {
     display(i);
  }
}
void display(unsigned int i)
{
  unsigned int ge,shi,bai,qian,k;
  ge=i%10;
  shi=i%100/10;
  bai=i%1000/100;
  qian=i/1000;
 for(k=0;k<66;k++)
  {P2=0x00;
  P0=table[qian];
  P2=0x01;
  delay(2);

  P2=0x00;
  P0=table[bai];
  P2=0x02;
  delay(2);

  P2=0x00;
  P0=table[shi];
  P2=0x04;
  delay(2);

  P2=0x00;
  P0=table[ge];
  P2=0x08;
  delay(2);}
}
void delay(unsigned int xms)
{
  unsigned int i,j;
  for(i=xms;i>0;i--)
    for(j=110;j>0;j--) ;
}