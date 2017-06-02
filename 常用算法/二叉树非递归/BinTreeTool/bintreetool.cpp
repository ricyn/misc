#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

// 二叉树生成和显示
#include "bintreetool.h"

////////////////////////////////////////////////////////////////
//                         私有函数                           //
////////////////////////////////////////////////////////////////

// 随机生成c个节点的二叉树
static node* gen_bintree(
    unsigned    cnt,
    bool        called = true/*外部调用:true,递归调用:false*/
){
    if(!cnt)
        return NULL;
    node* n=new node;

    unsigned lcnt,rcnt;
    lcnt=rand()%cnt;
    rcnt=(cnt-1)-lcnt;

    static int id;
    if(called)
        id=0;
    n->id=id++;
    
    n->u=gen_bintree(lcnt,false);
    n->l=gen_bintree(rcnt,false);
    return n;
}

// 显示二叉树
static void prn_bintree(
    node*       root,
    unsigned    level = 0,
    bool        prnifnochild = false/*即使左右都是空,也显示?*/
){
    if(!root)
        return;

    static vector<bool> closed;

    if(level==0){
        closed.clear();
    }
    
    cout<<'['<<root->id<<']'<<endl;

    if(prnifnochild || root->u || root->l){
        for(int i=0;i<level;i++){
            if(closed[i])
                cout<<"  ";
            else
                cout<<"│";
        }
        cout<<"├";
        
        if(closed.size()==level)
            closed.push_back(false);
        else
            closed[level]=false;
        
        if(root->u)
            prn_bintree(root->u,level+1);
        else
            cout<<"[X]"<<endl;

        
        for(int i=0;i<level;i++){
            if(closed[i])
                cout<<"  ";
            else
                cout<<"│";
        }
        cout<<"└";
        closed[level]=true;
        if(root->l)
            prn_bintree(root->l,level+1);
        else
            cout<<"[X]"<<endl;
    }
}

// 删除二叉树
static void del_bintree(node* root){
    if(!root)
        return;
    
    del_bintree(root->u);
    del_bintree(root->l);
    // cout<<root->id<<" deleted"<<endl;
    delete root;
}

////////////////////////////////////////////////////////////////
//                         导出函数                           //
////////////////////////////////////////////////////////////////

// 初始化随机数
void InitRand(){
    srand(time(NULL));
}

// 随机生成二叉树
node* GenBintree(unsigned NodeCnt){
    return gen_bintree(NodeCnt);
}

// 显示二叉树
void PrnBintree(node* Root){
    prn_bintree(Root);
}

// 删除二叉树
void DelBintree(node* Root){
    del_bintree(Root);
}

/* Usage Example ***********************************************

int main(){
    node* Root;
    InitRand();
    Root=GenBintree(20);
    PrnBintree(Root);
    DelBintree(Root);
    return 0;
}

***************************************************************/
