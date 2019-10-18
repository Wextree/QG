#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef enum Status //定义枚举类型常量
{
    ERROR = 0,SUCCESS = 1
}Status;

typedef struct intSqStack{ //定义一个数字栈
       int	*elem;
       int top;
       int size;
}intSqStack;

typedef struct charSqStack{  //定义一个字符栈
       char	*elem;
       int top;
       int size;
}charSqStack;

int priority(char c);
Status initIntStack(intSqStack *s1,int sizes);
Status initCharStack(charSqStack *s2,int sizes);
int getTopStack(intSqStack *s1);
Status changeTop(intSqStack *s1,int num);                   //这是对要使用的函数在头文件里面声明
Status pushIntStack(intSqStack *s1,int num);
Status pushCharStack(charSqStack *s2,char c);
char getCharTop(charSqStack *s1);                           //具体功能在fun.c文件里会有说明
Status changeCharTop(charSqStack *s2,char c);
Status getTwoNum(intSqStack *s1,int *num1,int *num2);
int calculate(int num1,int num2,char c);
char popCharStack(charSqStack *s2);
int stackLength(charSqStack *s2);

#endif
