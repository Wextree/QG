#include <reg52.h>
#include <intrins.h>

void delayms(unsigned int);

unsigned char aa;  //����һ������������P0�ڸ�ֵ

void main()
{
  aa=0xfe;    //��ֵΪ11111110
	while(1)   //�����ѭ���õ�Ƭ������������ˮ��
	{
		P0=aa;   //������һ�������
		delayms(500);   //��ʱ500ms
		aa=_crol_(aa,1);  //��aaѭ������һλ�������¸�ֵ��aa
	}
}

void delayms(unsigned int xms)
{
  unsigned int i,j;
	for(i=xms;i>0;i--)     //��ʱxms
	  for(j=110;j>0;j--) ;
}
