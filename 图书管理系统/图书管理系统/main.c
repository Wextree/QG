#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "book.h"

int main()
{
  int choose;
  menu();
  scanf("%d",&choose);
  while(choose)
  {
      switch(choose)
      {
        case 1:add();break;
        case 2:searchBook();break;
        case 3:bookDelete();break;
        case 4:getOut();break;
        case 5:getBack();break;
        case 6:showBook();break;
        case 7:showStudent();break;
        default:printf("你的输入有误，请重新输入！\n");break;
      }
      printf("按任意键继续......\n");
      getch();
      menu();
      scanf("%d",&choose);
  }
  return 0;
}
