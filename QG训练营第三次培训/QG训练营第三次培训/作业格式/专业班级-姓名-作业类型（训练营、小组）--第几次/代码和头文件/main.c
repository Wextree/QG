#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef int Elemtype;
int main()
{
    printf("��������Ҫ�����Ķ������ͣ�1.ѭ������ 2.��ʽ����\n");
    int ch1,ch2;
    Elemtype *e;void *data;
    scanf("%d",&ch1);
    if(!(ch1==1||ch1==2))
    {
        printf("���������������\n");
        scanf("%d",&ch1);
    }
    if(ch1==1)//��ʼ����һ��ѭ������
  {
      AQueue Q;//����һ���������ڳ�ʼ��ѭ������
      InitAQueue(&Q);
      printf("--------------------------------------------------------------------------------------\n");//��switch�������û���ѡ��
      printf("1.�жϿն��� 2.�ж϶��� 3.��ȡ��ͷ 4.���ջ�� 5.��� 6.���� 7.��ն� 8.������� 0.�˳�\n");
      printf("--------------------------------------------------------------------------------------\n");
      scanf("%d",&ch2);
      while(ch2)//ѡ��ͬ�Ĺ�����ʵ�ֲ�ͬ�ĺ���
      {

       switch(ch2)
       {
           case 1:if(IsEmptyAQueue(&Q)) printf("����һ���ն��С�\n");
                    else printf("����һ���ǿն��С�\n");break;
           case 2:if(IsFullAQueue(&Q)) printf("����������\n");
                    else printf("���л�û����\n");
           case 3:if(GetHeadAQueue(&Q,&e)) printf("����ֵΪ%d\n",*e);
                          else printf("����һ���ն��С�\n");break;
           case 4:printf("���г�Ϊ%d\n",LengthAQueue(&Q));break;
           case 5:printf("��������Ҫ��ӵ�ֵ��\n");data=(Elemtype*)malloc(sizeof(Elemtype));
                    scanf("%d",data);
                    if(EnAQueue(&Q,data)) printf("��ӳɹ���\n");
                    else printf("���ʧ�ܣ�\n");break;
           case 6:if(DeAQueue(&Q)) printf("���ӳɹ�!\n");
                     else printf("����ʧ�ܣ������ǿնӣ�\n");break;
           case 7:ClearAQueue(&Q);break;
           case 8:if(TraverseAQueue(&Q,APrint)) printf("�����ɣ�\n");
                     else printf("����Ϊ�գ�\n");break;
           default:printf("��ѡ����ڣ����������룡����\n\n");break;

       }
       printf("---------------------------------------------------------------------------------------\n");//����ѭ������ɲ��ϵ�ִ�й���
       printf("1.�жϿն��� 2.�ж϶��� 3.��ȡ��ͷ 4.���ջ�� 5.��� 6.���� 7.��ն�  8.������� 0.�˳�\n");
       printf("---------------------------------------------------------------------------------------\n");
       scanf("%d",&ch2);
      }
  }
  else//��ʼ������ʽ����
  {
      LQueue Q;//�����ڴ�;
      InitLQueue(&Q);
      printf("--------------------------------------------------------------------------------------\n");
      printf("1.�жϿն��� 2.��ȡ��ͷ 3.���ջ�� 4.��� 5.���� 6.��ն� 7.������� 8.�ݻٶ��� 0.�˳�\n");
      printf("--------------------------------------------------------------------------------------\n");
      scanf("%d",&ch2);
      while(ch2)                                         //ʣ�µ����������ͬ
      {
          switch(ch2)
          {
           case 1:if(IsEmptyLQueue(&Q)) printf("����һ���ն��С�\n");
                    else printf("����һ���ǿն��С�\n");break;
           case 2:if(GetHeadLQueue(&Q,&e)) printf("����ֵΪ%d\n",*e);
                          else printf("Ϊ�ն��У�\n");break;
           case 3:printf("ջ��Ϊ%d\n",LengthLQueue(&Q));break;
           case 4:printf("��������Ҫ��ӵ�ֵ��\n");data=(Elemtype*)malloc(sizeof(Elemtype));
                    scanf("%d",data);
                    if(EnLQueue(&Q,data)) printf("��ӳɹ���\n");
                    else printf("���ܶ�����\n");break;
           case 5:if(DeLQueue(&Q)) printf("���ӳɹ�!");
                    else printf("����ʧ�ܣ������ǿն��У�\n");break;
           case 6:ClearLQueue(&Q); break;
           case 7:if(TraverseLQueue(&Q,LPrint)) printf("�����ɡ�\n");
                     else printf("����Ϊ�գ�\n");break;
           case 8:DestoryLQueue(&Q);break;
           default:printf("��ѡ����ڣ����������룡����\n\n");break;
          }
       printf("--------------------------------------------------------------------------------------\n");
       printf("1.�жϿն��� 2.��ȡ��ͷ 3.���ջ�� 4.��� 5.���� 6.��ն� 7.������� 8.�ݻٶ��� 0.�˳�\n");
       printf("--------------------------------------------------------------------------------------\n");
       scanf("%d",&ch2);
      }
  }
}
