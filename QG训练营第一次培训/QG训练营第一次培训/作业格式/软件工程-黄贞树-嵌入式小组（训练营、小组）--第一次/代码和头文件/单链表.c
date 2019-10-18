#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{ int data;
  struct Node *next;
}Node, *ptr_Node;

typedef enum Status
{
	SUCCESS,
	ERROR
}Status;

//根据数组生成一条链表，成功则返回头节点，失败返回 NULL
ptr_Node create(int *arr, int n)
{
  int i=0;   //可自增控制循环并且作为数组的下标
  ptr_Node p,q;//辅助创建链表空间
  ptr_Node head;//存放创建的链表的头结点
  head=NULL;//保护一开始的结点
  p=q=(Node*)malloc(sizeof(Node));// 开始申请内存空间
  p->data=*arr;// 赋第一个数组的值
  while(i<n-1)//开始进行赋值并且创建新的空间的循环
  {
      i++;
      if(i==1)//分类讨论
      head=p;//给头结点赋值
      else q->next=p;// 结点间的指针链接
      q=p;
      p=(Node*)malloc(sizeof(Node));//申请新的内存
      p->data=*(arr+i);//进行对应的赋值
  }
  q->next=p;
  p->next=NULL;//结尾指针指向NULL
  return head;//返回头结点
}
//销毁给定的链表
void destroy(ptr_Node head)
{
	ptr_Node p,q;
	p=head;//拷贝头结点的指针
	while(p)//循环直到最后结点
	{
	    q=p->next;//结点往后移
	    free(p);//释放内存
	    p=q;
	}
}

//在第 index 位后面插入 node 结点
//插入成功返回 SUCCESS，失败返回 ERROR
Status insert(ptr_Node *head, ptr_Node node, int index)
{
	int i=0;
	ptr_Node cur,pre;//定义一个指向现在和之前的指针
	cur=*head;//赋值头结点
	pre=NULL;//赋空指针
	while(cur&&i<index)//寻找所要的结点位置
    {
        pre=cur;//更新之前的结点
        cur=cur->next;//结点往后移动
        ++i;
    }
    if(!cur||i>index)//判断是否找得到那个结点
        return ERROR;
    node->next=cur;//新增结点的指针指向现在的那个指针
    if(pre==NULL)//判断是插入头结点的位置
        *head=node;//直接把新增的结点赋值给head
    else
        pre->next=node;//如果不是插入头结点的一般操作
    return SUCCESS;
}

//删除第 index 位节点后面的节点，将删除的结点的值保存到（*data）中
//删除成功返回 SUCCESS，其他情况返回 ERROR
Status delete(ptr_Node *head, int index, int *data)
{
	int i=0;
	ptr_Node cur,pre;//定义一个指向现在和之前的指针
	cur=*head;//赋值头结点
	pre=NULL;//赋空指针
    while(cur&&i<index)//寻找所要的结点位置
    {
        pre=cur;//更新之前的结点
        cur=cur->next;//结点往后移动
        ++i;
    }
    if(!cur||i>index)//判断是否找得到那个结点
        return ERROR;
    if(pre==NULL)//判断是删除头结点的位置
        *head=cur->next;
    else//如果不是头结点的一般操作
        pre->next=cur->next;
    *data=cur->data;//删除的那个值保存下来
    free(cur);//释放删除结点的内存
    return SUCCESS;
}


//在链表中查找节点值与 data 相等的节点，并返回找到的第一个节点的前一个节点的位置
//（例：头节点相等，返回 0），没找到或者其他情况返回-1
int search(ptr_Node head, int data)
{
	int i=1;
	ptr_Node p;
	p=head;//定义的指针p指向头结点
	while (p)//找寻所给值相等的那个结点结点
    {
        if(p->data==data)//找到就直接退出循环
            break;
        p=p->next;//如果没有找到就继续找寻后面的结点
        i++;
    }
    if(i==1)//判断是头结点的位置
        return 0;
    else if(p)
        return i-1;//返回找到的那个位置的前一个结点的位置
    else  return -1;//如果找不到就返回-1
}


