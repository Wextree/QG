#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <io.h>
#include <tchar.h>
#include <direct.h>
#include <shellapi.h>
#include <stdbool.h>
#include "note.h"

int layer=0;
char treetxt[String_max];
PtrTree AddTree; //申请树根节点指针
char root[String_max];

	int flag=0;
	int flag3=0;
	char _remove[100][String_max]={0};
	int remove_k=0;
	char add[100][String_max]={0};
	int add_k=0;
	char del[100][String_max]={0};
	int del_k=0;
	
	


//进入界面时的显示函数
void screen(){
    printf("\t\t\t|--------------------------------------------------------|\n");
    printf("\t\t\t|                                                        |\n");
    printf("\t\t\t|                                                        |\n");
    printf("\t\t\t|                欢迎进入笔记管理系统！                  |\n");
    printf("\t\t\t|                                                        |\n");
    printf("\t\t\t|                                                        |\n");
    printf("\t\t\t|                按任意键进入下一步....                  |\n");
    printf("\t\t\t|                                                        |\n");
    printf("\t\t\t|--------------------------------------------------------|\n");
    getch();
}

//注册函数
void create(char* name){
        system("cls");
        int i=0;
        char tpassword[9];
        FILE *fp;
        member *p;
        p=(member*)calloc(1,LEN);
        printf("由于是第一次登录，请注册!\n");
        create1:strcpy(p->name,name);
        printf("请输入你的密码：(8位数字)\n");
        while(i<8&&(p->password[i]=getch())!='\r'){
            if(p->password[i]=='\b')
            {
                printf("\b");
                if(i<=0) ;
                else i--;
            }
            else{
                printf("*");
                i++;
                if(i>7){
                    printf("\n             注意：你输入的密码已经到达上限！\n                    再输入的字符无效！\n");
                }
            }
        }
        p->password[i]='\0';
        printf("请再次输入密码：\n");
        i=0;
       while(i<8&&(tpassword[i]=getch())!='\r')
	   {
            if(tpassword[i]=='\b')
            {
                printf("\b");
                if(i<=0) ;
                else i--;
            }
            else {
                    printf("*");
                    i++;
            }
        }
        tpassword[i]='\0';
        if(strcmp(p->password,tpassword)==0)
        {
            if((fp=fopen("member.txt","a"))==NULL)
            {
                printf("无法打开文件！\n");
                exit(1);
            }
            printf("\n请输入一个地址，我们将为你生成你的工作区。\n");
            scanf("%s",p->path);
            CreateDirectory(p->path,NULL);
            fprintf(fp,"%s %s %s",p->name,p->password,p->path);
            fprintf(fp,"\n");
            fclose(fp);
            printf("\t\t\t注册成功，请登录！");
            getch();
            system("cls");
        }
        else {
            printf("\t\t\t两次输入的密码不同，请重新注册！\n");
            goto create1;
        }
}

//登录函数
void login(char *path,char* name){
    system("cls");
    char name_f[20],pwd_f[9],path_f[100];
    int i=0,flag=0;
    FILE *fp;
    struct member *p;
    p=(member*)calloc(1,LEN);
    strcpy(p->name,name);
    relogin:
    printf("请输入你的密码：");
    i=0;
    while(i<8&&(p->password[i]=getch())!='\r')
	{
            if(p->password[i]=='\b')
            {
                printf("\b");
                if(i<=0) ;
                else i--;
            }
            else
			{
                printf("*");
                i++;
                if(i>7)
				{
                    printf("\n             注意：你输入的密码已经到达上限！\n                    再输入的字符无效！\n");
                }
            }
        }
    p->password[i]='\0';
    if((fp=fopen("member.txt","r"))==NULL)
            {
                printf("无法打开文件！\n");
                exit(1);
            }
    while(!feof(fp))
	{
        fscanf(fp,"%s%s%s",name_f,pwd_f,path_f);
        if(strcmp(name_f,p->name)==0&&strcmp(pwd_f,p->password)==0)
        {
            strcpy(path,path_f);
            flag=1;
        }
        if(flag)
        	break;
    }
    if(flag==1)
    {
        printf("登录成功！\n");
        strcpy(root,path_f);
        sprintf(treetxt,"%s.txt",p->name);////////////
        sprintf(treetxt2,"%s_2.txt",p->name);
        tree=fopen(treetxt,"a");
        fclose(tree);
        tree2=fopen(treetxt2,"a");
        fclose(tree2);
        readJudge();
  	    filesearch(path_f,0,AddTree);
	}
    else
	{

		printf("帐号或者密码输入错误！请重新输入\n");
		goto relogin;
	}

    fclose(fp);
}

