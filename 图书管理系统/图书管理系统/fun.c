#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#include <conio.h>//为了引用getch（）函数

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
        logfile=fopen("log.txt","w");//打开日志文件
        atexit(DEBUG_end);
    }
    fprintf(logfile,format);
}


void menu()//菜单
{
    system("cls");
    printf("\t\t|-------------------------------------------|\n");
    printf("\t\t|     Welcome To Library Books System!!!    |\n");
    printf("\t\t|-------------------------------------------|\n");
    printf("\t\t|               1.添加书籍                  |\n");
    printf("\t\t|               2.查找书籍                  |\n");
    printf("\t\t|               3.移除书籍                  |\n");
    printf("\t\t|               4.借阅书籍                  |\n");
    printf("\t\t|               5.归还书籍                  |\n");
    printf("\t\t|               6.显示书籍状态              |\n");
    printf("\t\t|               7.显示借阅者                |\n");
    printf("\t\t|               0.退出                      |\n");
    printf("\t\t|-------------------------------------------|\n");
}

void add()
{
    int count;
    char ch[2],name[SIZE];
    book *p,*q,*Bhead;
    Bhead=NULL;
    Bhead=open_book();
    printf("请输入你要添加的书籍名称：");
    scanf("%s",name);
    p=compare_book(Bhead,name,&count);//在书库里寻找对应书籍
    if(p==NULL)//表示没有这书籍
        {
            printf(" 书库中没有此书籍，需第一次加入书库！\n 是否加入？（Y/N）\n");
            scanf("%s",ch);
            if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)
            {
                q=(book*)calloc(1,BLEN);//重新建立一个新的结点存放新添加的书籍
                strcpy(q->bookname,name);
                q->number=count+1;
                q->allNum=q->nowNum=1;
                printf("请输入作者：\n");
                scanf("%s",q->writer);
                add_book(q);//写到文件去
            }
        }
    else {            //如果书库有的话就直接添加库存和现存量
            p->nowNum++;
            p->allNum++;
            DEBUG("某书数量+1");
            write_book(Bhead);
        }
    bookClear(Bhead);
}

