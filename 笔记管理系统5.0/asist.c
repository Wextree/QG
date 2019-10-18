#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <io.h>
#include "note.h"

char Address[4][String_max];

//����Ƿ��д��û�
int check_name(char* name)
{
    char name_f[20],pwd_f[9],path_f[100];
    FILE *fp;
    if((fp=fopen("member.txt","a+"))==NULL)
            {
                printf("�޷����ļ���\n");
                exit(1);
            }
    while(!feof(fp)){
        fscanf(fp,"%s%s%s",name_f,pwd_f,path_f);
        if(strcmp(name_f,name)==0)
            {
				fclose(fp);
				return 1;
			}
    }
    fclose(fp);
    return 0;
}

int layer;

//�����ļ���������
void filesearch(char *path, int layer,PtrTree T)
{
	char curr2[String_max]={0};
	PtrTree q=T;
	int done = 0,handle;   //done Ϊ״̬��Ǳ�����iΪѭ�����ӱ�����handle�����
	char curr[String_max]={0};
    struct _finddata_t filefind;   //�����ļ���Ϣ�ṹ��
	strcpy(curr,path);
    strcat(curr,"\\*.*");       //*.*��ʾ�����������ͣ� �޸Ĵ˴���ı���������
    if((handle = _findfirst(curr, &filefind)) != -1)  //�����λ
    {
        while((done = _findnext(handle, &filefind))==0)  //�ɹ��ƶ��������һ���ļ��������ڣ�
        {

            if(strcmp(filefind.name, "..") == 0)  //��������һ����Ŀ¼��
                continue;
            if((_A_SUBDIR == filefind.attrib))              // ���ļ���
            {
				PtrTree p=(PtrTree)malloc(sizeof(Tree));
				p->tag_k=0;
				p->child_k=0;
				p->isDir=1;
				strcpy(curr2,path);
                strcpy(curr,path);
                strcat(path,"\\" );
                strcat(path,filefind.name); //�����ļ�·��
                strcpy(curr,path);
                strcpy(p->address,path);
                strcpy(p->name,filefind.name);
                T->child[T->child_k++]=p;
                p->pre=T;
                q=p;
                filesearch(curr, layer+1,q);                  // �ݹ������һ����Ŀ¼
				strcpy(curr,curr2);
				strcpy(path,curr2);
            }
            else
            {
            	PtrTree p=(PtrTree)malloc(sizeof(Tree));
				p->tag_k=0;
				p->child_k=0;
				char term[String_max]={0};
				strcpy(term,path);
				strcat(term,"\\");
				strcat(term,filefind.name);
				strcpy(p->name,filefind.name);
				strcpy(p->address,term);
				T->child[T->child_k++]=p;
				p->pre=T;
                p->isDir=0;
            }
        }
        _findclose(handle);  //���پ��
    }
}

int strMatch( const char *str1, const char *str2)//ͨ���㷨
{
    int slen1 = strlen(str1);
    int slen2 = strlen(str2);
    //ʵ��ʹ��ʱ����strl�ĳ�������̬�������ڴ�
    char matchmap[128][128];
    memset(matchmap, 0, 128*128);
    matchmap[0][0] = 1;
    int i, j, k;
    //����Ŀ���ַ�������
    for(i = 1; i<= slen1; ++i)
    {
        //����ͨ�����
        for(j = 1; j<=slen2; ++j)
        {
            //��ǰ�ַ�֮ǰ���ַ��Ƿ��Ѿ��õ�ƥ��
            if(matchmap[i-1][j-1])
            {
                //ƥ�䵱ǰ�ַ�
                if(str1[i-1] == str2[j-1] || str2[j-1] == '?')
                {
                    matchmap[i][j] = 1;
                    //�����Ǻ���ĩβ�����
                    if( i  == slen1 && j < slen2)
                    {
                        for ( k = j+1 ; k <= slen2 ; ++k )
                        {
                            if( '*' == str2[k-1])
                            {
                                matchmap[i][k] = 1;
                            }else{
                                break;
                            }
                        }
                    }
                }else if(str2[j-1] == '*')
                {
                    //�����Ǻţ�Ŀ���ַ�����ĩβ���ܵõ�ƥ��
                    for(k = i-1; k<=slen1; ++k)
                    {
                        matchmap[k][j] = 1;
                    }
                }
            }
        }
        //�����ǰ�ַ��õ���ƥ�������ѭ��������ƥ��ʧ��
        for(k = 1; k<=slen2; ++k)
        {
            if(matchmap[i][k])
            {
                break;
            }
        }
        if(k>slen2)
        {
            return 0;
        }
    }
    return matchmap[slen1][slen2];
}

void PtrFileSearch(char *address,PtrTree *ptr,PtrTree T)
/*����������addressΪ��ƥ���ַ�ַ�����ptrΪ���ؽڵ�ָ�룬TΪ������*/

{
	if(T==NULL)
		return;
	else
    {
    	if(strcmp(T->address,address)==0)
    		*ptr=T;
        int i;
    	for(i=0;i<T->child_k;i++)
    		PtrFileSearch(address,ptr,T->child[i]);
	}
}

void PrintNow(PtrTree T)//��ӡ��ǰĿ¼�����ļ��к��ļ�����
{
    for(int i=0;i<T->child_k;i++)
    {
    	printf("|---");
    	printf("%s",(T->child[i]->isDir)?"[Dir]:":"[File]:");
    	printf("%s\n",T->child[i]->name);
    }
}

void Traverse(PtrTree T)//������ӡ��
{

	if(T==NULL)
     	return;
    else
    {
        int j;
		for(j=0;j<layer-1;j++)
			printf("\t");
		if(layer!=0)
			printf("|---");
		printf("%s",(T->isDir)?"[Dir]:":"[File]:");
    	printf("%s\n",T->name);
    	int i;
    	for(i=0;i<T->child_k;i++)
    	{
    		if(T->child_k!=0)
    			layer++;
    		Traverse(T->child[i]);
    		layer--;
		}

	}

}

//��ȡorder��Ӧ�ַ���
void saveString(char *str)
{
    int n,flag=0;
    int i,j = 0;
    int sign = 0;
    n = strlen(str);
    for(i = 0;i < n - 1;i++)
    {
          if(str[i] == '<')
          {
            if(flag==0)
            sign=1;
            else sign=3;
          }
          if(str[i+1]=='>') {
                Address[sign][j]='\0';
                flag=1;j=0;sign=0;
          }
          if(sign)
            Address[sign][j++] = str[i+1];
    }
}

int searchNow(char *str,PtrTree *ptr,PtrTree T)
// strΪ��ƥ���ļ����֣�ptrΪ���ش���ֵָ�룬TΪPtrNowAddress
{
    for(int i=0;i<T->child_k;i++)
    {
		if(strcmp(T->child[i]->name,str)==0)
		{
			*ptr=T->child[i];
			return 1;
		}
    }
    printf("��ǰĿ¼�޷��ҵ����ļ���\n");
    return 0;
}

