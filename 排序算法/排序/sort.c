#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>


typedef int Elemtype;

//��������
void Insertsort(Elemtype arr[], int n)
{
	int i,j;
	Elemtype tmp;
	for( i=1; i<n; i++ )
	{
		tmp = arr[i];//��ȡ��i��Ԫ��
		for( j=i; j>0&&arr[j-1]>tmp; j-- )//ѭ�������ֱ�i���Ԫ��ʱ��ѭ��δ����һ��Ԫ��ʱ
			arr[j] = arr[j-1];//����a[j]���Ԫ�غ���
		arr[j] = tmp;
	}
}

//�鲢����
void Merge( Elemtype arr[], Elemtype Tmparr[], int L, int R, int Rightend )
{
	int Leftend = R-1;//��ȡ������β��
	int i,tmp = L;
	int len = Rightend-L+1;//��ȡ���鳤��
	while( L<=Leftend&&R<=Rightend ){//ֱ����������һ������β��ǰ��������������������������
		if( arr[L]<=arr[R])  Tmparr[tmp++]=arr[L++];
		else Tmparr[tmp++]=arr[R++];
	}
	while( L<=Leftend )  Tmparr[tmp++]=arr[L++];//δ����Ĳ��ִ�������
	while( R<=Rightend ) Tmparr[tmp++]=arr[R++];
	for( i=0; i<len; i++, Rightend--)//���������������ԭ����
	 arr[Rightend] = Tmparr[Leftend];
}

//���ϲ������
void MSort( Elemtype arr[], Elemtype Tmparr[], int Left, int Right )
{
	int Center;
	if( Left<Right )
	{
		Center = (Left + Right)/2;
		MSort( arr, Tmparr, Left, Center );
		MSort( arr, Tmparr, Center+1, Right );
		Merge( arr, Tmparr, Left, Center+1, Right );
	}
}

//�鲢����ӿ�
void Mergesort( Elemtype arr[], int n)
{
	Elemtype *Tmparr;
	Tmparr = malloc( n*sizeof( Elemtype ));
	if( Tmparr!=NULL ){
		MSort( arr, Tmparr, 0, n-1 );
		free( Tmparr );//�ͷ�
	}
	else
	  printf("No space");
}

//����ȡ���Ż���������
Elemtype Median3( Elemtype arr[], int Left, int Right )
{
	int Center = (Left+Right)/2;
	if( arr[Left]>arr[Center] ) swap( &arr[Left], &arr[Center] );
	if( arr[Left]>arr[Right] ) swap( &arr[Left], &arr[Right] );
	if( arr[Center]>arr[Right] ) swap( &arr[Center], &arr[Right] );
	swap( &arr[Center], &arr[Right-1] );
	return arr[Right-1];
}
//���ڵ��ݹ鵽��С����ʱ������ȡ�п���Ч�ʵͣ����ò��Ž��
void Qsort( Elemtype arr[], int Left, int Right )
{
	int i,j;
	Elemtype Pivot;
	if( Left + 3 <=Right )
	{
		Pivot=Median3( arr, Left, Right );//�����Ŧ
		i = Left; j = Right-1;
		for( ; ; )//��С�ķ�����Ŧ��ˣ���ķ�����Ŧ�Ҷ�
		{
			while( arr[++i]<Pivot ) {};
			while( arr[--j]>Pivot ) {};
			if( i<j ) swap( &arr[i], &arr[j] );
			else break;
		}
		swap( &arr[i], &arr[Right-1] );	//ȷ-����Ŧ��λ��
		// ����Ŧ����������ͬ����ʽȷ��λ��
		Qsort( arr, Left, i-1 );
		Qsort( arr, i+1, Right );
	}
	else{//С�����ò���
		Insertsort( arr+Left , Right-Left+1 );
	}
}

//���Žӿ�
void Quicksort( Elemtype arr[], int n)
{
	Qsort( arr, 0, n-1 );
}

