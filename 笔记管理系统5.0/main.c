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

PtrTree AddTree; //���������ڵ�ָ��
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
	strcpy(AddTree->name,"��Ŀ¼");
    PtrTree ptrNowAddress=AddTree;
    char nowAddress[String_max]={0};
    Login();//��½���漯��
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
    	if(strMatch(order,"ls")==1)//�����
    	{
    		printf(" ��ʾ��ǰĿ¼�����еıʼǱ��ļ��У��Լ��ʼ��ļ�:\n\n");
    		PrintNow(ptrNowAddress);
		}
 		else if(strMatch(order,"ls -a")==1)//�����
 		{
 			printf(" ��ʾ���еıʼ��ļ����Լ��ʼ��ļ�:\n\n");
 			AddTree->child_k=0;
 			filesearch(root,0,AddTree);
 			PtrFileSearch(nowAddress,&ptrNowAddress,AddTree);
 			Traverse(AddTree);
		}
		else if(strMatch(order,"ls <*>")==1)
		{
			char Address[4][String_max]={0};
			printf(" ��ʾ����ָ���ļ������е�����:\n\n");
			saveString(order);
			printf("%s\n",Address[1]);         //��ȡ��ַ
            PtrTree ptr;
            PtrFileSearch(Address[1],&ptr,AddTree);      //ȡ�øõ�ַ��ָ��
            PrintNow(ptr);    //��ӡ
		}
		else if(strMatch(order,"ls <*> grep \"*\"")==1)
		{
			char Address[4][String_max]={0};
            printf(" ��ʾ����ָ���ļ������еĴ����������ݵ��ļ��������ļ���:\n\n");
            saveString(order);
            PtrTree ptr;
	        ptr= (PtrTree *)malloc(sizeof(PtrTree *));
	        PtrFileSearch(Address[1],&ptr,AddTree);
            Search(ptr,Address[2]);
		}
		else if(strMatch(order,"cd..")==1)
		{
            printf(" ��������·���л�Ϊ��ǰĿ¼�ĸ�Ŀ¼�����Ǹ�Ŀ¼���򲻽����л�\n\n");
            if(ptrNowAddress->pre)
				{ptrNowAddress=ptrNowAddress->pre;
				printf("�л��ɹ���\n\n");}
			else
				printf("�Ѿ�Ϊ���ڵ㣡\n\n");
		}
		else if(strMatch(order,"cd <*>")==1)     //��·���л�Ϊ������������ļ���·��
		{
          printf(" ��������·���л�Ϊ������������ļ���·��\n\n");
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

			printf(" �л��ɹ���\n\n");
		}
		else if(strMatch(order,"mv <*> <*\\*>")==1)//////δʵ��
		{
            printf("���������ʼ��ļ��ƶ���ָ�����ļ���Ŀ¼��\n\n");
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
            printf("�ƶ��ɹ���\n\n");
		}
        else if(strMatch(order,"mv <*> <*>")==1)//////δʵ��
        {
            printf("���ʼ��ļ���������������ԭ�ļ�����ΪĿ���ļ���\n\n");
            Rename_File(nowAddress,order);
            AddTree->child_k=0;
            filesearch(root,0,AddTree);
            PtrFileSearch(nowAddress,&ptrNowAddress,AddTree);
            SaveTree2(AddTree);
        }
        else if(strMatch(order,"mv -r <*> <*>")==1)// //δʵ��
        {
            printf("��ָ���ıʼ��ļ����ƶ���Ŀ���ļ���Ŀ¼��\n\n");
            MoveDirectoryP(nowAddress,order);
            AddTree->child_k=0;
			filesearch(root,0,AddTree);
			PtrFileSearch(nowAddress,&ptrNowAddress,AddTree);
			SaveTree2(AddTree);
        }
        else if(strMatch(order,"rm <*>")==1)////δʵ��
        {
            printf("�Աʼ��ļ�����ɾ����\n\n");
            char root_f[String_max]={0};
            saveString(order);
            strcat(root_f,nowAddress);
            strcat(root_f,"\\");
            strcat(root_f,Address[1]);
            remove(root_f);
            printf("ɾ���ɹ�����鿴��Ӧλ��\n\n");
            AddTree->child_k=0;
            filesearch(root,0,AddTree);
            PtrFileSearch(nowAddress,&ptrNowAddress,AddTree);
            SaveTree2(AddTree);
        }
        else if(strMatch(order,"rm -r <*>")==1)//δʵ��
        {
            printf("ɾ��ָ���ļ��Լ����ڲ��������ݡ�\n\n");
            char dirPath[String_max]={0};
            saveString(order);
            strcat(dirPath,nowAddress);
            strcat(dirPath,"\\");
            strcat(dirPath,Address[1]);
            removeDir(dirPath);
            printf("%s",dirPath);
            remove(dirPath);
            printf("ɾ���ɹ�����鿴��Ӧλ��\n");
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
			printf("��ʾָ���ʼ�/�ļ��еı�ǩ\n");
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
			printf("Ϊɾ��ָ���ʼ�/�ļ��е�ָ����ǩ\n");
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
			printf("���ݱ�ǩ���ݣ��ڵ�ǰĿ¼�½��бʼ����������ƥ��ı�ǩ����Ӧ�ıʼ��ļ���\n");
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
			printf("���ݱ�ǩ���ݣ������бʼǽ������������ƥ��ı�ǩ����Ӧ�ıʼǵ��ļ����Լ�����·��\n");
		}
		else if(strMatch(order,"md <*>")==1)
		{
			saveString(order);
			Create_directory(AddTree,Address[1]);
			SaveTree(AddTree);
			printf("�ʼ��ļ����ļ����Ѿ����ã�\n\n");

		}
		else if(strMatch(order,"sort <*>")==1)
		{
			printf("��ָ���ļ����ڵıʼ��ļ���������\n");
		}
		else if(strMatch(order,"exit")==1)
		{
			SaveTree2(AddTree);
			exit(0);
		}
		else
		{
	        printf("�޴�ָ�����������룡\n");
		}

		printf("->");
	}
    return 0;
}
