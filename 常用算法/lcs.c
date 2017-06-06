// C99
// 求最长公共子序列(的长度)
#include <stdio.h>

// 不考虑任何异常情况
int lcs(const int* const a, int la, const int* const b, int lb){
    int m[lb][la];
    int max_len=0;
    
    for(int i=0; i<lb; i++){
        m[i][0]=(a[0]==b[i]);
        if(m[i][0])
            max_len=1;
    }
    for(int i=0; i<la; i++){
        m[0][i]=(a[i]==b[0]);
        if(m[i][0])
            max_len=1;
    }
    
    for(int ib=1; ib<lb; ib++){ // row index
        for(int ia=1; ia<la; ia++){ // col index
            if(a[ia]==b[ib])
                m[ib][ia]=m[ib-1][ia-1]+1;
            else
                m[ib][ia]=0;
            if(m[ib][ia]>max_len)
                max_len=m[ib][ia];
        }
    }
    
    return max_len;
}

int main(void){
    int a[]={1,2,3,4,5};
    int b[]={3,4,5,0};
    int l=lcs(a,sizeof(a)/sizeof(a[0]),b,sizeof(b)/sizeof(b[0]));
    printf("%d\n",l);
    return 0;
}
