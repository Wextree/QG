#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

//循环队列
void InitAQueue(AQueue *Q)
{
    Q->front=0;
    Q->rear=0;
}

/*void DestoryAQueue(AQueue *Q)
{
    if(Q==NULL) return FALSE;
    Q->front=0;
    Q->rear=0;
    return TRUE;
}*/

Status IsFullAQueue(const AQueue *Q)
{
  if((Q->rear+1)%MAXQUEUE==Q->front)
    return TRUE;
  else return FALSE;
}

Status IsEmptyAQueue(const AQueue *Q)
{
  if(Q->front==Q->rear)
    return TRUE;
  else return FALSE;
}

Status GetHeadAQueue(AQueue *Q, void *e)
{
  if(IsEmptyAQueue(Q)) return FALSE;
  *(void**)e=(void*)(Q->data[Q->front]);
  return TRUE;
}

int LengthAQueue(AQueue *Q)
{
    if(Q->front>Q->rear)
    return (Q->rear-Q->front+MAXQUEUE);
    else return (Q->rear-Q->front);
}

Status EnAQueue(AQueue *Q, void *data)
{
   if(IsFullAQueue(Q)) return FALSE;
   else
    {
        (Q->data)[Q->rear]=data;
        Q->rear=(Q->rear+1)%MAXQUEUE;
        return TRUE;
    }
}

Status DeAQueue(AQueue *Q)
{
  if(IsEmptyAQueue(Q)) return FALSE;
  void *p=Q->front;
  Q->front=(Q->front+1)%MAXQUEUE;
  free(p);
  return TRUE;
}

void ClearAQueue(AQueue *Q)
{
    Q->front=0;
    Q->rear=0;
}


Status TraverseAQueue(const AQueue *Q, void (*f)(void *q))
{
  if(Q==NULL) return FALSE;
  int i;void *p;
  printf("输出如下：\n");
  for(i=Q->front;i!=Q->rear;i++)
  {
      p=(void*)(Q->data[i]);
      f(p);
      i=i%MAXQUEUE;
  }
  printf("\n");
  return TRUE;
}
void APrint(void *q)
{
  printf("  %d",*(int*)q);
}
//链式队列
void InitLQueue(LQueue *Q)
{
  Q->front=Q->rear=(Node*)malloc(sizeof(Node));
  Q->front->next=Q->rear->next=NULL;
}

void DestoryLQueue(LQueue *Q)
{
  Node *p;
  p=Q->front;
      while(p)
      {
          Q->front=Q->front->next;
          free(p);
          p=Q->front;
      }
      Q->rear=NULL;
}

Status IsEmptyLQueue(const LQueue *Q)
{
  if(Q->front==Q->rear)
    return TRUE;
  else return FALSE;
}

Status GetHeadLQueue(LQueue *Q, void *e)
{
  if(IsEmptyLQueue(Q)) return FALSE;
  *(void**)e=(void*)(Q->front->next->data); return TRUE;
}

int LengthLQueue(LQueue *Q)
{
  int len=0;
  Node *p=Q->front->next;
  while(p)
  {
      p=p->next;
      len++;
  }
  return len;
}

Status EnLQueue(LQueue *Q, void *data)
{
  Node *s=(Node*)malloc(sizeof(Node));
  if(!s) return FALSE;
  s->data=data;
  s->next=NULL;
  Q->rear->next=s;
  Q->rear=s;
  return TRUE;
}

Status DeLQueue(LQueue *Q)
{
  if(IsEmptyLQueue(Q)) return FALSE;
  Node *p=Q->front->next;
  Q->front->next=p->next;
  if(Q->rear==p) Q->rear=Q->front;
  free(p);
  return TRUE;
}

void ClearLQueue(LQueue *Q)
{
  Node *p=Q->front->next;
  Node *q=p;
  if(Q->front!=Q->rear)
  {
      while(p)
      {
          p=q->next;
          free(q);
          q=p;
      }
      Q->rear=Q->front;;
  }
}

Status TraverseLQueue(const LQueue *Q, void (*f)(void *q))
{
  if(Q->front==Q->rear) return FALSE;
  Node *p=Q->front->next;
  void *q;
  printf("输出如下：\n");
  while(p)
  {
      q=p->data;
      f(q);
      p=p->next;
  }
  printf("\n");
  return TRUE;
}



void LPrint(void *q)
{
  printf("  %d",*(int*)q);
}














