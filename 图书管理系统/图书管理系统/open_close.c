#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "book.h"

 book* open_book()//���ļ����������ȡ�ļ�����
 {
    int count=0;
    FILE *fp;
    book *Bhead,*p,*q;
    Bhead=NULL;
    if((fp=fopen("book.dat","rb"))==NULL){ //���ļ���ȡ
            printf("�޷����ļ���\n");
            exit(1);
        }
    if(!feof(fp)){ //��ʼ�����ݷ�������
        p=q=(book*)calloc(1,BLEN);
        fread(p,BLEN,1,fp);
        while(!feof(fp))//���϶�ȡ
           {
                count++;
                if(count==1) Bhead=p;
                else q->next=p;
                q=p;
                p=(book*)calloc(1,BLEN);
                fread(p,BLEN,1,fp);
           }
        q->next=p;
        p->next=NULL;
        }
    else printf("�ļ��ǿյģ�\n");
    fclose(fp);//�ر��ļ�
    fp=NULL;
    return Bhead;
 }

  Student* open_stu()//���ļ����������ȡ�ļ�����
 {
    int count=0;
    FILE *fp;
    Student *Shead,*p,*q;
    Shead=NULL;
    if((fp=fopen("student","rb"))==NULL){  //���ļ�
            printf("�޷����ļ���\n");
            exit(1);
        }
    if(!feof(fp)){  //���ļ����ݴ�ȡ��������
        p=q=(Student*)calloc(1,SLEN);
        fread(p,SLEN,1,fp);
        while(!feof(fp))
           {
                count++;
                if(count==1) Shead=p;
                else q->next=p;
                q=p;
                p=(Student*)calloc(1,SLEN);
                fread(p,SLEN,1,fp);
           }
        q->next=p;
        p->next=NULL;
        }
    else printf("�ļ��ǿյģ�\n");
    fclose(fp);//�ر��ļ�
    fp=NULL;
    return Shead;
 }

 book* compare_book(book *Bhead,char* name,int *count)//�ȽϷ���ָ��
 {
     int i=0;
     book *p=Bhead;
     while(p!=NULL)//��ʼ���бȽ�
    {
        if(!strcmp(name,p->bookname))
            break;
            i++;
            p=p->next;
    }
    *count=i;
    return p;
 }

void add_book(book* q)//���ͼ��
{
    FILE *fp;
    if((fp=fopen("book.dat","ab"))==NULL)//���ļ�
        {
            printf("��ʧ�ܣ�\n");
            exit(1);
        }
    fwrite(q,BLEN,1,fp);//д���ļ�
    DEBUG("���һ���µ��鼮");
    fclose(fp);
    printf("����ɹ���\n");
}

void add_stu(Student* q)//��ӽ��
{
    FILE *fp;
    if((fp=fopen("student","ab"))==NULL)//���ļ�
        {
            printf("��ʧ�ܣ�\n");
            exit(1);
        }
    fwrite(q,SLEN,1,fp);//д���ļ�
    fclose(fp);
}

void write_book(book* Bhead)//����д�ļ�
{
    book* p=Bhead;
    FILE *fp;
    if((fp=fopen("book.dat","wb"))==NULL)//���ļ�
        {
            printf("��ʧ�ܣ�\n");
            exit(1);
        }
        while(p->next)//��ʼ����������ݶ����ļ���
        {
           fwrite(p,BLEN,1,fp);
           p=p->next;
        }
        fclose(fp);
}

void write_stu(Student* Shead)//д�ļ�
{
    Student* p=Shead;
    FILE *fp;
    if((fp=fopen("Student","wb"))==NULL)//���ļ�
        {
            printf("��ʧ�ܣ�\n");
            exit(1);
        }
        while(p->next)//��ʼ����������д���ļ�����ȥ
        {
           fwrite(p,SLEN,1,fp);
           p=p->next;
        }
        fclose(fp);
}

void check_book(book* Bhead)//��������ﲻ���ϵ�ѡ��
{
    int count=0;
    book *p=Bhead;
    FILE *fp;
    while(p)//���в����ϵ�����ɸѡ
    {
        if(p->allNum==0)
        bookdelete(&Bhead,count);
        p=p->next;
        count++;
    }
    p=Bhead;
    count=1;
     if((fp=fopen("book.dat","wb"))==NULL)//���ļ�
    {
        printf("�޷����ļ���\n");
        exit(1);
    }
    while(p)//����д���ļ���
    {
        p->number=count;
        fwrite(p,BLEN,1,fp);
        p=p->next;
        count++;
    }
    fclose(fp);
}

void check_stu(Student* Shead)//��������ﲻ���ϵ�ѡ��
{
    int count=0;
    Student *p=Shead;
    FILE *fp;
    while(p)//��ʼ���������ж�
        {
            if(p->deadline.date==0)
            studelete(&Shead,count);
            p=p->next;
            count++;
        }
        if((fp=fopen("student","wb"))==NULL)
        {
            printf("�޷����ļ���\n");
            exit(1);
        }
        p=Shead;
        while(p)//����д���ļ�
        {
            fwrite(p,SLEN,1,fp);
            p=p->next;
        }
        fclose(fp);
}






















