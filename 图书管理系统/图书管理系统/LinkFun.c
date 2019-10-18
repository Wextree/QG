#include <stdio.h>
#include <stdlib.h>
#include "book.h"


void bookClear(book *Bhead)//清空链表
{
    book *p,*q;
	p=Bhead;//拷贝头结点的指针
	while(p)//循环直到最后结点
	{
	    q=p->next;//结点往后移
	    free(p);//释放内存
	    p=q;
	}
	Bhead=NULL;
}

void stuClear(Student *Shead)//清空链表
{
    Student *p,*q;
	p=Shead;//拷贝头结点的指针
	while(p)//循环直到最后结点
	{
	    q=p->next;//结点往后移
	    free(p);//释放内存
	    p=q;
	}
	Shead=NULL;
}


void bookdelete(book **Bhead,int count)//删除链表结点
{
    int i=0;
    book *cur,*pre;//定义一个指向现在和之前的指针
	cur=*Bhead;//赋值头结点
	pre=NULL;//赋空指针
    while(cur&&i<count)//寻找所要的结点位置
    {
        pre=cur;//更新之前的结点
        cur=cur->next;//结点往后移动
        ++i;
    }
    if(pre==NULL)//判断是删除头结点的位置
        *Bhead=cur->next;
    else//如果不是头结点的一般操作
        pre->next=cur->next;
    free(cur);//释放删除结点的内存
}

void studelete(Student **Shead,int count)//删除结点
{
    int i=0;
    Student *cur,*pre;//定义一个指向现在和之前的指针
	cur=*Shead;//赋值头结点
	pre=NULL;//赋空指针
    while(cur&&i<count)//寻找所要的结点位置
    {
        pre=cur;//更新之前的结点
        cur=cur->next;//结点往后移动
        ++i;
    }
    if(pre==NULL)//判断是删除头结点的位置
        *Shead=cur->next;
    else//如果不是头结点的一般操作
        pre->next=cur->next;
    free(cur);//释放删除结点的内存
}























