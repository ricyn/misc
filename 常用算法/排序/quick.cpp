// ¿ìËÙÅÅÐò:ÉýÐò
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
using namespace std;

void inline swap(int& a, int& b){
    int c = a;
    a = b;
    b = c;
}

void qsort_recur(int a[], int n){
    if(n<=1)
        return;
    int p,i,j;
    for(p=0,i=0,j=1;j<n;j++){
        if(a[j]<=a[p]){
            swap(a[i+1],a[j]);
            i++;
        }
    }
    swap(a[i],a[p]);
    qsort_recur(a,i);
    qsort_recur(a+i+1,n-i-1);
}

void qsort_iter(int a[], int n){
    stack<int> lifo;
    int* pa=a;
    int p,i,j;
    for(lifo.push(n),lifo.push(0);lifo.size();pa=a+lifo.top(),lifo.pop(),n=lifo.top(),lifo.pop()){
        for(p=0,i=0,j=1;j<n;j++){
            if(pa[j]<=pa[p]){
                swap(pa[i+1],pa[j]);
                i++;
            }
        }
        swap(pa[i],pa[p]);
        if(n-i-1>1){
            lifo.push(n-i-1);
            lifo.push(pa-a+i+1);
        }
        if(i>1){
            lifo.push(i);
            lifo.push(pa-a);
        }
    }
}

int main(){
    const int N = 16;
    int a[N];
    srand(time(NULL));
    cout<<"ÅÅÐòÇ°:"<<endl;
    for(int i=0;i<N;i++)
        cout<<(a[i]=rand() % (N<<2))<<' ';
    // qsort_recur(a,N);
    qsort_iter(a,N);
    cout<<"\nÅÅÐòºó:"<<endl;
    for(int i=0;i<N;i++)
        cout<<a[i]<<' ';
    cout<<endl;
    return 0;
}
