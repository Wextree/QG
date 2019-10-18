#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>


typedef int Elemtype;

//插入排序
void Insertsort(Elemtype arr[], int n)
{
	int i,j;
	Elemtype tmp;
	for( i=1; i<n; i++ )
	{
		tmp = arr[i];//获取第i个元素
		for( j=i; j>0&&arr[j-1]>tmp; j-- )//循环当出现比i大的元素时或循环未到第一个元素时
			arr[j] = arr[j-1];//将比a[j]大的元素后移
		arr[j] = tmp;
	}
}

//归并排序
void Merge( Elemtype arr[], Elemtype Tmparr[], int L, int R, int Rightend )
{
	int Leftend = R-1;//获取左数组尾端
	int i,tmp = L;
	int len = Rightend-L+1;//获取数组长度
	while( L<=Leftend&&R<=Rightend ){//直到到达其中一个数组尾部前，将数促销到大存入第三方数组
		if( arr[L]<=arr[R])  Tmparr[tmp++]=arr[L++];
		else Tmparr[tmp++]=arr[R++];
	}
	while( L<=Leftend )  Tmparr[tmp++]=arr[L++];//未排序的部分存入数组
	while( R<=Rightend ) Tmparr[tmp++]=arr[R++];
	for( i=0; i<len; i++, Rightend--)//将排序后的数组存入原数组
	 arr[Rightend] = Tmparr[Leftend];
}

//不断拆分序列
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

//归并排序接口
void Mergesort( Elemtype arr[], int n)
{
	Elemtype *Tmparr;
	Tmparr = malloc( n*sizeof( Elemtype ));
	if( Tmparr!=NULL ){
		MSort( arr, Tmparr, 0, n-1 );
		free( Tmparr );//释放
	}
	else
	  printf("No space");
}

//三数取中优化快速排序
Elemtype Median3( Elemtype arr[], int Left, int Right )
{
	int Center = (Left+Right)/2;
	if( arr[Left]>arr[Center] ) swap( &arr[Left], &arr[Center] );
	if( arr[Left]>arr[Right] ) swap( &arr[Left], &arr[Right] );
	if( arr[Center]>arr[Right] ) swap( &arr[Center], &arr[Right] );
	swap( &arr[Center], &arr[Right-1] );
	return arr[Right-1];
}
//由于当递归到较小数组时，三数取中快排效率低，采用插排解决
void Qsort( Elemtype arr[], int Left, int Right )
{
	int i,j;
	Elemtype Pivot;
	if( Left + 3 <=Right )
	{
		Pivot=Median3( arr, Left, Right );//获得枢纽
		i = Left; j = Right-1;
		for( ; ; )//将小的放在枢纽左端，大的放在枢纽右端
		{
			while( arr[++i]<Pivot ) {};
			while( arr[--j]>Pivot ) {};
			if( i<j ) swap( &arr[i], &arr[j] );
			else break;
		}
		swap( &arr[i], &arr[Right-1] );	//确-定枢纽的位置
		// 对枢纽左右两端以同样方式确定位置
		Qsort( arr, Left, i-1 );
		Qsort( arr, i+1, Right );
	}
	else{//小数组用插排
		Insertsort( arr+Left , Right-Left+1 );
	}
}

//快排接口
void Quicksort( Elemtype arr[], int n)
{
	Qsort( arr, 0, n-1 );
}

//交换两个数的函数
void swap(Elemtype *a,Elemtype *b)
{
    Elemtype temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

//非递归快排，实现方式中运用结构体数组
//结构体中存放左右端
struct node{
	int left;
	int right;
};

//思想与快排基本一样，不同地方在于用结构体不断记录左右极限，直到数组归0
void TQsort( Elemtype arr[], int left, int right )
{
	int Pivot, i,j;
	struct node stack[100];
	int top=0;
	stack[top].left = left;
    stack[top].right = right;
    while( top>=0 ){
    	i=left=stack[top].left;//获取新的左右端
    	j=right=stack[top].right;
    	top--;
    	Pivot=arr[left];
    	while(i<j)//将小的放在枢纽左端，大的放在枢纽右端
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
    	if( left<i-1 )//记录新的左右端
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

//非递归快排接口
void TQuicksort( Elemtype arr[], int n)
{
	TQsort( arr, 0, n-1 );
}

//计数排序
//计数排序本身很快，当由于申请了一个大内存，导致不同数据量时间较慢且相近
void Countsort( Elemtype arr[], int n,long int  max )
{
	int i;
	//计数数组，用于统计数组arr中各个不同数出现的次数
	Elemtype *count_arr=(int*)malloc(sizeof(int)*max);
	Elemtype *sort_arr=(int*)malloc(sizeof(int)*n);
	//统计数组arr中各个不同数出现的次数
	for( i=0; i<n; i++ )
		count_arr[arr[i]]++;
	for(  i=1; i<max; i++ )
		count_arr[i]+=count_arr[i-1];//排序，并将统计数组对应位置数减一
	for(  i=n-1; i>=0; i-- )
		sort_arr[--count_arr[arr[i]]]=arr[i];
	memcpy( arr, sort_arr, n*sizeof(int) );//将排序后的数组存回原数组
	free(count_arr);//释放内存
	free(sort_arr);
}

int temps[10][200000];
//获取最大位数的位置
int getExp(Elemtype arr[],int n){

    int i;
    Elemtype max = arr[0];
    //找到数组最大的数
    for(i=1;i<n;++i){
        max = arr[i]>max?arr[i]:max;
    }
    int exps = 1;
    max/=10;
    //获取最大位数
    while(max){
        max /= 10;
        exps++;
    }
    return exps;
}

//基数排序
void Radixsort(Elemtype arr[],int n){
    //存每个桶中数的个数
    int i,j,e;
    Elemtype countarr[10] = {0};//初始化
    int exps = getExp(arr,n);//获取最大位数
    int exp = 1;
    for(e=0;e<exps;++e){
        //入桶
        for(i=0;i<n;++i){
            int index = (arr[i]/exp)%10;//获得第exp位数字大小
            temps[index][countarr[index]++] = arr[i];//将第exp位排序入桶
        }
        int k=0;//取值，改变数组
        for(i=0;i<10;++i){
            //如果桶中数的个数大于0
            if(countarr[i]>0){
                int n  = countarr[i];
                //将数取出，改变数组
                for(j =0;j<n;++j){
                    arr[k++] = temps[i][j];
                }
            }
        }
        //将桶中的数的个数重置为0
        for(i=0;i<10;++i)
            countarr[i] = 0;
        exp *=10;//位数改变
    }

}

//判断是否完成排序
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























