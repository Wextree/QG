#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{ int data;
  struct Node *next;
}Node, *ptr_Node;

typedef enum Status
{
	SUCCESS,
	ERROR
}Status;

//������������һ�������ɹ��򷵻�ͷ�ڵ㣬ʧ�ܷ��� NULL
ptr_Node create(int *arr, int n)
{
  int i=0;   //����������ѭ��������Ϊ������±�
  ptr_Node p,q;//������������ռ�
  ptr_Node head;//��Ŵ����������ͷ���
  head=NULL;//����һ��ʼ�Ľ��
  p=q=(Node*)malloc(sizeof(Node));// ��ʼ�����ڴ�ռ�
  p->data=*arr;// ����һ�������ֵ
  while(i<n-1)//��ʼ���и�ֵ���Ҵ����µĿռ��ѭ��
  {
      i++;
      if(i==1)//��������
      head=p;//��ͷ��㸳ֵ
      else q->next=p;// �����ָ������
      q=p;
      p=(Node*)malloc(sizeof(Node));//�����µ��ڴ�
      p->data=*(arr+i);//���ж�Ӧ�ĸ�ֵ
  }
  q->next=p;
  p->next=NULL;//��βָ��ָ��NULL
  return head;//����ͷ���
}
//���ٸ���������
void destroy(ptr_Node head)
{
	ptr_Node p,q;
	p=head;//����ͷ����ָ��
	while(p)//ѭ��ֱ�������
	{
	    q=p->next;//���������
	    free(p);//�ͷ��ڴ�
	    p=q;
	}
}

//�ڵ� index λ������� node ���
//����ɹ����� SUCCESS��ʧ�ܷ��� ERROR
Status insert(ptr_Node *head, ptr_Node node, int index)
{
	int i=0;
	ptr_Node cur,pre;//����һ��ָ�����ں�֮ǰ��ָ��
	cur=*head;//��ֵͷ���
	pre=NULL;//����ָ��
	while(cur&&i<index)//Ѱ����Ҫ�Ľ��λ��
    {
        pre=cur;//����֮ǰ�Ľ��
        cur=cur->next;//��������ƶ�
        ++i;
    }
    if(!cur||i>index)//�ж��Ƿ��ҵõ��Ǹ����
        return ERROR;
    node->next=cur;//��������ָ��ָ�����ڵ��Ǹ�ָ��
    if(pre==NULL)//�ж��ǲ���ͷ����λ��
        *head=node;//ֱ�Ӱ������Ľ�㸳ֵ��head
    else
        pre->next=node;//������ǲ���ͷ����һ�����
    return SUCCESS;
}

//ɾ���� index λ�ڵ����Ľڵ㣬��ɾ���Ľ���ֵ���浽��*data����
//ɾ���ɹ����� SUCCESS������������� ERROR
Status delete(ptr_Node *head, int index, int *data)
{
	int i=0;
	ptr_Node cur,pre;//����һ��ָ�����ں�֮ǰ��ָ��
	cur=*head;//��ֵͷ���
	pre=NULL;//����ָ��
    while(cur&&i<index)//Ѱ����Ҫ�Ľ��λ��
    {
        pre=cur;//����֮ǰ�Ľ��
        cur=cur->next;//��������ƶ�
        ++i;
    }
    if(!cur||i>index)//�ж��Ƿ��ҵõ��Ǹ����
        return ERROR;
    if(pre==NULL)//�ж���ɾ��ͷ����λ��
        *head=cur->next;
    else//�������ͷ����һ�����
        pre->next=cur->next;
    *data=cur->data;//ɾ�����Ǹ�ֵ��������
    free(cur);//�ͷ�ɾ�������ڴ�
    return SUCCESS;
}


//�������в��ҽڵ�ֵ�� data ��ȵĽڵ㣬�������ҵ��ĵ�һ���ڵ��ǰһ���ڵ��λ��
//������ͷ�ڵ���ȣ����� 0����û�ҵ����������������-1
int search(ptr_Node head, int data)
{
	int i=1;
	ptr_Node p;
	p=head;//�����ָ��pָ��ͷ���
	while (p)//��Ѱ����ֵ��ȵ��Ǹ������
    {
        if(p->data==data)//�ҵ���ֱ���˳�ѭ��
            break;
        p=p->next;//���û���ҵ��ͼ�����Ѱ����Ľ��
        i++;
    }
    if(i==1)//�ж���ͷ����λ��
        return 0;
    else if(p)
        return i-1;//�����ҵ����Ǹ�λ�õ�ǰһ������λ��
    else  return -1;//����Ҳ����ͷ���-1
}