//登录注册函数接口
void Login()
{
    char ch;
	char name[String_max],path[String_max];
    screen();
    printf("->请输入你的帐号：");
    scanf("%s",name);
    if(!check_name(name))
	{
        getchar();
	    printf("账号错误！请问需要重新输入吗？输入'y'表示确认,输入'n'表示创建新账号。\n");

	    scanf("%c",&ch);
	    while(!check_name(name)&& ch == 'y')
        {
            printf("请输入你的帐号：");
            scanf("%s",name);
            fflush(stdin);
             if(!check_name(name))
              {
                   printf("账号错误！请问需要重新输入吗？输入'y'表示确认,输入'n'表示创建新账号。\n");
                   scanf("%c",&ch);

              }
        }
        if(ch == 'n')
    	{
    	    create(name);
    	    login(path,name);
    	}
    	else login(path,name);
	}

	else login(path,name);

}

int  removeDir(const char*  dirPath)//清空文件夹函数
{

  struct _finddata_t fb;   //查找相同属性文件的存储结构体
  char  path[250];
  long    handle;
  int  resultone;
  int   noFile;            //对系统隐藏文件的处理标记

  noFile = 0;
  handle = 0;


  //制作路径
  strcpy(path,dirPath);
  strcat (path,"/*");

  handle = _findfirst(path,&fb);
  //找到第一个匹配的文件
  if (handle != -1)
  {
    //当可以继续找到匹配的文件，继续执行
    while (0 == _findnext(handle,&fb))
    {
      //windows下，常有个系统文件，名为“..”,对它不做处理
      noFile = strcmp(fb.name,"..");

      if (0 != noFile)
      {
        //制作完整路径
        memset(path,0,sizeof(path));
        strcpy(path,dirPath);
        strcat(path,"/");
        strcat (path,fb.name);
        //属性值为16，则说明是文件夹，迭代
        if (fb.attrib == 16)
        {
          removeDir(path);
        }
        //非文件夹的文件，直接删除。对文件属性值的情况没做详细调查，可能还有其他情况。
        else
        {
          remove(path);
        }
      }
    }
    //关闭文件夹，只有关闭了才能删除。找这个函数找了很久，标准c中用的是closedir
    //经验介绍：一般产生Handle的函数执行后，都要进行关闭的动作。
    _findclose(handle);
  }
  //移除文件夹
  resultone = rmdir(dirPath);
  return  resultone;
}

/*---------------------移动文件夹需要的函数--------------*/
bool FloderCopy( LPCTSTR strFromFloder , LPCTSTR strToFloder )
{

  TCHAR	strFind[MAX_PATH] , strToFile[MAX_PATH] , strmypath[MAX_PATH] ;

  WIN32_FIND_DATA FindFileData;


  _tcscpy(strmypath ,strFromFloder ) ;

  if ( strmypath[_tcslen(strmypath)-1] != '\\' )

    _tcscat( strmypath , _T("\\") ) ;

  _stprintf( strFind , _T("%s*.*") , strmypath ) ;



  if( !CreateDirectory(strToFloder,NULL) )

    return false ;



  HANDLE hFind	=	FindFirstFile(strFind,&FindFileData);

  if(INVALID_HANDLE_VALUE == hFind)

    return false ;

  while(TRUE)

  {

    if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)

    {


      if(FindFileData.cFileName[0]!='.')

      {

        TCHAR	strChildDDir[MAX_PATH] ;

        _stprintf( strFind , _T("%s%s\\") , strmypath , FindFileData.cFileName ) ;

        _stprintf( strChildDDir , _T("%s\\%s\\") , strToFloder , FindFileData.cFileName ) ;

        if( !FloderCopy( strFind , strChildDDir ) )

          return false ;

      }

    }

    else

    {


      _stprintf( strFind , _T("%s%s") , strmypath , FindFileData.cFileName ) ;

      _stprintf( strToFile , _T("%s\\%s") , strToFloder , FindFileData.cFileName ) ;

      CopyFile(strFind,strToFile,false) ;

    }

    if(!FindNextFile(hFind,&FindFileData))	break;

  }

  FindClose(hFind);

  return true ;

}


