#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>


typedef int Elemtype;

void getarr( Elemtype arr[], long n, long min,long max ) //随机生成数
{

    int i=0;
    for( i=0; i<n; ++i ){
        arr[i] =  rand()*(max-min)/32768+min;
    }
}

void main()
{
    srand((unsigned)time(NULL));//获取随机种子包
    long int n,min,max;
    Elemtype *arr=NULL;
    clock_t start, finish;
    char ch='1';
    while(ch!='0'){
        printf("请输入数组的大小，最大值和最小值：\n");
        scanf("%ld%ld%ld",&n,&max,&min);
        arr=(Elemtype*)malloc(n*sizeof(Elemtype));
        getarr(arr,n,max,min);//获取随机数组
        printf("|----------------------------------------|\n");
        printf("|   容量大小   |   最大值   |   最小值   |\n");
        printf("|----------------------------------------|\n");
        printf("|%14ld|%12ld|%12ld|\n",n,max,min);
        printf("|----------------------------------------|\n");
        printf("|   排序类型   |  经历时间  |  是否排序  |\n");
        printf("|----------------------------------------|\n");
        start=clock();
        Insertsort(arr,n);
        finish=clock();
        printf("|   插入排序   |%10lfms|     %s     |\n",(double)(finish-start),isSort(arr,n) == true ? "是":"否");
        printf("|----------------------------------------|\n");
        getarr(arr,n,max,min);//获取随机数组
        start=clock();
        Mergesort(arr,n);
        finish=clock();
        printf("|   归并排序   |%10lfms|     %s     |\n",(double)(finish-start),isSort(arr,n) == true ? "是":"否");
        printf("|----------------------------------------|\n");
        getarr(arr,n,max,min);//获取随机数组
        start=clock();
        Quicksort(arr,n);
        finish=clock();
        printf("| 递归快速排序 |%10lfms|     %s     |\n",(double)(finish-start),isSort(arr,n) == true ? "是":"否");
        printf("|----------------------------------------|\n");
        getarr(arr,n,max,min);//获取随机数组
        start=clock();
        TQuicksort(arr,n);
        finish=clock();
        printf("| 非递快速排序 |%10lfms|     %s     |\n",(double)(finish-start),isSort(arr,n) == true ? "是":"否");
        printf("|----------------------------------------|\n");
        getarr(arr,n,max,min);//获取随机数组
        start=clock();
        Countsort(arr,n,max);
        finish=clock();
        printf("|   计数排序   |%10lfms|     %s     |\n",(double)(finish-start),isSort(arr,n) == true ? "是":"否");
        printf("|----------------------------------------|\n");
        getarr(arr,n,max,min);//获取随机数组
        start=clock();
        Radixsort(arr,n);
        finish=clock();
        printf("|   基数排序   |%10lfms|     %s     |\n",(double)(finish-start),isSort(arr,n) == true ? "是":"否");
        printf("|----------------------------------------|\n");
        printf("输出完毕，按0退出或者按其他键继续输入！\n");
        scanf("%c",&ch);
    }
    free(arr);
}

































