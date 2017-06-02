#ifndef BINTREE_TOOL
#define BINTREE_TOOL

// 节点类型声明
typedef struct node{
    int          id;
    struct node* u; // 上子节点,视为左子节点
    struct node* l; // 下子节点,视为右子节点
}node;

// 导出函数
extern void InitRand(); // 初始化随机数
extern node* GenBintree(unsigned NodeCnt); // 随机生成二叉树
extern void PrnBintree(node* Root); // 显示二叉树
extern void DelBintree(node* Root); // 删除二叉树

#endif // BINTREE_TOOL