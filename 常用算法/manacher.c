// C99
// 求最长回文子序列(的长度)
// Manacher算法
#include <stdio.h>
#include <string.h>

// 不考虑任何异常情况
#define SEP '`' // 假设输入字符串中不含SEP字符

int manacher(const char* const s){
    int len=strlen(s);
    char se[2*len+1+1]; // an extra +1 for '\0'

    // 补充分隔字符
    se[0]=SEP;
    se[2*len+1+1]='\0';
    for(int i=0; i<len; i++){
        se[2*i+1]=s[i];
        se[2*i+2]=SEP;
    }
    len=2*len+1;

    // Manacher
    int p[len]; // palindrome (radius)
    int c=0,r=0; // c for palin center, r for palin rbound
    for(int i=0, j=0; se[i]; j=2*c-(++i)){ // j is i's symmetric elem
        if(i<r){
            if(p[j]<r-i)
                p[i]=p[j];
            else
                p[i]=r-i;
        }else{
            p[i]=1;
        }

        while(se[i+p[i]]==se[i-p[i]])
            p[i]++;

        if(i+p[i]>r){
            r=i+p[i];
            c=i;
        }
    }

    // find max
    int max_len=0;
    for(int i=0; i<len; i++){
        if(p[i]>max_len)
            max_len=p[i];
    }
    max_len--;

    return max_len;
}

int main(void){
    printf("%d ",manacher("abc"));
    printf("%d ",manacher("google"));
    printf("%d ",manacher("1abba2"));
    printf("%d ",manacher("2regherg"));
    return 0;
}
