// 全排列算法:All permutations
// VS2010

#include <iostream>
using namespace std;

// 测试结果显示
void PRN_PERMUTATION(const int* const permutation, const int len){
    for(int i=0;i<len;i++){
        cout<<permutation[i]<<' ';
    }
    cout<<endl;
}

// 局部辅助函数
static inline int factorial(int n){
    // factorial(0) should return 1
    int r=1;
    for(;n;n--){
        r *= n;
    }
    return r;
}

static inline void insert(const int ins_num, int ins_index, int* const src_arr, int src_len, int* const dst_arr){
    for(int i=0;i<ins_index;i++){
        dst_arr[i]=src_arr[i];
    }

    dst_arr[ins_index]=ins_num;

    for(int i=ins_index+1;i<src_len+1;i++){
        dst_arr[i]=src_arr[i-1];
    }
}

static inline int** new2(int nrow, int ncol){
    int** p=new int*[nrow];
    p[0]=new int[nrow*ncol];
    for(int i=1;i<nrow;i++){
        p[i]=p[i-1]+ncol;
    }
    return p;
}


static inline void del2(int** p){
    delete[] p[0];
    delete[] p; 
}

// 迭代方法求全排列(动态规划)
void permute_iter(const int* const arr, const int len){
    // Initializations
    int** pre_iter=new2(factorial(len),len);
    int** cur_iter=new2(factorial(len),len);
    
    // Process
    for(int i=0;i<len;i++){
        for(int j=0;j<factorial(i);j++){
            for(int k=0;k<i+1;k++){
                insert(arr[i],k,pre_iter[j],i,cur_iter[j*(i+1)+k]);
            }
        }
        swap(cur_iter,pre_iter);
    }
    
    // 结果下标存储在pre_iter中
    for(int i=0;i<factorial(len);i++){
        PRN_PERMUTATION(pre_iter[i],len);
    }
    
    // Clean up
    del2(pre_iter);
    del2(cur_iter);
}

// 递归方法求全排列(原地修改原始数组,但是最终回归原始数组)
void permute_recur(int* const arr, const int len, int start_index=0){
    for(int i=start_index;i<len;i++){
        swap( arr[start_index], arr[i] );
        permute_recur( arr, len, start_index+1 );
        swap( arr[start_index], arr[i] ); // 此次交换保证数组内容不变
    }

    if(start_index==len){
        // 此时的arr[0:len-1]已经完成了(又)一次全排列
        PRN_PERMUTATION(arr,len);
    }
}

#define ARR_LEN(arr) (sizeof(arr)/sizeof(arr[0]))

int main(){
    int arr[]={1,3,5,7};
    
    cout<<"全排列-迭代方法:"<<endl;
    permute_iter(arr, ARR_LEN(arr));

    cout<<"全排列-递归方法:"<<endl;
    permute_recur(arr, ARR_LEN(arr));

    return 0;
}
