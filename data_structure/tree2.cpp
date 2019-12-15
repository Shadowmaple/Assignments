// 二叉树非递归遍历
// 根据1,2,3,...,n的顺序创建一个完全二叉树，用二叉链表方式存储，并使用非递归方法进行前、中、后序遍历，输出遍历结果

# include <iostream>
using namespace std;

# define NUM 10

typedef struct node {
    int data;
    struct node *left, *right;
} TreeNode;

typedef struct {
    TreeNode *elem[NUM];
    int top;
} Stack;

void stackInit(Stack *s, int size) {
    // s->elem = (TreeNode *) malloc(sizeof(TreeNode) * size);
    s->top = -1;
}

void stackPush(Stack *s, TreeNode *p) {
    s->elem[++s->top] = p;
}

void stackPop(Stack *s) {
    s->top--;
}

int stackEmpty(Stack *s) {
    return s->top == -1;
}

TreeNode *createBTree(int i, int n) {
    if (i <= n) {
        TreeNode *p = new TreeNode{i};
        p->left = createBTree(i * 2, n);
        p->right = createBTree(i * 2 + 1, n);
        return p;
    }
    return nullptr;
}

void preOrder(TreeNode *p) {
    Stack s;
    stackInit(&s, NUM);

    // while (p) {
    //     while (p) {
    //         cout << p->data << " ";

    //         if (p->right) stackPush(&s, p->right);
    //         p = p->left;
    //     }
    //     if (stackEmpty(&s)) break;
    //     p = s.elem[s.top];
    //     stackPop(&s);
    // }

    while (p || !stackEmpty(&s)) {
        if (p) {
            cout << p->data << " ";
            stackPush(&s, p);
            p = p->left;
        } else {
            p = s.elem[s.top];
            stackPop(&s);
            p = p->right;
        }
    }
    cout << endl;
}

void inOrder(TreeNode *p) {
    Stack s;
    stackInit(&s, NUM);
    while (p || !stackEmpty(&s)) {
        if (p) {
            stackPush(&s, p);
            p = p->left;
        } else {
            p = s.elem[s.top];
            stackPop(&s);
            cout << p->data << " ";
            p = p->right;
        }
    }
    cout << endl;
}

void afterOrder(TreeNode *p) {
    Stack s;
    stackInit(&s, NUM);
    TreeNode *flag = NULL;
    while (p || !stackEmpty(&s)) {
        if (p) {
            stackPush(&s, p);
            p = p->left;
        } else {
            p = s.elem[s.top];
            if (p->right && p->right != flag) {
                p = p->right;
                continue;
            }
            stackPop(&s);
            cout << p->data << " ";
            flag = p;
            p = nullptr;
        }
    }
    cout << endl;
}

int main() {
    TreeNode *tree = createBTree(1, 8);

    preOrder(tree);
    inOrder(tree);
    afterOrder(tree);

    return 0;
}