void move_folder(LPCTSTR strFromFloder , LPCTSTR strToFloder)
{
  FloderCopy(strFromFloder,strToFloder);//复制到移动的位置
  removeDir(strFromFloder);//清空旧目录
  RemoveDirectory(strFromFloder);//删除旧目录

}

void Create_directory(PtrTree T,char *fileName)      //在主目录下创建一个指定名字的文件夹
{
    char* str;

    int n = strlen(T->address);

    T->address[n] = '\\';              //主目录的地址后面没有斜杠，故需要自己加上去
    T->address[n+1] = '\0';

    str = strcat(T->address,fileName);     //把文件名接到主目录上面
    CreateDirectory(str, NULL);             //创建文件夹
}


void MoveDirectoryP(char nowAddress[String_max],char order[String_max])
{
  int ii=0;
  int kk=0;

  char oldname[String_max];
  char newname[String_max]="i";
  char oldad[String_max];
  char newad[String_max];
  strcpy(oldad,nowAddress);//当前目录接入
  strcpy(newad,root);//从根目录输入
  strcat(oldad,"\\\\");
  strcat(newad,"\\\\");
  while(order[ii]!='\0')
  {
    if(order[ii++]=='<' )
    {
      while(order[ii]!='>')
        oldname[kk++] = order[ii++];
      oldname[kk]='\0';
      ii+=2;
      if(order[ii]=='<')
      {
        ii++;
        kk = 0;
        while(order[ii]!='>')
        {
          newname[kk++] = order[ii++];
          puts(newname);
        }
        break;
      }
    }

  }
  strcat(newname,"\\\\");
  strcat(oldad,oldname);
  strcat(newad,newname);
  strcat(newad,oldname);
  move_folder(oldad,newad);

}

//移动文件
void Move_File(PtrTree T,char *newAddress)
{
            char *newad;
            
            newAddress[strlen(newAddress)] = '\\';
            newAddress[strlen(newAddress) + 1] = '\0';
            newad = strcat(newAddress,T->name);
            rename(T->address,newad);

}
//重命名文件
void Rename_File(char nowAddress[String_max],char order[String_max])
{

     int ii=0;
            int kk=0;
            char oldname[String_max];
            char newname[String_max];
            char oldad[String_max];
            char newad[String_max];
            strcpy(oldad,nowAddress);
            strcpy(newad,nowAddress);
            strcat(oldad,"\\\\");
            strcat(newad,"\\\\");
            while(order[ii]!='\0')
            {
                if(order[ii++]=='<' )
            {
            while(order[ii]!='>')
                oldname[kk++] = order[ii++];
            oldname[kk]='\0';
            ii+=2;
            if(order[ii]=='<')
              {
                ii++;
                kk = 0;
                while(order[ii]!='>')
                newname[kk++] = order[ii++];
                newname[kk] = '\0';
                break;
              }
            }
            }
           strcat(oldad,oldname);
      strcat(newad,newname);
            rename(oldad,newad);
}

void Search(PtrTree T,char *str)
{
    int i,k;
    int n ;
    int j;
    int p = 0;
	
    n = strlen(str);
    char tempStr[n+1];
   for(i = 0;i < T->child_k;i++)
    {
     int len=strlen(T->child[i]->name);
     for(k = 0; k <len-n;k++)
        {
            for(j = k;j < n + k;j++)
            {
               tempStr[p++] = T->child[i]->name[j];
            }
             p = 0;
             tempStr[n] = '\0';

    	     if(!strcmp(tempStr,str))
            {
               printf("%s",(T->child[i]->isDir)?"[Dir]:":"[File]:");
    	       printf("%s\n\n",T->child[i]->name);
            }

        }

    }
}

void wopen()
{
	tree=fopen(treetxt,"w");
    if(tree==NULL)
    {
        printf("不能打开%s文件\n",treetxt);
    }
}

void wclose()
{
	fclose(tree);
}

