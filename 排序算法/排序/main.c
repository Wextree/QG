#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>


typedef int Elemtype;

void getarr( Elemtype arr[], long n, long min,long max ) //���������
{

    int i=0;
    for( i=0; i<n; ++i ){
        arr[i] =  rand()*(max-min)/32768+min;
    }
}

void main()
{
    srand((unsigned)time(NULL));//��ȡ������Ӱ�
    long int n,min,max;
    Elemtype *arr=NULL;
    clock_t start, finish;
    char ch='1';
    while(ch!='0'){
        printf("����������Ĵ�С�����ֵ����Сֵ��\n");
        scanf("%ld%ld%ld",&n,&max,&min);
        arr=(Elemtype*)malloc(n*sizeof(Elemtype));
        getarr(arr,n,max,min);//��ȡ�������
        printf("|----------------------------------------|\n");
        printf("|   ������С   |   ���ֵ   |   ��Сֵ   |\n");
        printf("|----------------------------------------|\n");
        printf("|%14ld|%12ld|%12ld|\n",n,max,min);
        printf("|----------------------------------------|\n");
        printf("|   ��������   |  ����ʱ��  |  �Ƿ�����  |\n");
        printf("|----------------------------------------|\n");
        start=clock();
        Insertsort(arr,n);
        finish=clock();
        printf("|   ��������   |%10lfms|     %s     |\n",(double)(finish-start),isSort(arr,n) == true ? "��":"��");
        printf("|----------------------------------------|\n");
        getarr(arr,n,max,min);//��ȡ�������
        start=clock();
        Mergesort(arr,n);
        finish=clock();
        printf("|   �鲢����   |%10lfms|     %s     |\n",(double)(finish-start),isSort(arr,n) == true ? "��":"��");
        printf("|----------------------------------------|\n");
        getarr(arr,n,max,min);//��ȡ�������
        start=clock();
        Quicksort(arr,n);
        finish=clock();
        printf("| �ݹ�������� |%10lfms|     %s     |\n",(double)(finish-start),isSort(arr,n) == true ? "��":"��");
        printf("|----------------------------------------|\n");
        getarr(arr,n,max,min);//��ȡ�������
        start=clock();
        TQuicksort(arr,n);
        finish=clock();
        printf("| �ǵݿ������� |%10lfms|     %s     |\n",(double)(finish-start),isSort(arr,n) == true ? "��":"��");
        printf("|----------------------------------------|\n");
        getarr(arr,n,max,min);//��ȡ�������
        start=clock();
        Countsort(arr,n,max);
        finish=clock();
        printf("|   ��������   |%10lfms|     %s     |\n",(double)(finish-start),isSort(arr,n) == true ? "��":"��");
        printf("|----------------------------------------|\n");
        getarr(arr,n,max,min);//��ȡ�������
        start=clock();
        Radixsort(arr,n);
        finish=clock();
        printf("|   ��������   |%10lfms|     %s     |\n",(double)(finish-start),isSort(arr,n) == true ? "��":"��");
        printf("|----------------------------------------|\n");
        printf("�����ϣ���0�˳����߰��������������룡\n");
        scanf("%c",&ch);
    }
    free(arr);
}

