void searchBook()//查找某书
{
    int choose,number,flag=0,count=0;
    char name[SIZE];
    book *p,*Bhead;
    Bhead=NULL;
    Bhead=open_book();
    p=Bhead;
    printf("你有三种查找方式：1.通过编号 2.通过书名 3.通过作者\n");//选择查找方式
    scanf("%d",&choose);
    switch(choose)//进入不同的方式查找，通过比较查找书籍
    {
    case 1:printf("请输入编号：");scanf("%d",&number);DEBUG("通过编号查找");
    while(p!=NULL)
    {
        if(p->number==number)
        {printf(" 你查找的书籍：\n 编号：%d \n 书名：《%s》\n 作者：%s \n 现存量：%d \n 总数量：%d\n",p->number,p->bookname,p->writer,p->nowNum,p->allNum);
            break;}
            p=p->next;
    }
    if(p==NULL)
        printf(" 书库中没有你要查找的书籍！ \n");break;

    case 2:printf("请输入你要查找的书籍名称："); scanf("%s",name);DEBUG("通过书名查找");p=compare_book(Bhead,name,&count);
    if(p==NULL)
        printf(" 书库中没有你要查找的书籍！ \n");
        else printf(" 你查找的书籍：\n 编号：%d \n 书名：《%s》\n 作者：%s \n 现存量：%d \n 总数量：%d\n",p->number,p->bookname,p->writer,p->nowNum,p->allNum);
            break;
    case 3: {printf("请输入你要查找的书籍所对应的作者：");scanf("%s",name);DEBUG("通过作者查找");
    while(p!=NULL)
    {
        if(!strcmp(name,p->writer))
        {printf(" 你查找的书籍：\n 编号：%d \n 书名：《%s》\n 作者：%s \n 现存量：%d \n 总数量：%d\n\n",p->number,p->bookname,p->writer,p->nowNum,p->allNum);
        flag=1;}//flag来判断是否找到书籍
            p=p->next;
    }
    if(flag==0)
        printf(" 书库中没有你要查找的书籍！ \n");break;}
    default:printf("输入有误！\n");break;
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
    printf("请输入你要删除的书籍名称：");
    scanf("%s",name);
    p=compare_book(Bhead,name,&count);//查找要删除的书籍
    if(p==NULL) printf("没有找到你输入的书籍！\n");
    else {
    bookdelete(&Bhead,count);//删除对应的结点
    DEBUG("删除某书");
    write_book(Bhead);//重新把链表写入文件
    }
    printf("请使用显示查看删除是否成功！\n");
    bookClear(Bhead);
}

void getOut()//借出图书
{
    book *p1,*Bhead;
    Student *q2,*Shead;
    FILE *fp1,*fp2;
    Bhead=NULL;
    Shead=NULL;
    Bhead=open_book();
    Shead=open_stu();
    q2=(Student*)calloc(1,SLEN);//添加一个新的结点来存放借阅者的信息
    printf("请输入你的姓名：\n");
    scanf("%s",q2->name);
    printf("请输入你的学号：\n");
    scanf("%s",q2->ID);
    printf("请输入你所要借的书的书名：\n");
    scanf("%s",q2->bookname);
    printf("请输入今天日期（年月日，中间用空格隔开）：\n");
    scanf("%d%d%d",&(q2->deadline.year),&(q2->deadline.month),&(q2->deadline.date));
    p1=Bhead;
    while(p1!=NULL)//查找所要借的书籍
    {
        if(!strcmp(q2->bookname,p1->bookname)) break;
            p1=p1->next;
    }
    if(p1==NULL)
        printf(" 书库中没有你要借阅的书籍！ \n");
    else if(p1->nowNum==0)
    printf("你想借阅的书籍已被别人借完！\n");
    else {  //如果找到就对应书籍现存量减一
        p1->nowNum--;
    write_book(Bhead);//重新写入到书库文件
    add_stu(q2);//添加借阅者信息
    printf("借阅成功！\n");
    DEBUG("借出一本书");
    }
    bookClear(Bhead);
    stuClear(Shead);
}

void getBack()//归还书籍
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
    printf("请输入你的名字：\n");
    scanf("%s",name);
    printf("请输入你要归还的书籍：\n");
    scanf("%s",bookname);
    p2=Shead;
    while(p2)//输入名字和书名进行同时匹配查找信息
    {
        if(strcmp(name,p2->name)==0&&strcmp(bookname,p2->bookname)==0)
            break;
            count++;
        p2=p2->next;
    }
    if(p2==NULL) printf("找不到你的记录，请检查你的输入是否有误！\n");
    else studelete(&Shead,count);//若找到就删除借阅者的信息并且对应书籍的现存量加一
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
    DEBUG("归还一本书");
    bookClear(Bhead);
    stuClear(Shead);
}

void showBook()//显示书库信息
{
    system("cls");
    book *p,*Bhead;
    Bhead=NULL;
    Bhead=open_book();
    check_book(Bhead);
    DEBUG("书的显示");
    printf("==========================================================================\n");
    printf("  编号\t  书名  \t\t作者  \t\t\t现存量\t库存量   \n");
    printf("==========================================================================\n");
    p=Bhead;
    while(p)
    {
        printf("  %3d\t%-20s\t%-20s\t%6d\t%6d\t\n",p->number,p->bookname,p->writer,p->nowNum,p->allNum);
        p=p->next;
    }}

void showStudent()//显示借阅者信息
{
    system("cls");
    Student *p,*Shead;
    Shead=NULL;
    Shead=open_stu();
    check_stu(Shead);
    DEBUG("借阅者的显示");
    printf("=====================================================================================================\n");
    printf("  姓名  \t  \t学号  \t  \t\t所借书  \t\t借书日期\t\n");
    printf("=====================================================================================================\n");
    p=Shead;
    while(p)
    {
        printf(" %-20s\t%-20s\t%-20s\t%4d.%2d.%2d\t\n",p->name,p->ID,p->bookname,p->deadline.year,p->deadline.month,p->deadline.date);
        p=p->next;
    }
}




























