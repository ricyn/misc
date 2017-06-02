// ѡ������:����
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

// ���ѭ��ÿ�ΰ���С�Ķѵ�ͷ
// ʣ�µ����ݱ���˳��
void selection_sort(int a[], int n){
    for(int i=0;i<n-1;i++)
        for(int j=i+1;j<n;j++)
            if(a[i]>a[j])
                swap(a[i],a[j]);
}

// ���ѭ��ÿ�ΰ����Ķѵ�β
// ʣ�µ����ݱ���˳��
void bubble_sort(int a[], int n){
    for(int i=1;i<n;i++)
        for(int j=0;j<n-i;j++)
            if(a[j]>a[j+1])
                swap(a[j],a[j+1]);
}

// ���ѭ����ͣ����������(ץ��)
// �ڲ�ѭ��ͨ�������������ݲ�����ȷλ��
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
    cout<<("����ǰ:\n");
    for(int i=0;i<N;i++)
        cout<<(a[i]=rand() % (N<<2))<<',';
    bubble_sort(a,N);
    cout<<("\n�����:\n");
    for(int i=0;i<N;i++)
        cout<<(a[i])<<',';
    cout<<endl;
    return 0;
}
