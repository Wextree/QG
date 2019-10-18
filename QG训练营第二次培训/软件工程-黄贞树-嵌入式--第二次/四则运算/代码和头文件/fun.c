#include <stdio.h>
#include <stdlib.h>
#include "calculate.h"

int priority(char c)// �ж����������ַ������ȼ�
{
    switch(c)
    {
      case '(':return 3;
      case '*':
      case '/':return 2;
      case '-':
      case '+':return 1;
      default:break;
    }
}

Status initIntStack(intSqStack *s1,int sizes)//��ʼ������ջ
{
    s1->elem=(int*)malloc(sizeof(int)*sizes);//Ϊջ��������������ڴ�
    if(NULL==s1->elem)//�ж��ڴ��Ƿ��㹻
        return ERROR;
    s1->size=sizes;
    s1->top=-1; //ջ��ָ�븳ֵΪ��
  return SUCCESS;
}

Status initCharStack(charSqStack *s2,int sizes)//����һ���ַ�ջ
{
    s2->elem=(char*)malloc(sizeof(char)*sizes);//Ϊջ��������������ڴ�
    if(NULL==s2->elem)//�ж��ڴ��Ƿ��㹻
        return ERROR;
    s2->size=sizes;
    s2->top=-1; //ջ��ָ�븳ֵΪ��
  return SUCCESS;
}

int getTopStack(intSqStack *s1)//�������ջ��ջ��Ԫ��
{
    return (*(s1->elem+s1->top));
}

Status changeTop(intSqStack *s1,int num)//��������ջ��ջ��Ԫ��
{
    if(s1==NULL) return ERROR;
    *(s1->elem+s1->top)=num;
    return SUCCESS;
}

Status pushIntStack(intSqStack *s1,int num)  //����ջ��ջ
{
   if(s1==NULL)//�ж��Ƿ�����һ����ָ��
    return ERROR;
    if(s1->top==s1->size-1)
    {printf("ջ���ˣ�\n");return ERROR;}
    s1->top++;
    *(s1->elem+s1->top)=num;
    return SUCCESS;
}

Status pushCharStack(charSqStack *s2,char c)  //�ַ�ջ��ջ
{
   if(s2==NULL)//�ж��Ƿ�����һ����ָ��
    return ERROR;
    if(s2->top==s2->size-1)
    {printf("ջ���ˣ�\n");return ERROR;}
    s2->top++;
    *(s2->elem+s2->top)=c;
    return SUCCESS;
}

char getCharTop(charSqStack *s2)//����ַ�ջ��ջ��Ԫ��
{
    return (*(s2->elem+s2->top));
}

Status changeCharTop(charSqStack *s2,char c)//�����ַ�ջ��ջ��Ԫ��
{
    if(s2==NULL) return ERROR;
    *(s2->elem+s2->top)=c;
    return SUCCESS;
}

Status getTwoNum(intSqStack *s1,int *num1,int *num2)//��ȡ����ջ��ǰ��������
{
    if(s1==NULL) return ERROR;
    *num1=*(s1->elem+s1->top);
    *num2=*(s1->elem+(s1->top-1));
    s1->top-=2;
    return SUCCESS;
}

int calculate(int num1,int num2,char c)//����������������
{
    switch(c)
    {
      case '*':return num1*num2;
      case '/':return num2/num1;
      case '-':return num2-num1;
      case '+':return num1+num2;
      default:break;
    }
}

char popCharStack(charSqStack *s2)//���ַ�ջ��ջ��Ԫ��
{
  int c=*(s2->elem+s2->top);
  s2->top--;
  return c;
}

 int stackLength(charSqStack *s2)//����ַ�ջ�ĳ���
{
    return s2->top+1;
}
































