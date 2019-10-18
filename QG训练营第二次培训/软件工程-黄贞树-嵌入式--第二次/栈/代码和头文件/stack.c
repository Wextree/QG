#include <stdio.h>
#include <stdlib.h>
//顺序栈(基于数组的)
Status initStack(SqStack *s,int sizes)  //初始化链表
{
    s->elem=(ElemType*)malloc(sizeof(ElemType)*sizes);//为栈里面的数据申请内存
    if(NULL==s->elem)//判断内存是否足够
        return ERROR;
  s->size=sizes;
  s->top=-1; //栈顶指针赋值为空
  return OK;
}


Status isEmptyStack(SqStack *s)   //判断链表是否为空
{
   if(s->top==-1)//查看栈顶指针是否为空，，因为在初始化的时候已经是检验了内存申请是否成功，这里就不再检验
    return ERROR;
   else
    return OK;
}


Status getTopStack(SqStack *s,ElemType *e)   //得到栈头元素
{
   if(NULL==s||s->top==-1)  //判断是否为空栈或者内存申请失败
    return ERROR;
   *e=*(s->elem+s->top);
   return OK;
}


Status clearStack(SqStack *s)   //清空链表
{
    if(NULL==s)  //判断是否为空栈或者内存申请失败
    return ERROR;
     s->top=-1;//栈的头指针变为空
     return OK;
}


Status destoryStack(SqStack *s)  //销毁链表
{
   if(s==NULL) return ERROR;
   free(s->elem);//释放栈里面数据的内存
   free(s);//释放栈所占用的内存
   s=NULL;//把本来指向栈的那个指针指向空
   return OK;
}


Status stackLength(SqStack *s,int *length)   //检测栈长度
{
   if(NULL==s||s->top==-1)  //判断是否为空栈或者内存申请失败
   return ERROR;
   *length=s->top+1;
   return OK;
}

Status pushStack(SqStack *s,ElemType datas)  //入栈
{
   if(s==NULL)//判断是否传下来一个空指针
    return ERROR;
    if(s->top==s->size-1)
    {printf("栈满了！\n");return ERROR;}
    s->top++;
    *(s->elem+s->top)=datas;
    return OK;
}

Status popStack(SqStack *s,ElemType *datas)   //出栈
{
  if(s==NULL||s->top==-1)//判断是否为空栈或者内存申请失败
    return ERROR;
  *datas=*(s->elem+s->top);//把出栈的那个数据保存
  s->top--;//栈顶指针自减
    return OK;
}

//链栈(基于链表的)
Status initLStack(LinkStack *s)   //初始化
{
  if(s==NULL)//判断内存是否申请成功
    return ERROR;
  s->count=0;//一开始计数为0
  s->top=NULL;//栈顶指针指向空
  return OK;
}

Status isEmptyLStack(LinkStack *s)  //判断链表是否为空
{
   if(s->count==0)//查看计数，因为在初始化的时候已经是检验了内存申请是否成功，这里就不再检验
    return ERROR;
   else
    return OK;
}

Status getTopLStack(LinkStack *s,ElemType *e)  //得到链表头元素
{
  if(NULL==s||s->count==0)  //判断是否为空栈或者内存申请失败
  return ERROR;
  *e=s->top->data;//把栈的头元素赋值给e
  return OK;
}

Status clearLStack(LinkStack *s)   //清空链表
{
  if(s==NULL)//判断s是否为空指针
    return ERROR;
  LinkStackPtr p=s->top,q;
  while(p!=NULL)//清空栈
  {
      q=p->next;
      free(p);//释放内存
      p=q;
  }
  s->top=NULL;
  return OK;
}

Status destoryLStack(LinkStack *s)   //销毁链表
{
    if(s==NULL)//判断s是否为空指针
    return ERROR;
  LinkStackPtr p=s->top,q;
  while(p!=NULL)//清空栈
  {
      q=p->next;
      free(p);//释放内存
      p=q;
  }
  s->top=NULL;
  free(s);
  return OK;
}

Status LStackLength(LinkStack *s,int *length)    //检测链表长度
{
  if(s==NULL)//判断s是否为空指针
    return ERROR;
  *length=s->count;
}

Status pushLStack(LinkStack *s,ElemType datas)   //入栈
{
   LinkStackPtr p=(StackNode*)malloc(sizeof(StackNode));//为新入栈的结点分配空间
   if(!p)
    return ERROR;
   p->data=datas;//给新结点赋值
   p->next=s->top;//下两行是转换心的头结点赋值给top
   s->top=p;
   s->count++;//计数加一
   return OK;
}

Status popLStack(LinkStack *s,ElemType *datas)   //出栈
{
  if(s->top==NULL||s==NULL)//判断是否为空栈
    return ERROR;
    LinkStackPtr p;
    *datas=s->top->data;//保存出栈的那个值
    p=s->top;//更换头结点赋值给top
  s->top=s->top->next;
  free(p);//释放出栈的那个结点的内存
  s->count--;//计数减一
  return OK;
}
