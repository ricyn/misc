#ifndef BINTREE_TOOL
#define BINTREE_TOOL

// �ڵ���������
typedef struct node{
    int          id;
    struct node* u; // ���ӽڵ�,��Ϊ���ӽڵ�
    struct node* l; // ���ӽڵ�,��Ϊ���ӽڵ�
}node;

// ��������
extern void InitRand(); // ��ʼ�������
extern node* GenBintree(unsigned NodeCnt); // ������ɶ�����
extern void PrnBintree(node* Root); // ��ʾ������
extern void DelBintree(node* Root); // ɾ��������

#endif // BINTREE_TOOL