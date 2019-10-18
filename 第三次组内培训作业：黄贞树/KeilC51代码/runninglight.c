#include <reg52.h>
#include <intrins.h>

void delayms(unsigned int);

unsigned char aa;  //定义一个变量能来给P0口赋值

void main()
{
  aa=0xfe;    //赋值为11111110
	while(1)   //这个大循环让单片机不断运作流水灯
	{
		P0=aa;   //点亮第一个发光管
		delayms(500);   //延时500ms
		aa=_crol_(aa,1);  //将aa循环左移一位，再重新赋值给aa
	}
}

void delayms(unsigned int xms)
{
  unsigned int i,j;
	for(i=xms;i>0;i--)     //延时xms
	  for(j=110;j>0;j--) ;
}
