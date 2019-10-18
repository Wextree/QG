#include <stdio.h>
#include "stack.h"
#include <stdlib.h>
#include "stack.c"
int main()
{
  int length=0,ch1=0,ch2=0;//������Ҫʹ�õı���
  ElemType datas,e;
  printf("��������Ҫ������ջ���ͣ�1.˳��ջ 2.��ջ\n");
  scanf("%d",&ch1);
while(1)
{
    if(!scanf("%d",&ch1)||!(ch1==1||ch1==2))
        {getchar();printf("���������������\n");}
    else break;
}
  if(ch1==1)//��ʼ����һ��˳��ջ
  {
      SqStack s;//����һ���������ڳ�ʼ��˳��ջ
      int sizes;
      printf("������ջ�Ĵ�С��\n");
      scanf("%d",&sizes);//����ջ�Ĵ�С
      if(initStack(&s,sizes))
        printf("�����ɹ���\n");
      else {printf("����ʧ�ܣ���鿴�ڴ��Ƿ��㹻��");return 0;}
      printf("--------------------------------------------------------------------------\n");//��switch�������û���ѡ��
      printf("1.�жϿ�ջ 2.��ȡջ��ֵ 3.���ջ�� 4.��ջ 5.��ջ 6.���ջ 7.����ջ 0.�˳�\n");
      printf("--------------------------------------------------------------------------\n");
      scanf("%d",&ch2);
      while(ch2)//ѡ��ͬ�Ĺ�����ʵ�ֲ�ͬ�ĺ���
      {

       switch(ch2)
       {
           case 1:if(isEmptyStack(&s)) printf("����һ���ǿ�ջ��\n");
                    else printf("����һ����ջ��\n");break;
           case 2:if(getTopStack(&s,&e)) printf("ջ��ֵΪ%d\n",e);
                          else printf("�����ڴ�������Ϊ��ջ��\n");break;
           case 3:if(stackLength(&s,&length)) printf("ջ��Ϊ%d\n",length);
                               else printf("�����ڴ��������ǿ�ջ��\n");break;
           case 4:printf("��������Ҫ��ջ��ֵ��\n");
                    scanf("%d",&datas);
                    if(pushStack(&s,datas)) printf("��ջ�ɹ���\n");
                    else printf("��ջʧ�ܣ�\n");break;
           case 5:if(popStack(&s,&datas)) printf("��ջ�ɹ�������ջ��ֵΪ%d\n",datas);
                              else printf("��ջʧ�ܣ������ǿ�ջ���������ڴ�ʧ�ܣ�\n");break;
           case 6:if(clearStack(&s)) printf("��ճɹ���\n");
                    else printf("���ʧ�ܡ�\n");break;
           case 7:if(destoryStack(&s)) printf("�ݻٳɹ���\n");
                    else printf("�ݻ�ʧ�ܣ�\n");break;
           default:printf("��ѡ����ڣ����������룡����\n\n");break;

       }
       printf("--------------------------------------------------------------------------\n");//����ѭ������ɲ��ϵ�ִ�й���
       printf("1.�жϿ�ջ 2.��ȡջ��ֵ 3.���ջ�� 4.��ջ 5.��ջ 6.���ջ 7.����ջ 0.�˳�\n");
       printf("--------------------------------------------------------------------------\n");
       scanf("%d",&ch2);
      }
  }
  else//��ʼ������ջ
  {
      LinkStack s;//�����ڴ�;
      if(initLStack(&s))
        printf("�����ɹ���\n");
      else {printf("����ʧ�ܣ���鿴�ڴ��Ƿ��㹻��");return 0;}
      printf("--------------------------------------------------------------------------\n");
      printf("1.�жϿ�ջ 2.��ȡջ��ֵ 3.���ջ�� 4.��ջ 5.��ջ 6.���ջ 7.����ջ 0.�˳�\n");
      printf("--------------------------------------------------------------------------\n");
      scanf("%d",&ch2);
      while(ch2)                                         //ʣ�µ����������ͬ
      {
          switch(ch2)
          {
           case 1:if(isEmptyLStack(&s)) printf("����һ���ǿ�ջ��\n");
                    else printf("����һ����ջ��\n");break;
           case 2:if(getTopLStack(&s,&e)) printf("ջ��ֵΪ%d\n",e);
                          else printf("�����ڴ�������Ϊ��ջ��\n");break;
           case 3:if(LStackLength(&s,&length)) printf("ջ��Ϊ%d\n",length);
                               else printf("�����ڴ��������ǿ�ջ��\n");break;
           case 4:printf("��������Ҫ��ջ��ֵ��\n");
                    scanf("%d",&datas);
                    if(pushLStack(&s,datas)) printf("��ջ�ɹ���\n");
                    else printf("�����ڴ����ʧ�ܡ�\n");break;
           case 5:if(popLStack(&s,&datas)) printf("��ջ�ɹ�������ջ��ֵΪ%d\n",datas);
                              else printf("��ջʧ�ܣ������ǿ�ջ���������ڴ�ʧ�ܣ�\n");break;
           case 6:if(clearLStack(&s)) printf("��ճɹ���\n");
                    else printf("���ʧ�ܡ�\n");break;
           case 7:if(destoryLStack(&s)) printf("�ݻٳɹ���\n");
                    else printf("�ݻ�ʧ�ܣ�\n");break;
           default:printf("��ѡ����ڣ����������룡����\n\n");break;
          }
       printf("--------------------------------------------------------------------------\n");
       printf("1.�жϿ�ջ 2.��ȡջ��ֵ 3.���ջ�� 4.��ջ 5.��ջ 6.���ջ 7.����ջ 0.�˳�\n");
       printf("--------------------------------------------------------------------------\n");
       scanf("%d",&ch2);
      }
  }
  return 0;
}