void saveTree(PtrTree T)//配合wopen（）函数共同使用。
{
    if(T==NULL)
		return;
	fprintf(tree,"%s %s %d\n",T->name,T->address,T->tag_k);
	if(T->tag_k!=0)
		for(int j=0;j<T->tag_k;j++)
			fprintf(tree,"%s\n",T->tag[j]);
   	for(int i=0;i<T->child_k;i++)
   	{
    	if(T->child_k!=0)
    	saveTree(T->child[i]);
	}
}

void readTree(ptrTagNode *J)
{
	
    tree = fopen(treetxt,"r+");
    char ch=fgetc(tree);
    if(tree==NULL)
    {
        printf("不能打开%s文件\n",treetxt);
        exit(0);
    }
    if(ch==EOF)
    {
    	fclose(tree);
        return;
    }
            p1=(ptrTagNode)malloc(sizeof(tagNode));
            *J=p1;
            fscanf(tree,"%s %s %d\n",p1->name,p1->address,&p1->tag_k);
            
             if(p1->tag_k!=0)
             {
             	
                 int k=0;
                 while(k<p1->tag_k)
                 {
                     fscanf(tree,"%s",p1->tag[k++]);
                 }
             }
            while(!feof(tree))
            {
                p2=(ptrTagNode)malloc(sizeof(tagNode));
                fscanf(tree,"%s %s %d\n",p2->name,p2->address,&p2->tag_k);
           	    if(p2->tag_k!=0)
          	    {
               	    int k=0;
               		while(k<p2->tag_k)
               	    {
                    	fscanf(tree,"%s",p2->tag[k++]);
                	}
           	    }
				p1->next=p2;
				p1=p2;
            }
            p1->next=NULL;
            fclose(tree);

}



void addTag(char *str,PtrTree T)
{
	strcpy(T->tag[T->tag_k++],str);
	printf("添加标签成功！\n");

}

void showTag(PtrTree T)
{
	if(T->tag_k==0)
	{
		printf("该文件（夹）暂无标签！\n");
		return;
	}
	else
	{
		printf("%s",(T->isDir)?"[Dir]:":"[File]:");
		printf("%s Tag:",T->name);
		for(int i=0;i<T->tag_k;i++)
			printf("<%s>",T->tag[i]);
		printf("\n");
	}
}

void searchTag(char *str,PtrTree T)
{
	int flag1=0;
	int flag2=0;
	for(int i=0;i<T->child_k;i++)
    {
    	for(int j=0;j<T->child[i]->tag_k;j++)
		if(strcmp(T->child[i]->tag[j],str)==0)
		{
			printf("%s",(T->isDir)?"[Dir]:":"[File]:");
			printf("%s Tag:",T->child[i]->name);
			for(int ii=0;ii<T->child[i]->tag_k;ii++)
				printf("<%s>",T->child[i]->tag[ii]);
			printf("\n");
			flag1=1;
			flag2=1;
		}
		if(flag1)
		{
			flag1=0;
			continue;
		}
    }
   	if(!flag2)
	printf("当前目录未找到含<%s>标签文件（夹）\n",str);
}

void delTag(char *str,PtrTree T)
{
	for(int i=0;i<T->tag_k;i++)
		if(strcmp(str,T->tag[i])==0)
		{
			if(i!=(T->tag_k-1))
				for(int j=i;j<T->tag_k;j++)
				{
					strcpy(T->tag[j],T->tag[j+1]);
				}
			else
				strcpy(T->tag[i],T->tag[i+1]);
			T->tag_k--;
			printf("删除标签<%s>成功！\n",str);
			return;
		}
		printf("未找到此标签!\n");

}

void searchAllTag(char *str,PtrTree T)
{
	int flag1=0;
		if(T==NULL)
    return;
    else
    {
		for(int j=0;j<T->tag_k;j++)
		{
    		if(strcmp(T->tag[j],str)==0)
    		{
    			printf("%s",(T->isDir)?"[Dir]:":"[File]:");
				printf("%s Tag:",T->name);
				for(int ii=0;ii<T->tag_k;ii++)
					printf("<%s>",T->tag[ii]);
				printf("\n");
				printf("address:%s\n",T->address);
				flag1=1;
			}
			if(flag1)
			{
				flag1=0;
				continue;
			}
		}
    	for(int i=0;i<T->child_k;i++)
    	{
    		searchAllTag(str,T->child[i]);
		}


	}
}

