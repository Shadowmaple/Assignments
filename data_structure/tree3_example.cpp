/************************************************************
给定一个字符串，如“ABC##DE#G##F###”,其中符号#表示空节点，
根据该序列，利用非递归方式先序创建一棵二叉树，用二叉链方式存储。
***************************************************************/
#include <iostream>
using namespace std;

#define NUM 100

typedef struct Node
{
    char data;
    struct Node *lchild, *rchild;
} TreeNode, *pTreeNode;

typedef struct
{
    pTreeNode **elem;
    int top;
    int stacksize;
} stack, *pstack;

void initStack(stack &s)
{
    s.elem = new pTreeNode *[NUM];
    s.top = -1;
    s.stacksize = NUM;
}

void push(stack &s, pTreeNode *e)
{
    if (s.top == s.stacksize - 1)
    {
        printf("stack full\n");
        return;
    }
    s.elem[++s.top] = e;
}

void pop(stack &s, pTreeNode *&e)
{
    // if (s.top == -1)
    // {
    //     printf("stack empty\n");
    //     return;
    // }
    e = s.elem[s.top--];
}

int stackEmpty(stack &s)
{
    if (s.top == -1)
        return 1;
    return 0;
}

int stackFull(stack &s)
{
    if (s.top == s.stacksize - 1)
        return 1;
    return 0;
}

pTreeNode createTree(char *str)
{
    stack st;
    initStack(st);
    pTreeNode *p;
    pTreeNode TP, pre;
    int popflag = 0;
    if (str[0] != '#') //创建根节点
    {
        TP = new TreeNode;
        TP->data = str[0];
        TP->lchild = TP->rchild = NULL;
        push(st, &TP->rchild);
        pre = TP;
    }
    else
        return NULL;

    int i = 1;
    // while (str[i] != '\0' || !stackEmpty(st))
    while (str[i] != '\0')
    {
        if (str[i] != '#')
        {
            pTreeNode np = new TreeNode;
            np->data = str[i];
            np->lchild = np->rchild = NULL;
            if (popflag) //如果是从栈里弹出来的右孩子指针的地址
            {
                *p = np;
                popflag = 0;
            }
            else
                pre->lchild = np;
            push(st, &np->rchild);
            pre = np;
        }
        else if (str[i] == '#' && !stackEmpty(st))
        {
            pop(st, p);
            popflag = 1;
        }
        i++;
    }
    return TP;
}

void preOrder(pTreeNode pt)
{
    if (pt)
    {
        cout << pt->data;
        preOrder(pt->lchild);
        preOrder(pt->rchild);
    }
    else
        cout << '#';
}

int main()
{
    char str[] = "ABC##DE#G##F###";
    pTreeNode tp = createTree(str);
    preOrder(tp);
    cout << endl;
    return 0;
}