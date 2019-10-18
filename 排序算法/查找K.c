#include <stdio.h>
#include <stdlib.h>

void swap( int*a, int *b )//交换值 
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

//使用快排中的划分法使得我们可以在时间复杂度为O(nlogn)的情况下找到特定排位的数
int Seeksort( int left, int right,int arr[], int K )
{	
	int key=arr[left];//将最左端值确定为枢纽 
	int i=left;
	int j=right;
	while(1)
	{
		
		i=left;
		j=right;
		key=arr[left];
		while( i<j )//将比枢纽小的值放在左端，大的放在右端 
		{
			while(arr[j]>key&&i<j) {j--;}
			if(i<j)
				swap( &arr[i++], &arr[j] );		
			while(arr[i]<key&&i<j) {i++;}
			if(i<j)
				swap( &arr[i], &arr[j--] );
		}
		if( i==K )//当枢纽位置恰好为要查找的位置，返回其值 
			return arr[i];
		if( K<i )//枢纽位置在其左端，改变右端值继续查找 
			right = i-1;
		if( K>i )//枢纽位置在其右端，改变左端值继续查找 
			left = i+1; 
	}
}

int main()
{
	int N;
	printf("\n\t输入数组个数：");
	scanf("%d",&N);
	int arr[N];
	printf("\n\t为数组赋值：");
	for( int i=0; i<N; i++ )
		scanf("%d",&arr[i]);
	int K;
	printf("\n\t查找第K小的数，K:");
	scanf("%d",&K);
	K=Seeksort( 0, N-1, arr, K-1 );
	printf("\n\t你要查找的值为："); 
	printf("%d",K);
}