void readTag(PtrTree T)//加载标签
{
    tree=fopen(treetxt,"r+");
    if(tree==NULL)
    {
        printf("不能打开%s文件\n",treetxt);
        exit(0);
    }
	ptrTagNode q;
	if(T==NULL)
		return;
	else
	{
		for(q=TagHead;q!=NULL;q=q->next)
		if(strcmp(q->address,T->address)==0)
		{
			for(int j=0;j<q->tag_k;j++)
				strcpy(T->tag[T->tag_k++],q->tag[j]);
		}
		for(int i=0;i<T->child_k;i++)
		{
			readTag(T->child[i]);
		}
	}
	fclose(tree);
}

void SaveTree(PtrTree T)
{
	wopen();
	saveTree(T);
	wclose();
}

void wopen2()
{
	tree2=fopen(treetxt2,"w");
    if(tree2==NULL)
    {
        printf("不能打开%s文件\n",treetxt2);
    } 
}

void wclose2()
{
	fclose(tree2);
}

void saveTree2(PtrTree T)//配合wopen2（）函数共同使用。 
{
    if(T==NULL) 
		return;  
	fprintf(tree2,"%s %s %d\n",T->name,T->address,T->tag_k);
	for(int i=0;i<T->child_k;i++)
   	{
    	if(T->child_k!=0)
    	saveTree2(T->child[i]);
	} 
}

void SaveTree2(PtrTree T)
{
	wopen2();
	saveTree2(T);
	wclose2();
}

void readJudge()
{

	tree2=fopen(treetxt2,"r+");
	char ch=fgetc(tree2);
	if(tree2==NULL)
    {
        printf("不能打开%s文件\n",treetxt2);
        exit(0);
    }
    if(ch==EOF)
    {
    	judgeHead=NULL;
    	fclose(tree2);
        return;
    }
    p3=(ptrTagNode)malloc(sizeof(tagNode));
    judgeHead=p3;
    fscanf(tree2,"%s %s %d\n",p3->name,p3->address,&p3->tag_k);
    while(!feof(tree2))
    {
        p4=(ptrTagNode)malloc(sizeof(tagNode));
        fscanf(tree2,"%s %s %d\n",p4->name,p4->address,&p4->tag_k);
 		p3->next=p4;
		p3=p4;
    }
    p3->next=NULL;
	fclose(tree2);


	
}

void judge(PtrTree T,ptrTagNode J)
{
	
	int flag2=0;
	ptrTagNode p5=J;
	if(T==NULL)
		return;
	for(;p5!=NULL;p5=p5->next)
	{
		if(strcmp(T->address,p5->address)==0)
		{
			p5->tag_k=-1;//标记 
			flag2=1;
			goto qq;
		}
		else if(strcmp(p5->name,T->name)==0)
		{
			p5->tag_k=-1;//标记 
			strcpy(_remove[remove_k++],T->name);
			flag=1;
			flag2=1;
			goto qq;
		}
	}
	qq:
	if(!flag2)
	{
		strcpy(add[add_k++],T->name);
		flag=1;	
	}
	
   	for(int i=0;i<T->child_k;i++)
   	{
    	judge(T->child[i],J);
	}
	
}
void Judge(PtrTree T,ptrTagNode J)
{
	if(J==NULL)
		return;
	judge(AddTree,judgeHead);
	ptrTagNode p6;
	for(p6=judgeHead;p6!=NULL;p6=p6->next)
		if(p6->tag_k!=-1)
		{
			strcpy(del[del_k++],p6->name);
			flag3=1;
		}
	if(flag3)
	{
		printf("您的工作区文件有修改\n");
		if(remove_k)
		{ 
			for(int i=0;i<remove_k;i++)
				printf("<移动> %s\n",_remove[i]);
		}
		if(add_k)
		{ 
			for(int i=0;i<add_k;i++)
				printf("<增加> %s\n",add[i]);
		}
		if(del_k)
		{ 
			for(int i=0;i<del_k;i++)
				printf("<删除> %s\n",del[i]);
		}
	}
	else 
		printf("工作区内文件无变动\n"); 
}








