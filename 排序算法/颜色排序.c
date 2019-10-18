#include <stdio.h>
#include <stdlib.h>

void swap( int *a, int *b )//交换两值 
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

void Colorsort( int arr[], int n )
{
	int p, p1, p2;
	// 使用两个索引控制0和2的放置位置，再用一个索引进行遍历
	for( p1=0,p2=n-1,p=0; ;p++ )
	{
		if( arr[p]==2||arr[p]==0 )
		{
			//当前索引遇到0时后移
			if( arr[p1]==0 )
			{
				p1++;
				p--;
				continue;
			}
			//后索引遇到2时前移 
			if( arr[p2]==2 )
			{
				p2--;
				p--;
				continue;
			}
			//遍历索引位置需大于前索引 
			if( p<p1 ) continue;
			//遇到0或2时与索引对应位置进行交换，并再检查一次交换过来的值是否需要再放置
			if( arr[p]>arr[p2] )
			{
				swap( &arr[p],&arr[p2--]);
			}
			if( arr[p]<arr[p1] )
			{
				swap( &arr[p],&arr[p1++] );
			}
		}
		//直到p与p2相遇则结束 
		if( p>=p2 )
		{
			if( arr[p2]<arr[p1] )
				swap( &arr[p2],&arr[p1] );
			break; 
		}
	}
}

void print( int arr[], int n )
{
	for( int i=0; i<n; i++ )
		printf("%d ",arr[i] );
}

int main()
{
	int N;
	printf("\n\t请输入要输入的012个数：");
	scanf("%d",&N);
	printf("\n\t请输入要输入的012：");
	int arr[N];
	for(  int i=0; i<N; i++ )
		scanf("%d",&arr[i] );
	Colorsort( arr, N );
	printf("\n\t排序后结果："); 
	print( arr, N );
} 

