#include <stdio.h>
#include <stdlib.h>

void swap( int *a, int *b )//������ֵ 
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

void Colorsort( int arr[], int n )
{
	int p, p1, p2;
	// ʹ��������������0��2�ķ���λ�ã�����һ���������б���
	for( p1=0,p2=n-1,p=0; ;p++ )
	{
		if( arr[p]==2||arr[p]==0 )
		{
			//��ǰ��������0ʱ����
			if( arr[p1]==0 )
			{
				p1++;
				p--;
				continue;
			}
			//����������2ʱǰ�� 
			if( arr[p2]==2 )
			{
				p2--;
				p--;
				continue;
			}
			//��������λ�������ǰ���� 
			if( p<p1 ) continue;
			//����0��2ʱ��������Ӧλ�ý��н��������ټ��һ�ν���������ֵ�Ƿ���Ҫ�ٷ���
			if( arr[p]>arr[p2] )
			{
				swap( &arr[p],&arr[p2--]);
			}
			if( arr[p]<arr[p1] )
			{
				swap( &arr[p],&arr[p1++] );
			}
		}
		//ֱ��p��p2��������� 
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
	printf("\n\t������Ҫ�����012������");
	scanf("%d",&N);
	printf("\n\t������Ҫ�����012��");
	int arr[N];
	for(  int i=0; i<N; i++ )
		scanf("%d",&arr[i] );
	Colorsort( arr, N );
	printf("\n\t���������"); 
	print( arr, N );
} 

