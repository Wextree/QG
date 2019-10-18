#include <stdio.h>
#include "stack.h"
#include <stdlib.h>
#include "stack.c"
int main()
{
  int length=0,ch1=0,ch2=0;//定义需要使用的变量
  ElemType datas,e;
  printf("请输入你要创建的栈类型：1.顺序栈 2.链栈\n");
  scanf("%d",&ch1);
while(1)
{
    if(!scanf("%d",&ch1)||!(ch1==1||ch1==2))
        {getchar();printf("你输入的数字有误！\n");}
    else break;
}
  if(ch1==1)//开始建立一个顺序栈
  {
      SqStack s;//定义一个变量用于初始化顺序栈
      int sizes;
      printf("请输入栈的大小：\n");
      scanf("%d",&sizes);//输入栈的大小
      if(initStack(&s,sizes))
        printf("创建成功。\n");
      else {printf("创建失败，请查看内存是否足够。");return 0;}
      printf("--------------------------------------------------------------------------\n");//用switch来进行用户的选择
      printf("1.判断空栈 2.获取栈顶值 3.检测栈长 4.入栈 5.出栈 6.清空栈 7.销毁栈 0.退出\n");
      printf("--------------------------------------------------------------------------\n");
      scanf("%d",&ch2);
      while(ch2)//选择不同的功能来实现不同的函数
      {

       switch(ch2)
       {
           case 1:if(isEmptyStack(&s)) printf("这是一个非空栈。\n");
                    else printf("这是一个空栈。\n");break;
           case 2:if(getTopStack(&s,&e)) printf("栈顶值为%d\n",e);
                          else printf("申请内存错误或者为空栈。\n");break;
           case 3:if(stackLength(&s,&length)) printf("栈长为%d\n",length);
                               else printf("申请内存错误或者是空栈。\n");break;
           case 4:printf("请输入你要入栈的值：\n");
                    scanf("%d",&datas);
                    if(pushStack(&s,datas)) printf("入栈成功！\n");
                    else printf("入栈失败！\n");break;
           case 5:if(popStack(&s,&datas)) printf("出栈成功，被出栈的值为%d\n",datas);
                              else printf("出栈失败，可能是空栈或者申请内存失败！\n");break;
           case 6:if(clearStack(&s)) printf("清空成功！\n");
                    else printf("清空失败。\n");break;
           case 7:if(destoryStack(&s)) printf("摧毁成功。\n");
                    else printf("摧毁失败！\n");break;
           default:printf("该选项不存在，请重新输入！！！\n\n");break;

       }
       printf("--------------------------------------------------------------------------\n");//放在循环里面可不断地执行功能
       printf("1.判断空栈 2.获取栈顶值 3.检测栈长 4.入栈 5.出栈 6.清空栈 7.销毁栈 0.退出\n");
       printf("--------------------------------------------------------------------------\n");
       scanf("%d",&ch2);
      }
  }
  else//开始建立链栈
  {
      LinkStack s;//申请内存;
      if(initLStack(&s))
        printf("创建成功。\n");
      else {printf("创建失败，请查看内存是否足够。");return 0;}
      printf("--------------------------------------------------------------------------\n");
      printf("1.判断空栈 2.获取栈顶值 3.检测栈长 4.入栈 5.出栈 6.清空栈 7.销毁栈 0.退出\n");
      printf("--------------------------------------------------------------------------\n");
      scanf("%d",&ch2);
      while(ch2)                                         //剩下的与上面的相同
      {
          switch(ch2)
          {
           case 1:if(isEmptyLStack(&s)) printf("这是一个非空栈。\n");
                    else printf("这是一个空栈。\n");break;
           case 2:if(getTopLStack(&s,&e)) printf("栈顶值为%d\n",e);
                          else printf("申请内存错误或者为空栈。\n");break;
           case 3:if(LStackLength(&s,&length)) printf("栈长为%d\n",length);
                               else printf("申请内存错误或者是空栈。\n");break;
           case 4:printf("请输入你要入栈的值：\n");
                    scanf("%d",&datas);
                    if(pushLStack(&s,datas)) printf("入栈成功！\n");
                    else printf("申请内存可能失败。\n");break;
           case 5:if(popLStack(&s,&datas)) printf("出栈成功，被出栈的值为%d\n",datas);
                              else printf("出栈失败，可能是空栈或者申请内存失败！\n");break;
           case 6:if(clearLStack(&s)) printf("清空成功！\n");
                    else printf("清空失败。\n");break;
           case 7:if(destoryLStack(&s)) printf("摧毁成功。\n");
                    else printf("摧毁失败！\n");break;
           default:printf("该选项不存在，请重新输入！！！\n\n");break;
          }
       printf("--------------------------------------------------------------------------\n");
       printf("1.判断空栈 2.获取栈顶值 3.检测栈长 4.入栈 5.出栈 6.清空栈 7.销毁栈 0.退出\n");
       printf("--------------------------------------------------------------------------\n");
       scanf("%d",&ch2);
      }
  }
  return 0;
}
