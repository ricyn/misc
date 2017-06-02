// 二叉树遍历(非递归)
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
    // NULL不会入栈
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
    // NULL可以入栈,表示当前节点没有下(右)子树
    while(Root || lifo.size()){
        while(Root){
        // 上(左)子节点一直入栈到尽头
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
        // NULL不入栈
        if((lifo.top()->l && Root==lifo.top()->l) || Root==lifo.top()->u){ // 子节点均已访问,出栈
            // Root用来记录上一个pop出(访问)的节点
            Root=lifo.top();
            lifo.pop();
            cout<<Root->id<<'\x20';
        }else{ // 子节点尚未访问,持续入栈
            // Root用来记录当前栈顶
            while(lifo.top()->u || lifo.top()->l){
                Root=lifo.top();
                if(Root->l)
                    lifo.push(Root->l);
                if(Root->u)
                    lifo.push(Root->u);
            }
            Root=NULL; // 出栈标志
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

    cout<<"广度优先:"<<endl;
    BF_Traverse(Root);
    cout<<"先序:"<<endl;
    Pre_Traverse(Root);
    cout<<"中序:"<<endl;
    In_Traverse(Root);
    cout<<"后序:"<<endl;
    Post_Traverse(Root);
    
    DelBintree(Root);
    return 0;
}
