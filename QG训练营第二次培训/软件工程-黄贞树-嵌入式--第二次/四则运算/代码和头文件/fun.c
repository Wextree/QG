#include <stdio.h>
#include <stdlib.h>
#include "calculate.h"

int priority(char c)// 判定四则运算字符的优先级
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

Status initIntStack(intSqStack *s1,int sizes)//初始化数字栈
{
    s1->elem=(int*)malloc(sizeof(int)*sizes);//为栈里面的数据申请内存
    if(NULL==s1->elem)//判断内存是否足够
        return ERROR;
    s1->size=sizes;
    s1->top=-1; //栈顶指针赋值为空
  return SUCCESS;
}

Status initCharStack(charSqStack *s2,int sizes)//建立一个字符栈
{
    s2->elem=(char*)malloc(sizeof(char)*sizes);//为栈里面的数据申请内存
    if(NULL==s2->elem)//判断内存是否足够
        return ERROR;
    s2->size=sizes;
    s2->top=-1; //栈顶指针赋值为空
  return SUCCESS;
}

int getTopStack(intSqStack *s1)//获得数字栈的栈顶元素
{
    return (*(s1->elem+s1->top));
}

Status changeTop(intSqStack *s1,int num)//更换数字栈的栈顶元素
{
    if(s1==NULL) return ERROR;
    *(s1->elem+s1->top)=num;
    return SUCCESS;
}

Status pushIntStack(intSqStack *s1,int num)  //数字栈入栈
{
   if(s1==NULL)//判断是否传下来一个空指针
    return ERROR;
    if(s1->top==s1->size-1)
    {printf("栈满了！\n");return ERROR;}
    s1->top++;
    *(s1->elem+s1->top)=num;
    return SUCCESS;
}

Status pushCharStack(charSqStack *s2,char c)  //字符栈入栈
{
   if(s2==NULL)//判断是否传下来一个空指针
    return ERROR;
    if(s2->top==s2->size-1)
    {printf("栈满了！\n");return ERROR;}
    s2->top++;
    *(s2->elem+s2->top)=c;
    return SUCCESS;
}

char getCharTop(charSqStack *s2)//获得字符栈的栈顶元素
{
    return (*(s2->elem+s2->top));
}

Status changeCharTop(charSqStack *s2,char c)//更换字符栈的栈顶元素
{
    if(s2==NULL) return ERROR;
    *(s2->elem+s2->top)=c;
    return SUCCESS;
}

Status getTwoNum(intSqStack *s1,int *num1,int *num2)//提取数字栈的前两个数字
{
    if(s1==NULL) return ERROR;
    *num1=*(s1->elem+s1->top);
    *num2=*(s1->elem+(s1->top-1));
    s1->top-=2;
    return SUCCESS;
}

int calculate(int num1,int num2,char c)//两数进行四则运算
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

char popCharStack(charSqStack *s2)//出字符栈的栈顶元素
{
  int c=*(s2->elem+s2->top);
  s2->top--;
  return c;
}

 int stackLength(charSqStack *s2)//检测字符栈的长度
{
    return s2->top+1;
}
