//�����������ĺ���
void swap(Elemtype *a,Elemtype *b)
{
    Elemtype temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

//�ǵݹ���ţ�ʵ�ַ�ʽ�����ýṹ������
//�ṹ���д�����Ҷ�
struct node{
	int left;
	int right;
};

//˼������Ż���һ������ͬ�ط������ýṹ�岻�ϼ�¼���Ҽ��ޣ�ֱ�������0
void TQsort( Elemtype arr[], int left, int right )
{
	int Pivot, i,j;
	struct node stack[100];
	int top=0;
	stack[top].left = left;
    stack[top].right = right;
    while( top>=0 ){
    	i=left=stack[top].left;//��ȡ�µ����Ҷ�
    	j=right=stack[top].right;
    	top--;
    	Pivot=arr[left];
    	while(i<j)//��С�ķ�����Ŧ��ˣ���ķ�����Ŧ�Ҷ�
    	{
    		while(i<j&&Pivot<=arr[j]) {j--;}
    		if( i<j ){
    			swap( &arr[i], &arr[j] );
    			i++;
    		}
    		while(i<j&&Pivot>=arr[i]) {i++;}
    		if( i<j ){
    			swap( &arr[i], &arr[j] );
    			j--;
    		}
    	}
    	if( left<i-1 )//��¼�µ����Ҷ�
    	{
    		top++;
        	stack[top].left = left;
        	stack[top].right = i-1;
    	}
    	if( right>i+1 )
    	{
    		top++;
        	stack[top].left = i+1;
        	stack[top].right = right;
    	}
    }
}

//�ǵݹ���Žӿ�
void TQuicksort( Elemtype arr[], int n)
{
	TQsort( arr, 0, n-1 );
}

//��������
//����������ܿ죬������������һ�����ڴ棬���²�ͬ������ʱ����������
void Countsort( Elemtype arr[], int n,long int  max )
{
	int i;
	//�������飬����ͳ������arr�и�����ͬ�����ֵĴ���
	Elemtype *count_arr=(int*)malloc(sizeof(int)*max);
	Elemtype *sort_arr=(int*)malloc(sizeof(int)*n);
	//ͳ������arr�и�����ͬ�����ֵĴ���
	for( i=0; i<n; i++ )
		count_arr[arr[i]]++;
	for(  i=1; i<max; i++ )
		count_arr[i]+=count_arr[i-1];//���򣬲���ͳ�������Ӧλ������һ
	for(  i=n-1; i>=0; i-- )
		sort_arr[--count_arr[arr[i]]]=arr[i];
	memcpy( arr, sort_arr, n*sizeof(int) );//��������������ԭ����
	free(count_arr);//�ͷ��ڴ�
	free(sort_arr);
}

int temps[10][200000];
//��ȡ���λ����λ��
int getExp(Elemtype arr[],int n){

    int i;
    Elemtype max = arr[0];
    //�ҵ�����������
    for(i=1;i<n;++i){
        max = arr[i]>max?arr[i]:max;
    }
    int exps = 1;
    max/=10;
    //��ȡ���λ��
    while(max){
        max /= 10;
        exps++;
    }
    return exps;
}

//��������
void Radixsort(Elemtype arr[],int n){
    //��ÿ��Ͱ�����ĸ���
    int i,j,e;
    Elemtype countarr[10] = {0};//��ʼ��
    int exps = getExp(arr,n);//��ȡ���λ��
    int exp = 1;
    for(e=0;e<exps;++e){
        //��Ͱ
        for(i=0;i<n;++i){
            int index = (arr[i]/exp)%10;//��õ�expλ���ִ�С
            temps[index][countarr[index]++] = arr[i];//����expλ������Ͱ
        }
        int k=0;//ȡֵ���ı�����
        for(i=0;i<10;++i){
            //���Ͱ�����ĸ�������0
            if(countarr[i]>0){
                int n  = countarr[i];
                //����ȡ�����ı�����
                for(j =0;j<n;++j){
                    arr[k++] = temps[i][j];
                }
            }
        }
        //��Ͱ�е����ĸ�������Ϊ0
        for(i=0;i<10;++i)
            countarr[i] = 0;
        exp *=10;//λ���ı�
    }

}

//�ж��Ƿ��������
bool isSort(Elemtype arr[], int n)
{
	 int i;
	 bool flag = true;
	 for( i=0; i<n-1; i++ )
	 {
	 	if(arr[i] > arr[i+1]){
	 	 flag = false;
	 	 break;
	 	}
	 }
	 return flag;
}























