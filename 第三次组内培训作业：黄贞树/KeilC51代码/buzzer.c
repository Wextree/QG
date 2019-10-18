#include <reg52.h>
sbit laba=P1^3;
void delay(unsigned int);
void main()
{
 while(1)
 {
   delay(200);
   laba=0;
   delay(200);
   laba=1;
 }
}
void delay(unsigned int xms)
{
  unsigned int i,j;
  for(i=xms;i>0;i--)
    for(j=110;j>0;j--) ;
}