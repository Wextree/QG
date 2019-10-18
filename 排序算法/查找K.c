#include <stdio.h>
#include <stdlib.h>

void swap( int*a, int *b )//����ֵ 
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

//ʹ�ÿ����еĻ��ַ�ʹ�����ǿ�����ʱ�临�Ӷ�ΪO(nlogn)��������ҵ��ض���λ����
int Seeksort( int left, int right,int arr[], int K )
{	
	int key=arr[left];//�������ֵȷ��Ϊ��Ŧ 
	int i=left;
	int j=right;
	while(1)
	{
		
		i=left;
		j=right;
		key=arr[left];
		while( i<j )//������ŦС��ֵ������ˣ���ķ����Ҷ� 
		{
			while(arr[j]>key&&i<j) {j--;}
			if(i<j)
				swap( &arr[i++], &arr[j] );		
			while(arr[i]<key&&i<j) {i++;}
			if(i<j)
				swap( &arr[i], &arr[j--] );
		}
		if( i==K )//����Ŧλ��ǡ��ΪҪ���ҵ�λ�ã�������ֵ 
			return arr[i];
		if( K<i )//��Ŧλ��������ˣ��ı��Ҷ�ֵ�������� 
			right = i-1;
		if( K>i )//��Ŧλ�������Ҷˣ��ı����ֵ�������� 
			left = i+1; 
	}
}

int main()
{
	int N;
	printf("\n\t�������������");
	scanf("%d",&N);
	int arr[N];
	printf("\n\tΪ���鸳ֵ��");
	for( int i=0; i<N; i++ )
		scanf("%d",&arr[i]);
	int K;
	printf("\n\t���ҵ�KС������K:");
	scanf("%d",&K);
	K=Seeksort( 0, N-1, arr, K-1 );
	printf("\n\t��Ҫ���ҵ�ֵΪ��"); 
	printf("%d",K);
}
