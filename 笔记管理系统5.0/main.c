#include <stdio.h>
#include <tchar.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <io.h>
#include <direct.h>
#include <shellapi.h>
#include "note.h"

PtrTree AddTree; //申请树根节点指针
char root[String_max];
char Address[4][String_max];

char treetxt[String_max];
char treetxt2[String_max];


int main()
{
	judgeHead=NULL;
	TagHead=NULL;
	AddTree=(PtrTree)malloc(sizeof(Tree));
	AddTree->tag_k=0;
	AddTree->child_k=0;
	AddTree->pre=NULL;
	AddTree->isDir=1;
	judgeHead=(ptrTagNode)malloc(sizeof(tagNode));
	TagHead=(ptrTagNode)malloc(sizeof(tagNode));
	strcpy(AddTree->name,"根目录");
    PtrTree ptrNowAddress=AddTree;
    char nowAddress[String_max]={0};
    Login();//登陆界面集合
    strcpy(AddTree->address,root);
    strcpy(nowAddress,root);
    readTree(&TagHead);
	readTag(AddTree);
    char order[String_max]={0};
	Judge(AddTree,judgeHead);
	printf("->");
    getchar();
    while(gets(order))
    {
    	if(strMatch(order,"ls")==1)//已完成
    	{
    		printf(" 显示当前目录下所有的笔记本文件夹，以及笔记文件:\n\n");
    		PrintNow(ptrNowAddress);
		}
 		else if(strMatch(order,"ls -a")==1)//已完成
 		{
 			printf(" 显示所有的笔记文件夹以及笔记文件:\n\n");
 			AddTree->child_k=0;
 			filesearch(root,0,AddTree);
 			PtrFileSearch(nowAddress,&ptrNowAddress,AddTree);
 			Traverse(AddTree);
		}
		else if(strMatch(order,"ls <*>")==1)
		{
			char Address[4][String_max]={0};
			printf(" 显示命令指定文件下所有的内容:\n\n");
			saveString(order);
			printf("%s\n",Address[1]);         //获取地址
            PtrTree ptr;
            PtrFileSearch(Address[1],&ptr,AddTree);      //取得该地址的指针
            PrintNow(ptr);    //打印
		}
		else if(strMatch(order,"ls <*> grep \"*\"")==1)
		{
			char Address[4][String_max]={0};
            printf(" 显示命令指定文件下所有的带有搜索内容的文件夹名及文件名:\n\n");
            saveString(order);
            PtrTree ptr;
	        ptr= (PtrTree *)malloc(sizeof(PtrTree *));
	        PtrFileSearch(Address[1],&ptr,AddTree);
            Search(ptr,Address[2]);
		}
		else if(strMatch(order,"cd..")==1)
		{
            printf(" 本操作将路径切换为当前目录的父目录，若是根目录则则不进行切换\n\n");
            if(ptrNowAddress->pre)
				{ptrNowAddress=ptrNowAddress->pre;
				printf("切换成功！\n\n");}
			else
				printf("已经为根节点！\n\n");
		}
		else if(strMatch(order,"cd <*>")==1)     //将路径切换为命令中输入的文件夹路径
		{
          printf(" 本操作将路径切换为命令中输入的文件夹路径\n\n");
			int ii=0;
			int kk=0;
			while(order[ii]!='\0')
			{
				if(order[ii++]=='<')
					break;
			}
			while(order[ii]!='>')
				nowAddress[kk++]=order[ii++];
			PtrFileSearch(nowAddress,&ptrNowAddress,AddTree);

			printf(" 切换成功！\n\n");
		}
		else if(strMatch(order,"mv <*> <*\\*>")==1)//////未实现
		{
            printf("本操作将笔记文件移动到指定的文件夹目录下\n\n");
            saveString(order);
            PtrTree *ptr;
	        ptr = (PtrTree *)malloc(sizeof(PtrTree *));

	        char tempString[String_max];
	        strcpy(tempString,nowAddress);
	        tempString[strlen(tempString)] = '\\';
            tempString[strlen(tempString) + 1] = '\0';

	        strcat(tempString,Address[1]);
            PtrFileSearch(tempString,ptr,ptrNowAddress);
            Move_File(*ptr,Address[3]);
            AddTree->child_k=0;
			filesearch(root,0,AddTree);
			PtrFileSearch(nowAddress,&ptrNowAddress,AddTree);
			SaveTree2(AddTree);
            printf("移动成功！\n\n");
		}
        else if(strMatch(order,"mv <*> <*>")==1)//////未实现
        {
            printf("将笔记文件进行重命名，从原文件名改为目标文件名\n\n");
            Rename_File(nowAddress,order);
            AddTree->child_k=0;
            filesearch(root,0,AddTree);
            PtrFileSearch(nowAddress,&ptrNowAddress,AddTree);
            SaveTree2(AddTree);
        }
        else if(strMatch(order,"mv -r <*> <*>")==1)// //未实现
        {
            printf("将指定的笔记文件夹移动到目标文件夹目录下\n\n");
            MoveDirectoryP(nowAddress,order);
            AddTree->child_k=0;
			filesearch(root,0,AddTree);
			PtrFileSearch(nowAddress,&ptrNowAddress,AddTree);
			SaveTree2(AddTree);
        }
        else if(strMatch(order,"rm <*>")==1)////未实现
        {
            printf("对笔记文件进行删除。\n\n");
            char root_f[String_max]={0};
            saveString(order);
            strcat(root_f,nowAddress);
            strcat(root_f,"\\");
            strcat(root_f,Address[1]);
            remove(root_f);
            printf("删除成功，请查看对应位置\n\n");
            AddTree->child_k=0;
            filesearch(root,0,AddTree);
            PtrFileSearch(nowAddress,&ptrNowAddress,AddTree);
            SaveTree2(AddTree);
        }
        else if(strMatch(order,"rm -r <*>")==1)//未实现
        {
            printf("删除指定文件以及其内部所有内容。\n\n");
            char dirPath[String_max]={0};
            saveString(order);
            strcat(dirPath,nowAddress);
            strcat(dirPath,"\\");
            strcat(dirPath,Address[1]);
            removeDir(dirPath);
            printf("%s",dirPath);
            remove(dirPath);
            printf("删除成功，请查看对应位置\n");
            AddTree->child_k=0;
            filesearch(root,0,AddTree);
            PtrFileSearch(nowAddress,&ptrNowAddress,AddTree);
            SaveTree2(AddTree);
		}
		else if(strMatch(order,"tag <*>")==1)
		{
			PtrTree pp;
			char s[String_max]={0};
			int ii=0;
			int kk=0;
			while(order[ii]!='\0')
			{
				if(order[ii++]=='<')
					break;
			}
			while(order[ii]!='>')
				s[kk++]=order[ii++];
			searchNow(s,&pp,ptrNowAddress);
			showTag(pp);
			printf("显示指定笔记/文件夹的标签\n");
		}
		else if(strMatch(order,"tag -add <*> \"*\"")==1)
		{
			PtrTree pp;
			char s1[String_max]={0};
			char s2[String_max]={0};
			int ii=0;
			int kk=0;
			int ww=0;
			while(order[ii]!='\0')
			{
				if(order[ii++]=='<')
					break;
			}
			while(order[ii]!='>')
				s1[kk++]=order[ii++];
			while(order[ii]!='\0')
			{
				if(order[ii++]=='"')
					break;
			}
			while(order[ii]!='"')
				s2[ww++]=order[ii++];
			if(searchNow(s1,&pp,ptrNowAddress))
			{
				addTag(s2,pp);
				SaveTree(AddTree);
			}
		}
		else if(strMatch(order,"tag -del <*> \"*\"")==1)
		{
						PtrTree pp;
			char s1[String_max]={0};
			char s2[String_max]={0};
			int ii=0;
			int kk=0;
			int ww=0;
			while(order[ii]!='\0')
			{
				if(order[ii++]=='<')
					break;
			}
			while(order[ii]!='>')
				s1[kk++]=order[ii++];
			while(order[ii]!='\0')
			{
				if(order[ii++]=='"')
					break;
			}
			while(order[ii]!='"')
				s2[ww++]=order[ii++];
			if(searchNow(s1,&pp,ptrNowAddress));
			{
				delTag(s2,pp);
				SaveTree(AddTree);
			}
			printf("为删除指定笔记/文件夹的指定标签\n");
		}
		else if(strMatch(order,"tag -s \"*\"")==1)
		{
			char s[String_max]={0};
			int ii=0;
			int kk=0;
			while(order[ii]!='\0')
			{
				if(order[ii++]=='"')
					break;
			}
			while(order[ii]!='"')
				s[kk++]=order[ii++];
			searchTag(s,ptrNowAddress);
			printf("根据标签内容，在当前目录下进行笔记搜索，输出匹配的标签所对应的笔记文件名\n");
		}
		else if(strMatch(order,"tag -sa \"*\"")==1)
		{
			char s[String_max]={0};
			int ii=0;
			int kk=0;
			while(order[ii]!='\0')
			{
				if(order[ii++]=='"')
					break;
			}
			while(order[ii]!='"')
				s[kk++]=order[ii++];
			searchAllTag(s,AddTree);
			printf("根据标签内容，对所有笔记进行搜索，输出匹配的标签所对应的笔记的文件名以及绝对路径\n");
		}
		else if(strMatch(order,"md <*>")==1)
		{
			saveString(order);
			Create_directory(AddTree,Address[1]);
			SaveTree(AddTree);
			printf("笔记文件夹文件夹已经建好！\n\n");

		}
		else if(strMatch(order,"sort <*>")==1)
		{
			printf("对指定文件夹内的笔记文件进行排序\n");
		}
		else if(strMatch(order,"exit")==1)
		{
			SaveTree2(AddTree);
			exit(0);
		}
		else
		{
	        printf("无此指令，请查正后输入！\n");
		}

		printf("->");
	}
    return 0;
}
