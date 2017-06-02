// �鲢����:����
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

// �ݹ�(�Զ�����)�鲢����
void MergeSort_Recur(int* Array,int nArray){
    int *Ping=Array, Pong[nArray]; // VLA (C99)
    for(int i=0;i<nArray;i++)
        Pong[i]=Ping[i];

    // Nested func (GNU C)
    void _MergeSort_Recur(int sIndex,int nArray,int* sArray, int* dArray){
        // sIndex:��������������±�
        // nArray:���������鳤��
        // sArray:����������洢������
        // dArray:���������洢������
        if(nArray==1)
            return;
        int nLeft=(nArray>>1), nRight=(nArray-nLeft);
        _MergeSort_Recur(sIndex,nLeft,dArray,sArray);
        _MergeSort_Recur(sIndex+nLeft,nRight,dArray,sArray);
        Merge(sArray+sIndex,nLeft,sArray+sIndex+nLeft,nRight,dArray+sIndex);
    }

    _MergeSort_Recur(0,nArray,Pong,Ping);
}

// ����(�Ե�����)�鲢����
void MergeSort_Iter(int* Array, int nArray){
    int *Ping=Array, Pong[nArray]; // VLA
    int *sArray=Pong, *dArray=Ping; // ��ֵ:��Ҫ
    int nLeft,nRight;

    for(int nSection=1;nSection<nArray;nSection<<=1){
        // ��������Ϊ����(����),һ�����һ��Section
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

            if(nRight){ // ������Section�Ž��й鲢
                Merge(sArray+sIndex,nSection,sArray+sIndex+nSection,nRight,dArray+sIndex);
            }else{ // ��������Sectionֱ�Ӹ�����Section
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
    printf("����ǰ:\n");
    for(int i=0;i<N;i++)
        printf("%d ",a[i]=rand() % (N<<1));
    // MergeSort_Recur(a,N);
    MergeSort_Iter(a,N);
    printf("\n�����:\n");
    for(int i=0;i<N;i++)
        printf("%d ",a[i]);
    printf("\n");
    return 0;
}
