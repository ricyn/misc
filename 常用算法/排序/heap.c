// ������:����(����)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* �����±��0��ʼ */
/*   δ���쳣����  */
// C99

// ����������ߺ�
void swap(int* pa, int* pb){
    int s=*pa;
    *pa=*pb;
    *pb=s;
}

void heapify(int a[], int n){ // ���������ѻ�
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

void insert(int k, int a[], int n){ // �����ڳ�n�Ķ�a��������k,n��Ϊ0
    a[n]=k;
    for(int i=n,p=(i-1)>>1;i;i=p,p=(i-1)>>1){
        if(a[i]>a[p])
            swap(a+i,a+p);
        else
            break;
    }
}

int extract(int a[], int n){ // �����Ѷ�Ԫ��
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
    printf("����ǰ:\n");
    for(int i=0;i<N;i++)
        printf("%d ",a[i]=rand() % (N<<2));
    // ����һ
    heapify(a,N);
    // ������
    // for(int i=1;i<N;i++)
    //     insert(a[i],a,i);
    // Joined
    for(int i=0;i<N;i++)
        extract(a,N-i);
    printf("\n�����:\n");
    for(int i=0;i<N;i++)
        printf("%d ",a[i]);
    printf("\n");
    return 0;
}
