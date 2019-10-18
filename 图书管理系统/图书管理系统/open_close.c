#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "book.h"

 book* open_book()//打开文件，用链表读取文件内容
 {
    int count=0;
    FILE *fp;
    book *Bhead,*p,*q;
    Bhead=NULL;
    if((fp=fopen("book.dat","rb"))==NULL){ //打开文件读取
            printf("无法打开文件！\n");
            exit(1);
        }
    if(!feof(fp)){ //开始把内容放在链表
        p=q=(book*)calloc(1,BLEN);
        fread(p,BLEN,1,fp);
        while(!feof(fp))//不断读取
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
    else printf("文件是空的！\n");
    fclose(fp);//关闭文件
    fp=NULL;
    return Bhead;
 }

  Student* open_stu()//打开文件，用链表读取文件内容
 {
    int count=0;
    FILE *fp;
    Student *Shead,*p,*q;
    Shead=NULL;
    if((fp=fopen("student","rb"))==NULL){  //打开文件
            printf("无法打开文件！\n");
            exit(1);
        }
    if(!feof(fp)){  //把文件内容存取到链表里
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
    else printf("文件是空的！\n");
    fclose(fp);//关闭文件
    fp=NULL;
    return Shead;
 }

 book* compare_book(book *Bhead,char* name,int *count)//比较返回指针
 {
     int i=0;
     book *p=Bhead;
     while(p!=NULL)//开始进行比较
    {
        if(!strcmp(name,p->bookname))
            break;
            i++;
            p=p->next;
    }
    *count=i;
    return p;
 }

void add_book(book* q)//添加图书
{
    FILE *fp;
    if((fp=fopen("book.dat","ab"))==NULL)//打开文件
        {
            printf("打开失败！\n");
            exit(1);
        }
    fwrite(q,BLEN,1,fp);//写入文件
    DEBUG("添加一本新的书籍");
    fclose(fp);
    printf("加入成功！\n");
}

void add_stu(Student* q)//添加结点
{
    FILE *fp;
    if((fp=fopen("student","ab"))==NULL)//打开文件
        {
            printf("打开失败！\n");
            exit(1);
        }
    fwrite(q,SLEN,1,fp);//写入文件
    fclose(fp);
}

void write_book(book* Bhead)//重新写文件
{
    book* p=Bhead;
    FILE *fp;
    if((fp=fopen("book.dat","wb"))==NULL)//打开文件
        {
            printf("打开失败！\n");
            exit(1);
        }
        while(p->next)//开始把链表的内容读到文件里
        {
           fwrite(p,BLEN,1,fp);
           p=p->next;
        }
        fclose(fp);
}

void write_stu(Student* Shead)//写文件
{
    Student* p=Shead;
    FILE *fp;
    if((fp=fopen("Student","wb"))==NULL)//打开文件
        {
            printf("打开失败！\n");
            exit(1);
        }
        while(p->next)//开始把链表内容写到文件里面去
        {
           fwrite(p,SLEN,1,fp);
           p=p->next;
        }
        fclose(fp);
}

void check_book(book* Bhead)//检查链表里不符合的选项
{
    int count=0;
    book *p=Bhead;
    FILE *fp;
    while(p)//进行不符合的条件筛选
    {
        if(p->allNum==0)
        bookdelete(&Bhead,count);
        p=p->next;
        count++;
    }
    p=Bhead;
    count=1;
     if((fp=fopen("book.dat","wb"))==NULL)//打开文件
    {
        printf("无法打开文件！\n");
        exit(1);
    }
    while(p)//重新写入文件里
    {
        p->number=count;
        fwrite(p,BLEN,1,fp);
        p=p->next;
        count++;
    }
    fclose(fp);
}

void check_stu(Student* Shead)//检查链表里不符合的选项
{
    int count=0;
    Student *p=Shead;
    FILE *fp;
    while(p)//开始进行条件判断
        {
            if(p->deadline.date==0)
            studelete(&Shead,count);
            p=p->next;
            count++;
        }
        if((fp=fopen("student","wb"))==NULL)
        {
            printf("无法打开文件！\n");
            exit(1);
        }
        p=Shead;
        while(p)//重新写入文件
        {
            fwrite(p,SLEN,1,fp);
            p=p->next;
        }
        fclose(fp);
}






