//将链表中 index 位点后面的结点的值修改为(*data)，将原值保存到(*data)
//修改成功返回 SUCCESS，其他情况返回 ERROR
Status edit(ptr_Node head,int index,int *data)
{
   int i,temp;//定义一个计数和一个用来代替的值
   i=1;
   ptr_Node p;
   p=head;//定义的一个指针用来指向头结点
   while(p->next&&i<index)//寻找所要更换数值的那个位置
   {
       p=p->next;
       i++;
   }
   if(!(p->next)||i>index)//判断是否找得到
    return ERROR;
   temp=p->next->data;//以下三行为交换值
   p->next->data=*data;
   *data=temp;//将更换的值存放在data里
   return SUCCESS;
}
//此题选做,实现单链表按照节点值大小升序排序
Status sort(ptr_Node *head)
{
  if(!head)//判断是否穿传下来一个空指针
    return ERROR;                                                                                        //改了很多次，现在不会说直接程序不能运行
  ptr_Node p,q;
  int temp;                                                                                              //但是现在一直输出一个不知道是什么的符号
  for(p=*head;(p->next)!=NULL;p=p->next)//第一个循环从第一个结点的值开始与下面的其他值进行比较
  {
    for(q=p->next;q!=NULL;q=q->next)//循环第一个循环p后面的剩下结点的值
  {
      if(p->data>q->data)//进行值的大小的比较
      {
          temp=p->data;//以下三行市进行值的交换
          p->data=q->data;
          q->data=temp;
      }
  }
  }
  return SUCCESS;
}

//将链表结点值按照一定的格式输出（每行多少个自己定义，格式越漂亮越好）
void print(ptr_Node head)
{
  int i;//计数来排版输出的数
  ptr_Node p;
  p=head;
  printf("print this Linklist:\n");
  for(i=1;p!=NULL;i++)
  {
      printf("%6d",p->data);//输出对应结点的值
      if(i%4==0)//每四个值就换行
        printf("\n");
      p=p->next;
  }
}

int main()
{
     int i,n,len,choose,index,data;//定义各种所需要的变量
     printf("首先你需要创建一个链表.\n");//先让用户创建一个新的链表以便进行各种操作
     printf("请输入所需链表的长度：");
     scanf("%d",&n);
     printf("\n");
     int arr[n];
     printf("请输入链表每个结点对应的值（两个值之间用空格分开）：\n");
     for(i=0;i<n;i++)//输入数组的值
     {
         scanf("%d",&arr[i]);
     }
     ptr_Node head;//定义一个指针存放头结点
     head=create(arr, n);
     print(head);
     printf("\n");
     printf("---------------------------------------------------------------\n");//提示对方进行各种操作
     printf("1.插入结点 2.删除结点 3.寻找结点 4.编辑结点 5.排序结点 0.退出\n");
     printf("---------------------------------------------------------------\n");
     scanf("%d",&choose);//输入序号对应功能
     while(choose)//此循环让用户可以多次使用功能
    {
     switch(choose)//使用多选择函数功能分类，实现交互
     {
        case 1:printf("输入一个位置及你要插入的值（中间用空格分开）：\n");
               scanf("%d %d",&index,&data);
               ptr_Node node=(Node*)malloc(sizeof(Node));
               node->data=data;
               node->next=NULL;
               if(insert(&head,node,index)) printf("请检查输入的信息是否有误并重新输入\n");
               else print(head);printf("\n");break;
        case 2:printf("请输入你要删除的位置：\n");
               scanf("%d",&index);
               if(delete(&head,index,&data)) printf("请检查输入的信息是否有误并重新输入\n");
               else print(head);printf("\n");break;
        case 3:printf("请输入你要查找的结点的值：\n");
               scanf("%d",&data);
               printf("你要查找的值的位置在%d（0表示在头结点，-1表示找不到）",search(head,data));
               printf("\n");break;
        case 4:printf("请输入你要编辑的结点的位置和值（中间用空格分开）：\n");
               scanf("%d %d",&index,&data);
               if(edit(head,index,&data)) printf("请检查输入的信息是否有误并重新输入\n");
               else print(head);printf("\n");break;
        case 5:if(sort(&head)) printf("请检查输入的信息是否有误并重新输入\n");
               else print(head);printf("\n");break;
        default:printf("该选项不存在，请重新输入！！！\n\n");break;
     }
    printf("---------------------------------------------------------------\n");
     printf("1.插入结点 2.删除结点 3.寻找结点 4.编辑结点 5.排序结点 0.退出\n");
     printf("---------------------------------------------------------------\n");
     scanf("%d",&choose);
     }
     destroy(head);//函数使用完对申请的空间进行销毁
     return 0;
}