//�������� index λ�����Ľ���ֵ�޸�Ϊ(*data)����ԭֵ���浽(*data)
//�޸ĳɹ����� SUCCESS������������� ERROR
Status edit(ptr_Node head,int index,int *data)
{
   int i,temp;//����һ��������һ�����������ֵ
   i=1;
   ptr_Node p;
   p=head;//�����һ��ָ������ָ��ͷ���
   while(p->next&&i<index)//Ѱ����Ҫ������ֵ���Ǹ�λ��
   {
       p=p->next;
       i++;
   }
   if(!(p->next)||i>index)//�ж��Ƿ��ҵõ�
    return ERROR;
   temp=p->next->data;//��������Ϊ����ֵ
   p->next->data=*data;
   *data=temp;//��������ֵ�����data��
   return SUCCESS;
}
//����ѡ��,ʵ�ֵ������սڵ�ֵ��С��������
Status sort(ptr_Node *head)
{
  if(!head)//�ж��Ƿ񴩴�����һ����ָ��
    return ERROR;                                                                                        //���˺ܶ�Σ����ڲ���˵ֱ�ӳ���������
  ptr_Node p,q;
  int temp;                                                                                              //��������һֱ���һ����֪����ʲô�ķ���
  for(p=*head;(p->next)!=NULL;p=p->next)//��һ��ѭ���ӵ�һ������ֵ��ʼ�����������ֵ���бȽ�
  {
    for(q=p->next;q!=NULL;q=q->next)//ѭ����һ��ѭ��p�����ʣ�½���ֵ
  {
      if(p->data>q->data)//����ֵ�Ĵ�С�ıȽ�
      {
          temp=p->data;//���������н���ֵ�Ľ���
          p->data=q->data;
          q->data=temp;
      }
  }
  }
  return SUCCESS;
}

//��������ֵ����һ���ĸ�ʽ�����ÿ�ж��ٸ��Լ����壬��ʽԽƯ��Խ�ã�
void print(ptr_Node head)
{
  int i;//�������Ű��������
  ptr_Node p;
  p=head;
  printf("print this Linklist:\n");
  for(i=1;p!=NULL;i++)
  {
      printf("%6d",p->data);//�����Ӧ����ֵ
      if(i%4==0)//ÿ�ĸ�ֵ�ͻ���
        printf("\n");
      p=p->next;
  }
}

int main()
{
     int i,n,len,choose,index,data;//�����������Ҫ�ı���
     printf("��������Ҫ����һ������.\n");//�����û�����һ���µ������Ա���и��ֲ���
     printf("��������������ĳ��ȣ�");
     scanf("%d",&n);
     printf("\n");
     int arr[n];
     printf("����������ÿ������Ӧ��ֵ������ֵ֮���ÿո�ֿ�����\n");
     for(i=0;i<n;i++)//���������ֵ
     {
         scanf("%d",&arr[i]);
     }
     ptr_Node head;//����һ��ָ����ͷ���
     head=create(arr, n);
     print(head);
     printf("\n");
     printf("---------------------------------------------------------------\n");//��ʾ�Է����и��ֲ���
     printf("1.������ 2.ɾ����� 3.Ѱ�ҽ�� 4.�༭��� 5.������ 0.�˳�\n");
     printf("---------------------------------------------------------------\n");
     scanf("%d",&choose);//������Ŷ�Ӧ����
     while(choose)//��ѭ�����û����Զ��ʹ�ù���
    {
     switch(choose)//ʹ�ö�ѡ�������ܷ��࣬ʵ�ֽ���
     {
        case 1:printf("����һ��λ�ü���Ҫ�����ֵ���м��ÿո�ֿ�����\n");
               scanf("%d %d",&index,&data);
               ptr_Node node=(Node*)malloc(sizeof(Node));
               node->data=data;
               node->next=NULL;
               if(insert(&head,node,index)) printf("�����������Ϣ�Ƿ�������������\n");
               else print(head);printf("\n");break;
        case 2:printf("��������Ҫɾ����λ�ã�\n");
               scanf("%d",&index);
               if(delete(&head,index,&data)) printf("�����������Ϣ�Ƿ�������������\n");
               else print(head);printf("\n");break;
        case 3:printf("��������Ҫ���ҵĽ���ֵ��\n");
               scanf("%d",&data);
               printf("��Ҫ���ҵ�ֵ��λ����%d��0��ʾ��ͷ��㣬-1��ʾ�Ҳ�����",search(head,data));
               printf("\n");break;
        case 4:printf("��������Ҫ�༭�Ľ���λ�ú�ֵ���м��ÿո�ֿ�����\n");
               scanf("%d %d",&index,&data);
               if(edit(head,index,&data)) printf("�����������Ϣ�Ƿ�������������\n");
               else print(head);printf("\n");break;
        case 5:if(sort(&head)) printf("�����������Ϣ�Ƿ�������������\n");
               else print(head);printf("\n");break;
        default:printf("��ѡ����ڣ����������룡����\n\n");break;
     }
    printf("---------------------------------------------------------------\n");
     printf("1.������ 2.ɾ����� 3.Ѱ�ҽ�� 4.�༭��� 5.������ 0.�˳�\n");
     printf("---------------------------------------------------------------\n");
     scanf("%d",&choose);
     }
     destroy(head);//����ʹ���������Ŀռ��������
     return 0;
}
