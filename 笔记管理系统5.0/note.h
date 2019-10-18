#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#define LEN sizeof(member)

#define String_max 100
#define Child_max 20
#define Tag_max 20

typedef struct member{              //�����û���Ϣ
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

typedef struct Node{                      //����ȫ���ļ����ļ�����Ϣ
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




//ʵ�ֹ��ܵĺ���
void screen();            //����
void create(char* name);        //ע��
void login(char *path,char* name);      //��½
void Login();      //��½��ע��ĺϼ�
void MoveDirectoryP(char* nowAddress,char* order);      //ָ���ıʼ��ļ����ƶ���Ŀ���ļ���Ŀ¼��
void Move_File(PtrTree T,char *newAdress);        //�ƶ��ļ�
void Rename_File(char nowAddress[String_max],char order[String_max]);    //�������ļ�
void Create_directory(PtrTree T,char *fileName);            //�����ļ���
void Search(PtrTree T,char *str);                    //����ָ������
int removeDir(const char*  dirPath);   //ɾ��ָ���ļ��Լ����ڲ��������ݡ�

//��������s
int check_name(char* name);       //����Ƿ�������û�
void filesearch(char *path, int layer,PtrTree T);   //�����ļ���������
int strMatch( const char *str1, const char *str2);   //�ַ�ͨ�亯��
void PtrFileSearch(char *address,PtrTree *ptr,PtrTree T);  //���ݵ�ַ��Ѱ���������
void Traverse(PtrTree T);  //������ӡ��
void PrintNow(PtrTree T);   //��ӡ��ǰĿ¼�����ļ��к��ļ�����
void saveString(char *str);   //�����ļ����ļ���ַ��
void wopen(); // ûɶ�õ��ǲ���ɾ
void wclose();//ûɶ�õ��ǲ���ɾ
void saveTree(PtrTree T);//ûɶ�õ��ǲ���ɾ
void SaveTree(PtrTree T);//���浵
void readTree();//������
void addTag(char *str,PtrTree T);//��ӱ�ǩ
void showTag(PtrTree T);//��ǩ���أ���Ҫ�ȶ���
void searchTag(char *str,PtrTree T);//��ǰĿ¼Ѱ�Һ��иñ�ǩ���ļ�����ӡ
void delTag(char *str,PtrTree T);//ɾ����ǩ
void searchAllTag(char *str,PtrTree T);//�����ļ���Ѱ�Һ��иñ�ǩ���ļ�����ӡ
void readTag(PtrTree T);//���ر�ǩ
int searchNow(char *str,PtrTree *ptr,PtrTree T);//�����ļ������ڵ�ǰĿ¼Ѱ�Ҹ��ļ������ظ��ļ�ָ��
void SaveTree2(PtrTree T);
void wclose2();
void wopen2();
void readJudge();
void readTree(ptrTagNode *J);
void tranLine(PtrTree T,ptrTagNode J);
void judge(PtrTree T,ptrTagNode J);
void Judge(PtrTree T,ptrTagNode J);

#endif
