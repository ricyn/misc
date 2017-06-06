// C99
// 求最长递增子序列(的长度)
#include <stdio.h>

// 不考虑任何异常情况
int lis(const int* const arr, int len){
    int lis_till[len];
    lis_till[0]=1;
    int max_len=1;
    for(int i=1;i<len;i++){
        lis_till[i]=0;
        for(int j=0;j<i;j++){
            if(arr[i]>arr[j] && lis_till[j]+1>lis_till[i]){
                lis_till[i]=lis_till[j]+1;
            }
        }
        if(lis_till[i]>max_len)
            max_len=lis_till[i];
    }
    return max_len;
}

int main(void){
    int a[]={1,1,2,3,4,2,5,9,3};
    for(int i=0; i<sizeof(a)/sizeof(a[0]); i++){
        printf("%d ",a[i]);
    }
    printf("\n%d\n",lis(a,sizeof(a)/sizeof(a[0])));
    return 0;
}
