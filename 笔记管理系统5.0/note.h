#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#define LEN sizeof(member)

#define String_max 100
#define Child_max 20
#define Tag_max 20

typedef struct member{              //储存用户信息
    char name[20];
    char password[9];
    char path[100];
}member;

typedef struct tagNode{
	char name[String_max];
	char address[String_max];
	int tag_k;
	char tag[Tag_max][String_max];
	struct tagNode *next;
}*ptrTagNode,tagNode;

typedef struct Node{                      //储存全部文件及文件夹信息
	char name[String_max];
    char address[String_max];
	struct Node *child[Child_max];
	struct Node *pre;
	int	child_k;
	int tag_k;
	int isDir;
	char tag[Tag_max][String_max];
}*PtrTree,Tree;

FILE *tree,*tree2;
char treetxt[String_max];
char treetxt2[String_max];
ptrTagNode TagHead,p1,p2;
ptrTagNode judgeHead,p3,p4;




//实现功能的函数
void screen();            //界面
void create(char* name);        //注册
void login(char *path,char* name);      //登陆
void Login();      //登陆与注册的合集
void MoveDirectoryP(char* nowAddress,char* order);      //指定的笔记文件夹移动到目标文件夹目录下
void Move_File(PtrTree T,char *newAdress);        //移动文件
void Rename_File(char nowAddress[String_max],char order[String_max]);    //重命名文件
void Create_directory(PtrTree T,char *fileName);            //创建文件夹
void Search(PtrTree T,char *str);                    //搜索指定内容
int removeDir(const char*  dirPath);   //删除指定文件以及其内部所有内容。

//辅助函数s
int check_name(char* name);       //检查是否有这个用户
void filesearch(char *path, int layer,PtrTree T);   //遍历文件夹生成树
int strMatch( const char *str1, const char *str2);   //字符通配函数
void PtrFileSearch(char *address,PtrTree *ptr,PtrTree T);  //根据地址搜寻到该树结点
void Traverse(PtrTree T);  //遍历打印树
void PrintNow(PtrTree T);   //打印当前目录所有文件夹和文件名字
void saveString(char *str);   //保存文件名文件地址等
void wopen(); // 没啥用但是不能删
void wclose();//没啥用但是不能删
void saveTree(PtrTree T);//没啥用但是不能删
void SaveTree(PtrTree T);//树存档
void readTree();//树读档
void addTag(char *str,PtrTree T);//添加标签
void showTag(PtrTree T);//标签加载，需要先独挡
void searchTag(char *str,PtrTree T);//当前目录寻找含有该标签的文件并打印
void delTag(char *str,PtrTree T);//删除标签
void searchAllTag(char *str,PtrTree T);//所有文件中寻找含有该标签的文件并打印
void readTag(PtrTree T);//加载标签
int searchNow(char *str,PtrTree *ptr,PtrTree T);//传入文件名，在当前目录寻找该文件，返回该文件指针
void SaveTree2(PtrTree T);
void wclose2();
void wopen2();
void readJudge();
void readTree(ptrTagNode *J);
void tranLine(PtrTree T,ptrTagNode J);
void judge(PtrTree T,ptrTagNode J);
void Judge(PtrTree T,ptrTagNode J);

#endif
