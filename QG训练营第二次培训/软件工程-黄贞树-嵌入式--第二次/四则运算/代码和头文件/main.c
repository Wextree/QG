#include <stdio.h>
#include <stdlib.h>
#include "calculate.h"

int main()
{
  char str[100];char c;//定义一个字符串数组存放表达式
  int i,flag=0,num,num1,num2,count=0,pro=0,sizes=100;
  intSqStack s1;//定义两个变量去初始化两个栈
  charSqStack s2;
  if(initIntStack(&s1,sizes))//开始创建两个栈
  printf("数字栈创建成功\n");
  else printf("数字栈创建失败！\n");
  if(initCharStack(&s2,sizes))
  printf("字符栈创建成功\n");
  else printf("字符栈创建失败！！\n");
  printf("请输入你想要计算的表达式：\n");
  scanf("%s",str);//输入表达式
  for(i=0;str[i]!='\0';i++)//遍历输入的字符串
  {
      if(str[i]>='0'&&str[i]<='9')//判断是否是数字
      {
          if(flag==1)//如果前面的那个也是数字的话，提取数字栈的栈顶元素合并后再重新存放
          {
                num=getTopStack(&s1);num=num*10+(str[i]-'0');
                if(!changeTop(&s1,num)) {printf("更换失败！\n");return 0;}
          }
          else {num=str[i]-'0';if(!pushIntStack(&s1,num)) {printf("入栈失败！\n");return 0;}flag=1;}//如果前面不是数字，直接存放进数字栈
      }
      else if(str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/'||str[i]=='('||str[i]==')')//开始判断字符
      {
          flag=0;//表示这一个不是一个数字
          if(str[i]==')')//右括号不做优先级比较，提取出来配对前面的左括号
          {
              c=popCharStack(&s2);
              count--;
              while(c!='(')//不断输出符号栈的元素与数字栈的元素进行四则运算，直到遇到左括号
              {
                  if(!getTwoNum(&s1,&num1,&num2)) printf("错误！\n");
                  num=calculate(num1,num2,c);
                  if(!pushIntStack(&s1,num)) printf("入栈错误！\n");
                  c=popCharStack(&s2);
              }
              c=getCharTop(&s2);//更新现在栈顶元素的优先级
              pro=priority(c);
          }
          else if(pro>priority(str[i]))//开始判断优先级
          {
              while(pro>priority(str[i])&&getCharTop(&s2)!='(')//除了左括号，优先级比栈顶元素低的 输出前面优先级比它高的符号
              {                                                //并且输出数字栈一起进行四则运算
                  c=popCharStack(&s2);
                  if(!getTwoNum(&s1,&num1,&num2)) printf("错误！\n");
                  num=calculate(num1,num2,c);
                  if(!pushIntStack(&s1,num)) printf("入栈错误！\n");
              }
              if(getCharTop(&s2)=='(') count++;
              if(!pushCharStack(&s2,str[i])) printf("入栈失败！\n");
              c=getCharTop(&s2);//更新栈顶元素优先级
              pro=priority(c);
          }
          else
            {
                if(!pushCharStack(&s2,str[i])) printf("入栈失败！\n");//如果优先级比栈顶元素高，就直接进栈
                c=getCharTop(&s2);
                pro=priority(c);
            }
      }
      else {printf("你输入的表达式里有非法字符！\n");return 0;}//如果里面有非四则运算的字符,直接退出
  }
  while(stackLength(&s2))//剩下的字符栈里的字符顺序出来与数字栈的数字四则运算
    {
       c=popCharStack(&s2);
       if(!getTwoNum(&s1,&num1,&num2)) printf("交换错误！\n");
       num=calculate(num1,num2,c);
       if(!pushIntStack(&s1,num)) printf("入栈错误！\n");
    }
  printf("%d",getTopStack(&s1));//最后输出数字栈的栈顶元素
  return 0;
}






















