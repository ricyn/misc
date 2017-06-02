// ����������(�ǵݹ�)
#include <iostream>
#include <queue>
#include <stack>
#include <conio.h>
using namespace std;

#include "bintreetool/bintreetool.h"

void BF_Traverse(node* Root){ // breadth-first
    queue<node*> fifo;
    if(Root)
        for(fifo.push(Root);fifo.size();fifo.pop()){
            cout<<fifo.front()->id<<'\x20'; // Current node
            if(fifo.front()->u)
                fifo.push(fifo.front()->u);
            if(fifo.front()->l)
                fifo.push(fifo.front()->l);
        }
    cout<<endl;
}

void Pre_Traverse(node* Root){ // pre-order
    stack<node*> lifo;
    // NULL������ջ
    if(Root)
        lifo.push(Root);
    while(lifo.size()){
        Root=lifo.top();
        cout<<Root->id<<'\x20'; // Current node
        lifo.pop();
        if(Root->l)
            lifo.push(Root->l);
        if(Root->u)
            lifo.push(Root->u);
    }
    cout<<endl;
}

void In_Traverse(node* Root){ // in-order
    stack<node*> lifo;
    // NULL������ջ,��ʾ��ǰ�ڵ�û����(��)����
    while(Root || lifo.size()){
        while(Root){
        // ��(��)�ӽڵ�һֱ��ջ����ͷ
            lifo.push(Root);
            Root=Root->u;
        }
        Root=lifo.top();
        cout<<Root->id<<'\x20';
        lifo.pop();
        Root=Root->l;
    }
    cout<<endl;
}

void Post_Traverse(node* Root){ // post-order
    stack<node*> lifo;
    if(Root)
        lifo.push(Root);
    while(lifo.size()){
        // NULL����ջ
        if((lifo.top()->l && Root==lifo.top()->l) || Root==lifo.top()->u){ // �ӽڵ���ѷ���,��ջ
            // Root������¼��һ��pop��(����)�Ľڵ�
            Root=lifo.top();
            lifo.pop();
            cout<<Root->id<<'\x20';
        }else{ // �ӽڵ���δ����,������ջ
            // Root������¼��ǰջ��
            while(lifo.top()->u || lifo.top()->l){
                Root=lifo.top();
                if(Root->l)
                    lifo.push(Root->l);
                if(Root->u)
                    lifo.push(Root->u);
            }
            Root=NULL; // ��ջ��־
        }
    }
    cout<<endl;
}

//
int main(){
    InitRand();
    node* Root;
    Root=GenBintree(16);
    PrnBintree(Root);

    cout<<"�������:"<<endl;
    BF_Traverse(Root);
    cout<<"����:"<<endl;
    Pre_Traverse(Root);
    cout<<"����:"<<endl;
    In_Traverse(Root);
    cout<<"����:"<<endl;
    Post_Traverse(Root);
    
    DelBintree(Root);
    return 0;
}
