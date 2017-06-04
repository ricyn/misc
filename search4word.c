#include <stdlib.h>
#include <stdio.h>

size_t next_letter_at(const char* const str, size_t starts_at){
    for(size_t i=starts_at; str[i]; i++)
        if(isalpha(str[i]))
            return i;
    return (size_t)(-1);
}

// 需要确保starts_at已经指向字母
size_t ends_at(const char* const str, size_t starts_at){
    size_t i=starts_at;
    do{
        while(isalpha(str[++i]));
    }while(str[i]=='-' && isalpha(str[i+1]));
    return i;
}

int main(void){
    char s[]=" -aaa_bbb -cc-dd-ee- ffff-";
    for(int i=next_letter_at(s,0),j=ends_at(s,i); i!=-1; i=next_letter_at(s,j),j=ends_at(s,i)){
        for(int k=i; k<j; k++)
            putchar(s[k]);
        putchar('\n');
    }
    return 0;
}
