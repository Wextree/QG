#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef enum Status //����ö�����ͳ���
{
    ERROR = 0,SUCCESS = 1
}Status;

typedef struct intSqStack{ //����һ������ջ
       int	*elem;
       int top;
       int size;
}intSqStack;

typedef struct charSqStack{  //����һ���ַ�ջ
       char	*elem;
       int top;
       int size;
}charSqStack;

int priority(char c);
Status initIntStack(intSqStack *s1,int sizes);
Status initCharStack(charSqStack *s2,int sizes);
int getTopStack(intSqStack *s1);
Status changeTop(intSqStack *s1,int num);                   //���Ƕ�Ҫʹ�õĺ�����ͷ�ļ���������
Status pushIntStack(intSqStack *s1,int num);
Status pushCharStack(charSqStack *s2,char c);
char getCharTop(charSqStack *s1);                           //���幦����fun.c�ļ������˵��
Status changeCharTop(charSqStack *s2,char c);
Status getTwoNum(intSqStack *s1,int *num1,int *num2);
int calculate(int num1,int num2,char c);
char popCharStack(charSqStack *s2);
int stackLength(charSqStack *s2);

#endif
