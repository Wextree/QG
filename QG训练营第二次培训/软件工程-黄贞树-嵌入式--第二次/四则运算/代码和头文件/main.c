#include <stdio.h>
#include <stdlib.h>
#include "calculate.h"

int main()
{
  char str[100];char c;//����һ���ַ��������ű��ʽ
  int i,flag=0,num,num1,num2,count=0,pro=0,sizes=100;
  intSqStack s1;//������������ȥ��ʼ������ջ
  charSqStack s2;
  if(initIntStack(&s1,sizes))//��ʼ��������ջ
  printf("����ջ�����ɹ�\n");
  else printf("����ջ����ʧ�ܣ�\n");
  if(initCharStack(&s2,sizes))
  printf("�ַ�ջ�����ɹ�\n");
  else printf("�ַ�ջ����ʧ�ܣ���\n");
  printf("����������Ҫ����ı��ʽ��\n");
  scanf("%s",str);//������ʽ
  for(i=0;str[i]!='\0';i++)//����������ַ���
  {
      if(str[i]>='0'&&str[i]<='9')//�ж��Ƿ�������
      {
          if(flag==1)//���ǰ����Ǹ�Ҳ�����ֵĻ�����ȡ����ջ��ջ��Ԫ�غϲ��������´��
          {
                num=getTopStack(&s1);num=num*10+(str[i]-'0');
                if(!changeTop(&s1,num)) {printf("����ʧ�ܣ�\n");return 0;}
          }
          else {num=str[i]-'0';if(!pushIntStack(&s1,num)) {printf("��ջʧ�ܣ�\n");return 0;}flag=1;}//���ǰ�治�����֣�ֱ�Ӵ�Ž�����ջ
      }
      else if(str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/'||str[i]=='('||str[i]==')')//��ʼ�ж��ַ�
      {
          flag=0;//��ʾ��һ������һ������
          if(str[i]==')')//�����Ų������ȼ��Ƚϣ���ȡ�������ǰ���������
          {
              c=popCharStack(&s2);
              count--;
              while(c!='(')//�����������ջ��Ԫ��������ջ��Ԫ�ؽ����������㣬ֱ������������
              {
                  if(!getTwoNum(&s1,&num1,&num2)) printf("����\n");
                  num=calculate(num1,num2,c);
                  if(!pushIntStack(&s1,num)) printf("��ջ����\n");
                  c=popCharStack(&s2);
              }
              c=getCharTop(&s2);//��������ջ��Ԫ�ص����ȼ�
              pro=priority(c);
          }
          else if(pro>priority(str[i]))//��ʼ�ж����ȼ�
          {
              while(pro>priority(str[i])&&getCharTop(&s2)!='(')//���������ţ����ȼ���ջ��Ԫ�ص͵� ���ǰ�����ȼ������ߵķ���
              {                                                //�����������ջһ�������������
                  c=popCharStack(&s2);
                  if(!getTwoNum(&s1,&num1,&num2)) printf("����\n");
                  num=calculate(num1,num2,c);
                  if(!pushIntStack(&s1,num)) printf("��ջ����\n");
              }
              if(getCharTop(&s2)=='(') count++;
              if(!pushCharStack(&s2,str[i])) printf("��ջʧ�ܣ�\n");
              c=getCharTop(&s2);//����ջ��Ԫ�����ȼ�
              pro=priority(c);
          }
          else
            {
                if(!pushCharStack(&s2,str[i])) printf("��ջʧ�ܣ�\n");//������ȼ���ջ��Ԫ�ظߣ���ֱ�ӽ�ջ
                c=getCharTop(&s2);
                pro=priority(c);
            }
      }
      else {printf("������ı��ʽ���зǷ��ַ���\n");return 0;}//��������з�����������ַ�,ֱ���˳�
  }
  while(stackLength(&s2))//ʣ�µ��ַ�ջ����ַ�˳�����������ջ��������������
    {
       c=popCharStack(&s2);
       if(!getTwoNum(&s1,&num1,&num2)) printf("��������\n");
       num=calculate(num1,num2,c);
       if(!pushIntStack(&s1,num)) printf("��ջ����\n");
    }
  printf("%d",getTopStack(&s1));//����������ջ��ջ��Ԫ��
  return 0;
}






















