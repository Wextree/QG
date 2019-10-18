#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef int Elemtype;
int main()
{
    printf("请输入你要建立的队列类型：1.循环队列 2.链式队列\n");
    int ch1,ch2;
    Elemtype *e;void *data;
    scanf("%d",&ch1);
    if(!(ch1==1||ch1==2))
    {
        printf("你输入的数字有误！\n");
        scanf("%d",&ch1);
    }
    if(ch1==1)//开始建立一个循环队列
  {
      AQueue Q;//定义一个变量用于初始化循环队列
      InitAQueue(&Q);
      printf("--------------------------------------------------------------------------------------\n");//用switch来进行用户的选择
      printf("1.判断空队列 2.判断队满 3.获取队头 4.检测栈长 5.入队 6.出队 7.清空队 8.输出队列 0.退出\n");
      printf("--------------------------------------------------------------------------------------\n");
      scanf("%d",&ch2);
      while(ch2)//选择不同的功能来实现不同的函数
      {

       switch(ch2)
       {
           case 1:if(IsEmptyAQueue(&Q)) printf("这是一个空队列。\n");
                    else printf("这是一个非空队列。\n");break;
           case 2:if(IsFullAQueue(&Q)) printf("队列已满！\n");
                    else printf("队列还没满！\n");
           case 3:if(GetHeadAQueue(&Q,&e)) printf("队首值为%d\n",*e);
                          else printf("这是一个空队列。\n");break;
           case 4:printf("队列长为%d\n",LengthAQueue(&Q));break;
           case 5:printf("请输入你要入队的值：\n");data=(Elemtype*)malloc(sizeof(Elemtype));
                    scanf("%d",data);
                    if(EnAQueue(&Q,data)) printf("入队成功！\n");
                    else printf("入队失败！\n");break;
           case 6:if(DeAQueue(&Q)) printf("出队成功!\n");
                     else printf("出队失败，可能是空队！\n");break;
           case 7:ClearAQueue(&Q);break;
           case 8:if(TraverseAQueue(&Q,APrint)) printf("输出完成！\n");
                     else printf("可能为空！\n");break;
           default:printf("该选项不存在，请重新输入！！！\n\n");break;

       }
       printf("---------------------------------------------------------------------------------------\n");//放在循环里面可不断地执行功能
       printf("1.判断空队列 2.判断队满 3.获取队头 4.检测栈长 5.入队 6.出队 7.清空队  8.输出队列 0.退出\n");
       printf("---------------------------------------------------------------------------------------\n");
       scanf("%d",&ch2);
      }
  }
  else//开始建立链式队列
  {
      LQueue Q;//申请内存;
      InitLQueue(&Q);
      printf("--------------------------------------------------------------------------------------\n");
      printf("1.判断空队列 2.获取队头 3.检测栈长 4.入队 5.出队 6.清空队 7.输出队列 8.摧毁队列 0.退出\n");
      printf("--------------------------------------------------------------------------------------\n");
      scanf("%d",&ch2);
      while(ch2)                                         //剩下的与上面的相同
      {
          switch(ch2)
          {
           case 1:if(IsEmptyLQueue(&Q)) printf("这是一个空队列。\n");
                    else printf("这是一个非空队列。\n");break;
           case 2:if(GetHeadLQueue(&Q,&e)) printf("队首值为%d\n",*e);
                          else printf("为空队列！\n");break;
           case 3:printf("栈长为%d\n",LengthLQueue(&Q));break;
           case 4:printf("请输入你要入队的值：\n");data=(Elemtype*)malloc(sizeof(Elemtype));
                    scanf("%d",data);
                    if(EnLQueue(&Q,data)) printf("入队成功！\n");
                    else printf("可能队满！\n");break;
           case 5:if(DeLQueue(&Q)) printf("出队成功!");
                    else printf("出队失败，可能是空队列！\n");break;
           case 6:ClearLQueue(&Q); break;
           case 7:if(TraverseLQueue(&Q,LPrint)) printf("输出完成。\n");
                     else printf("可能为空！\n");break;
           case 8:DestoryLQueue(&Q);break;
           default:printf("该选项不存在，请重新输入！！！\n\n");break;
          }
       printf("--------------------------------------------------------------------------------------\n");
       printf("1.判断空队列 2.获取队头 3.检测栈长 4.入队 5.出队 6.清空队 7.输出队列 8.摧毁队列 0.退出\n");
       printf("--------------------------------------------------------------------------------------\n");
       scanf("%d",&ch2);
      }
  }
}
