#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#define SIZE 12
#define BLEN sizeof(book)
#define SLEN sizeof(Student)
#define DEBUG(__e) DEBUG_base("debug: " __e "\n")//可以使用DEBUG

typedef struct book//定义管理图书的结构体
{
  int number;
  char bookname[SIZE];
  char writer[SIZE];
  int nowNum;//现存量
  int allNum;//总库存
  struct book *next;
} book;

struct Day//结束日期
{
    int year;
    int month;
    int date;
};

typedef struct Student//借阅者信息
{
    char name[SIZE];
    char ID[SIZE];
    char bookname[SIZE];
    struct Day deadline;
    struct Student *next;
} Student;



//功能函数
void menu();
void add();
void searchBook();
void bookDelete();
void getOut();
void getBack();
void showBook();
void showStudent();

//链表操作函数
void bookdelete(book **Bhead,int count);
void studelete(Student **Shead,int count);
void stuClear(Student *Shead);
void bookClear(book *Bhead);

//文件操作函数
void DEBUG_base(const char* format);
void DEBUG_end();
book* open_book();
Student* open_stu();
book* compare_book(book *Bhead,char* name,int* count);
void add_book(book* p);
void write_book(book* Bhead);
void write_stu(Student* Shead);
void check_book(book* Bhead);
void check_stu(Student* Shead);

#endif
