#include <stdio.h>
#include <stdlib.h>
//˳��ջ(���������)
Status initStack(SqStack *s,int sizes)  //��ʼ������
{
    s->elem=(ElemType*)malloc(sizeof(ElemType)*sizes);//Ϊջ��������������ڴ�
    if(NULL==s->elem)//�ж��ڴ��Ƿ��㹻
        return ERROR;
  s->size=sizes;
  s->top=-1; //ջ��ָ�븳ֵΪ��
  return OK;
}


Status isEmptyStack(SqStack *s)   //�ж������Ƿ�Ϊ��
{
   if(s->top==-1)//�鿴ջ��ָ���Ƿ�Ϊ�գ�����Ϊ�ڳ�ʼ����ʱ���Ѿ��Ǽ������ڴ������Ƿ�ɹ�������Ͳ��ټ���
    return ERROR;
   else
    return OK;
}


Status getTopStack(SqStack *s,ElemType *e)   //�õ�ջͷԪ��
{
   if(NULL==s||s->top==-1)  //�ж��Ƿ�Ϊ��ջ�����ڴ�����ʧ��
    return ERROR;
   *e=*(s->elem+s->top);
   return OK;
}


Status clearStack(SqStack *s)   //�������
{
    if(NULL==s)  //�ж��Ƿ�Ϊ��ջ�����ڴ�����ʧ��
    return ERROR;
     s->top=-1;//ջ��ͷָ���Ϊ��
     return OK;
}


Status destoryStack(SqStack *s)  //��������
{
   if(s==NULL) return ERROR;
   free(s->elem);//�ͷ�ջ�������ݵ��ڴ�
   free(s);//�ͷ�ջ��ռ�õ��ڴ�
   s=NULL;//�ѱ���ָ��ջ���Ǹ�ָ��ָ���
   return OK;
}


Status stackLength(SqStack *s,int *length)   //���ջ����
{
   if(NULL==s||s->top==-1)  //�ж��Ƿ�Ϊ��ջ�����ڴ�����ʧ��
   return ERROR;
   *length=s->top+1;
   return OK;
}

Status pushStack(SqStack *s,ElemType datas)  //��ջ
{
   if(s==NULL)//�ж��Ƿ�����һ����ָ��
    return ERROR;
    if(s->top==s->size-1)
    {printf("ջ���ˣ�\n");return ERROR;}
    s->top++;
    *(s->elem+s->top)=datas;
    return OK;
}

Status popStack(SqStack *s,ElemType *datas)   //��ջ
{
  if(s==NULL||s->top==-1)//�ж��Ƿ�Ϊ��ջ�����ڴ�����ʧ��
    return ERROR;
  *datas=*(s->elem+s->top);//�ѳ�ջ���Ǹ����ݱ���
  s->top--;//ջ��ָ���Լ�
    return OK;
}

//��ջ(���������)
Status initLStack(LinkStack *s)   //��ʼ��
{
  if(s==NULL)//�ж��ڴ��Ƿ�����ɹ�
    return ERROR;
  s->count=0;//һ��ʼ����Ϊ0
  s->top=NULL;//ջ��ָ��ָ���
  return OK;
}

Status isEmptyLStack(LinkStack *s)  //�ж������Ƿ�Ϊ��
{
   if(s->count==0)//�鿴��������Ϊ�ڳ�ʼ����ʱ���Ѿ��Ǽ������ڴ������Ƿ�ɹ�������Ͳ��ټ���
    return ERROR;
   else
    return OK;
}

Status getTopLStack(LinkStack *s,ElemType *e)  //�õ�����ͷԪ��
{
  if(NULL==s||s->count==0)  //�ж��Ƿ�Ϊ��ջ�����ڴ�����ʧ��
  return ERROR;
  *e=s->top->data;//��ջ��ͷԪ�ظ�ֵ��e
  return OK;
}

Status clearLStack(LinkStack *s)   //�������
{
  if(s==NULL)//�ж�s�Ƿ�Ϊ��ָ��
    return ERROR;
  LinkStackPtr p=s->top,q;
  while(p!=NULL)//���ջ
  {
      q=p->next;
      free(p);//�ͷ��ڴ�
      p=q;
  }
  s->top=NULL;
  return OK;
}

Status destoryLStack(LinkStack *s)   //��������
{
    if(s==NULL)//�ж�s�Ƿ�Ϊ��ָ��
    return ERROR;
  LinkStackPtr p=s->top,q;
  while(p!=NULL)//���ջ
  {
      q=p->next;
      free(p);//�ͷ��ڴ�
      p=q;
  }
  s->top=NULL;
  free(s);
  return OK;
}

Status LStackLength(LinkStack *s,int *length)    //���������
{
  if(s==NULL)//�ж�s�Ƿ�Ϊ��ָ��
    return ERROR;
  *length=s->count;
}

Status pushLStack(LinkStack *s,ElemType datas)   //��ջ
{
   LinkStackPtr p=(StackNode*)malloc(sizeof(StackNode));//Ϊ����ջ�Ľ�����ռ�
   if(!p)
    return ERROR;
   p->data=datas;//���½�㸳ֵ
   p->next=s->top;//��������ת���ĵ�ͷ��㸳ֵ��top
   s->top=p;
   s->count++;//������һ
   return OK;
}

Status popLStack(LinkStack *s,ElemType *datas)   //��ջ
{
  if(s->top==NULL||s==NULL)//�ж��Ƿ�Ϊ��ջ
    return ERROR;
    LinkStackPtr p;
    *datas=s->top->data;//�����ջ���Ǹ�ֵ
    p=s->top;//����ͷ��㸳ֵ��top
  s->top=s->top->next;
  free(p);//�ͷų�ջ���Ǹ������ڴ�
  s->count--;//������һ
  return OK;
}
