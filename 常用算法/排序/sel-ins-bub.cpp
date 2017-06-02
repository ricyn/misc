// 选择排序:升序
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//
inline void swap(int& a, int& b){
    int c=a;
    a=b;
    b=c;
}

// 外层循环每次把最小的堆到头
// 剩下的数据保持顺序
void selection_sort(int a[], int n){
    for(int i=0;i<n-1;i++)
        for(int j=i+1;j<n;j++)
            if(a[i]>a[j])
                swap(a[i],a[j]);
}

// 外层循环每次把最大的堆到尾
// 剩下的数据保持顺序
void bubble_sort(int a[], int n){
    for(int i=1;i<n;i++)
        for(int j=0;j<n-i;j++)
            if(a[j]>a[j+1])
                swap(a[j],a[j+1]);
}

// 外层循环不停纳入新数据(抓牌)
// 内层循环通过交换将新数据插入正确位置
void insertion_sort(int a[], int n){
    for(int i=1;i<n;i++)
        for(int j=i;j;j--)
            if(a[j-1]>a[j])
                swap(a[j-1],a[j]);
}

//
int main(){
    const int N=16;
    int a[N];
    srand(time(NULL));
    cout<<("排序前:\n");
    for(int i=0;i<N;i++)
        cout<<(a[i]=rand() % (N<<2))<<',';
    bubble_sort(a,N);
    cout<<("\n排序后:\n");
    for(int i=0;i<N;i++)
        cout<<(a[i])<<',';
    cout<<endl;
    return 0;
}
