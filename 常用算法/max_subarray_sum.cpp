#include <stdio.h>

// O(n)的动态规划算法
int max_subarray_sum(int arr[], int len){
    int max_sum=0, tmp_max_sum=0;
    
    for(int i=0; i<len; i++){
        if(tmp_max_sum+arr[i]<0)
            tmp_max_sum=0;
        else
            tmp_max_sum+=arr[i];
        
        if(tmp_max_sum>max_sum)
            max_sum=tmp_max_sum;
    }
    
    return max_sum;
}

int main(){
    int a[]={-2,11,-4,13,-5,-2};
    
    printf("Max subarray sum %d\n",max_subarray_sum(a,sizeof(a)/sizeof(a[0])));
    
    return 0;
}
