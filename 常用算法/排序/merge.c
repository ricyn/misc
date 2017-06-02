// 归并排序:升序
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 15

static void inline Merge(int* pLeft,int nLeft, int* pRight,int nRight, int* pMerged){
    int iLeft=0, iRight=0, iMerged=0;
    while(iLeft<nLeft && iRight<nRight){
        if(pLeft[iLeft]<pRight[iRight])
            pMerged[iMerged++]=pLeft[iLeft++];
        else
            pMerged[iMerged++]=pRight[iRight++];
    }
    while(iLeft<nLeft)
        pMerged[iMerged++]=pLeft[iLeft++];
    while(iRight<nRight)
        pMerged[iMerged++]=pRight[iRight++];
}

// 递归(自顶向下)归并排序
void MergeSort_Recur(int* Array,int nArray){
    int *Ping=Array, Pong[nArray]; // VLA (C99)
    for(int i=0;i<nArray;i++)
        Pong[i]=Ping[i];

    // Nested func (GNU C)
    void _MergeSort_Recur(int sIndex,int nArray,int* sArray, int* dArray){
        // sIndex:待排序数组起点下标
        // nArray:带排序数组长度
        // sArray:待排序数组存储缓冲区
        // dArray:排序后数组存储缓冲区
        if(nArray==1)
            return;
        int nLeft=(nArray>>1), nRight=(nArray-nLeft);
        _MergeSort_Recur(sIndex,nLeft,dArray,sArray);
        _MergeSort_Recur(sIndex+nLeft,nRight,dArray,sArray);
        Merge(sArray+sIndex,nLeft,sArray+sIndex+nLeft,nRight,dArray+sIndex);
    }

    _MergeSort_Recur(0,nArray,Pong,Ping);
}

// 迭代(自底向上)归并排序
void MergeSort_Iter(int* Array, int nArray){
    int *Ping=Array, Pong[nArray]; // VLA
    int *sArray=Pong, *dArray=Ping; // 初值:重要
    int nLeft,nRight;

    for(int nSection=1;nSection<nArray;nSection<<=1){
        // 将数组拆分为两块(分治),一块就是一个Section
        if(sArray==Ping){
            sArray=Pong;
            dArray=Ping;
        }else{
            sArray=Ping;
            dArray=Pong;
        }

        for(int sIndex=0;sIndex<nArray;sIndex+=(nSection<<1)){
            nRight=nArray-sIndex-nSection;
            if(nRight<0)
                nRight=0;
            else if(nRight>nSection)
                nRight=nSection;

            if(nRight){ // 存在右Section才进行归并
                Merge(sArray+sIndex,nSection,sArray+sIndex+nSection,nRight,dArray+sIndex);
            }else{ // 不存在右Section直接复制左Section
                nLeft=nArray-sIndex;
                for(int iLeft=sIndex;iLeft<sIndex+nLeft;iLeft++)
                    dArray[iLeft]=sArray[iLeft];
            }
        }
    }

    if(sArray==Ping)
        for(int i=0;i<nArray;i++)
            Ping[i]=Pong[i];
}

int main(){
    int a[N];
    srand(time(NULL));
    printf("排序前:\n");
    for(int i=0;i<N;i++)
        printf("%d ",a[i]=rand() % (N<<1));
    // MergeSort_Recur(a,N);
    MergeSort_Iter(a,N);
    printf("\n排序后:\n");
    for(int i=0;i<N;i++)
        printf("%d ",a[i]);
    printf("\n");
    return 0;
}
