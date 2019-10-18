#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <io.h>
#include "note.h"

char Address[4][String_max];

//检查是否有此用户
int check_name(char* name)
{
    char name_f[20],pwd_f[9],path_f[100];
    FILE *fp;
    if((fp=fopen("member.txt","a+"))==NULL)
            {
                printf("无法打开文件！\n");
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

//遍历文件夹生成树
void filesearch(char *path, int layer,PtrTree T)
{
	char curr2[String_max]={0};
	PtrTree q=T;
	int done = 0,handle;   //done 为状态标记变量，i为循环叠加变量，handle句柄。
	char curr[String_max]={0};
    struct _finddata_t filefind;   //定义文件信息结构体
	strcpy(curr,path);
    strcat(curr,"\\*.*");       //*.*表示搜索所有类型， 修改此处则改变搜索条件
    if((handle = _findfirst(curr, &filefind)) != -1)  //句柄定位
    {
        while((done = _findnext(handle, &filefind))==0)  //成功移动句柄到下一个文件（若存在）
        {

            if(strcmp(filefind.name, "..") == 0)  //跳过【上一个】目录行
                continue;
            if((_A_SUBDIR == filefind.attrib))              // 是文件夹
            {
				PtrTree p=(PtrTree)malloc(sizeof(Tree));
				p->tag_k=0;
				p->child_k=0;
				p->isDir=1;
				strcpy(curr2,path);
                strcpy(curr,path);
                strcat(path,"\\" );
                strcat(path,filefind.name); //更新文件路径
                strcpy(curr,path);
                strcpy(p->address,path);
                strcpy(p->name,filefind.name);
                T->child[T->child_k++]=p;
                p->pre=T;
                q=p;
                filesearch(curr, layer+1,q);                  // 递归遍历下一个子目录
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
        _findclose(handle);  //销毁句柄
    }
}

int strMatch( const char *str1, const char *str2)//通配算法
{
    int slen1 = strlen(str1);
    int slen2 = strlen(str2);
    //实际使用时根据strl的长度来动态分配表的内存
    char matchmap[128][128];
    memset(matchmap, 0, 128*128);
    matchmap[0][0] = 1;
    int i, j, k;
    //遍历目标字符串符串
    for(i = 1; i<= slen1; ++i)
    {
        //遍历通配符串
        for(j = 1; j<=slen2; ++j)
        {
            //当前字符之前的字符是否已经得到匹配
            if(matchmap[i-1][j-1])
            {
                //匹配当前字符
                if(str1[i-1] == str2[j-1] || str2[j-1] == '?')
                {
                    matchmap[i][j] = 1;
                    //考虑星号在末尾的情况
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
                    //遇到星号，目标字符串到末尾都能得到匹配
                    for(k = i-1; k<=slen1; ++k)
                    {
                        matchmap[k][j] = 1;
                    }
                }
            }
        }
        //如果当前字符得到了匹配则继续循环，否则匹配失败
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
/*搜索函数，address为待匹配地址字符串，ptr为返回节点指针，T为搜索树*/

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

void PrintNow(PtrTree T)//打印当前目录所有文件夹和文件名字
{
    for(int i=0;i<T->child_k;i++)
    {
    	printf("|---");
    	printf("%s",(T->child[i]->isDir)?"[Dir]:":"[File]:");
    	printf("%s\n",T->child[i]->name);
    }
}

void Traverse(PtrTree T)//遍历打印树
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

//提取order对应字符串
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
// str为待匹配文件名字，ptr为返回待赋值指针，T为PtrNowAddress
{
    for(int i=0;i<T->child_k;i++)
    {
		if(strcmp(T->child[i]->name,str)==0)
		{
			*ptr=T->child[i];
			return 1;
		}
    }
    printf("当前目录无法找到该文件！\n");
    return 0;
}

