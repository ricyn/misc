// ȫ�����㷨:All permutations
// VS2010

#include <iostream>
using namespace std;

// ���Խ����ʾ
void PRN_PERMUTATION(const int* const permutation, const int len){
    for(int i=0;i<len;i++){
        cout<<permutation[i]<<' ';
    }
    cout<<endl;
}

// �ֲ���������
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

// ����������ȫ����(��̬�滮)
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
    
    // ����±�洢��pre_iter��
    for(int i=0;i<factorial(len);i++){
        PRN_PERMUTATION(pre_iter[i],len);
    }
    
    // Clean up
    del2(pre_iter);
    del2(cur_iter);
}

// �ݹ鷽����ȫ����(ԭ���޸�ԭʼ����,�������ջع�ԭʼ����)
void permute_recur(int* const arr, const int len, int start_index=0){
    for(int i=start_index;i<len;i++){
        swap( arr[start_index], arr[i] );
        permute_recur( arr, len, start_index+1 );
        swap( arr[start_index], arr[i] ); // �˴ν�����֤�������ݲ���
    }

    if(start_index==len){
        // ��ʱ��arr[0:len-1]�Ѿ������(��)һ��ȫ����
        PRN_PERMUTATION(arr,len);
    }
}

#define ARR_LEN(arr) (sizeof(arr)/sizeof(arr[0]))

int main(){
    int arr[]={1,3,5,7};
    
    cout<<"ȫ����-��������:"<<endl;
    permute_iter(arr, ARR_LEN(arr));

    cout<<"ȫ����-�ݹ鷽��:"<<endl;
    permute_recur(arr, ARR_LEN(arr));

    return 0;
}
