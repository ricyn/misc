#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

// ���������ɺ���ʾ
#include "bintreetool.h"

////////////////////////////////////////////////////////////////
//                         ˽�к���                           //
////////////////////////////////////////////////////////////////

// �������c���ڵ�Ķ�����
static node* gen_bintree(
    unsigned    cnt,
    bool        called = true/*�ⲿ����:true,�ݹ����:false*/
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

// ��ʾ������
static void prn_bintree(
    node*       root,
    unsigned    level = 0,
    bool        prnifnochild = false/*��ʹ���Ҷ��ǿ�,Ҳ��ʾ?*/
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
                cout<<"��";
        }
        cout<<"��";
        
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
                cout<<"��";
        }
        cout<<"��";
        closed[level]=true;
        if(root->l)
            prn_bintree(root->l,level+1);
        else
            cout<<"[X]"<<endl;
    }
}

// ɾ��������
static void del_bintree(node* root){
    if(!root)
        return;
    
    del_bintree(root->u);
    del_bintree(root->l);
    // cout<<root->id<<" deleted"<<endl;
    delete root;
}

////////////////////////////////////////////////////////////////
//                         ��������                           //
////////////////////////////////////////////////////////////////

// ��ʼ�������
void InitRand(){
    srand(time(NULL));
}

// ������ɶ�����
node* GenBintree(unsigned NodeCnt){
    return gen_bintree(NodeCnt);
}

// ��ʾ������
void PrnBintree(node* Root){
    prn_bintree(Root);
}

// ɾ��������
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
