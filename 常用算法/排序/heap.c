// 堆排序:升序(最大堆)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 数组下标从0开始 */
/*   未做异常处理  */
// C99

// 最好内联或者宏
void swap(int* pa, int* pb){
    int s=*pa;
    *pa=*pb;
    *pb=s;
}

void heapify(int a[], int n){ // 将数组最大堆化
    for(int i=(n>>1);i>=0;i--){
        for(int j=i,l=(j<<1)|1,r=l+1,m=j;l<n;j=m,l=(j<<1)|1,r=l+1){
            if(a[m]<a[l])
                m=l;
            if(r<n && a[m]<a[r])
                m=r;
            if(m==j)
                break;
            else
                swap(a+j,a+m);
        }
    }
}

void insert(int k, int a[], int n){ // 向现在长n的堆a插入数字k,n可为0
    a[n]=k;
    for(int i=n,p=(i-1)>>1;i;i=p,p=(i-1)>>1){
        if(a[i]>a[p])
            swap(a+i,a+p);
        else
            break;
    }
}

int extract(int a[], int n){ // 弹出堆顶元素
    swap(a,a+(--n));
    for(int j=0,l=(j<<1)|1,r=l+1,m=0;l<n;j=m,l=(j<<1)|1,r=l+1){
        if(a[m]<a[l])
            m=l;
        if(r<n && a[m]<a[r])
            m=r;
        if(m==j)
            break;
        else
            swap(a+j,a+m);
    }
    return a[n];
}

int main(){
    const int N = 16;
    int a[N];
    srand(time(NULL));
    printf("排序前:\n");
    for(int i=0;i<N;i++)
        printf("%d ",a[i]=rand() % (N<<2));
    // 方法一
    heapify(a,N);
    // 方法二
    // for(int i=1;i<N;i++)
    //     insert(a[i],a,i);
    // Joined
    for(int i=0;i<N;i++)
        extract(a,N-i);
    printf("\n排序后:\n");
    for(int i=0;i<N;i++)
        printf("%d ",a[i]);
    printf("\n");
    return 0;
}
