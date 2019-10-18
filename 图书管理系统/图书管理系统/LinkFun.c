#include <stdio.h>
#include <stdlib.h>
#include "book.h"


void bookClear(book *Bhead)//�������
{
    book *p,*q;
	p=Bhead;//����ͷ����ָ��
	while(p)//ѭ��ֱ�������
	{
	    q=p->next;//���������
	    free(p);//�ͷ��ڴ�
	    p=q;
	}
	Bhead=NULL;
}

void stuClear(Student *Shead)//�������
{
    Student *p,*q;
	p=Shead;//����ͷ����ָ��
	while(p)//ѭ��ֱ�������
	{
	    q=p->next;//���������
	    free(p);//�ͷ��ڴ�
	    p=q;
	}
	Shead=NULL;
}


void bookdelete(book **Bhead,int count)//ɾ��������
{
    int i=0;
    book *cur,*pre;//����һ��ָ�����ں�֮ǰ��ָ��
	cur=*Bhead;//��ֵͷ���
	pre=NULL;//����ָ��
    while(cur&&i<count)//Ѱ����Ҫ�Ľ��λ��
    {
        pre=cur;//����֮ǰ�Ľ��
        cur=cur->next;//��������ƶ�
        ++i;
    }
    if(pre==NULL)//�ж���ɾ��ͷ����λ��
        *Bhead=cur->next;
    else//�������ͷ����һ�����
        pre->next=cur->next;
    free(cur);//�ͷ�ɾ�������ڴ�
}

void studelete(Student **Shead,int count)//ɾ�����
{
    int i=0;
    Student *cur,*pre;//����һ��ָ�����ں�֮ǰ��ָ��
	cur=*Shead;//��ֵͷ���
	pre=NULL;//����ָ��
    while(cur&&i<count)//Ѱ����Ҫ�Ľ��λ��
    {
        pre=cur;//����֮ǰ�Ľ��
        cur=cur->next;//��������ƶ�
        ++i;
    }
    if(pre==NULL)//�ж���ɾ��ͷ����λ��
        *Shead=cur->next;
    else//�������ͷ����һ�����
        pre->next=cur->next;
    free(cur);//�ͷ�ɾ�������ڴ�
}























