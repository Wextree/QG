#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#include <conio.h>//Ϊ������getch��������

#include <stdarg.h>
FILE* logfile=NULL;
void DEBUG_end(){
    if(logfile){
        fclose(logfile);
        logfile=NULL;
    }
}

#define DEBUG(__e) DEBUG_base("debug: " __e "\n")
void DEBUG_base(const char* format){
    if(!logfile){
        logfile=fopen("log.txt","w");//����־�ļ�
        atexit(DEBUG_end);
    }
    fprintf(logfile,format);
}


void menu()//�˵�
{
    system("cls");
    printf("\t\t|-------------------------------------------|\n");
    printf("\t\t|     Welcome To Library Books System!!!    |\n");
    printf("\t\t|-------------------------------------------|\n");
    printf("\t\t|               1.����鼮                  |\n");
    printf("\t\t|               2.�����鼮                  |\n");
    printf("\t\t|               3.�Ƴ��鼮                  |\n");
    printf("\t\t|               4.�����鼮                  |\n");
    printf("\t\t|               5.�黹�鼮                  |\n");
    printf("\t\t|               6.��ʾ�鼮״̬              |\n");
    printf("\t\t|               7.��ʾ������                |\n");
    printf("\t\t|               0.�˳�                      |\n");
    printf("\t\t|-------------------------------------------|\n");
}

void add()
{
    int count;
    char ch[2],name[SIZE];
    book *p,*q,*Bhead;
    Bhead=NULL;
    Bhead=open_book();
    printf("��������Ҫ��ӵ��鼮���ƣ�");
    scanf("%s",name);
    p=compare_book(Bhead,name,&count);//�������Ѱ�Ҷ�Ӧ�鼮
    if(p==NULL)//��ʾû�����鼮
        {
            printf(" �����û�д��鼮�����һ�μ�����⣡\n �Ƿ���룿��Y/N��\n");
            scanf("%s",ch);
            if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)
            {
                q=(book*)calloc(1,BLEN);//���½���һ���µĽ��������ӵ��鼮
                strcpy(q->bookname,name);
                q->number=count+1;
                q->allNum=q->nowNum=1;
                printf("���������ߣ�\n");
                scanf("%s",q->writer);
                add_book(q);//д���ļ�ȥ
            }
        }
    else {            //�������еĻ���ֱ����ӿ����ִ���
            p->nowNum++;
            p->allNum++;
            DEBUG("ĳ������+1");
            write_book(Bhead);
        }
    bookClear(Bhead);
}

void searchBook()//����ĳ��
{
    int choose,number,flag=0,count=0;
    char name[SIZE];
    book *p,*Bhead;
    Bhead=NULL;
    Bhead=open_book();
    p=Bhead;
    printf("�������ֲ��ҷ�ʽ��1.ͨ����� 2.ͨ������ 3.ͨ������\n");//ѡ����ҷ�ʽ
    scanf("%d",&choose);
    switch(choose)//���벻ͬ�ķ�ʽ���ң�ͨ���Ƚϲ����鼮
    {
    case 1:printf("�������ţ�");scanf("%d",&number);DEBUG("ͨ����Ų���");
    while(p!=NULL)
    {
        if(p->number==number)
        {printf(" ����ҵ��鼮��\n ��ţ�%d \n ��������%s��\n ���ߣ�%s \n �ִ�����%d \n ��������%d\n",p->number,p->bookname,p->writer,p->nowNum,p->allNum);
            break;}
            p=p->next;
    }
    if(p==NULL)
        printf(" �����û����Ҫ���ҵ��鼮�� \n");break;

    case 2:printf("��������Ҫ���ҵ��鼮���ƣ�"); scanf("%s",name);DEBUG("ͨ����������");p=compare_book(Bhead,name,&count);
    if(p==NULL)
        printf(" �����û����Ҫ���ҵ��鼮�� \n");
        else printf(" ����ҵ��鼮��\n ��ţ�%d \n ��������%s��\n ���ߣ�%s \n �ִ�����%d \n ��������%d\n",p->number,p->bookname,p->writer,p->nowNum,p->allNum);
            break;
    case 3: {printf("��������Ҫ���ҵ��鼮����Ӧ�����ߣ�");scanf("%s",name);DEBUG("ͨ�����߲���");
    while(p!=NULL)
    {
        if(!strcmp(name,p->writer))
        {printf(" ����ҵ��鼮��\n ��ţ�%d \n ��������%s��\n ���ߣ�%s \n �ִ�����%d \n ��������%d\n\n",p->number,p->bookname,p->writer,p->nowNum,p->allNum);
        flag=1;}//flag���ж��Ƿ��ҵ��鼮
            p=p->next;
    }
    if(flag==0)
        printf(" �����û����Ҫ���ҵ��鼮�� \n");break;}
    default:printf("��������\n");break;
    bookClear(Bhead);
}
}

