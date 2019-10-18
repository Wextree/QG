#include<stdio.h>
#include<stdlib.h>

typedef struct TNode
{
	int data;
	struct TNode *next;
	struct TNode *pre;
}TNode, *ptr_TNode;

typedef enum Status
{
	SUCCESS,
	ERROR
}Status;

//根据数组生成一条双向链表，成功则返回头节点，失败返回 NULL
ptr_TNode create(int *arr, int n)
{
  int i=0;
  ptr_TNode p,q;
  ptr_TNode head;
  head=NULL;
  p=q=(TNode*)malloc(sizeof(TNode));
  p->data=*arr;
  while(i<n-1)
  {
      i++;
      if(i==1)
      {
          head=p;
          p->pre=NULL;
      }
      else {q->next=p;p->pre=q;}
      q=p;
      p=(TNode*)malloc(sizeof(TNode));
      p->data=*(arr+i);
  }
  q->next=p;
  p->pre=q;
  p->next=NULL;
  return head;
}

//双向链表,删除第 index 位节点后面的节点，将删除的结点的值保存到（*data）中
Status delete_T(ptr_TNode *head, int index, int *data)
{
  	int i=1;
	ptr_TNode p,q;
	p=*head;
	if(index==1)
        {*head=p->next;
        p->next->pre=NULL;
        return SUCCESS;}
	while(p->next&&i<index)
    {
        p=p->next;
        ++i;
    }
    if(!(p->next)||i>index)
        return ERROR;
    q=p->next;
    p->next=q->next;
    q->next->pre=p;
    data=&(q->data);
    free(q);
    return SUCCESS;
}
//双向链表,在第 index 位后面插入 node 结点
//插入成功返回 SUCCESS，失败返回 ERROR
Status insert_T(ptr_TNode *head, ptr_TNode node, int index)
{
  	int i=1;
	ptr_TNode p;
	p=*head;
	if(index==0)
    {
        node->next=p;
        *head=node;
        node->pre=NULL;
        return SUCCESS;
    }
	while(p&&i<index)
    {
        p=p->next;
        ++i;
    }
    if(!p||i>index)
        return ERROR;
    node->next=p->next;
    node->pre=p;
    p->next=node;
    p->next->pre=node;
    return SUCCESS;
}
//销毁给定的链表
void destroy(ptr_TNode head)
{
  	ptr_TNode p,q;
	p=head;
	while(p)
	{
	    q=p->next;
	    free(p);
	    p=q;
	}
}
//将链表结点值按照一定的格式输出（每行多少个自己定义，格式越漂亮越好）
void print(ptr_TNode head)
{
  int i;
  ptr_TNode p;
  p=head;
  printf("printf this Linklist:\n");
  for(i=1;p!=NULL;i++)
  {
      printf("%6d",p->data);
      if(i%4==0)
        printf("\n");
      p=p->next;
  }
}

int main()
{
    int n,i;
	printf("How many numbers do you want?\n");
	scanf("%d",&n);
	int arr[n];
	printf("Please write down your numbers\n");
	for(i=0;i<n;i++)
    scanf("%d",&arr[i]);
    ptr_TNode node,head;
    head=create(arr,n);
    print(head);
    int index;
     printf("give me a index\n");
     scanf("%d",&index);
     node=(TNode*)malloc(sizeof(TNode));
     printf("give me a data of node\n");
     scanf("%d",&node->data);
     printf("insert return %d\n",insert_T(&head,node,index));
     print(head);
     int *data=NULL;
     printf("\n");
     printf("Please write a new index to delete:\n");
     scanf("%d",&index);
     printf("delete return %d\n",delete_T(&head,index,data));
     print(head);
     getchar();
     destroy(head);
	return 0;
}