void bookDelete()
{
    int count;
    char name[SIZE];
    book *p,*Bhead;
    FILE *fp;
    Bhead=NULL;
    Bhead=open_book();
    p=Bhead;
    printf("��������Ҫɾ�����鼮���ƣ�");
    scanf("%s",name);
    p=compare_book(Bhead,name,&count);//����Ҫɾ�����鼮
    if(p==NULL) printf("û���ҵ���������鼮��\n");
    else {
    bookdelete(&Bhead,count);//ɾ����Ӧ�Ľ��
    DEBUG("ɾ��ĳ��");
    write_book(Bhead);//���°�����д���ļ�
    }
    printf("��ʹ����ʾ�鿴ɾ���Ƿ�ɹ���\n");
    bookClear(Bhead);
}

void getOut()//���ͼ��
{
    book *p1,*Bhead;
    Student *q2,*Shead;
    FILE *fp1,*fp2;
    Bhead=NULL;
    Shead=NULL;
    Bhead=open_book();
    Shead=open_stu();
    q2=(Student*)calloc(1,SLEN);//���һ���µĽ������Ž����ߵ���Ϣ
    printf("���������������\n");
    scanf("%s",q2->name);
    printf("���������ѧ�ţ�\n");
    scanf("%s",q2->ID);
    printf("����������Ҫ������������\n");
    scanf("%s",q2->bookname);
    printf("������������ڣ������գ��м��ÿո��������\n");
    scanf("%d%d%d",&(q2->deadline.year),&(q2->deadline.month),&(q2->deadline.date));
    p1=Bhead;
    while(p1!=NULL)//������Ҫ����鼮
    {
        if(!strcmp(q2->bookname,p1->bookname)) break;
            p1=p1->next;
    }
    if(p1==NULL)
        printf(" �����û����Ҫ���ĵ��鼮�� \n");
    else if(p1->nowNum==0)
    printf("������ĵ��鼮�ѱ����˽��꣡\n");
    else {  //����ҵ��Ͷ�Ӧ�鼮�ִ�����һ
        p1->nowNum--;
    write_book(Bhead);//����д�뵽����ļ�
    add_stu(q2);//��ӽ�������Ϣ
    printf("���ĳɹ���\n");
    DEBUG("���һ����");
    }
    bookClear(Bhead);
    stuClear(Shead);
}

void getBack()//�黹�鼮
{
    int count=0;
    char name[SIZE],bookname[SIZE];
    book *p1,*Bhead;
    Student *p2,*Shead;
    FILE *fp1,*fp2;
    Bhead=NULL;
    Shead=NULL;
    Bhead=open_book();
    Shead=open_stu();
    printf("������������֣�\n");
    scanf("%s",name);
    printf("��������Ҫ�黹���鼮��\n");
    scanf("%s",bookname);
    p2=Shead;
    while(p2)//�������ֺ���������ͬʱƥ�������Ϣ
    {
        if(strcmp(name,p2->name)==0&&strcmp(bookname,p2->bookname)==0)
            break;
            count++;
        p2=p2->next;
    }
    if(p2==NULL) printf("�Ҳ�����ļ�¼��������������Ƿ�����\n");
    else studelete(&Shead,count);//���ҵ���ɾ�������ߵ���Ϣ���Ҷ�Ӧ�鼮���ִ�����һ
     write_stu(Shead);
    p1=Bhead;
    while(p1)
    {
        if(!strcmp(bookname,p1->bookname))
            break;
        p1=p1->next;
    }
    p1->nowNum++;
    write_book(Bhead);
    DEBUG("�黹һ����");
    bookClear(Bhead);
    stuClear(Shead);
}

void showBook()//��ʾ�����Ϣ
{
    system("cls");
    book *p,*Bhead;
    Bhead=NULL;
    Bhead=open_book();
    check_book(Bhead);
    DEBUG("�����ʾ");
    printf("==========================================================================\n");
    printf("  ���\t  ����  \t\t����  \t\t\t�ִ���\t�����   \n");
    printf("==========================================================================\n");
    p=Bhead;
    while(p)
    {
        printf("  %3d\t%-20s\t%-20s\t%6d\t%6d\t\n",p->number,p->bookname,p->writer,p->nowNum,p->allNum);
        p=p->next;
    }}

void showStudent()//��ʾ��������Ϣ
{
    system("cls");
    Student *p,*Shead;
    Shead=NULL;
    Shead=open_stu();
    check_stu(Shead);
    DEBUG("�����ߵ���ʾ");
    printf("=====================================================================================================\n");
    printf("  ����  \t  \tѧ��  \t  \t\t������  \t\t��������\t\n");
    printf("=====================================================================================================\n");
    p=Shead;
    while(p)
    {
        printf(" %-20s\t%-20s\t%-20s\t%4d.%2d.%2d\t\n",p->name,p->ID,p->bookname,p->deadline.year,p->deadline.month,p->deadline.date);
        p=p->next;
    }
}




























